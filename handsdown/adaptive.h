// define some macros to make adaptive code easier to read

#define KEY_PAIR(priorKey, secondKey) (((priorKey) << 8) | (secondKey))

// Replace the 2nd key with newSecondKey
#define _REPLACE2NDKEY(newSecondKey)\
        tap_code(newSecondKey);\
        return_state = false;\
        break;

#define REPLACE2NDKEY_(priorKey, newSecondKey)\
    case ((priorKey)):{\
        _REPLACE2NDKEY(newSecondKey);\
    }

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

// replace prior key and send a string
#define _REPLACESTRING(newString)\
        tap_code(KC_BSPC);\
        send_string(newString);\
        return_state = false;\
        break;

#define REPLACESTRING(priorKey, secondKey, newString)\
    case KEY_PAIR((priorKey), (secondKey)):{\
        _REPLACESTRING(newString);\
    }

// insert newKey between prior and 2nd (letting 2nd key go through)
#define _INSERTEBETWEEN(newKey)\
        tap_code(newKey);\
        break;

#define INSERTEBETWEEN(priorKey, secondKey, insertKey)\
    case KEY_PAIR((priorKey), (secondKey)):{\
        _INSERTEBETWEEN(insertKey);\
    }

