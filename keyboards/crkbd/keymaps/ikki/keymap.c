/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// タップダンスの宣言
enum {
    TD_LGUI_RALT,
    TD_RALT_LGUI
};

// タップダンスの定義
tap_dance_action_t tap_dance_actions[] = {
    // 1回タップすると Win/Cmd キー、2回タップすると Alt/Option キー。
    [TD_LGUI_RALT]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_RALT),
    // 1回タップすると Alt/Option キー、2回タップすると Win/Cmd キー。
    [TD_RALT_LGUI]  = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_LGUI),
};


// TAPPING_TERM_PER_KEY設定
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_LGUI_RALT):
            return TAPPING_TERM_LONG;
        case TD(TD_RALT_LGUI):
            return TAPPING_TERM_LONG;
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MT(MOD_LCTL,KC_TAB),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  MT(MOD_LSFT,KC_INT1),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        TD(TD_LGUI_RALT),   LT(1,KC_LNG2),  LT(2,KC_SPC),                       LT(1,KC_ENT),   LT(2,KC_LNG1), TD(TD_RALT_LGUI)
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_LNG2,  S(KC_1),  S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),                S(KC_6), S(KC_7), S(KC_8), S(KC_9), KC_LBRC, KC_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_INT3,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO,   KC_NO,   KC_RBRC, KC_BSLS, KC_NO, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        TD(TD_LGUI_RALT),    KC_TRNS,  KC_SPC,                                  KC_ENT,   KC_TRNS, TD(TD_RALT_LGUI)
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_LNG1, KC_F6,   KC_F7, KC_F8,  KC_F9, KC_F10,                            KC_PGDN, KC_PGUP, KC_BSPC, KC_DEL, KC_PSCR, KC_INS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                KC_LEFT,  KC_DOWN, KC_UP, KC_RGHT, KC_APP,  KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                           KC_VOLD, KC_VOLU, KC_HOME, KC_END, KC_MUTE, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        TD(TD_LGUI_RALT),   KC_TRNS,  KC_SPC,                                    KC_ENT, KC_TRNS, TD(TD_RALT_LGUI)
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};
