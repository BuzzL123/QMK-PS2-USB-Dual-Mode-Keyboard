// keyboards/bjl/ps2demo/keyboard.c
#include "keyboard.h"
#include "ps2_device.h"
#include "ps2_scancodes.h"
#include "print.h"  // For debug output

// Mode state
static bool usb_mode = true;  // true = USB, false = PS/2

// Typematic repeat state (for PS/2 mode)
static struct {
    uint8_t scancode;       // Current held key scancode
    bool needs_e0;          // Does this key need E0 prefix?
    bool active;            // Is a key being held?
    uint32_t press_time;    // When key was pressed
    uint32_t last_repeat;   // When last repeat was sent
    uint16_t repeat_delay;  // Delay before repeat starts (ms)
    uint16_t repeat_rate;   // Time between repeats (ms)
} typematic = {
    .scancode = 0,
    .needs_e0 = false,
    .active = false,
    .press_time = 0,
    .last_repeat = 0,
    .repeat_delay = 500,    // 500ms delay before repeat (standard)
    .repeat_rate = 33       // ~30 repeats per second (standard)
};

// Structure to hold scancode mapping
typedef struct {
    uint8_t scancode;
    bool needs_e0_prefix;
} ps2_mapping_t;

// Convert QMK keycode to PS/2 scancode
// Returns scancode in lower byte, E0 prefix flag in upper byte (0x0100 = needs E0)
static ps2_mapping_t qmk_to_ps2_scancode(uint16_t keycode) {
    ps2_mapping_t result = {0, false};

    switch (keycode) {
        // Letters
        case KC_A: result.scancode = PS2_A; break;
        case KC_B: result.scancode = PS2_B; break;
        case KC_C: result.scancode = PS2_C; break;
        case KC_D: result.scancode = PS2_D; break;
        case KC_E: result.scancode = PS2_E; break;
        case KC_F: result.scancode = PS2_F; break;
        case KC_G: result.scancode = PS2_G; break;
        case KC_H: result.scancode = PS2_H; break;
        case KC_I: result.scancode = PS2_I; break;
        case KC_J: result.scancode = PS2_J; break;
        case KC_K: result.scancode = PS2_K; break;
        case KC_L: result.scancode = PS2_L; break;
        case KC_M: result.scancode = PS2_M; break;
        case KC_N: result.scancode = PS2_N; break;
        case KC_O: result.scancode = PS2_O; break;
        case KC_P: result.scancode = PS2_P; break;
        case KC_Q: result.scancode = PS2_Q; break;
        case KC_R: result.scancode = PS2_R; break;
        case KC_S: result.scancode = PS2_S; break;
        case KC_T: result.scancode = PS2_T; break;
        case KC_U: result.scancode = PS2_U; break;
        case KC_V: result.scancode = PS2_V; break;
        case KC_W: result.scancode = PS2_W; break;
        case KC_X: result.scancode = PS2_X; break;
        case KC_Y: result.scancode = PS2_Y; break;
        case KC_Z: result.scancode = PS2_Z; break;

        // Numbers
        case KC_1: result.scancode = PS2_1; break;
        case KC_2: result.scancode = PS2_2; break;
        case KC_3: result.scancode = PS2_3; break;
        case KC_4: result.scancode = PS2_4; break;
        case KC_5: result.scancode = PS2_5; break;
        case KC_6: result.scancode = PS2_6; break;
        case KC_7: result.scancode = PS2_7; break;
        case KC_8: result.scancode = PS2_8; break;
        case KC_9: result.scancode = PS2_9; break;
        case KC_0: result.scancode = PS2_0; break;

        // Function keys
        case KC_F1:  result.scancode = PS2_F1; break;
        case KC_F2:  result.scancode = PS2_F2; break;
        case KC_F3:  result.scancode = PS2_F3; break;
        case KC_F4:  result.scancode = PS2_F4; break;
        case KC_F5:  result.scancode = PS2_F5; break;
        case KC_F6:  result.scancode = PS2_F6; break;
        case KC_F7:  result.scancode = PS2_F7; break;
        case KC_F8:  result.scancode = PS2_F8; break;
        case KC_F9:  result.scancode = PS2_F9; break;
        case KC_F10: result.scancode = PS2_F10; break;
        case KC_F11: result.scancode = PS2_F11; break;
        case KC_F12: result.scancode = PS2_F12; break;
        case KC_F13: result.scancode = PS2_F13; break;
        case KC_F14: result.scancode = PS2_F14; break;
        case KC_F15: result.scancode = PS2_F15; break;
        case KC_F16: result.scancode = PS2_F16; break;
        case KC_F17: result.scancode = PS2_F17; break;
        case KC_F18: result.scancode = PS2_F18; break;
        case KC_F19: result.scancode = PS2_F19; break;
        case KC_F20: result.scancode = PS2_F20; break;
        case KC_F21: result.scancode = PS2_F21; break;
        case KC_F22: result.scancode = PS2_F22; break;
        case KC_F23: result.scancode = PS2_F23; break;
        case KC_F24: result.scancode = PS2_F24; break;

        // Special characters
        case KC_GRV:  result.scancode = PS2_GRAVE; break;
        case KC_MINS: result.scancode = PS2_MINUS; break;
        case KC_EQL:  result.scancode = PS2_EQUAL; break;
        case KC_BSLS: result.scancode = PS2_BACKSLASH; break;
        case KC_LBRC: result.scancode = PS2_LBRACKET; break;
        case KC_RBRC: result.scancode = PS2_RBRACKET; break;
        case KC_SCLN: result.scancode = PS2_SEMICOLON; break;
        case KC_QUOT: result.scancode = PS2_QUOTE; break;
        case KC_COMM: result.scancode = PS2_COMMA; break;
        case KC_DOT:  result.scancode = PS2_DOT; break;
        case KC_SLSH: result.scancode = PS2_SLASH; break;

        // Control keys
        case KC_ESC:  result.scancode = PS2_ESC; break;
        case KC_BSPC: result.scancode = PS2_BACKSPACE; break;
        case KC_TAB:  result.scancode = PS2_TAB; break;
        case KC_CAPS: result.scancode = PS2_CAPS; break;
        case KC_LSFT: result.scancode = PS2_LSHIFT; break;
        case KC_LCTL: result.scancode = PS2_LCTRL; break;
        case KC_LALT: result.scancode = PS2_LALT; break;
        case KC_SPC:  result.scancode = PS2_SPACE; break;
        case KC_RALT: result.scancode = PS2_RALT; result.needs_e0_prefix = true; break;
        case KC_RCTL: result.scancode = PS2_RCTRL; result.needs_e0_prefix = true; break;
        case KC_RSFT: result.scancode = PS2_RSHIFT; break;
        case KC_ENT:  result.scancode = PS2_ENTER; break;
        case KC_APP:  result.scancode = PS2_MENU; result.needs_e0_prefix = true; break;

        // Navigation cluster (all need E0)
        case KC_INS:  result.scancode = PS2_INSERT; result.needs_e0_prefix = true; break;
        case KC_HOME: result.scancode = PS2_HOME; result.needs_e0_prefix = true; break;
        case KC_PGUP: result.scancode = PS2_PGUP; result.needs_e0_prefix = true; break;
        case KC_DEL:  result.scancode = PS2_DELETE; result.needs_e0_prefix = true; break;
        case KC_END:  result.scancode = PS2_END; result.needs_e0_prefix = true; break;
        case KC_PGDN: result.scancode = PS2_PGDN; result.needs_e0_prefix = true; break;

        // Arrow keys (all need E0)
        case KC_UP:   result.scancode = PS2_UP; result.needs_e0_prefix = true; break;
        case KC_DOWN: result.scancode = PS2_DOWN; result.needs_e0_prefix = true; break;
        case KC_LEFT: result.scancode = PS2_LEFT; result.needs_e0_prefix = true; break;
        case KC_RGHT: result.scancode = PS2_RIGHT; result.needs_e0_prefix = true; break;

        // Keypad
        case KC_NUM:  result.scancode = PS2_NUMLOCK; break;
        case KC_PSLS: result.scancode = PS2_KP_SLASH; result.needs_e0_prefix = true; break;
        case KC_PAST: result.scancode = PS2_KP_ASTERISK; break;
        case KC_PMNS: result.scancode = PS2_KP_MINUS; break;
        case KC_PPLS: result.scancode = PS2_KP_PLUS; break;
        case KC_PENT: result.scancode = PS2_KP_ENTER; result.needs_e0_prefix = true; break;
        case KC_PDOT: result.scancode = PS2_KP_DOT; break;
        case KC_P0:   result.scancode = PS2_KP_0; break;
        case KC_P1:   result.scancode = PS2_KP_1; break;
        case KC_P2:   result.scancode = PS2_KP_2; break;
        case KC_P3:   result.scancode = PS2_KP_3; break;
        case KC_P4:   result.scancode = PS2_KP_4; break;
        case KC_P5:   result.scancode = PS2_KP_5; break;
        case KC_P6:   result.scancode = PS2_KP_6; break;
        case KC_P7:   result.scancode = PS2_KP_7; break;
        case KC_P8:   result.scancode = PS2_KP_8; break;
        case KC_P9:   result.scancode = PS2_KP_9; break;

        // Lock keys
        case KC_SCRL: result.scancode = PS2_SCROLL; break;
        case KC_PSCR: result.scancode = PS2_PSCREEN; result.needs_e0_prefix = true; break;

        // GUI/Windows keys (need E0)
        case KC_LGUI: result.scancode = PS2_LGUI; result.needs_e0_prefix = true; break;
        case KC_RGUI: result.scancode = PS2_RGUI; result.needs_e0_prefix = true; break;

        // Multimedia keys (need E0)
        case KC_MUTE: result.scancode = PS2_MUTE; result.needs_e0_prefix = true; break;
        case KC_VOLD: result.scancode = PS2_VOLUMEDOWN; result.needs_e0_prefix = true; break;
        case KC_VOLU: result.scancode = PS2_VOLUMEUP; result.needs_e0_prefix = true; break;
        case KC_MNXT: result.scancode = PS2_MEDIA_NEXT; result.needs_e0_prefix = true; break;
        case KC_MPRV: result.scancode = PS2_MEDIA_PREV; result.needs_e0_prefix = true; break;
        case KC_MSTP: result.scancode = PS2_MEDIA_STOP; result.needs_e0_prefix = true; break;
        case KC_MPLY: result.scancode = PS2_MEDIA_PLAY; result.needs_e0_prefix = true; break;
        case KC_MSEL: result.scancode = PS2_MEDIA_SELECT; result.needs_e0_prefix = true; break;

        // Browser keys (need E0)
        case KC_WSCH: result.scancode = PS2_WWW_SEARCH; result.needs_e0_prefix = true; break;
        case KC_WHOM: result.scancode = PS2_WWW_HOME; result.needs_e0_prefix = true; break;
        case KC_WBAK: result.scancode = PS2_WWW_BACK; result.needs_e0_prefix = true; break;
        case KC_WFWD: result.scancode = PS2_WWW_FORWARD; result.needs_e0_prefix = true; break;
        case KC_WSTP: result.scancode = PS2_WWW_STOP; result.needs_e0_prefix = true; break;
        case KC_WREF: result.scancode = PS2_WWW_REFRESH; result.needs_e0_prefix = true; break;
        case KC_WFAV: result.scancode = PS2_WWW_FAVORITES; result.needs_e0_prefix = true; break;

        // Application keys (need E0)
        case KC_MAIL: result.scancode = PS2_APP_MAIL; result.needs_e0_prefix = true; break;
        case KC_CALC: result.scancode = PS2_APP_CALC; result.needs_e0_prefix = true; break;
        case KC_MYCM: result.scancode = PS2_APP_MYCOMP; result.needs_e0_prefix = true; break;

        // ACPI Power keys (need E0)
        case KC_PWR:  result.scancode = PS2_POWER; result.needs_e0_prefix = true; break;
        case KC_SLEP: result.scancode = PS2_SLEEP; result.needs_e0_prefix = true; break;
        case KC_WAKE: result.scancode = PS2_WAKE; result.needs_e0_prefix = true; break;

        // International keys
        case KC_INT1: result.scancode = PS2_INTL1; break;
        case KC_INT2: result.scancode = PS2_INTL2; break;
        case KC_INT3: result.scancode = PS2_INTL3; break;
        case KC_INT4: result.scancode = PS2_INTL4; break;
        case KC_INT5: result.scancode = PS2_INTL5; break;
        case KC_LNG1: result.scancode = PS2_LANG1; break;
        case KC_LNG2: result.scancode = PS2_LANG2; break;

        default:
            // Unknown keycode
            result.scancode = 0;
            break;
    }

    return result;
}

// Helper functions for mode detection
bool is_usb_mode(void) {
    return usb_mode;
}

bool is_ps2_mode(void) {
    return !usb_mode;
}

// Early initialization - before USB or anything else
void keyboard_pre_init_kb(void) {
    // Initialize mode switch pin early
    setPinInputHigh(MODE_SWITCH_PIN);

    keyboard_pre_init_user();
}

// Post initialization - after USB is ready
void keyboard_post_init_kb(void) {
    // Check initial mode state - read multiple times to ensure stability
    usb_mode = readPin(MODE_SWITCH_PIN);
    wait_ms(10);  // Small delay for pin to settle
    usb_mode = readPin(MODE_SWITCH_PIN);

    // Debug output
    uprintf("================================\n");
    uprintf("Mode switch pin (GP14) state: %d\n", usb_mode);
    uprintf("Mode: %s\n", usb_mode ? "USB" : "PS/2");
    uprintf("================================\n");

    if (!usb_mode) {
        // Initialize PS/2 mode if switch is in PS/2 position
        uprintf("[PS2] Initializing PS/2 device...\n");
        ps2_device_init(PS2_CLOCK_PIN, PS2_DATA_PIN);
        uprintf("[PS2] PS/2 device initialized (CLK=GP16, DATA=GP17)\n");
        uprintf("[PS2] Full scancode support enabled\n");
        uprintf("[PS2] Typematic: delay=%dms, rate=%dms\n", typematic.repeat_delay, typematic.repeat_rate);
    } else {
        uprintf("[USB] USB mode selected\n");
    }

    keyboard_post_init_user();
}

// Main task loop - runs continuously
void housekeeping_task_kb(void) {
    // Check if mode switch has changed
    bool new_mode = readPin(MODE_SWITCH_PIN);

    if (new_mode != usb_mode) {
        usb_mode = new_mode;
        uprintf("\n!!! MODE CHANGE DETECTED !!!\n");
        uprintf("Mode switched to: %s\n", usb_mode ? "USB" : "PS/2");

        if (!usb_mode) {
            // Switched to PS/2 mode - initialize PS/2
            uprintf("[PS2] Initializing PS/2 on mode switch...\n");
            ps2_device_init(PS2_CLOCK_PIN, PS2_DATA_PIN);
            uprintf("[PS2] PS/2 reinitialized\n");
        } else {
            uprintf("[USB] Switched to USB mode\n");
            // Clear typematic state when switching to USB
            typematic.active = false;
        }
        uprintf("!!! MODE CHANGE COMPLETE !!!\n\n");
    }

    // Run PS/2 task if in PS/2 mode
    if (!usb_mode) {
        ps2_device_task();

        // Handle typematic repeat
        if (typematic.active) {
            uint32_t now = timer_read32();

            // Check if we should start repeating
            if ((now - typematic.press_time) >= typematic.repeat_delay) {
                // Check if it's time for another repeat
                if ((now - typematic.last_repeat) >= typematic.repeat_rate) {
                    // Send E0 prefix if needed
                    if (typematic.needs_e0) {
                        ps2_device_send_key_make(PS2_PREFIX_E0);
                    }
                    // Send make code again
                    if (ps2_device_send_key_make(typematic.scancode)) {
                        typematic.last_repeat = now;
                        uprintf("[PS2] Typematic repeat: %s0x%02X\n",
                                typematic.needs_e0 ? "E0 " : "", typematic.scancode);
                    }
                }
            }
        }
    }

    housekeeping_task_user();
}

// Process all key presses
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // Debug output
    uprintf("[KEY] keycode=%d, pressed=%d, mode=%s\n",
            keycode, record->event.pressed, usb_mode ? "USB" : "PS/2");

    // Let user keymap process first
    if (!process_record_user(keycode, record)) {
        return false;
    }

    // If in PS/2 mode, send via PS/2 protocol
    if (!usb_mode) {
        uprintf("[PS2] PS/2 mode active - processing key\n");

        // Get PS/2 scancode for this keycode
        ps2_mapping_t mapping = qmk_to_ps2_scancode(keycode);

        if (mapping.scancode == 0) {
            uprintf("[PS2] No PS/2 mapping for keycode %d\n", keycode);
            return false;
        }

        if (record->event.pressed) {
            // Key pressed - send make code
            uprintf("[PS2] Sending PS/2 make: %s0x%02X\n",
                    mapping.needs_e0_prefix ? "E0 " : "", mapping.scancode);

            // Send E0 prefix if needed
            if (mapping.needs_e0_prefix) {
                ps2_device_send_key_make(PS2_PREFIX_E0);
            }

            // Send make code
            bool result = ps2_device_send_key_make(mapping.scancode);
            uprintf("[PS2] Make code queued: %s\n", result ? "success" : "FAILED");

            // Start typematic repeat
            typematic.scancode = mapping.scancode;
            typematic.needs_e0 = mapping.needs_e0_prefix;
            typematic.active = true;
            typematic.press_time = timer_read32();
            typematic.last_repeat = timer_read32();
            uprintf("[PS2] Typematic repeat armed\n");
        } else {
            // Key released - send break code
            uprintf("[PS2] Sending PS/2 break: %s0xF0 0x%02X\n",
                    mapping.needs_e0_prefix ? "E0 " : "", mapping.scancode);

            // Send E0 prefix if needed
            if (mapping.needs_e0_prefix) {
                ps2_device_send_key_make(PS2_PREFIX_E0);
            }

            // Send break code (0xF0 + scancode)
            bool result = ps2_device_send_key_break(mapping.scancode);
            uprintf("[PS2] Break code queued: %s\n", result ? "success" : "FAILED");

            // Stop typematic repeat
            typematic.active = false;
            uprintf("[PS2] Typematic repeat stopped\n");
        }

        return false;  // Don't process through USB stack
    }

    // USB mode - process normally
    uprintf("[USB] USB mode - processing normally\n");
    return true;
}

// LED update callback (USB mode only)
bool led_update_kb(led_t led_state) {
    return led_update_user(led_state);
}

// Matrix scanning override (optional)
void matrix_init_kb(void) {
    matrix_init_user();
}

void matrix_scan_kb(void) {
    matrix_scan_user();
}

// Allow user to configure typematic settings
void ps2_set_typematic_rate(uint16_t delay_ms, uint16_t rate_ms) {
    typematic.repeat_delay = delay_ms;
    typematic.repeat_rate = rate_ms;
    uprintf("[PS2] Typematic updated: delay=%dms, rate=%dms\n", delay_ms, rate_ms);
}
