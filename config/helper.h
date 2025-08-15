// .h = only #defines. #defines do not have to be made in a strict order.


/* Timings */

#if !defined QUICK_TAP_MS
	#define QUICK_TAP_MS 175
#endif
#if !defined DEFAULT_ADAPTIVE_TIMEOUT_MS
	#define DEFAULT_ADAPTIVE_TIMEOUT_MS 1000
#endif
#if !defined SLOW_ADAPTIVE_TIMEOUT_MS
	#define SLOW_ADAPTIVE_TIMEOUT_MS 2000
#endif


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


/* SIMPLE_MACRO */

#define SIMPLE_MACRO(NAME, SEQUENCE) \
	ZMK_MACRO(NAME, \
		wait-ms = <0>; \
		tap-ms = <0>; \
		bindings = <SEQUENCE>; \
	)


/* KP_WITH_MOD_SEQUENCE */

#if !defined KP_WITH_MOD_SEQUENCE__WAIT_MS
	#define KP_WITH_MOD_SEQUENCE__WAIT_MS 30
#endif
#if !defined KP_WITH_MOD_SEQUENCE__TAP_MS
	#define KP_WITH_MOD_SEQUENCE__TAP_MS 0
#endif

#define KP_WITH_MOD_SEQUENCE(NAME, MOD) \
	ZMK_MACRO_ONE_PARAM(NAME, \
		wait-ms = <KP_WITH_MOD_SEQUENCE__WAIT_MS>; \
		tap-ms = <KP_WITH_MOD_SEQUENCE__TAP_MS>; \
		bindings \
		= <&macro_press &kp MOD> /* Interestingly, sk won’t work */ \
		, <&macro_param_1to1> \
		, <&macro_tap &kp MACRO_PLACEHOLDER> \
		, <&macro_release &kp MOD>; \
	)


/* MAKE_HOMEROW_MODS */

#if !defined MAKE_HOMEROW_MODS__TAPPING_TERM_MS
	#define MAKE_HOMEROW_MODS__TAPPING_TERM_MS 180
#endif
#if !defined MAKE_HOMEROW_MODS__REQUIRE_PRIOR_IDLE_MS
	#define MAKE_HOMEROW_MODS__REQUIRE_PRIOR_IDLE_MS 200
#endif

#define MAKE_HOMEROW_MODS(NAME, HOLD, TAP, TRIGGER_POS) \
    ZMK_HOLD_TAP(NAME, \
        flavor = "balanced"; \
        tapping-term-ms = <MAKE_HOMEROW_MODS__TAPPING_TERM_MS>; \
        quick-tap-ms = <QUICK_TAP_MS>; \
        require-prior-idle-ms = <MAKE_HOMEROW_MODS__REQUIRE_PRIOR_IDLE_MS>; \
        bindings = <HOLD>, <TAP>; \
        hold-trigger-key-positions = <TRIGGER_POS>; \
        hold-trigger-on-release; \
    )


/* MAKE_SMART_SHIFT */

#if !defined MAKE_SMART_SHIFT__HT_TAPPING_TERM_MS
	#define MAKE_SMART_SHIFT__HT_TAPPING_TERM_MS 200
#endif
#if !defined MAKE_SMART_SHIFT__DANCE_TAPPING_TERM_MS
	#define MAKE_SMART_SHIFT__DANCE_TAPPING_TERM_MS 400
#endif

#define MAKE_SMART_SHIFT(NAME, SHIFT_KEY, SHIFT_KEY_LOWER) \
	ZMK_ADAPTIVE_KEY(NAME, \
		bindings = <&ht_kp_ ## SHIFT_KEY_LOWER ## _dance SHIFT_KEY 0>; \
	) \
	ZMK_HOLD_TAP(ht_kp_ ## SHIFT_KEY_LOWER ## _dance, \
		flavor = "balanced"; \
		tapping-term-ms = <MAKE_SMART_SHIFT__HT_TAPPING_TERM_MS>; \
		quick-tap-ms = <QUICK_TAP_MS>; \
		bindings = <&kp>, <&SHIFT_KEY_LOWER ## _dance>; \
	) \
	ZMK_TAP_DANCE(SHIFT_KEY_LOWER ## _dance, \
		tapping-term-ms = <MAKE_SMART_SHIFT__DANCE_TAPPING_TERM_MS>; \
		bindings = <&sk SHIFT_KEY>, <&caps_word>, <&kp CAPSLOCK>; \
	)


/* MAKE_LETTER_KEY */

#if !defined MAKE_LETTER_KEY__BEHAVIOR
	#define MAKE_LETTER_KEY__BEHAVIOR ht_rgkp_kp
#endif

#define MAKE_LETTER_KEY(...) CONCAT(MAKE_LETTER_KEY_, VARGS(__VA_ARGS__))(__VA_ARGS__)
#define MAKE_LETTER_KEY_2(KEY, KEY_LOWER) \
    MAKE_LETTER_KEY_3(KEY, KEY_LOWER, MAKE_LETTER_KEY__BEHAVIOR)
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
		NUMBER_ROW_VAARGS /* Placing va_args here to allow for potential overrides */ \
		ag_repeat { \
			trigger-keys = <RG(N1) RG(N2) RG(N3) RG(N4) RG(N5) RG(N6) RG(N7) RG(N8) RG(N9) RG(N0)>; \
			bindings = <&ht_rgkp_rgkp NUMBER NUMBER>; /* Why <&ht_rgkp_rgkp NUMBER NUMBER>; ? Because a simple <&kp RG(NUMBER)> would be repeated while holding */ \
			max-prior-idle-ms = <SLOW_ADAPTIVE_TIMEOUT_MS>; \
		}; \
	) \
	ZMK_MOD_MORPH(KEY_LOWER ## _rs_morph, \
		bindings = <&KEY_LOWER ## _ls_morph>, <&ht_rgkp_kp RS(NUMBER) RS_KEY>; \
		mods = <(MOD_RSFT)>; \
	) \
	ZMK_MOD_MORPH(KEY_LOWER ## _ls_morph, \
		bindings = <&ht_rgkp_kp NUMBER KEY>, <&kp RS_KEY>; \
		mods = <(MOD_LSFT)>; \
	)


/* MAKE_SPECIAL_CHAR_KEY */

#define MAKE_SPECIAL_CHAR_KEY(...) CONCAT(MAKE_SPECIAL_CHAR_KEY_, VARGS(__VA_ARGS__))(__VA_ARGS__)
#define MAKE_SPECIAL_CHAR_KEY_4(KEY, KEY_LOWER, RS_KEY, RS_KEY_LOWER) \
	MAKE_SPECIAL_CHAR_KEY_5(KEY, KEY_LOWER, RS_KEY, RS_KEY_LOWER, )
#define MAKE_SPECIAL_CHAR_KEY_5(KEY, KEY_LOWER, RS_KEY, RS_KEY_LOWER, SPECIAL_CHAR_VAARGS) \
	ZMK_ADAPTIVE_KEY(ag_ ## KEY_LOWER, \
		bindings = <&KEY_LOWER ## _rs_morph>; \
		SPECIAL_CHAR_VAARGS /* Placing va_args here to allow for potential overrides */ \
		ag_ ## RS_KEY_LOWER { trigger-keys = <RS_KEY>; bindings = <&key_repeat>; max-prior-idle-ms = <DEFAULT_ADAPTIVE_TIMEOUT_MS>; allow-more-modifiers; }; \
	) \
	ZMK_MOD_MORPH(KEY_LOWER ## _rs_morph, \
		bindings = <&ht_rgkp_kp KEY KEY>, <&ht_rgkp_kp RS_KEY RS_KEY>; \
		mods = <(MOD_RSFT)>; \
	)
