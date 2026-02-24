/*
 Adaptive Keys
 Called from within process_record_user

 Tailored for HD Vibranium-v (vv)

 NOTE: assumed dual-function keys (MOD_TAP, LAYER_TAP) have already been handled AND
    FILTERED OUT! The combos handler will have already taken out combo candidates,
    which have a shorter keydown threshhold (COMBO_TERM).

 */

#include "adaptive.h"


bool process_adaptive_key(uint16_t keycode, const keyrecord_t *record) {
    bool return_state = true; // assume we don't do anything.
    uint16_t keyPair = KEY_PAIR(prior_keycode, keycode & QK_BASIC_MAX);

    // Are we in an adaptive context? (adaptive on is assumed).
    if (timer_elapsed(prior_keydown) > ADAPTIVE_TERM
        || ((keycode == KC_SLSH) && (timer_elapsed(prior_keydown) > ADAPTIVE_TERM * 16))) {
        prior_keycode = preprior_keycode = prior_keydown = 0; // turn off Adaptives.
        return true; // no adaptive conditions, so return.
    }

    // K, this could be adaptive, so process.
    saved_mods = get_mods();

    if (!caps_word_timer) { // turn off shift, (first-words & Proper nouns)
        unregister_mods(MOD_MASK_SHIFT);  //CAPS_WORD/LOCK won't be affected.
    } // may want more granular control than this…

    switch (keyPair) {

/*
   Left hand adaptives (most are single-handed neighbor fingers, bc speed, dexterity limits)
*/
        // M becomes L (pull up "L" to same row)
        REPLACE2NDKEY(KC_G, KC_M,  KC_L); // pull up "L" (GL is 5x more common than GM)
        REPLACE2NDKEY(KC_X, KC_M,  KC_L); // pull up "L" (XL is 1.5x more common than XM)

        case KEY_PAIR(KC_W, KC_M):  // WM = LM (LM 20x more common)
            if (!preprior_keycode) {
                _REPLACEPRIOR(KC_L);  // wm => lm
                break;
            }
            switch (preprior_keycode) {
                case KC_M:      // mwm => mpl
                case KC_X:      // xwm => xpl (?)
                    _REPLACE2NDKEY(KC_L);
            };
            break;

        REPLACE2NDKEY(KC_X, KC_W,  KC_P);   // pull up P (W becomes P after X to set up "xp"+l)
        REPLACE2NDKEY(KC_M, KC_W,  KC_P);   // pull up P (W becomes P after M to set up "mp"+l)
        REPLACE2NDKEY(KC_G, KC_W,  KC_D);

        REPLACE2NDKEY(KC_K, KC_G,  KC_L);   // pull up "L" (KL is 5x more common than KG)
        REPLACEPRIOR(KC_M,  KC_G,  KC_L);   // mg => lg
        INSERTEBETWEEN(KC_J,KC_G,  KC_P);   // jg => jpg
        REPLACESTRING(KC_W, KC_G, "lml");   // wg => lml
        REPLACEPRIOR(KC_X, KC_G,  KC_N);    //pq roll XG for NG

        // (for KD=KL; least code, no side effects)
        REPLACE2NDKEY(KC_K, KC_D,  KC_L); // pull up "L" (KL is 5x more common than KG)
        REPLACE2NDKEY(KC_V, KC_D,  KC_L);
        case KEY_PAIR(KC_L, KC_D) :
            if (preprior_keycode == KC_P) { // PLD = PWD
                _REPLACEPRIOR(KC_W);
                break; // process the D normally
            }
        break;

        // catch this so we can unshift L on these rolls.
        REPLACE2NDKEY(KC_P, KC_L,  KC_L);
        REPLACE2NDKEY(KC_S, KC_L,  KC_L);

        // alt fingering remedy for middle-index splits
        REPLACE2NDKEY(KC_K, KC_T,  KC_N);   // quickly typing "k?" yields "kn" (+48x)

        REPLACESTRING(KC_T, KC_C, "tch");   // 85% of tc is tch, so this saves a lot of "H" key presses

        REPLACE2NDKEY(KC_D, KC_F,  KC_G);   // eliminate SFB (DG is 10x more common than DF)
        REPLACEPRIOR(KC_V, KC_F,  KC_S);    // avoid row step (SF 311x more common than VF)

        REPLACE2NDKEY(KC_F, KC_V,  KC_S);   // avoid row step FV FS (91x more frequent)

        // remedy ring-index split by shifting fingering
        REPLACEPRIOR(KC_T, KC_K,  KC_C);   // TK/DK/GK = CK (252x more frequent)
        REPLACEPRIOR(KC_D, KC_K,  KC_L);   // DK = LK (11x more frequent)
        REPLACEPRIOR(KC_G, KC_K,  KC_L);   // GK = LK (74x more frequent)

        // LL is the highest consonant repeat, and it's off home, so eliminate this SFB
        REPLACE2NDKEY(KC_L, KC_R,  KC_L);   // quickly typing "lr" yields "ll" (+56x)

        REPLACE2NDKEY(KC_W, KC_X,  KC_L);   // eliminate scissor (2818x gain)
        REPLACE2NDKEY(KC_M, KC_X,  KC_F);   // eliminate scissor (107x gain) pull up F from bottom row.
        REPLACE2NDKEY(KC_G, KC_X,  KC_T);   // eliminate GT SFB. "GX" is 778x more frequent than "GT"

    }

/*
   right hand adaptives
*/
    switch (keycode & QK_BASIC_MAX) { // process ignoring multi-function keys
        case KC_SLSH:
        case KC_H: // H precedes a vowel much more often than it follows (thanks, Ancient Greek!)
            switch (prior_keycode) { // maybe OK? What about xxR? resulting in a SFB on thumb?
                // AE is a fraction less common, but I find the EAE trill harder than EAH.
                REPLACE2NDKEY_(KC_A, KC_U); // "AH" yields "AU" (8x more common, eliminates SFB)
                REPLACE2NDKEY_(KC_E, KC_O); // "EH" yields "EO" (1.75:1)
                REPLACE2NDKEY_(KC_O, KC_E); // "OH" yields "OE" (almost 1:1, but eliminates an SFB)
                REPLACE2NDKEY_(KC_U, KC_A); // "UH" yields "UA" (126x more common)
                REPLACE2NDKEY_(KC_I, KC_P); // "IH" yields "IP" (41x more common), avoid row skip on outward pinky roll
            }
            break;
    }

    switch (keyPair) {
        REPLACE2NDKEY(KC_Y, KC_P,  KC_I);   // YP = YI (eliminate SFB on ring finger YI is 37x YF)

        // pq, this this does not work because we are masking mods and KC_DQUO is shift-'
        // case KC_DQUO:
        //     switch (prior_keycode) {
        //         case KC_B: //
        //             tap_code(KC_Y); // BJ = BY (eliminate scissor on ring finger BY is 6x BJ)
        //             return_state = false; // done.
        //             break;
        //         case KC_DOT:
        //             send_string("edu");
        //             return_state = false; // done.
        //             break;
        //     }
        //     break;

        REPLACESTRING(KC_DOT, KC_QUOT, ".com");
        REPLACESTRING(KC_DOT, KC_B, ".org");
        REPLACESTRING(KC_DOT, KC_J, ".net");

        REPLACE2NDKEY(KC_B,   KC_J,  KC_Y);     // BJ = BY (eliminate scissor on ring finger BY is 6x BJ)

        REPLACE2NDKEY(KC_QUOT,KC_QUOT,  KC_O);  // '' => 'o
        REPLACE2NDKEY(KC_B,   KC_QUOT,  KC_O);  // b' => bo (eliminate scissor)

        // This could be smarter (only after O rolled up)
        REPLACE2NDKEY(KC_QUOT,KC_DOT, KC_U);    // '. => 'u
        REPLACE2NDKEY(KC_B,   KC_DOT, KC_U);    // b. => bu (eliminate scissor)

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
