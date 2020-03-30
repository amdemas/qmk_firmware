#include QMK_KEYBOARD_H
#include "lib/lib8tion/lib8tion.h"

extern uint8_t is_master;
extern led_config_t g_led_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  UC_FLIP,
  UC_TABL,
  UC_SHRG,
  UC_DISA,
  UC_FLIA
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ADJUST ADJUST
#define KC_RST   RESET
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_EEP   EEPROM_RESET
#define KC_CTAB  LCTL_T(KC_TAB)
#define KC_CZ LCTL_T(KC_Z)
#define KC_AA ALT_T(KC_A)
#define KC_AS RALT_T(KC_SCLN)
#define KC_CS RCTL_T(KC_SLSH)
#define KC_SA ALT_T(KC_SCLN)
#define KC_RS LT(_RAISE, KC_SPC)
#define KC_LR LT(_LOWER, KC_ENT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       CTAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       GESC,    AA,     S,     D,     F,     G,                      H,     J,     K,     L,    AS,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LGUI,    CZ,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,    CS,  LGUI,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   CAPS,  LSFT,    LR,       RS,  RSFT,   DEL \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,    F1,    F2,    F3,    F4,    F5,                   LEFT,  DOWN,    UP, RIGHT, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,    F6,    F7,    F8,    F9,   F10,                    F11,   F12, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, LOWER,    RAISE, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  UNDS,  PLUS,   EQL,  PIPE,  MINS,                   MUTE,  VOLD,  VOLU,  MNXT, XXXXX,   GRV,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  BSLS,  LABK,  LCBR,  LPRN,  LBRC,                   RBRC,  RPRN,  RCBR,  RABK,  SLSH, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, LOWER,    RAISE, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,------------------------------------------.
        RST, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,   RST,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+-------|
        EEP,  LHUI,  LSAI,  LVAI,  LTOG, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,   EEP,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+-------|
      XXXXX,  LMOD,  LHUD,  LSAD,  LVAD, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+-------|
                                  _____, _____, LOWER,    RAISE, _____, _____ \
                              //`--------------------'  `--------------------'
  )
};

static char keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};
static uint16_t log_timer= 0;
uint16_t oled_timer;

static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};


#ifdef TAPPING_TERM
uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case ALT_T(KC_Z):
            return TAPPING_TERM + 100;
        default:
            return TAPPING_TERM;
    }
}
#endif

#ifdef RGB_MATRIX_ENABLE
bool has_initialized;

void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_config.hsv.v) {
        hsv.v = rgb_matrix_config.hsv.v;
    }

    switch (mode) {
        case 1:  // breathing
        {
            uint16_t time = scale16by8(g_rgb_counters.tick, speed / 8);
            hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb       = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
        default:  // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
    }
}

void suspend_power_down_user(void) { rgb_matrix_set_suspend_state(true); }

void suspend_wakeup_init_user(void) { rgb_matrix_set_suspend_state(false); }

void rgb_matrix_indicators_user(void) {
    switch (biton32(layer_state)) {
        case _RAISE:
            rgb_matrix_layer_helper(HSV_BLUE, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
            break;
        case _LOWER:
            rgb_matrix_layer_helper(HSV_GREEN, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
            break;
        case _ADJUST:
            rgb_matrix_layer_helper(HSV_RED, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
            break;
        default:
            break;
    }
}

void matrix_scan_rgb(void) {
    if (has_initialized) {
        rgb_matrix_layer_helper(HSV_CYAN, 0, rgb_matrix_config.speed, LED_FLAG_KEYLIGHT);
        rgb_matrix_layer_helper(HSV_CYAN, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
        rgb_matrix_layer_helper(HSV_CYAN, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
    }
}
#endif


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_master)
    return OLED_ROTATION_270;
  return rotation;
}

void render_crkbd_logo_only(void) {
    static const char PROGMEM crkbd_logo[] = {
      0x81, 0x82, 0x83, 0x84, 0x85,
      0xa1, 0xa2, 0xa3, 0xa4, 0xa5,
      0xc1, 0xc2, 0xc3, 0xc4, 0xc5,
      0};
    oled_write_P(crkbd_logo, false);
}

void render_status_main(void) {
    render_crkbd_logo_only();
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Lower"), layer_state_is(_LOWER) && !layer_state_is(_ADJUST));
    oled_write_P(PSTR("Raise"), layer_state_is(_RAISE) && !layer_state_is(_ADJUST));
    oled_write_P(PSTR("Adjst"), layer_state_is(_ADJUST));
    uint8_t modifiers = get_mods() | get_oneshot_mods();
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
    oled_write_ln_P(PSTR("     "), false);
    oled_write(keylog_str, false);
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};
    oled_write_P(crkbd_logo, false);
}

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    for (uint8_t i = 4; i > 0; --i) {
        keylog_str[i] = keylog_str[i - 1];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
    }

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

void oled_task_user(void) {
    if (timer_elapsed(oled_timer) > 30000) {
        oled_off();
        rgb_matrix_disable_noeeprom();
        return;
    } else {
        oled_on();
        rgb_matrix_enable_noeeprom();
    }
    update_log();
    if (is_master) {
        render_status_main();
    } else {
        render_crkbd_logo();
    }
}
#endif

void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode);
        oled_timer = timer_read();
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_timer = timer_read();
        add_keylog(keycode);
    }
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
        case KC_EEP:
            break;
        // case UC_FLIP:  // (ノಠ痊ಠ)ノ彡┻━┻
        //     if (record->event.pressed) {
        //         send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
        //     }
        //     break;
        // case UC_DISA:  // ಠ_ಠ
        //     if (record->event.pressed) {
        //         send_unicode_hex_string("0CA0 005F 0CA0");
        //     }
        //     break;
    }
    return true;
}

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    layer_state_set_user(layer_state);
    uint16_t old_hue = 128; // CYAN Hue
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    for (uint16_t i = 255; i > 0; i--) {
        rgblight_sethsv_noeeprom((i + old_hue) % 255, 255, 255);
        matrix_scan();
        wait_ms(10);
    }
#endif
}
