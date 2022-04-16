/* Copyright 2021 Craig Gardner
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H

#define _MAIN 0

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_PURPLE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif


bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    switch(biton32(layer_state)){
      case 0:
        if (clockwise) {
          tap_code(KC_MS_WH_DOWN);
        } else {
          tap_code(KC_MS_WH_UP);
        }
        break;

      case 1:
        if (clockwise){
            rgblight_increase_hue();
        } else{
            rgblight_step();
        }
        break;

    }
  }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //button closest to USB is first
  [0] = LAYOUT(
     KC_MS_BTN3, LT(1, KC_MUTE), KC_VOLU, KC_VOLD, LCTL(KC_1)
  ),
  [1] = LAYOUT(
     KC_MS_BTN3, KC_TRNS, RGB_TOG, RGB_HUD, RGB_RMOD
  ), 
};
