#include QMK_KEYBOARD_H

/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_J, KC_F, KC_M, KC_P, KC_V, KC_APP, TG(5), KC_HASH, KC_DOT, KC_SLSH, KC_QUOT, KC_DQUO, LCTL_T(KC_R), LALT_T(KC_S), LGUI_T(KC_N), LSFT_T(KC_T), KC_K, LT(5,KC_TAB), LT(5,KC_ESC), KC_COMM, RSFT_T(KC_A), RGUI_T(KC_E), RALT_T(KC_C), RCTL_T(KC_I), KC_X, KC_G, KC_L, KC_D, KC_B, KC_LBRC, KC_RBRC, KC_MINS, KC_U, KC_O, KC_W, KC_Y, KC_LEFT, KC_RGHT, LT(5,KC_BSPC), LT(4,KC_H), LT(2,KC_LANG2), LT(3,KC_MUTE), LT(3,KC_MPLY), LT(6,KC_LANG1), LT(2,KC_SPC), LT(4,KC_ENT), KC_UP, KC_DOWN),
	[1] = LAYOUT(KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, KC_TRNS, KC_TRNS, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS, KC_TRNS, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, LSFT(KC_NUHS), LSFT(KC_NUBS), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY),
	[2] = LAYOUT(KC_Q, KC_Z, LALT(KC_LBRC), A(S(KC_LBRC)), A(S(KC_9)), S(G(KC_4)), KC_TRNS, LALT(KC_4), KC_DLR, A(S(KC_2)), LALT_T(KC_Y), RALT(KC_3), KC_LT, KC_GT, KC_LPRN, KC_RPRN, LALT(KC_8), C(S(G(KC_4))), KC_TRNS, RALT(KC_1), LSFT_T(KC_PAST), RGUI_T(KC_PEQL), RALT_T(KC_PPLS), RCTL_T(KC_RO), A(S(KC_5)), KC_TRNS, KC_LCBR, KC_RPRN, RALT(KC_5), KC_TRNS, KC_TRNS, KC_UNDS, KC_PIPE, KC_AMPR, KC_CIRC, KC_PERC, KC_TRNS, KC_TRNS, SK_DELWDL, SK_DELWDR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT(KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_TRNS, KC_SLSH, KC_7, KC_8, KC_9, KC_0, LCTL_T(KC_F6), LALT_T(KC_F7), LGUI_T(KC_F8), LSFT_T(KC_F9), KC_F10, KC_F17, KC_TRNS, KC_EQL, RSFT_T(KC_4), RGUI_T(KC_5), RALT_T(KC_6), RCTL_T(KC_MINS), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F18, KC_TRNS, KC_MINS, KC_1, KC_2, KC_3, KC_EQL, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_NO, KC_NO, KC_NLCK, KC_SLCK, KC_INS, KC_TRNS, KC_TRNS),
	[4] = LAYOUT(SK_QUIT, SK_CLOZ, SK_SCAP, SK_SCLP, SK_FAGN, KC_VOLU, KC_MRWD, SK_DOCBEG, KC_HOME, KC_UP, KC_PGUP, SK_PARAPRV, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, SK_FIND, KC_VOLD, KC_MFFD, SK_WORDPRV, KC_LEFT, KC_DOWN, KC_RGHT, SK_WORDNXT, SK_UNDO, SK_CUT, SK_COPY, SK_PSTE, SK_PSTM, KC_MPRV, KC_MNXT, SK_DOCEND, KC_END, KC_DOWN, KC_LALT, SK_PARANXT, KC_TRNS, KC_TRNS, SK_DELWDL, SK_DELWDR, KC_TRNS, KC_MUTE, KC_MPLY, SK_ZOOMRST, SK_HISTPRV, SK_HISTNXT, SK_ZOOMOUT, SK_ZOOMIN),
	[5] = LAYOUT(LALT(KC_RBRC), A(S(KC_RBRC)), LALT(KC_LBRC), A(S(KC_LBRC)), A(S(KC_LBRC)), KC_TRNS, KC_TRNS, KC_PSLS, KC_P7, KC_P8, KC_P9, KC_PMNS, KC_LT, KC_GT, KC_LPRN, KC_RPRN, LALT(KC_8), KC_TRNS, KC_NLCK, KC_PAST, KC_P4, KC_P5, KC_P6, KC_PPLS, A(S(KC_5)), A(S(KC_7)), KC_LCBR, KC_RCBR, RALT(KC_5), KC_TRNS, KC_TAB, KC_PCMM, KC_P1, KC_P2, KC_P3, KC_PEQL, KC_TRNS, KC_TRNS, KC_BSPC, KC_DEL, KC_TRNS, KC_ENT, KC_TRNS, KC_C, KC_PEQL, KC_P0, KC_P0, KC_PDOT),
	[6] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RESET, KC_NO, BL_BRTG, RGB_SPI, RGB_SPD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BRIU, BL_STEP, BL_INC, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, TO(1), DF(1), KC_NO, AG_SWAP, CG_SWAP, KC_BRID, BL_TOGG, BL_DEC, RGB_HUD, RGB_SAD, RGB_VAD, TO(0), DF(0), KC_NO, AG_NORM, CG_NORM, KC_NO, KC_NO, KC_NO, BL_ON, BL_OFF, KC_NO, KC_NO)
};