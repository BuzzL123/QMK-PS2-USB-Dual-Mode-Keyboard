# PS/2 Scan Code Reference

Complete PS/2 Scan Code Set 2 implementation for the dual-mode keyboard.

## Overview

This firmware implements **complete PS/2 Scan Code Set 2 support**, including:
- All standard 104-key layout keys
- Extended function keys (F13-F24)
- Multimedia controls
- Browser navigation
- Application launchers
- Power management
- International keyboard support

## How It Works

### Automatic Mapping

The firmware automatically converts QMK keycodes to PS/2 scancodes. You don't need to write any additional code!

```c
// Just add keys to your keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A, KC_B, KC_MPLY, KC_CALC
    )
};
// That's it! The firmware handles everything.
```

### E0 Prefix Handling

Extended keys (arrows, navigation, multimedia) automatically get the E0 prefix:

```
User presses: KC_UP
Firmware sends: E0 75 (make)
User releases: KC_UP  
Firmware sends: E0 F0 75 (break)
```

## Complete Scancode Table

### Letters (A-Z)

| Key | QMK Code | Scancode | | Key | QMK Code | Scancode |
|-----|----------|----------|---|-----|----------|----------|
| A | KC_A | 0x1C | | N | KC_N | 0x31 |
| B | KC_B | 0x32 | | O | KC_O | 0x44 |
| C | KC_C | 0x21 | | P | KC_P | 0x4D |
| D | KC_D | 0x23 | | Q | KC_Q | 0x15 |
| E | KC_E | 0x24 | | R | KC_R | 0x2D |
| F | KC_F | 0x2B | | S | KC_S | 0x1B |
| G | KC_G | 0x34 | | T | KC_T | 0x2C |
| H | KC_H | 0x33 | | U | KC_U | 0x3C |
| I | KC_I | 0x43 | | V | KC_V | 0x2A |
| J | KC_J | 0x3B | | W | KC_W | 0x1D |
| K | KC_K | 0x42 | | X | KC_X | 0x22 |
| L | KC_L | 0x4B | | Y | KC_Y | 0x35 |
| M | KC_M | 0x3A | | Z | KC_Z | 0x1A |

### Numbers (0-9)

| Key | QMK Code | Scancode |
|-----|----------|----------|
| 1 | KC_1 | 0x16 |
| 2 | KC_2 | 0x1E |
| 3 | KC_3 | 0x26 |
| 4 | KC_4 | 0x25 |
| 5 | KC_5 | 0x2E |
| 6 | KC_6 | 0x36 |
| 7 | KC_7 | 0x3D |
| 8 | KC_8 | 0x3E |
| 9 | KC_9 | 0x46 |
| 0 | KC_0 | 0x45 |

### Function Keys (F1-F24)

| Key | QMK Code | Scancode | | Key | QMK Code | Scancode |
|-----|----------|----------|---|-----|----------|----------|
| F1 | KC_F1 | 0x05 | | F13 | KC_F13 | 0x08 |
| F2 | KC_F2 | 0x06 | | F14 | KC_F14 | 0x10 |
| F3 | KC_F3 | 0x04 | | F15 | KC_F15 | 0x18 |
| F4 | KC_F4 | 0x0C | | F16 | KC_F16 | 0x20 |
| F5 | KC_F5 | 0x03 | | F17 | KC_F17 | 0x28 |
| F6 | KC_F6 | 0x0B | | F18 | KC_F18 | 0x30 |
| F7 | KC_F7 | 0x83 | | F19 | KC_F19 | 0x38 |
| F8 | KC_F8 | 0x0A | | F20 | KC_F20 | 0x40 |
| F9 | KC_F9 | 0x01 | | F21 | KC_F21 | 0x48 |
| F10 | KC_F10 | 0x09 | | F22 | KC_F22 | 0x50 |
| F11 | KC_F11 | 0x78 | | F23 | KC_F23 | 0x57 |
| F12 | KC_F12 | 0x07 | | F24 | KC_F24 | 0x5F |

### Special Characters

| Key | QMK Code | Scancode | Character |
|-----|----------|----------|-----------|
| Grave | KC_GRV | 0x0E | ` ~ |
| Minus | KC_MINS | 0x4E | - _ |
| Equal | KC_EQL | 0x55 | = + |
| Backslash | KC_BSLS | 0x5D | \ \| |
| Left Bracket | KC_LBRC | 0x54 | [ { |
| Right Bracket | KC_RBRC | 0x5B | ] } |
| Semicolon | KC_SCLN | 0x4C | ; : |
| Quote | KC_QUOT | 0x52 | ' " |
| Comma | KC_COMM | 0x41 | , < |
| Dot | KC_DOT | 0x49 | . > |
| Slash | KC_SLSH | 0x4A | / ? |

### Control Keys

| Key | QMK Code | Scancode | E0? |
|-----|----------|----------|-----|
| Escape | KC_ESC | 0x76 | No |
| Backspace | KC_BSPC | 0x66 | No |
| Tab | KC_TAB | 0x0D | No |
| Caps Lock | KC_CAPS | 0x58 | No |
| Left Shift | KC_LSFT | 0x12 | No |
| Left Ctrl | KC_LCTL | 0x14 | No |
| Left Alt | KC_LALT | 0x11 | No |
| Space | KC_SPC | 0x29 | No |
| Right Alt | KC_RALT | 0x11 | **Yes** |
| Right Ctrl | KC_RCTL | 0x14 | **Yes** |
| Right Shift | KC_RSFT | 0x59 | No |
| Enter | KC_ENT | 0x5A | No |
| Menu | KC_APP | 0x2F | **Yes** |

### Navigation Cluster

All navigation keys require E0 prefix.

| Key | QMK Code | Scancode | E0? |
|-----|----------|----------|-----|
| Insert | KC_INS | 0x70 | **Yes** |
| Home | KC_HOME | 0x6C | **Yes** |
| Page Up | KC_PGUP | 0x7D | **Yes** |
| Delete | KC_DEL | 0x71 | **Yes** |
| End | KC_END | 0x69 | **Yes** |
| Page Down | KC_PGDN | 0x7A | **Yes** |

### Arrow Keys

All arrow keys require E0 prefix.

| Key | QMK Code | Scancode | E0? |
|-----|----------|----------|-----|
| Up | KC_UP | 0x75 | **Yes** |
| Down | KC_DOWN | 0x72 | **Yes** |
| Left | KC_LEFT | 0x6B | **Yes** |
| Right | KC_RGHT | 0x74 | **Yes** |

### Numeric Keypad

| Key | QMK Code | Scancode | E0? |
|-----|----------|----------|-----|
| Num Lock | KC_NUM | 0x77 | No |
| KP / | KC_PSLS | 0x4A | **Yes** |
| KP * | KC_PAST | 0x7C | No |
| KP - | KC_PMNS | 0x7B | No |
| KP + | KC_PPLS | 0x79 | No |
| KP Enter | KC_PENT | 0x5A | **Yes** |
| KP . | KC_PDOT | 0x71 | No |
| KP 0 | KC_P0 | 0x70 | No |
| KP 1 | KC_P1 | 0x69 | No |
| KP 2 | KC_P2 | 0x72 | No |
| KP 3 | KC_P3 | 0x7A | No |
| KP 4 | KC_P4 | 0x6B | No |
| KP 5 | KC_P5 | 0x73 | No |
| KP 6 | KC_P6 | 0x74 | No |
| KP 7 | KC_P7 | 0x6C | No |
| KP 8 | KC_P8 | 0x75 | No |
| KP 9 | KC_P9 | 0x7D | No |

### Lock Keys

| Key | QMK Code | Scancode |
|-----|----------|----------|
| Caps Lock | KC_CAPS | 0x58 |
| Num Lock | KC_NUM | 0x77 |
| Scroll Lock | KC_SCRL | 0x7E |

### Multimedia Keys

All multimedia keys require E0 prefix.

| Key | QMK Code | Scancode | E0? |
|-----|----------|----------|-----|
| Mute | KC_MUTE | 0x23 | **Yes** |
| Volume Down | KC_VOLD | 0x21 | **Yes** |
| Volume Up | KC_VOLU | 0x32 | **Yes** |
| Next Track | KC_MNXT | 0x4D | **Yes** |
| Previous Track | KC_MPRV | 0x15 | **Yes** |
| Stop | KC_MSTP | 0x3B | **Yes** |
| Play/Pause | KC_MPLY | 0x34 | **Yes** |
| Media Select | KC_MSEL | 0x50 | **Yes** |

### Browser Controls

All browser keys require E0 prefix.

| Key | QMK Code | Scancode | E0? |
|-----|----------|----------|-----|
| WWW Search | KC_WSCH | 0x10 | **Yes** |
| WWW Home | KC_WHOM | 0x3A | **Yes** |
| WWW Back | KC_WBAK | 0x38 | **Yes** |
| WWW Forward | KC_WFWD | 0x30 | **Yes** |
| WWW Stop | KC_WSTP | 0x28 | **Yes** |
| WWW Refresh | KC_WREF | 0x20 | **Yes** |
| WWW Favorites | KC_WFAV | 0x18 | **Yes** |

### Application Launchers

All application keys require E0 prefix.

| Key | QMK Code | Scancode | E0? |
|-----|----------|----------|-----|
| Mail | KC_MAIL | 0x48 | **Yes** |
| Calculator | KC_CALC | 0x2B | **Yes** |
| My Computer | KC_MYCM | 0x40 | **Yes** |

### System/Power Keys

All power keys require E0 prefix.

| Key | QMK Code | Scancode | E0? |
|-----|----------|----------|-----|
| Power | KC_PWR | 0x37 | **Yes** |
| Sleep | KC_SLEP | 0x3F | **Yes** |
| Wake | KC_WAKE | 0x5E | **Yes** |

### Windows/GUI Keys

All GUI keys require E0 prefix.

| Key | QMK Code | Scancode | E0? |
|-----|----------|----------|-----|
| Left GUI/Win | KC_LGUI | 0x1F | **Yes** |
| Right GUI/Win | KC_RGUI | 0x27 | **Yes** |

### International Keys

| Key | QMK Code | Scancode | Description |
|-----|----------|----------|-------------|
| INT1 | KC_INT1 | 0x51 | Ro (Japanese) |
| INT2 | KC_INT2 | 0x13 | Katakana/Hiragana |
| INT3 | KC_INT3 | 0x6A | Yen |
| INT4 | KC_INT4 | 0x64 | Henkan |
| INT5 | KC_INT5 | 0x67 | Muhenkan |
| LANG1 | KC_LNG1 | 0xF2 | Hangul/English |
| LANG2 | KC_LNG2 | 0xF1 | Hanja |

## Understanding E0 Prefix

### What is E0?

The E0 prefix (0xE0) is a special byte that indicates an "extended" scancode. It's used for:
- Navigation keys (Insert, Delete, Home, End, etc.)
- Arrow keys
- Right Alt and Right Ctrl (to distinguish from left)
- Multimedia and browser keys
- Power management keys

### How It Works

When you press a key that needs E0 prefix:

```
Make sequence:  E0 [scancode]
Break sequence: E0 F0 [scancode]
```

Example - Pressing Up Arrow:
```
Press:   E0 75
Release: E0 F0 75
```

The firmware handles this automatically - you never need to manually send E0!

## Typematic Repeat

All keys support typematic repeat (auto-repeat when held):
- **Initial delay**: 500ms
- **Repeat rate**: 33ms (~30 repeats per second)
- **Works with E0 keys**: E0 prefix is automatically repeated

## Usage Examples

### Basic Keyboard

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x12(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT
    )
};
```

### Multimedia Keyboard

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_1x8(
        KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_CALC, KC_MAIL
    )
};
```

### Gaming Macro Pad

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        KC_F13,  KC_F14,  KC_F15,   // Custom macros
        KC_F16,  KC_F17,  KC_F18,
        KC_F19,  KC_F20,  KC_F21
    )
};
```

## Adding New Keycodes

If you need a keycode not yet mapped:

1. Add the scancode definition to `ps2_scancodes.h`:
```c
#define PS2_MYKEY    0x??  // Your scancode
```

2. Add the mapping to `keyboard.c`:
```c
case KC_MYKEY:
    result.scancode = PS2_MYKEY;
    result.needs_e0_prefix = false;  // or true if needed
    break;
```

3. Use it in your keymap!

## References

- [PS/2 Keyboard Protocol](https://www.avrfreaks.net/sites/default/files/PS2%20Keyboard.pdf)
- [Scan Code Set 2 Reference](https://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/scancode.doc)
- [QMK Keycodes](https://docs.qmk.fm/#/keycodes)

---

**Note**: This implementation covers all standard PS/2 Scan Code Set 2 keys. Print Screen and Pause/Break require special multi-byte sequences and are not yet implemented.
