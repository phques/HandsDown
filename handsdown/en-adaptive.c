/*
 Adaptive Keys
 Called from early within process_record_user

 Tailored for Enthium (en)

 NOTE: assumed dual-function keys (MOD_TAP, LAYER_TAP) have already been handled AND
    FILTERED OUT! The combos handler will have already taken out combo candidates,
    which have a shorter keydown threshhold (COMBO_TERM).

 */
//    Base (alpha) Layer Enthium (HRMs /+ thumb mods)
//       Define SWAP_QB to swap Q and B
//            ╭─────────────────────╮                 ╭─────────────────────╮
//    ESC     │  Q/b Y   O   U   =  │ L_CFG     L_NUM │   X   L   D   P   Z │ LANG2/henk
//     B/q    │  C   I   A   E   -  | (             ) |   K   H   T   N   S │ W
//    tab     │  '   ,   .   ;   /  │ [ copy   pste ] │   J   M   G   F   V │
//            ╰───────────╮ spc bsp │ &             | │  ret  R  ╭──────────╯
//          left rght app ╰─────────╯                 ╰──────────╯ tgLN  up  dn
//
// For small boards, Q (LT3) & Z (LT4) are (also) on the sym layer
// and accessible combos (defined below)

#include "adaptive.h"
#include "keycodes.h"
bool process_adaptive_key(uint16_t keycode, const keyrecord_t *record) {
    bool return_state = true; // assume we don't do anything.

    // Are we in an adaptive context? (adaptive on is assumed).
    if (timer_elapsed(prior_keydown) > ADAPTIVE_TERM) { // outside adaptive threshhold
        prior_keycode = preprior_keycode = prior_keydown = 0; // turn off Adaptives.
        return true; // no adaptive conditions, so return.
    }

    // K, this could be adaptive, so process.
    saved_mods = get_mods();

    if (!caps_word_timer) { // turn off shift, (first-words & Proper nouns)
        unregister_mods(MOD_MASK_SHIFT);  //CAPS_WORD/LOCK won't be affected.
    } // may want more granular control than this…

//        switch (((keycode >= SAFE_RANGE) && (keycode <= SemKeys_COUNT)) ? (keycode) : (keycode & QK_BASIC_MAX)) { // only handling normal, SHFT or ALT cases.

    // ##PQ, these are mostly from Promethium, (adapted for small diffs, for e.g. W is now F)

    switch (keycode) { // process ignoring multi-function keys & shift state?


/*
  Left hand adaptives
*/

        case KC_C: // PQ, yq used for y,
            switch (prior_keycode) {
                case KC_Y: // YC = YI, avoid sfb
                    //tap_code(KC_BSPC);
                    tap_code(KC_I);
                    return_state = false; // done.
            }
            break;

// PM doesn't use the common vowel block, so…
//#include "adapt_h.c" // the common vowel block adaptives (esp. for AU SFB)

        case KC_E:
            switch (prior_keycode) {
                case KC_A: // "AE" yields "AU" (8x more common) keeping it on home row
                    tap_code(KC_U);
                    return_state = false; // done.
            }
            break;

/*
 Rigth hand adaptives (most are single-handed neighbor fingers, bc speed, dexterity limits)
*/
        case KC_F:
            switch (prior_keycode) {
                case KC_G: // eliminate SFB
                    tap_code(KC_D); // GF = GD (3.8x more common)
                    return_state = false; // done.
                    break;
                case KC_M: // eliminate SFB/scissor
//                    tap_code(KC_N); // MW = MN (14x more common) (if F is on bottom)
                    tap_code(KC_P); // MF = MP (if P is on bottom)
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_H:
            switch (prior_keycode) {
                case KC_K: // to avoid the lat stretch
                    tap_code(KC_N); // KH = KN (KN is 15x more common)
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_J:
            switch (prior_keycode) {
                case KC_G: // 99.7% of GT are followed by H
                    send_string("th"); // for "length"
                    return_state = false; // done.
                    break;
                case KC_F: // Eliminate FL Scissor
                case KC_W: // Eliminate WL scissor
                    tap_code(KC_L); // WJ = wl (WL is 468x more common than WJ)
                    return_state = false; // done.
                    break;
            }
            break;

            // remedy ring-index split by shifting fingering
            // Since the hand is already displaced to reach the inner column,
            // pull the L over with alternate fingering to avoid the stretch.
        case KC_K:
            switch (prior_keycode) {
                case KC_H: // eliminate lateral stretch
                    tap_code(KC_BSPC); // replace H
                    tap_code(KC_N); // HK = NK (219x more common)
                    break; // Send K normally
            }
            break;

        // PQ ??
        // case KC_L: // catch this so we can unshift L on these involving pinky/ring rolls.
        //     switch (prior_keycode) {
        //         case KC_P:
        //         case KC_B: //
        //         case KC_S: //
        //             tap_code(KC_L);  //
        //             return_state = false; // done.
        //             break;
        //     }
        //     break;

        case KC_M: // M becomes L (pull up "L" to same row)
            switch (prior_keycode) {
                case KC_G: // eliminate scissor (GL is 5x more common than GM)
                case KC_V: // eliminate VL scissor ()
                    tap_code(KC_L);
                    return_state = false; // done.
                    break;
                case KC_F:
                    switch (preprior_keycode) {
                        case KC_M: // eliminate 2r/2c scissor
                            tap_code(KC_L); // WM = LM (LM 20x more common)
                            return_state = false; // done.
                            break;
                        default:
                            tap_code(KC_BSPC);
                            send_string("lm");
                            return_state = false; // done.
                            break;
                   }
            }
            break;

        case KC_P:
            switch (prior_keycode) {
                case KC_Z: // eliminate SP scissor
                    tap_code(KC_BSPC); // remove F
                    tap_code(KC_S);  // ZP=SP (SP 860x more common)
                    break; // Send P normally
                case KC_P: // eliminate DG sfb
                    tap_code(KC_G);  //
                    return_state = false; // done.
                    break; //
            }
            break;

        case KC_V:
            switch (prior_keycode) {
                case KC_G: // "GT" is 363x more frequent than "GV"
                    tap_code(KC_T); // eliminate GT SFB.
                    return_state = false; // done.
                    break;
                case KC_M: // eliminate LV scissor.
                    tap_code(KC_BSPC); // replace M
                    tap_code(KC_L); // "LV" is 119x more frequent than "MV"
                    break;
            }
            break;


#if defined (HD_MAGIC) || defined (HD_MAGIC_A) || defined (HD_MAGIC_B)
#include "adapt_magic.c" // the common adaptive "magic" key
#endif //

    }

    //PQ Enthium, left hand
    switch (KEY_PAIR(prior_keycode, keycode)) {
#ifndef SWAP_QB
        REPLACE2NDKEY(KC_Y, KC_Q, KC_COMMA); // YQ = Y, (avoid sfb)
        REPLACE2NDKEY(KC_B, KC_C, KC_E);     // BC = BE, (avoid stretch)
        REPLACE2NDKEY(KC_B, KC_Q, KC_U);     // BQ = BU, (avoid stretch)
#else
        // PQ, BI is difficult, but not sure how to avoid it.
        REPLACE2NDKEY(KC_Y, KC_B, KC_COMMA); // YB = Y, (avoid sfb)
#endif
        REPLACE2NDKEY(KC_Y, KC_U, KC_DOT);  // YU = Y. (avoid scissor)

        REPLACEPRIOR(KC_DOT, KC_COMMA, KC_O); // ., = o, (avoid sfb)
        REPLACEPRIOR(KC_COMMA, KC_DOT, KC_O); // ,. = o. (avoid scissor)
    }

    if (return_state)  // no adaptive processed, cancel state and pass it on.
        set_mods(saved_mods);

    return return_state; //
}
