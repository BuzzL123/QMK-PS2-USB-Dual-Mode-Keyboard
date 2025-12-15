// keyboards/bjl/ps2demo/ps2_scancodes.h
// PS/2 Scan Code Set 2 - Complete mapping table
#ifndef PS2_SCANCODES_H
#define PS2_SCANCODES_H

#include <stdint.h>

// PS/2 Scan Code Set 2 - Standard Keys
// Make codes only (break = 0xF0 + make code)
#define PS2_A           0x1C
#define PS2_B           0x32
#define PS2_C           0x21
#define PS2_D           0x23
#define PS2_E           0x24
#define PS2_F           0x2B
#define PS2_G           0x34
#define PS2_H           0x33
#define PS2_I           0x43
#define PS2_J           0x3B
#define PS2_K           0x42
#define PS2_L           0x4B
#define PS2_M           0x3A
#define PS2_N           0x31
#define PS2_O           0x44
#define PS2_P           0x4D
#define PS2_Q           0x15
#define PS2_R           0x2D
#define PS2_S           0x1B
#define PS2_T           0x2C
#define PS2_U           0x3C
#define PS2_V           0x2A
#define PS2_W           0x1D
#define PS2_X           0x22
#define PS2_Y           0x35
#define PS2_Z           0x1A

// Numbers
#define PS2_1           0x16
#define PS2_2           0x1E
#define PS2_3           0x26
#define PS2_4           0x25
#define PS2_5           0x2E
#define PS2_6           0x36
#define PS2_7           0x3D
#define PS2_8           0x3E
#define PS2_9           0x46
#define PS2_0           0x45

// Function keys
#define PS2_F1          0x05
#define PS2_F2          0x06
#define PS2_F3          0x04
#define PS2_F4          0x0C
#define PS2_F5          0x03
#define PS2_F6          0x0B
#define PS2_F7          0x83
#define PS2_F8          0x0A
#define PS2_F9          0x01
#define PS2_F10         0x09
#define PS2_F11         0x78
#define PS2_F12         0x07
#define PS2_F13         0x08  // Shift+F1 (some keyboards)
#define PS2_F14         0x10  // Shift+F2
#define PS2_F15         0x18  // Shift+F3
#define PS2_F16         0x20  // Shift+F4
#define PS2_F17         0x28  // Shift+F5
#define PS2_F18         0x30  // Shift+F6
#define PS2_F19         0x38  // Shift+F7
#define PS2_F20         0x40  // Shift+F8
#define PS2_F21         0x48  // Shift+F9
#define PS2_F22         0x50  // Shift+F10
#define PS2_F23         0x57  // Shift+F11
#define PS2_F24         0x5F  // Shift+F12

// Special characters
#define PS2_GRAVE       0x0E  // ` ~
#define PS2_MINUS       0x4E  // - _
#define PS2_EQUAL       0x55  // = +
#define PS2_BACKSLASH   0x5D  // \ |
#define PS2_LBRACKET    0x54  // [ {
#define PS2_RBRACKET    0x5B  // ] }
#define PS2_SEMICOLON   0x4C  // ; :
#define PS2_QUOTE       0x52  // ' "
#define PS2_COMMA       0x41  // , <
#define PS2_DOT         0x49  // . >
#define PS2_SLASH       0x4A  // / ?

// Control keys
#define PS2_ESC         0x76
#define PS2_BACKSPACE   0x66
#define PS2_TAB         0x0D
#define PS2_CAPS        0x58
#define PS2_LSHIFT      0x12
#define PS2_LCTRL       0x14
#define PS2_LALT        0x11
#define PS2_SPACE       0x29
#define PS2_RALT        0x11  // E0 prefix required
#define PS2_RCTRL       0x14  // E0 prefix required
#define PS2_RSHIFT      0x59
#define PS2_ENTER       0x5A
#define PS2_MENU        0x2F  // E0 prefix required

// Navigation cluster
#define PS2_INSERT      0x70  // E0 prefix required
#define PS2_HOME        0x6C  // E0 prefix required
#define PS2_PGUP        0x7D  // E0 prefix required
#define PS2_DELETE      0x71  // E0 prefix required
#define PS2_END         0x69  // E0 prefix required
#define PS2_PGDN        0x7A  // E0 prefix required

// Arrow keys (all require E0 prefix)
#define PS2_UP          0x75
#define PS2_DOWN        0x72
#define PS2_LEFT        0x6B
#define PS2_RIGHT       0x74

// Keypad
#define PS2_NUMLOCK     0x77
#define PS2_KP_SLASH    0x4A  // E0 prefix required
#define PS2_KP_ASTERISK 0x7C
#define PS2_KP_MINUS    0x7B
#define PS2_KP_PLUS     0x79
#define PS2_KP_ENTER    0x5A  // E0 prefix required
#define PS2_KP_DOT      0x71
#define PS2_KP_0        0x70
#define PS2_KP_1        0x69
#define PS2_KP_2        0x72
#define PS2_KP_3        0x7A
#define PS2_KP_4        0x6B
#define PS2_KP_5        0x73
#define PS2_KP_6        0x74
#define PS2_KP_7        0x6C
#define PS2_KP_8        0x75
#define PS2_KP_9        0x7D

// Lock keys
#define PS2_SCROLL      0x7E

// Print Screen (special: E0,12,E0,7C for make)
#define PS2_PSCREEN     0x7C  // Requires special handling

// Pause/Break (special: E1,14,77,E1,F0,14,F0,77)
#define PS2_PAUSE       0x77  // Requires special handling

// Windows/GUI keys (E0 prefix required)
#define PS2_LGUI        0x1F
#define PS2_RGUI        0x27

// Multimedia keys (E0 prefix required for most)
#define PS2_MUTE        0x23  // E0 prefix
#define PS2_VOLUMEDOWN  0x21  // E0 prefix
#define PS2_VOLUMEUP    0x32  // E0 prefix
#define PS2_MEDIA_NEXT  0x4D  // E0 prefix
#define PS2_MEDIA_PREV  0x15  // E0 prefix
#define PS2_MEDIA_STOP  0x3B  // E0 prefix
#define PS2_MEDIA_PLAY  0x34  // E0 prefix (Play/Pause)
#define PS2_MEDIA_SELECT 0x50 // E0 prefix

// Browser keys (E0 prefix required)
#define PS2_WWW_SEARCH  0x10  // E0 prefix
#define PS2_WWW_HOME    0x3A  // E0 prefix
#define PS2_WWW_BACK    0x38  // E0 prefix
#define PS2_WWW_FORWARD 0x30  // E0 prefix
#define PS2_WWW_STOP    0x28  // E0 prefix
#define PS2_WWW_REFRESH 0x20  // E0 prefix
#define PS2_WWW_FAVORITES 0x18 // E0 prefix

// Application keys (E0 prefix required)
#define PS2_APP_MAIL    0x48  // E0 prefix
#define PS2_APP_CALC    0x2B  // E0 prefix
#define PS2_APP_MYCOMP  0x40  // E0 prefix

// ACPI Power keys (E0 prefix required)
#define PS2_POWER       0x37  // E0 prefix
#define PS2_SLEEP       0x3F  // E0 prefix
#define PS2_WAKE        0x5E  // E0 prefix

// Additional special keys
#define PS2_INTL1       0x51  // International 1 (Ro/Backslash on Japanese)
#define PS2_INTL2       0x13  // International 2 (Katakana/Hiragana)
#define PS2_INTL3       0x6A  // International 3 (Yen)
#define PS2_INTL4       0x64  // International 4 (Henkan)
#define PS2_INTL5       0x67  // International 5 (Muhenkan)
#define PS2_LANG1       0xF2  // Language 1 (Hangul/English on Korean)
#define PS2_LANG2       0xF1  // Language 2 (Hanja on Korean)

// Special prefix codes
#define PS2_PREFIX_E0   0xE0
#define PS2_PREFIX_E1   0xE1
#define PS2_PREFIX_F0   0xF0  // Break code prefix

#endif // PS2_SCANCODES_H
