// .h = only #defines. #defines do not have to be made in a strict order.


/* Key position groups */

#define KEYS_LEFT  0  1  2  3  4  5  6 \
                  14 15 16 17 18 19 20 \
                  28 29 30 31 32 33 34 \
                  46 47 48 49 50 51    \
                  60 61 62 63 64

#define KEYS_RIGHT  7  8  9 10 11 12 13 \
                   21 22 23 24 25 26 27 \
                   39 40 41 42 43 44 45 \
                      54 55 56 57 58 59 \
                         71 72 73 74 75

#define THUMBS_LEFT    35 36 \
                          52 \
                    65 66 67

#define THUMBS_RIGHT 37 38    \
                     53       \
                     68 69 70

#define NUMPAD     9 10 11 12    \
                  23 24 25 26 27 \
                  41 42 43 44    \
                  55 56 57 58    \
                     72 73       \
                                 \
               69 70


/* MAKE_LETTER_KEY */

#define MAKE_LETTER_KEY(...) CONCAT(MAKE_LETTER_KEY_, VARGS(__VA_ARGS__))(__VA_ARGS__)
#define MAKE_LETTER_KEY_2(KEY, KEY_LOWER) \
    MAKE_LETTER_KEY_3(KEY, KEY_LOWER, ht_rgkp_kp)
#define MAKE_LETTER_KEY_3(KEY, KEY_LOWER, BEHAVIOR) \
    MAKE_LETTER_KEY_4(KEY, KEY_LOWER, BEHAVIOR, )
#define MAKE_LETTER_KEY_4(KEY, KEY_LOWER, BEHAVIOR, LETTER_VAARGS) \
	ZMK_ADAPTIVE_KEY(ag_ ## KEY_LOWER, \
		bindings = <&BEHAVIOR KEY KEY>; \
		rs_ ## KEY_LOWER { trigger-keys = <RS(KEY)>; bindings = <&key_repeat>; max-prior-idle-ms = <DEFAULT_ADAPTIVE_TIMEOUT_MS>; }; \
		LETTER_VAARGS \
	)


/* MAKE_NUMBER_ROW_KEY */

#define MAKE_NUMBER_ROW_KEY(...) CONCAT(MAKE_NUMBER_ROW_KEY_, VARGS(__VA_ARGS__))(__VA_ARGS__)
#define MAKE_NUMBER_ROW_KEY_6(NUMBER, NUMBER_LOWER, KEY, KEY_LOWER, RS_KEY, RS_KEY_LOWER) \
    MAKE_NUMBER_ROW_KEY_7(NUMBER, NUMBER_LOWER, KEY, KEY_LOWER, RS_KEY, RS_KEY_LOWER, )
#define MAKE_NUMBER_ROW_KEY_7(NUMBER, NUMBER_LOWER, KEY, KEY_LOWER, RS_KEY, RS_KEY_LOWER, NUMBER_ROW_VAARGS) \
	ZMK_ADAPTIVE_KEY(ag_ ## NUMBER_LOWER, \
		bindings = <&KEY_LOWER ## _rs_morph>; \
		NUMBER_ROW_VAARGS /* Placing it here allows for potential overrides */ \
		ag_repeat { \
			trigger-keys = <RG(N1) RG(N2) RG(N3) RG(N4) RG(N5) RG(N6) RG(N7) RG(N8) RG(N9) RG(N0)>; \
			bindings = <&ht_rgkp_rgkp NUMBER NUMBER>; /* Why <&ht_rgkp_rgkp NUMBER NUMBER>; ? Because a simple <&kp RG(NUMBER)> would be repeated while holding */ \
			max-prior-idle-ms = <SLOW_ADAPTIVE_TIMEOUT_MS>; \
		}; \
	) \
	ZMK_MOD_MORPH(KEY_LOWER ## _rs_morph, \
		bindings = <&ht_rgkp_kp NUMBER KEY>, <&KEY_LOWER ## _shifted_ls_morph>; \
		mods = <(MOD_RSFT)>; \
	) \
	ZMK_MOD_MORPH(KEY_LOWER ## _shifted_ls_morph, \
		bindings = <&ht_rgkp_kp KEY RS_KEY>, <&ht_rgkp_kp LS(NUMBER) RS_KEY>; \
		mods = <(MOD_LSFT)>; \
	)


/* MAKE_SPECIAL_CHAR_KEY */

#define MAKE_SPECIAL_CHAR_KEY(...) CONCAT(MAKE_SPECIAL_CHAR_KEY_, VARGS(__VA_ARGS__))(__VA_ARGS__)
#define MAKE_SPECIAL_CHAR_KEY_4(KEY, KEY_LOWER, RS_KEY, RS_KEY_LOWER) \
	MAKE_SPECIAL_CHAR_KEY_5(KEY, KEY_LOWER, RS_KEY, RS_KEY_LOWER, )
#define MAKE_SPECIAL_CHAR_KEY_5(KEY, KEY_LOWER, RS_KEY, RS_KEY_LOWER, SPECIAL_CHAR_VAARGS) \
	ZMK_ADAPTIVE_KEY(ag_ ## KEY_LOWER, \
		bindings = <&KEY_LOWER ## _rs_morph>; \
		SPECIAL_CHAR_VAARGS /* Placing it here allows for potential overrides */ \
		ag_ ## RS_KEY_LOWER { trigger-keys = <RS_KEY>; bindings = <&key_repeat>; max-prior-idle-ms = <DEFAULT_ADAPTIVE_TIMEOUT_MS>; allow-more-modifiers; }; \
	) \
	ZMK_MOD_MORPH(KEY_LOWER ## _rs_morph, \
		bindings = <&ht_rgkp_kp KEY KEY>, <&ht_rgkp_kp RS_KEY RS_KEY>; \
		mods = <(MOD_RSFT)>; \
	)
