#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>

using namespace std;

#include "session/config.pb.h"
#include "session/config_handler.h"

using namespace mozc;

#define EQ(a, b)        (strcmp(a, b) == 0)
#define BOOL_TO_STR(b)  (b ? "true" : "false")
#define QUOTED_STR(s)   "\"" << s << "\""

void get(char *name) {
    if (EQ("config_version", name)) {
        cout << "config_version: " << GET_CONFIG(config_version) << endl;
    } else if (EQ("last_modified_product_version", name)) {
        cout << "last_modified_product_version: " << QUOTED_STR(GET_CONFIG(last_modified_product_version)) << endl;
    } else if (EQ("last_modified_time", name)) {
        cout << "last_modified_time: " << GET_CONFIG(last_modified_time) << endl;
    } else if (EQ("platform", name)) {
        cout << "platform: " << QUOTED_STR(GET_CONFIG(platform)) << endl;
    } else if (EQ("ui_locale", name)) {
        cout << "ui_locale: " << QUOTED_STR(GET_CONFIG(ui_locale)) << endl;
    } else if (EQ("verbose_level", name)) {
        cout << "verbose_level: " << GET_CONFIG(verbose_level) << endl;
    } else if (EQ("incognito_mode", name)) {
        cout << "incognito_mode: " << BOOL_TO_STR(GET_CONFIG(incognito_mode)) << endl;
    } else if (EQ("check_default", name)) {
        cout << "check_default: " << BOOL_TO_STR(GET_CONFIG(check_default)) << endl;
    } else if (EQ("preedit_method", name)) {
        int i = GET_CONFIG(preedit_method);
        cout << "preedit_method: "
             << ((i == 0) ? "ROMAN" :
                 (i == 1) ? "KANA" : "INVARID_VALUE") << endl;
    } else if (EQ("session_keymap", name)) {
        int i = GET_CONFIG(session_keymap);
        cout << "session_keymap: "
             << ((i ==-1) ? "NONE" :
                 (i == 0) ? "CUSTOM" :
                 (i == 1) ? "ATOK" :
                 (i == 2) ? "MSIME" :
                 (i == 3) ? "KOTOERI" : "INVARID_VALUE") << endl;
    } else if (EQ("custom_keymap_table", name)) {
        cout << "custom_keymap_table: " << QUOTED_STR(GET_CONFIG(custom_keymap_table)) << endl;
    } else if (EQ("custom_roman_table", name)) {
        cout << "custom_roman_table: " << QUOTED_STR(GET_CONFIG(custom_roman_table)) << endl;
    } else if (EQ("punctuation_method", name)) {
        int i = GET_CONFIG(punctuation_method);
        cout << "punctuation_method: "
             << ((i == 0) ? "KUTEN_TOUTEN" :
                 (i == 1) ? "COMMA_PERIOD" :
                 (i == 2) ? "KUTEN_PERIOD" :
                 (i == 3) ? "COMMA_TOUTEN" : "INVARID_VALUE") << endl;
    } else if (EQ("symbol_method", name)) {
        int i = GET_CONFIG(symbol_method);
        cout << "symbol_method: "
             << ((i == 0) ? "CORNER_BRACKET_MIDDLE_DOT" :
                 (i == 1) ? "SQUARE_BRACKET_SLASH" :
                 (i == 2) ? "CORNER_BRACKET_SLASH" :
                 (i == 3) ? "SQUARE_BRACKET_MIDDLE_DOT" : "INVARID_VALUE") << endl;
    } else if (EQ("space_character_form", name)) {
        int i = GET_CONFIG(space_character_form);
        cout << "space_character_form: "
             << ((i == 0) ? "FUNDAMENTAL_INPUT_MODE" :
                 (i == 1) ? "FUNDAMENTAL_FULL_WIDTH" :
                 (i == 2) ? "FUNDAMENTAL_HALF_WIDTH" : "INVARID_VALUE") << endl;
    } else if (EQ("history_learning_level", name)) {
        int i = GET_CONFIG(history_learning_level);
        cout << "history_learning_level: "
             << ((i == 0) ? "DEFAULT_HISTORY" :
                 (i == 1) ? "READ_ONLY" :
                 (i == 2) ? "NO_HISTORY" : "INVARID_VALUE") << endl;
    } else if (EQ("selection_shortcut", name)) {
        int i = GET_CONFIG(selection_shortcut);
        cout << "selection_shortcut: "
             << ((i == 0) ? "NO_SHORTCUT" :
                 (i == 1) ? "SHORTCUT_123456789" :
                 (i == 2) ? "SHORTCUT_ASDFGHJKL" : "INVARID_VALUE") << endl;
//    } else if (EQ("character_form_rules", name)) {
//        cout << "character_form_rules: " << GET_CONFIG(character_form_rules) << endl;
    } else if (EQ("use_auto_ime_turn_off", name)) {
        cout << "use_auto_ime_turn_off: " << BOOL_TO_STR(GET_CONFIG(use_auto_ime_turn_off)) << endl;
    } else if (EQ("use_cascading_window", name)) {
        cout << "use_cascading_window: " << BOOL_TO_STR(GET_CONFIG(use_cascading_window)) << endl;
    } else if (EQ("shift_key_mode_switch", name)) {
        int i = GET_CONFIG(shift_key_mode_switch);
        cout << "shift_key_mode_switch: "
             << ((i == 0) ? "OFF" :
                 (i == 1) ? "ASCII_INPUT_MODE" :
                 (i == 2) ? "KATAKANA_INPUT_MODE" : "INVARID_VALUE") << endl;
    } else if (EQ("numpad_character_form", name)) {
        int i = GET_CONFIG(numpad_character_form);
        cout << "numpad_character_form: "
             << ((i == 0) ? "NUMPAD_INPUT_MODE" :
                 (i == 1) ? "NUMPAD_FULL_WIDTH" :
                 (i == 2) ? "NUMPAD_HALF_WIDTH" :
                 (i == 3) ? "NUMPAD_DIRECT_INPUT" : "INVARID_VALUE") << endl;
    } else if (EQ("use_date_conversion", name)) {
        cout << "use_date_conversion: " << BOOL_TO_STR(GET_CONFIG(use_date_conversion)) << endl;
    } else if (EQ("use_single_kanji_conversion", name)) {
        cout << "use_single_kanji_conversion: " << BOOL_TO_STR(GET_CONFIG(use_single_kanji_conversion)) << endl;
    } else if (EQ("use_symbol_conversion", name)) {
        cout << "use_symbol_conversion: " << BOOL_TO_STR(GET_CONFIG(use_symbol_conversion)) << endl;
    } else if (EQ("use_number_conversion", name)) {
        cout << "use_number_conversion: " << BOOL_TO_STR(GET_CONFIG(use_number_conversion)) << endl;
    } else if (EQ("use_history_suggest", name)) {
        cout << "use_history_suggest: " << BOOL_TO_STR(GET_CONFIG(use_history_suggest)) << endl;
    } else if (EQ("use_dictionary_suggest", name)) {
        cout << "use_dictionary_suggest: " << BOOL_TO_STR(GET_CONFIG(use_dictionary_suggest)) << endl;
    } else if (EQ("suggestions_size", name)) {
        cout << "suggestions_size: " << GET_CONFIG(suggestions_size) << endl;
    }
}

void set(char *name, char *value) {
    config::Config conf;
    config::ConfigHandler::GetConfig(&conf);

    map<string, bool> bools;
    bools["true"] = true;
    bools["false"] = false;

    if (EQ("config_version", name)) {
        cout << "config_version - " << "Must Not Change" << endl;
        return;
    } else if (EQ("last_modified_product_version", name)) {
        cout << "last_modified_product_version - " << "Must Not Change" << endl;
        return;
    } else if (EQ("last_modified_time", name)) {
        cout << "last_modified_time - " << "Must Not Change" << endl;
        return;
    } else if (EQ("platform", name)) {
        conf.set_platform(value);
    } else if (EQ("ui_locale", name)) {
        conf.set_ui_locale(value);
    } else if (EQ("verbose_level", name)) {
        conf.set_verbose_level(atoi(value));
    } else if (EQ("incognito_mode", name)) {
        if (bools.find(value) == bools.end()) return;
        conf.set_incognito_mode(bools[value]);
    } else if (EQ("check_default", name)) {
        if (bools.find(value) == bools.end()) return;
        conf.set_check_default(bools[value]);
    } else if (EQ("preedit_method", name)) {
        map <string, config::Config_PreeditMethod> vals;
        vals["KANA"]  = config::Config_PreeditMethod_KANA;
        vals["ROMAN"] = config::Config_PreeditMethod_ROMAN;
        if (vals.find(value) == vals.end()) return;
        conf.set_preedit_method(vals[value]);
    } else if (EQ("session_keymap", name)) {
        map <string, config::Config_SessionKeymap> vals;
        vals["NONE"]    = config::Config_SessionKeymap_NONE;
        vals["CUSTOM"]  = config::Config_SessionKeymap_CUSTOM;
        vals["ATOK"]    = config::Config_SessionKeymap_ATOK;
        vals["MSIME"]   = config::Config_SessionKeymap_MSIME;
        vals["KOTOERI"] = config::Config_SessionKeymap_KOTOERI;
        if (vals.find(value) == vals.end()) return;
        conf.set_session_keymap(vals[value]);
//    } else if (EQ("custom_keymap_table", name)) {
//        conf.set_custom_keymap_table();
//    } else if (EQ("custom_roman_table", name)) {
//        conf.set_custom_roman_table();
    } else if (EQ("punctuation_method", name)) {
        map <string, config::Config_PunctuationMethod> vals;
        vals["KUTEN_TOUTEN"] = config::Config_PunctuationMethod_KUTEN_TOUTEN;
        vals["COMMA_PERIOD"] = config::Config_PunctuationMethod_COMMA_PERIOD;
        vals["KUTEN_PERIOD"] = config::Config_PunctuationMethod_KUTEN_PERIOD;
        vals["COMMA_TOUTEN"] = config::Config_PunctuationMethod_COMMA_TOUTEN;
        if (vals.find(value) == vals.end()) return;
        conf.set_punctuation_method(vals[value]);
    } else if (EQ("symbol_method", name)) {
        map <string, config::Config_SymbolMethod> vals;
        vals["CORNER_BRACKET_MIDDLE_DOT"] = config::Config_SymbolMethod_CORNER_BRACKET_MIDDLE_DOT;
        vals["SQUARE_BRACKET_SLASH"]      = config::Config_SymbolMethod_SQUARE_BRACKET_SLASH;
        vals["CORNER_BRACKET_SLASH"]      = config::Config_SymbolMethod_CORNER_BRACKET_SLASH;
        vals["SQUARE_BRACKET_MIDDLE_DOT"] = config::Config_SymbolMethod_SQUARE_BRACKET_MIDDLE_DOT;
        if (vals.find(value) == vals.end()) return;
        conf.set_symbol_method(vals[value]);
    } else if (EQ("space_character_form", name)) {
        map <string, config::Config_FundamentalCharacterForm> vals;
        vals["FUNDAMENTAL_INPUT_MODE"] = config::Config_FundamentalCharacterForm_FUNDAMENTAL_INPUT_MODE;
        vals["FUNDAMENTAL_FULL_WIDTH"] = config::Config_FundamentalCharacterForm_FUNDAMENTAL_FULL_WIDTH;
        vals["FUNDAMENTAL_HALF_WIDTH"] = config::Config_FundamentalCharacterForm_FUNDAMENTAL_HALF_WIDTH;
        if (vals.find(value) == vals.end()) return;
        conf.set_space_character_form(vals[value]);
    } else if (EQ("history_learning_level", name)) {
        map <string, config::Config_HistoryLearningLevel> vals;
        vals["DEFAULT_HISTORY"] = config::Config_HistoryLearningLevel_DEFAULT_HISTORY;
        vals["READ_ONLY"]       = config::Config_HistoryLearningLevel_READ_ONLY;
        vals["NO_HISTORY"]      = config::Config_HistoryLearningLevel_NO_HISTORY;
        if (vals.find(value) == vals.end()) return;
        conf.set_history_learning_level(vals[value]);
    } else if (EQ("selection_shortcut", name)) {
        map <string, config::Config_SelectionShortcut> vals;
        vals["NO_SHORTCUT"]        = config::Config_SelectionShortcut_NO_SHORTCUT;
        vals["SHORTCUT_123456789"] = config::Config_SelectionShortcut_SHORTCUT_123456789;
        vals["SHORTCUT_ASDFGHJKL"] = config::Config_SelectionShortcut_SHORTCUT_ASDFGHJKL;
        if (vals.find(value) == vals.end()) return;
        conf.set_selection_shortcut(vals[value]);
//    } else if (EQ("character_form_rules", name)) {
//        conf.set_character_form_rules();
    } else if (EQ("use_auto_ime_turn_off", name)) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_auto_ime_turn_off(bools[value]);
    } else if (EQ("use_cascading_window", name)) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_cascading_window(bools[value]);
    } else if (EQ("shift_key_mode_switch", name)) {
        map<string, config::Config_ShiftKeyModeSwitch> vals;
        vals["OFF"]                 = config::Config_ShiftKeyModeSwitch_OFF;
        vals["ASCII_INPUT_MODE"]    = config::Config_ShiftKeyModeSwitch_ASCII_INPUT_MODE;
        vals["KATAKANA_INPUT_MODE"] = config::Config_ShiftKeyModeSwitch_KATAKANA_INPUT_MODE;
        if (vals.count(value) < 1) return;
        conf.set_shift_key_mode_switch(vals[value]);
    } else if (EQ("numpad_character_form", name)) {
        map<string, config::Config_NumpadCharacterForm> vals;
        vals["NUMPAD_INPUT_MODE"]   = config::Config_NumpadCharacterForm_NUMPAD_INPUT_MODE;
        vals["NUMPAD_FULL_WIDTH"]   = config::Config_NumpadCharacterForm_NUMPAD_FULL_WIDTH;
        vals["NUMPAD_HALF_WIDTH"]   = config::Config_NumpadCharacterForm_NUMPAD_HALF_WIDTH;
        vals["NUMPAD_DIRECT_INPUT"] = config::Config_NumpadCharacterForm_NUMPAD_DIRECT_INPUT;
        if (vals.find(value) == vals.end()) return;
        conf.set_numpad_character_form(vals[value]);
    } else if (EQ("use_date_conversion", name)) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_date_conversion(bools[value]);
    } else if (EQ("use_single_kanji_conversion", name)) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_single_kanji_conversion(bools[value]);
    } else if (EQ("use_symbol_conversion", name)) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_symbol_conversion(bools[value]);
    } else if (EQ("use_number_conversion", name)) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_number_conversion(bools[value]);
    } else if (EQ("use_history_suggest", name)) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_history_suggest(bools[value]);
    } else if (EQ("use_dictionary_suggest", name)) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_dictionary_suggest(bools[value]);
    } else if (EQ("suggestions_size", name)) {
        conf.set_suggestions_size(atol(value));
    } else {
        return;
    }

    config::ConfigHandler::SetConfig(conf);
}

void clear(char *name) {
    config::Config conf;

    config::ConfigHandler::GetConfig(&conf);

    if (EQ("config_version", name)) {
        cout << "config_version - " << "Must Not Change" << endl;
        return;
    } else if (EQ("last_modified_product_version", name)) {
        cout << "last_modified_product_version - " << "Must Not Change" << endl;
        return;
    } else if (EQ("last_modified_time", name)) {
        cout << "last_modified_time - " << "Must Not Change" << endl;
        return;
    } else if (EQ("platform", name)) {
        cout << "platform - " << "Must Not Change" << endl;
        return;
    } else if (EQ("ui_locale", name)) {
        conf.clear_ui_locale();
    } else if (EQ("verbose_level", name)) {
        conf.clear_verbose_level();
    } else if (EQ("incognito_mode", name)) {
        conf.clear_incognito_mode();
    } else if (EQ("check_default", name)) {
        conf.clear_check_default();
    } else if (EQ("preedit_method", name)) {
        conf.clear_preedit_method();
    } else if (EQ("session_keymap", name)) {
        cout << "session_keymap - " << "Must Not Change" << endl;
        return;
    } else if (EQ("custom_keymap_table", name)) {
        conf.clear_custom_keymap_table();
    } else if (EQ("custom_roman_table", name)) {
        conf.clear_custom_roman_table();
    } else if (EQ("punctuation_method", name)) {
        conf.clear_punctuation_method();
    } else if (EQ("symbol_method", name)) {
        conf.clear_symbol_method();
    } else if (EQ("space_character_form", name)) {
        conf.clear_space_character_form();
    } else if (EQ("history_learning_level", name)) {
        conf.clear_history_learning_level();
    } else if (EQ("selection_shortcut", name)) {
        conf.clear_selection_shortcut();
    } else if (EQ("character_form_rules", name)) {
        conf.clear_character_form_rules();
    } else if (EQ("use_auto_ime_turn_off", name)) {
        conf.clear_use_auto_ime_turn_off();
    } else if (EQ("use_cascading_window", name)) {
        conf.clear_use_cascading_window();
    } else if (EQ("shift_key_mode_switch", name)) {
        conf.clear_shift_key_mode_switch();
    } else if (EQ("numpad_character_form", name)) {
        conf.clear_numpad_character_form();
    } else if (EQ("use_date_conversion", name)) {
        conf.clear_use_date_conversion();
    } else if (EQ("use_single_kanji_conversion", name)) {
        conf.clear_use_single_kanji_conversion();
    } else if (EQ("use_symbol_conversion", name)) {
        conf.clear_use_symbol_conversion();
    } else if (EQ("use_number_conversion", name)) {
        conf.clear_use_number_conversion();
    } else if (EQ("use_history_suggest", name)) {
        conf.clear_use_history_suggest();
    } else if (EQ("use_dictionary_suggest", name)) {
        conf.clear_use_dictionary_suggest();
    } else if (EQ("suggestions_size", name)) {
        conf.clear_suggestions_size();
    } else {
        return;
    }

    config::ConfigHandler::SetConfig(conf);
}

void print_all() {
    string names[] = {
        "config_version",
        "last_modified_product_version",
        "last_modified_time",
        "platform",
        "ui_locale",
        "verbose_level",
//        "DEPRECATED_log_all_commands",
        "incognito_mode",
//        "DEPRECATED_upload_usage_stats",
        "check_default",
        "preedit_method",
        "session_keymap",
        "custom_keymap_table",
        "custom_roman_table",
        "punctuation_method",
        "symbol_method",
        "space_character_form",
        "history_learning_level",
        "selection_shortcut",
        "character_form_rules",
        "use_auto_ime_turn_off",
        "use_cascading_window",
        "shift_key_mode_switch",
        "numpad_character_form",
        "use_date_conversion",
        "use_single_kanji_conversion",
        "use_symbol_conversion",
        "use_number_conversion",
        "use_history_suggest",
        "use_dictionary_suggest",
        "suggestions_size",
        ""
    };

    for (int i = 0; names[i] != ""; i++)
        get((char *)names[i].c_str());
}

void print_modifier() {
    config::Config conf;

    config::ConfigHandler::GetConfig(&conf);
    cout << conf.DebugString();
}

void print_help() {
    cout << "mozc-config [ -h | -a | -m | -g <NAME> | -s <NAME> <VALUE> | -c <NAME> ]" << endl;
    cout << "    -h                - ヘルプを表示する" << endl;
    cout << "    -a                - すべてのプロパティを表示する" << endl;
    cout << "    -m                - 変更されたプロパティを表示する" << endl;
    cout << "    -g <NAME>         - <NAME> プロパティを表示する" << endl;
    cout << "    -s <NAME> <VALUE> - <NAME> プロパティに <VALUE> 値をセットする" << endl;
    cout << "    -c <NAME>         - <NAME> プロパティをクリアする" << endl;
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        print_help();
        return -1;
    }

    if (EQ(argv[1], "-a")) {
        print_all();
    } else if (EQ(argv[1], "-m")) {
        print_modifier();
    } else if (EQ(argv[1], "-g")) {
        if (argc > 2)
            get(argv[2]);
    } else if (EQ(argv[1], "-s")) {
        if (argc > 3)
            set(argv[2], argv[3]);
    } else if (EQ(argv[1], "-c")) {
        if (argc > 2)
            clear(argv[2]);
    } else if (EQ(argv[1], "-h")) {
        print_help();
        return -1;
    }

    return 0;
}
