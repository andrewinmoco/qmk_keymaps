#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KC_ESCAPE, LSFT(KC_TAB), RGB_TOG,
               KC_F4, KC_TAB, KC_LALT,
               LGUI(KC_D), KC_NO, KC_ENTER),

};
