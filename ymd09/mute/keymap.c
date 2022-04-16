#include QMK_KEYBOARD_H

enum custom_keycodes {
    MIC_SILENT = SAFE_RANGE,
    MIC_ON,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MIC_SILENT:
        if (record->event.pressed) {
            // when keycode MIC_SILENT is pressed
            SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LGUI)SS_TAP(X_G)SS_UP(X_LGUI)SS_UP(X_LCTRL));
	    rgblight_setrgb (0x7F,  0x00, 0x00);
        } else {
            // when keycode MIC_SILENT is released
        }
        break;
    case MIC_ON:
       if (record->event.pressed) {
            // when keycode MIC_ON is pressed
            SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LGUI)SS_TAP(X_F)SS_UP(X_LGUI)SS_UP(X_LCTRL));
            rgblight_setrgb (0x00,  0x7F, 0x00);
        } else {
            // when keycode MIC_ON is released
        }
        break;
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KC_VOLD, KC_MUTE, KC_VOLU,
               KC_MRWD, KC_MPLY, KC_MFFD,
               MIC_SILENT, LT(1, KC_KP_2), MIC_ON),

  [1] = LAYOUT(RGB_RMOD, RGB_VAI, RGB_MOD,
               RGB_HUI, RGB_VAD, RGB_SAI,
               RGB_HUD, KC_TRNS, RGB_SAD),

};
