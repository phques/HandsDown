/*
 Adaptive Keys
 Called from within process_record_user

 Tailored for HD Vibranium-v (vv)

 NOTE: assumed dual-function keys (MOD_TAP, LAYER_TAP) have already been handled AND
    FILTERED OUT! The combos handler will have already taken out combo candidates,
    which have a shorter keydown threshhold (COMBO_TERM).

 */

#define KEY_PAIR(priorKey, secondKey) (((priorKey) << 8) | (secondKey))

// Replace the 2nd key with newSecondKey
#define _REPLACE2NDKEY(newSecondKey)\
        tap_code(newSecondKey);\
        return_state = false;\
        break;

#define REPLACE2NDKEY(priorKey, secondKey, newSecondKey)\
    case KEY_PAIR((priorKey), (secondKey)):{\
        _REPLACE2NDKEY(newSecondKey);\
    }

// replace prior key and let current keycode send normally
#define _REPLACEPRIOR(newKey)\
        tap_code(KC_BSPC);\
        tap_code(newKey);\
        break;

#define REPLACEPRIOR(priorKey, secondKey, newPriorKey)\
    case KEY_PAIR((priorKey), (secondKey)):{\
        _REPLACEPRIOR(newPriorKey);\
    }

// insert newKey before letting 2nd key go through
#define INSERTEBETWEEN(newKey)\
        tap_code(newKey);\
        break;


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

        // M becomes L (pull up "L" to same row)
        REPLACE2NDKEY(KC_G, KC_M,  KC_L); // pull up "L" (GL is 5x more common than GM)
        REPLACE2NDKEY(KC_X, KC_M,  KC_L); // pull up "L" (XL is 1.5x more common than XM)

        case KEY_PAIR(KC_W, KC_M):  // WM = LM (LM 20x more common)
            if (!preprior_keycode) {
                _REPLACE2NDKEY(KC_L);  // wm => lm
                break;
            }
            switch (preprior_keycode) {
                case KC_M:      // mwm => mpl
                case KC_X:      // xwm => xpl (?)
                    _REPLACE2NDKEY(KC_L);
            };

        REPLACE2NDKEY(KC_X, KC_W,  KC_P);   // pull up P (W becomes P after X to set up "xp"+l)
        REPLACE2NDKEY(KC_M, KC_W,  KC_P);   // pull up P (W becomes P after M to set up "mp"+l)
        REPLACE2NDKEY(KC_G, KC_W,  KC_D);

        REPLACE2NDKEY(KC_K, KC_G,  KC_L) :  // pull up "L" (KL is 5x more common than KG)
        REPLACEPRIOR(KC_M,  KC_G,  KC_L) :  // mg => lg
        INSERTEBETWEEN(KC_J,KC_G,  KC_P) :  // jg => jpg

        case KEY_PAIR(KC_W, KC_G) :
            tap_code(KC_BSPC);
            send_string("lml"); // for "calmly" though not quite intuitive…
            return_state = false; // done.
            break;
    }

    switch (keycode & QK_BASIC_MAX) { // process ignoring multi-function keys

/*
   Left hand adaptives (most are single-handed neighbor fingers, bc speed, dexterity limits)
*/


        case KC_G:
            switch (prior_keycode) {
                case KC_K:
                    tap_code(KC_L);  // pull up "L" (KL is 5x more common than KG)
                    return_state = false; // done.
                    break;
               case KC_M:
                    tap_code(KC_BSPC);
                    tap_code(KC_L);
                    break; // and let current keycode send normally
                case KC_J: // JG = jpg
                    tap_code(KC_P); // insert a P
                    break; // and let current keycode send normally
                case KC_W:
                    tap_code(KC_BSPC);
                    send_string("lml"); // for "calmly" though not quite intuitive…
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_D: // (for KD=KL; least code, no side effects)
            switch (prior_keycode) { //
                case KC_K:
                case KC_V:
                    tap_code(KC_L);  // pull up "L" (PL is 15x more common than PM)
                    return_state = false; // done.
                    break;
                case KC_L:
                    if (preprior_keycode == KC_P) { // PLD = PWD?
                        tap_code(KC_BSPC);
                        tap_code(KC_W); // replace the L with W
                        break; // process the D normally
                    }
            }
            break;

        case KC_L: // catch this so we can unshift L on these rolls.
            switch (prior_keycode) {
                case KC_P:
                case KC_S: //
                    tap_code(KC_L);  // pull up "L" (PL is 15x more common than PM)
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_T:  // alt fingering remedy for middle-index splits
            switch (prior_keycode) {
                case KC_K: // quickly typing "k?" yields "kn" (+48x)
                    tap_code(KC_N);
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_C:
            switch (prior_keycode) {
                case KC_T: // roll for tch
                    send_string("ch"); // 85% of tc is tch, so this saves a lot of "H" key presses
                    return_state = false; // done.
                    break;
                case KC_N: //pq roll NC for NG
                    tap_code(KC_G);
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_F:
            switch (prior_keycode) {
                case KC_D: //
                    tap_code(KC_G); // eliminate SFB (DG is 10x more common than DF)
                    return_state = false; // done.
                    break;
                case KC_V: //
                    tap_code(KC_BSPC);
                    tap_code(KC_S); // avoid row step (311x more common than VF)
                    break;
            }
            break;

        case KC_V:
            switch (prior_keycode) {
                case KC_F: // avoid row step (91x more frequent)
                    tap_code(KC_S);
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_K: // remedy ring-index split by shifting fingering
            switch (prior_keycode) {
                case KC_T: // TK/DK/GK = CK (252x more frequent)
                    tap_code(KC_BSPC);
                    tap_code(KC_C);
                    break;
                case KC_D: // DK = LK (11x more frequent)
                case KC_G: // GK = LK (74x more frequent)
                    tap_code(KC_BSPC);
                    tap_code(KC_L);
                    break;
           }
            break;

        case KC_R:  // LL is the highest consonant repeat, and it's off home, so eliminate this SFB
            switch (prior_keycode) {
                case KC_L: // quickly typing "lr" yields "ll" (+56x)
                    tap_code(KC_L);
                    return_state = false; // done.
                    break;
            }
            break;

        case KC_X:
            switch (prior_keycode) {
                case KC_W: // eliminate scissor (2818x gain)
                    tap_code(KC_L);
                    return_state = false; // done.
                    break;
                case KC_M: // eliminate scissor (107x gain)
                    tap_code(KC_F); // pull up F from bottom row.
                    return_state = false; // done.
                    break;
                case KC_G: // "GX" is 778x more frequent than "GT"
                    tap_code(KC_T); // eliminate GT SFB.
                    return_state = false; // done.
                    break;
            }
            break;


/*
   right hand adaptives
*/

        case KC_SLSH:
        case KC_H: // H precedes a vowel much more often than it follows (thanks, Ancient Greek!)
            switch (prior_keycode) { // maybe OK? What about xxR? resulting in a SFB on thumb?
                case KC_A: // AE is a fraction less common, but I find the EAE trill harder than EAH.
                    tap_code(KC_U); // "AH" yields "AU" (8x more common, eliminates SFB)
                    return_state = false; // done.
                    break;
                case KC_E:
                    tap_code(KC_O); // "EH" yields "EO" (1.75:1)
                    return_state = false; // done.
                    break;
                case KC_O:
                    tap_code(KC_E); // "OH" yields "OE" (almost 1:1, but eliminates an SFB)
                    return_state = false; // done.
                    break;
                case KC_U:
                    tap_code(KC_A); // "UH" yields "UA" (126x more common)
                    return_state = false; // done.
                    break;
                case KC_I: // avoid row skip on outward pinky roll
                    tap_code(KC_P); // "IH" yields "IP" (41x more common)
                    return_state = false; // done.
                    break;

            }
            break;

        case KC_P:
            switch (prior_keycode) {
                case KC_Y: //
                    tap_code(KC_I); // YP = YI (eliminate SFB on ring finger YI is 37x YF)
                    return_state = false; // done.
                    break;
            }
            break;
        // pq this will never be true since we are masking mods and KC_DQUO is shift-'
        case KC_DQUO:
            switch (prior_keycode) {
                case KC_B: //
                    tap_code(KC_Y); // BJ = BY (eliminate scissor on ring finger BY is 6x BJ)
                    return_state = false; // done.
                    break;
                case KC_DOT:
                    send_string("edu");
                    return_state = false; // done.
                    break;
            }
            break;
        case KC_J:
            switch (prior_keycode) {
                case KC_B: //
                    tap_code(KC_Y); // BJ = BY (eliminate scissor on ring finger BY is 6x BJ)
                    return_state = false; // done.
                    break;
                case KC_DOT:
                    send_string("net");
                    return_state = false; // done.
                    break;
            }
            break;
        case KC_QUOT:
            switch (prior_keycode) {
                case KC_DOT:
                    send_string("com");
                    return_state = false; // done.
                    break;
                case KC_QUOT: //
                case KC_B: //
                    tap_code(KC_O); // (eliminate scissor)
                    return_state = false; // done.
                    break;
            }
            break;
        case KC_DOT:
            switch (prior_keycode) {
                case KC_QUOT: // This could be smarter (only after O rolled up)
                case KC_B: //
                    tap_code(KC_U); // (eliminate scissor)
                    return_state = false; // done.
                    break;
            }
            break;
      case KC_B:
          switch (prior_keycode) {
              case KC_DOT:
                  tap_code(KC_BSPC);
                  send_string(".org");
                  return_state = false; // done.
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
