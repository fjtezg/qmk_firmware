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

// タップダンスの全state宣言
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// タップダンスの宣言
enum {
    TD_LGUI_LALT
};



// 現在のタップダンスの状態を決定します
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (!state->pressed) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;
    }
    else return TD_UNKNOWN;
}

// この例のタップダンスキーに関連付けられた "tap" 構造体を初期化します
static td_tap_t lgui_lalt_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};


// タップダンスキーの動作をコントロールする関数
void lgui_lalt_finished(tap_dance_state_t *state, void *user_data) {
    lgui_lalt_tap_state.state = cur_dance(state);
    switch (lgui_lalt_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_LALT);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LALT);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_LGUI);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LGUI);
            break;
        default: break;
    }
}

void lgui_lalt_reset(tap_dance_state_t *state, void *user_data) {
    // キーを押し続けていて今離したら、レイヤーをオフに切り替えます。
    switch (lgui_lalt_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_LALT);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LGUI);
            break;
        default: break;

    }
    lgui_lalt_tap_state.state = TD_NONE;
}

// タップダンスの定義
tap_dance_action_t tap_dance_actions[] = {
    // 1回タップすると ALTキー、2回タップすると Win/Cmd キー。
    [TD_LGUI_LALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lgui_lalt_finished, lgui_lalt_reset)
};


// //HOLD_ON_OTHER_KEY_PRESS_PER_KEY設定
// bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case LT(1,KC_LNG2):
//         case LT(2,KC_LNG1):
//             // Do not select the hold action when another key is pressed.
//             return false;
//         default:
//             // Immediately select the hold action when another key is pressed.
//             return true;
//     }
// }

// TAPPING_TERM_PER_KEY設定
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case MT(MOD_LALT,KC_SPC):
        // case MT(MOD_LALT,KC_ENT):
        //     return -1;  //ALTはRETRO_TAPが効かないので、TAPPING_TERMを無制限にしてHOLD_ON_OTHER_KEY_PRESSでALTを使用する
        case TD(TD_LGUI_LALT):
            return TAPPING_TERM_LONG;   //タップダンスはTAPPING_TERMを長めに取る
        default:
            return TAPPING_TERM;
    }
}

enum combos {
  JK_LNG1,
  DF_LNG2,
  PMINS_BS,
  QW_F2,
  RT_F5,
  MINSQUOT_DEL,
  CMB_ENT
};

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM pmins_combo[] = {KC_P, KC_MINS, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM rt_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM minsquot_combo[] = {KC_MINS, KC_QUOT, COMBO_END};
const uint16_t PROGMEM ent_combo[] = {KC_SLSH, MT(MOD_LSFT,KC_INT1), COMBO_END};




combo_t key_combos[] = {
  [JK_LNG1] = COMBO(jk_combo, KC_LNG1),
  [DF_LNG2] = COMBO(df_combo, KC_LNG2),
  [PMINS_BS] = COMBO(pmins_combo, KC_BSPC),
  [QW_F2] = COMBO(qw_combo, KC_F2),
  [RT_F5] = COMBO(rt_combo, KC_F5),
  [MINSQUOT_DEL] = COMBO(minsquot_combo, KC_DEL),
  [CMB_ENT] = COMBO(ent_combo, KC_ENT)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MT(MOD_LCTL,KC_TAB),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  MT(MOD_LSFT,KC_INT1),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        TD(TD_LGUI_LALT),   MO(1),  KC_SPC,                                     KC_ENT,   MO(2), MO(1)
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_LNG2,  S(KC_1),  S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),                S(KC_6), S(KC_7), S(KC_8), S(KC_9), KC_LBRC, KC_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_INT3,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                XXXXXXX,   XXXXXXX,   KC_RBRC, KC_BSLS, XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI,    KC_TRNS,  KC_SPC,                                             KC_ENT,   KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_LNG1, KC_F6,   KC_F7, KC_F8,  KC_F9, KC_F10,                            KC_PGDN, KC_PGUP, KC_BSPC, KC_DEL, KC_PSCR, KC_INS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                KC_LEFT,  KC_DOWN, KC_UP, KC_RGHT, KC_APP,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                           KC_VOLD, KC_VOLU, KC_HOME, KC_END, KC_MUTE, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI,   KC_TRNS,  KC_SPC,                                    KC_ENT, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_LNG2,  S(KC_1),  S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),                S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_LBRC), S(KC_EQL),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,   XXXXXXX, S(KC_INT3),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,                        XXXXXXX,   XXXXXXX,   S(KC_RBRC), S(KC_BSLS), XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI,   KC_TRNS,  KC_SPC,                                    KC_ENT, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  )
};
