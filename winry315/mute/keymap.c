// Copyright 2022 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
int MUTE_STATUS = 2; //Init the global MUTE_STATUS variable.  0=unmuted, 1=muted, 2=unset


// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RGB,
};

enum custom_keycodes {
    MIC_SILENT = SAFE_RANGE,
    MIC_ON,
    MIC_CLEAR
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MIC_SILENT:
        if (record->event.pressed) {
            // when keycode MIC_SILENT is pressed
            SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LGUI)SS_TAP(X_G)SS_UP(X_LGUI)SS_UP(X_LCTRL)); //Send the keys for MeetMute
            MUTE_STATUS = 1; //Set the set the var to 'Muted'
        } else {
            // when keycode MIC_SILENT is released
        }
        break;
    case MIC_ON:
       if (record->event.pressed) {
            // when keycode MIC_ON is pressed
            SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LGUI)SS_TAP(X_F)SS_UP(X_LGUI)SS_UP(X_LCTRL)); //Send the keys for MeetMute
            MUTE_STATUS = 0; //Set the var to 'unmuted'
        } else {
            // when keycode MIC_ON is released
        }
        break;
    case MIC_CLEAR:
       if (record->event.pressed) {
            // when keycode MIC_CLEAR is pressed
            MUTE_STATUS = 2; //Set the var to 'unset'
        } else {
            // when keycode MIC_CLEAR is released
        }
        break;
    }
    return true;
};

// Shorter defines for some QMK keycodes (to keep the keymap aligned)
#define U_LTESC LT(_RGB, KC_ESC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base
    [_BASE] = LAYOUT_top(
            KC_BTN3,      KC_MUTE,     KC_MPLY,
        KC_7,    KC_8,    KC_9,    U_LTESC,    MIC_ON,
        KC_4,    KC_5,    KC_6,    KC_MPLY,    MIC_CLEAR,
        KC_1,    KC_2,    KC_3,  KC_0, MIC_SILENT
    ),

    // RGB configuration
    [_RGB] = LAYOUT_top(
            RGB_M_P,      RGB_M_B,     RGB_M_R,
        RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,
        RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, QK_BOOTLOADER,
        KC_TRNS, RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R
    ),
};

//Set Matrix color based on the MUTE_STATUS var 
const uint8_t led_indexes[7] = {0, 18, 19, 20, 22, 25, 26};  //These are the LEDs down the right hand side. 
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (int i=0; i<7; i++) {
        switch(MUTE_STATUS) {
            case 2: //Mute unset, do nothing. 
                break;
            case 1: //Muted.  Set the LEDs to red
                rgb_matrix_set_color(led_indexes[i], RGB_RED);
                break;
            case 0: //Unmuted.  Set the LEDs to green
                rgb_matrix_set_color(led_indexes[i], RGB_GREEN);
            default:
                break;
        }
    }
}

// clang-format on

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    switch (index) {
        case 0:
            // Left encoder
            if (layer == _RGB) {
                if (clockwise) {
                    rgblight_increase_hue_noeeprom();
                } else {
                    rgblight_decrease_hue_noeeprom();
                }
            } else {
                tap_code(clockwise ? KC_WH_D : KC_WH_U);
            }
            break;

        case 1:
            // Center encoder
            if (layer == _RGB) {
                if (clockwise) {
                    rgblight_increase_sat_noeeprom();
                } else {
                    rgblight_decrease_sat_noeeprom();
                }
            } else {
                tap_code_delay(clockwise ? KC_VOLU : KC_VOLD, 10);
            }
            break;

        case 2:
            // Right encoder
            if (layer == _RGB) {
                if (clockwise) {
                    rgblight_increase_val_noeeprom();
                } else {
                    rgblight_decrease_val_noeeprom();
                }
            } else {
                tap_code_delay(clockwise ? KC_MNXT : KC_MPRV, 10);
            }
            break;
    }
    return false;
}
