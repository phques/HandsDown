/*
 Adaptive Keys
 Called from within process_record_user

 Tailored for HD Gold (au) swap WK, GF

 NOTE: assumed dual-function keys (MOD_TAP, LAYER_TAP) have already been handled AND
    FILTERED OUT! The combos handler will have already taken out combo candidates,
    which have a shorter keydown threshhold (COMBO_TERM).

 All the goto shenanigans should be resolved after complete migration to STM/RP controllersr
 (not totally possible, as many of my boards have embedded AVR mcus)

 */
//              Hands Down Gold
// ╭─────────────────────╮ ╭─────────────────────╮
// │  J   G   M   P   V  │ │  #$  .:  /*  "[  '] │
// │  R   S   N   D   B  | |  ,;   A   E   I   H │
// │  X   F   L   C   K  │ │  -+   U   O   Y   W │
// ╰───────────╮ BSP  T  │ │ SPC  RET ╭──────────╯
//             ╰─────────╯ ╰──────────╯
// Q (LT3) & Z (LT4) are on the punc layer


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

    switch (keycode & QK_BASIC_MAX) { // process ignoring multi-function keys

/*
// Left hand adaptives (most are single-handed neighbor fingers, bc speed, dexterity limits)
*/
        // pq 2024-06-08, copied from the other variants, even though T is on the thumb in Gold !
        case KC_C:
            switch (prior_keycode) {
                case KC_T: // roll for tch
                    send_string("ch"); // 85% of tc is tch, so this saves a lot of key press "H"
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_M: // M becomes L (pull up "L" to same row)
            switch (prior_keycode) {
                case KC_P: // pull up "L" (PL is 15x more common than PM)
                case KC_G: // pull up "L" (GL is 5x more common than GM)
                case KC_F: // pull up "L" (pq 2024-06-08, swap FG)
                    tap_code(KC_L);  // pull up "L"
                    return_state = false; // done.
                    break;
                case KC_J: //
                    tap_code(KC_BSPC);
                    tap_code(KC_L);
                    break;
            }
            break;

        case KC_B:  // avoid the index-middle split
            switch (prior_keycode) {
                case KC_P: // pull up M over
                    tap_code(KC_M);
                    return_state = false; // done.
                case KC_D: // pull L over
                    tap_code(KC_L);  // pull up "L"
                    return_state = false; // done.
                    break;
                break;
           }
            break;

        case KC_D: //
            switch (prior_keycode) { //
                case KC_B:
                    tap_code(KC_L);  // pull up "L"
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_P:
            switch (prior_keycode) {
                case KC_G: // avoid the LP scissor
                case KC_F: // avoid the LP scissor (pq 2024-06-08 swap FG)
                    tap_code(KC_BSPC);
                    tap_code(KC_L);
                    break;
                case KC_J:
                    tap_code(KC_BSPC);
                    send_string("lml"); // for "calmly" but not quite intuitive…
                    return_state = false; // done.
                    break;
                case KC_V: // avoid the index-middle split
                    tap_code(KC_L);  // pull up "L"
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_X: //
            switch (prior_keycode) { //
                case KC_C: // CD is 70x more common than CX
                    tap_code(KC_D);  // eliminate the SFB
                    return_state = false; // done.
                    break;
            }
            break;



/*
// right hand adaptives
*/

        case KC_H: // How often are we likely to hit BS so quickly after?
            switch (prior_keycode) { // maybe OK? What about xxR? resulting in a SFB on thumb?
                case KC_A: // AE is a fraction less common, but I find the EAE trill harder than EAH.
                    tap_code(KC_U); // "AH" yields "AU" (8x more common)
                    return_state = false; // done.
                    break;
                case KC_E:
                    tap_code(KC_O); // "EH" yields "EO" (1.75:1)
                    return_state = false; // done.
                    break;
                case KC_O:
                    tap_code(KC_E); // "OH" yields "OE" (almost 1:1, but eliminates an SFB?)
                    return_state = false; // done.
                    break;
                case KC_U:
                    tap_code(KC_A); // "UH" yields "UA" (126x more common)
                    return_state = false; // done.
                    break;
                case KC_Y: // (y'all)
                    return_state = false; // done.
#ifdef FR_ADAPTIVES // eliminate 'h SFB for French
                case KC_J: // j'habite
                case KC_L: // l'hôtel
                case KC_N: // n'habite
                case KC_D: // d'habitude
#ifdef EN_HDIGRAPH_COMBOS
                case KC_T: // t'habitude can't do this (bc Th) unless Th digraph combo is used…
#endif
#endif
                    tap_code(KC_QUOT); // YH => Y' (pull down to avoid ring-pinky T-B scissor)
                    return_state = false; // done.
            }
            break;

        case KC_W: //pq 2024-06 swap KW
        //case KC_K:
            switch (prior_keycode) {
                case KC_Y:  // eliminate SFB on ring finger
                    tap_code(KC_I);
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_U:
            switch (prior_keycode) {
                case KC_K: // make KU send Qu
                    tap_code(KC_BSPC);
                    tap_code(KC_Q);
                    break;
            }
            break;


#ifdef THUMB_REPEATER
        case HD_REPEATER_A: // Make a repeat key of the secondary thumb key on both sides
        case HD_REPEATER_B: // for most common double letters (inherently SFBs)
            switch (prior_keycode) {
                case KC_A ... KC_SLASH: // Any alpha can be repeated?
/* double-letter frequencies from Peter Norvig's data <https://norvig.com/mayzner.html>
                case KC_L: // 0.577%
                case KC_S: // 0.405%
                case KC_E: // 0.378%
                case KC_O: // 0.210%
                case KC_T: // 0.171%
                case KC_F: // 0.146%
                case KC_P: // 0.137%
                case KC_R: // 0.121%
                case KC_M: // 0.096%
                case KC_C: // 0.083%
                case KC_N: // 0.073%
                case KC_D: // 0.043%
                case KC_G: // 0.025%
                case KC_I: // 0.023%
                case KC_B: // 0.011%
                case KC_A: // 0.003%
                case KC_Z: // 0.003%
                case KC_X: // 0.003%
                case KC_U: // 0.001%
                case KC_H: // 0.001%
*/
                    tap_code(prior_keycode); // eliminate SFB on double
                    return_state = false; // done.
            }
            break;
#endif
#ifdef ADAPTIVE_TRAILER
#include "adaptive_trailer.c"
#endif // ADAPTIVE_TRAILER

    }
    if (return_state) { // no adaptive processed, cancel state and pass it on.
        set_mods(saved_mods);
        prior_keycode = preprior_keycode = keycode = 0;
    }
    return return_state; //
}
