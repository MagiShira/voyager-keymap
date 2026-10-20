#include QMK_KEYBOARD_H

// Mac-style Cmd on the thumb: Meta + these letters is sent as Ctrl + letter.
// Everything else (Meta+Tab, Meta+arrows, Meta+digits, a bare Meta tap) stays real Meta.
bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed || !(get_mods() & MOD_BIT(KC_LGUI))) {
    return true;
  }
  switch (keycode) {
    case KC_A: case KC_C: case KC_F: case KC_N: case KC_O: case KC_P: case KC_Q:
    case KC_R: case KC_S: case KC_T: case KC_V: case KC_W: case KC_X: case KC_Z:
      // Ctrl goes down before Meta lifts (and Meta returns before Ctrl lifts) so KWin
      // never observes a bare Meta tap, which would open the application launcher.
      add_mods(MOD_BIT(KC_LCTL));
      send_keyboard_report();
      del_mods(MOD_BIT(KC_LGUI));
      send_keyboard_report();
      tap_code(keycode);
      add_mods(MOD_BIT(KC_LGUI));
      send_keyboard_report();
      del_mods(MOD_BIT(KC_LCTL));
      send_keyboard_report();
      return false;
  }
  return true;
}
