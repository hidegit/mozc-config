#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

#include "session/config.pb.h"
#include "session/config_handler.h"

using namespace mozc;
using namespace config;

#define BOOL_TO_STR(b)  (b ? "true" : "false")
#define QUOTED_STR(s)   "\"" << s << "\""

int atoi(string s) {
    return atoi(s.c_str());
}

int atol(string s) {
    return atol(s.c_str());
}

void get(string name) {
    if ("config_version" == name) {
        cout << "config_version: " << GET_CONFIG(config_version) << endl;
    } else if ("last_modified_product_version" == name) {
        cout << "last_modified_product_version: " << QUOTED_STR(GET_CONFIG(last_modified_product_version)) << endl;
    } else if ("last_modified_time" == name) {
        cout << "last_modified_time: " << GET_CONFIG(last_modified_time) << endl;
    } else if ("platform" == name) {
        cout << "platform: " << QUOTED_STR(GET_CONFIG(platform)) << endl;
    } else if ("ui_locale" == name) {
        cout << "ui_locale: " << QUOTED_STR(GET_CONFIG(ui_locale)) << endl;
    } else if ("verbose_level" == name) {
        cout << "verbose_level: " << GET_CONFIG(verbose_level) << endl;
    } else if ("incognito_mode" == name) {
        cout << "incognito_mode: " << BOOL_TO_STR(GET_CONFIG(incognito_mode)) << endl;
    } else if ("check_default" == name) {
        cout << "check_default: " << BOOL_TO_STR(GET_CONFIG(check_default)) << endl;
    } else if ("preedit_method" == name) {
        int i = GET_CONFIG(preedit_method);
        cout << "preedit_method: "
             << ((i == 0) ? "ROMAN" :
                 (i == 1) ? "KANA" : "INVARID_VALUE") << endl;
    } else if ("session_keymap" == name) {
        int i = GET_CONFIG(session_keymap);
        cout << "session_keymap: "
             << ((i ==-1) ? "NONE" :
                 (i == 0) ? "CUSTOM" :
                 (i == 1) ? "ATOK" :
                 (i == 2) ? "MSIME" :
                 (i == 3) ? "KOTOERI" : "INVARID_VALUE") << endl;
    } else if ("custom_keymap_table" == name) {
        cout << "custom_keymap_table: " << QUOTED_STR(GET_CONFIG(custom_keymap_table)) << endl;
    } else if ("custom_roman_table" == name) {
        cout << "custom_roman_table: " << QUOTED_STR(GET_CONFIG(custom_roman_table)) << endl;
    } else if ("punctuation_method" == name) {
        int i = GET_CONFIG(punctuation_method);
        cout << "punctuation_method: "
             << ((i == 0) ? "KUTEN_TOUTEN" :
                 (i == 1) ? "COMMA_PERIOD" :
                 (i == 2) ? "KUTEN_PERIOD" :
                 (i == 3) ? "COMMA_TOUTEN" : "INVARID_VALUE") << endl;
    } else if ("symbol_method" == name) {
        int i = GET_CONFIG(symbol_method);
        cout << "symbol_method: "
             << ((i == 0) ? "CORNER_BRACKET_MIDDLE_DOT" :
                 (i == 1) ? "SQUARE_BRACKET_SLASH" :
                 (i == 2) ? "CORNER_BRACKET_SLASH" :
                 (i == 3) ? "SQUARE_BRACKET_MIDDLE_DOT" : "INVARID_VALUE") << endl;
    } else if ("space_character_form" == name) {
        int i = GET_CONFIG(space_character_form);
        cout << "space_character_form: "
             << ((i == 0) ? "FUNDAMENTAL_INPUT_MODE" :
                 (i == 1) ? "FUNDAMENTAL_FULL_WIDTH" :
                 (i == 2) ? "FUNDAMENTAL_HALF_WIDTH" : "INVARID_VALUE") << endl;
    } else if ("history_learning_level" == name) {
        int i = GET_CONFIG(history_learning_level);
        cout << "history_learning_level: "
             << ((i == 0) ? "DEFAULT_HISTORY" :
                 (i == 1) ? "READ_ONLY" :
                 (i == 2) ? "NO_HISTORY" : "INVARID_VALUE") << endl;
    } else if ("selection_shortcut" == name) {
        int i = GET_CONFIG(selection_shortcut);
        cout << "selection_shortcut: "
             << ((i == 0) ? "NO_SHORTCUT" :
                 (i == 1) ? "SHORTCUT_123456789" :
                 (i == 2) ? "SHORTCUT_ASDFGHJKL" : "INVARID_VALUE") << endl;
//    } else if ("character_form_rules" == name) {
//        cout << "character_form_rules: " << GET_CONFIG(character_form_rules) << endl;
    } else if ("use_auto_ime_turn_off" == name) {
        cout << "use_auto_ime_turn_off: " << BOOL_TO_STR(GET_CONFIG(use_auto_ime_turn_off)) << endl;
    } else if ("use_cascading_window" == name) {
        cout << "use_cascading_window: " << BOOL_TO_STR(GET_CONFIG(use_cascading_window)) << endl;
    } else if ("shift_key_mode_switch" == name) {
        int i = GET_CONFIG(shift_key_mode_switch);
        cout << "shift_key_mode_switch: "
             << ((i == 0) ? "OFF" :
                 (i == 1) ? "ASCII_INPUT_MODE" :
                 (i == 2) ? "KATAKANA_INPUT_MODE" : "INVARID_VALUE") << endl;
    } else if ("numpad_character_form" == name) {
        int i = GET_CONFIG(numpad_character_form);
        cout << "numpad_character_form: "
             << ((i == 0) ? "NUMPAD_INPUT_MODE" :
                 (i == 1) ? "NUMPAD_FULL_WIDTH" :
                 (i == 2) ? "NUMPAD_HALF_WIDTH" :
                 (i == 3) ? "NUMPAD_DIRECT_INPUT" : "INVARID_VALUE") << endl;
    } else if ("use_date_conversion" == name) {
        cout << "use_date_conversion: " << BOOL_TO_STR(GET_CONFIG(use_date_conversion)) << endl;
    } else if ("use_single_kanji_conversion" == name) {
        cout << "use_single_kanji_conversion: " << BOOL_TO_STR(GET_CONFIG(use_single_kanji_conversion)) << endl;
    } else if ("use_symbol_conversion" == name) {
        cout << "use_symbol_conversion: " << BOOL_TO_STR(GET_CONFIG(use_symbol_conversion)) << endl;
    } else if ("use_number_conversion" == name) {
        cout << "use_number_conversion: " << BOOL_TO_STR(GET_CONFIG(use_number_conversion)) << endl;
    } else if ("use_history_suggest" == name) {
        cout << "use_history_suggest: " << BOOL_TO_STR(GET_CONFIG(use_history_suggest)) << endl;
    } else if ("use_dictionary_suggest" == name) {
        cout << "use_dictionary_suggest: " << BOOL_TO_STR(GET_CONFIG(use_dictionary_suggest)) << endl;
    } else if ("suggestions_size" == name) {
        cout << "suggestions_size: " << GET_CONFIG(suggestions_size) << endl;
    }
}

void set(string name, string value) {
    Config conf;
    ConfigHandler::GetConfig(&conf);

    map<string, bool> bools;
    bools["true"] = true;
    bools["false"] = false;

    if ("config_version" == name) {
        cout << "config_version - " << "Must Not Change" << endl;
        return;
    } else if ("last_modified_product_version" == name) {
        cout << "last_modified_product_version - " << "Must Not Change" << endl;
        return;
    } else if ("last_modified_time" == name) {
        cout << "last_modified_time - " << "Must Not Change" << endl;
        return;
    } else if ("platform" == name) {
        conf.set_platform(value);
    } else if ("ui_locale" == name) {
        conf.set_ui_locale(value);
    } else if ("verbose_level" == name) {
        conf.set_verbose_level(atoi(value));
    } else if ("incognito_mode" == name) {
        if (bools.find(value) == bools.end()) return;
        conf.set_incognito_mode(bools[value]);
    } else if ("check_default" == name) {
        if (bools.find(value) == bools.end()) return;
        conf.set_check_default(bools[value]);
    } else if ("preedit_method" == name) {
        map <string, Config_PreeditMethod> vals;
        vals["KANA"]  = Config_PreeditMethod_KANA;
        vals["ROMAN"] = Config_PreeditMethod_ROMAN;
        if (vals.find(value) == vals.end()) return;
        conf.set_preedit_method(vals[value]);
    } else if ("session_keymap" == name) {
        map <string, Config_SessionKeymap> vals;
        vals["NONE"]    = Config_SessionKeymap_NONE;
        vals["CUSTOM"]  = Config_SessionKeymap_CUSTOM;
        vals["ATOK"]    = Config_SessionKeymap_ATOK;
        vals["MSIME"]   = Config_SessionKeymap_MSIME;
        vals["KOTOERI"] = Config_SessionKeymap_KOTOERI;
        if (vals.find(value) == vals.end()) return;
        conf.set_session_keymap(vals[value]);
//    } else if ("custom_keymap_table" == name) {
//        conf.set_custom_keymap_table();
//    } else if ("custom_roman_table" == name) {
//        conf.set_custom_roman_table();
    } else if ("punctuation_method" == name) {
        map <string, Config_PunctuationMethod> vals;
        vals["KUTEN_TOUTEN"] = Config_PunctuationMethod_KUTEN_TOUTEN;
        vals["COMMA_PERIOD"] = Config_PunctuationMethod_COMMA_PERIOD;
        vals["KUTEN_PERIOD"] = Config_PunctuationMethod_KUTEN_PERIOD;
        vals["COMMA_TOUTEN"] = Config_PunctuationMethod_COMMA_TOUTEN;
        if (vals.find(value) == vals.end()) return;
        conf.set_punctuation_method(vals[value]);
    } else if ("symbol_method" == name) {
        map <string, Config_SymbolMethod> vals;
        vals["CORNER_BRACKET_MIDDLE_DOT"] = Config_SymbolMethod_CORNER_BRACKET_MIDDLE_DOT;
        vals["SQUARE_BRACKET_SLASH"]      = Config_SymbolMethod_SQUARE_BRACKET_SLASH;
        vals["CORNER_BRACKET_SLASH"]      = Config_SymbolMethod_CORNER_BRACKET_SLASH;
        vals["SQUARE_BRACKET_MIDDLE_DOT"] = Config_SymbolMethod_SQUARE_BRACKET_MIDDLE_DOT;
        if (vals.find(value) == vals.end()) return;
        conf.set_symbol_method(vals[value]);
    } else if ("space_character_form" == name) {
        map <string, Config_FundamentalCharacterForm> vals;
        vals["FUNDAMENTAL_INPUT_MODE"] = Config_FundamentalCharacterForm_FUNDAMENTAL_INPUT_MODE;
        vals["FUNDAMENTAL_FULL_WIDTH"] = Config_FundamentalCharacterForm_FUNDAMENTAL_FULL_WIDTH;
        vals["FUNDAMENTAL_HALF_WIDTH"] = Config_FundamentalCharacterForm_FUNDAMENTAL_HALF_WIDTH;
        if (vals.find(value) == vals.end()) return;
        conf.set_space_character_form(vals[value]);
    } else if ("history_learning_level" == name) {
        map <string, Config_HistoryLearningLevel> vals;
        vals["DEFAULT_HISTORY"] = Config_HistoryLearningLevel_DEFAULT_HISTORY;
        vals["READ_ONLY"]       = Config_HistoryLearningLevel_READ_ONLY;
        vals["NO_HISTORY"]      = Config_HistoryLearningLevel_NO_HISTORY;
        if (vals.find(value) == vals.end()) return;
        conf.set_history_learning_level(vals[value]);
    } else if ("selection_shortcut" == name) {
        map <string, Config_SelectionShortcut> vals;
        vals["NO_SHORTCUT"]        = Config_SelectionShortcut_NO_SHORTCUT;
        vals["SHORTCUT_123456789"] = Config_SelectionShortcut_SHORTCUT_123456789;
        vals["SHORTCUT_ASDFGHJKL"] = Config_SelectionShortcut_SHORTCUT_ASDFGHJKL;
        if (vals.find(value) == vals.end()) return;
        conf.set_selection_shortcut(vals[value]);
//    } else if ("character_form_rules" == name) {
//        conf.set_character_form_rules();
    } else if ("use_auto_ime_turn_off" == name) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_auto_ime_turn_off(bools[value]);
    } else if ("use_cascading_window" == name) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_cascading_window(bools[value]);
    } else if ("shift_key_mode_switch" == name) {
        map<string, Config_ShiftKeyModeSwitch> vals;
        vals["OFF"]                 = Config_ShiftKeyModeSwitch_OFF;
        vals["ASCII_INPUT_MODE"]    = Config_ShiftKeyModeSwitch_ASCII_INPUT_MODE;
        vals["KATAKANA_INPUT_MODE"] = Config_ShiftKeyModeSwitch_KATAKANA_INPUT_MODE;
        if (vals.count(value) < 1) return;
        conf.set_shift_key_mode_switch(vals[value]);
    } else if ("numpad_character_form" == name) {
        map<string, Config_NumpadCharacterForm> vals;
        vals["NUMPAD_INPUT_MODE"]   = Config_NumpadCharacterForm_NUMPAD_INPUT_MODE;
        vals["NUMPAD_FULL_WIDTH"]   = Config_NumpadCharacterForm_NUMPAD_FULL_WIDTH;
        vals["NUMPAD_HALF_WIDTH"]   = Config_NumpadCharacterForm_NUMPAD_HALF_WIDTH;
        vals["NUMPAD_DIRECT_INPUT"] = Config_NumpadCharacterForm_NUMPAD_DIRECT_INPUT;
        if (vals.find(value) == vals.end()) return;
        conf.set_numpad_character_form(vals[value]);
    } else if ("use_date_conversion" == name) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_date_conversion(bools[value]);
    } else if ("use_single_kanji_conversion" == name) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_single_kanji_conversion(bools[value]);
    } else if ("use_symbol_conversion" == name) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_symbol_conversion(bools[value]);
    } else if ("use_number_conversion" == name) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_number_conversion(bools[value]);
    } else if ("use_history_suggest" == name) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_history_suggest(bools[value]);
    } else if ("use_dictionary_suggest" == name) {
        if (bools.find(value) == bools.end()) return;
        conf.set_use_dictionary_suggest(bools[value]);
    } else if ("suggestions_size" == name) {
        conf.set_suggestions_size(atol(value));
    } else {
        return;
    }

    ConfigHandler::SetConfig(conf);
}

void clear(string name) {
    Config conf;

    ConfigHandler::GetConfig(&conf);

    if ("config_version" == name) {
        cout << "config_version - " << "Must Not Change" << endl;
        return;
    } else if ("last_modified_product_version" == name) {
        cout << "last_modified_product_version - " << "Must Not Change" << endl;
        return;
    } else if ("last_modified_time" == name) {
        cout << "last_modified_time - " << "Must Not Change" << endl;
        return;
    } else if ("platform" == name) {
        cout << "platform - " << "Must Not Change" << endl;
        return;
    } else if ("ui_locale" == name) {
        conf.clear_ui_locale();
    } else if ("verbose_level" == name) {
        conf.clear_verbose_level();
    } else if ("incognito_mode" == name) {
        conf.clear_incognito_mode();
    } else if ("check_default" == name) {
        conf.clear_check_default();
    } else if ("preedit_method" == name) {
        conf.clear_preedit_method();
    } else if ("session_keymap" == name) {
        cout << "session_keymap - " << "Must Not Change" << endl;
        return;
    } else if ("custom_keymap_table" == name) {
        conf.clear_custom_keymap_table();
    } else if ("custom_roman_table" == name) {
        conf.clear_custom_roman_table();
    } else if ("punctuation_method" == name) {
        conf.clear_punctuation_method();
    } else if ("symbol_method" == name) {
        conf.clear_symbol_method();
    } else if ("space_character_form" == name) {
        conf.clear_space_character_form();
    } else if ("history_learning_level" == name) {
        conf.clear_history_learning_level();
    } else if ("selection_shortcut" == name) {
        conf.clear_selection_shortcut();
    } else if ("character_form_rules" == name) {
        conf.clear_character_form_rules();
    } else if ("use_auto_ime_turn_off" == name) {
        conf.clear_use_auto_ime_turn_off();
    } else if ("use_cascading_window" == name) {
        conf.clear_use_cascading_window();
    } else if ("shift_key_mode_switch" == name) {
        conf.clear_shift_key_mode_switch();
    } else if ("numpad_character_form" == name) {
        conf.clear_numpad_character_form();
    } else if ("use_date_conversion" == name) {
        conf.clear_use_date_conversion();
    } else if ("use_single_kanji_conversion" == name) {
        conf.clear_use_single_kanji_conversion();
    } else if ("use_symbol_conversion" == name) {
        conf.clear_use_symbol_conversion();
    } else if ("use_number_conversion" == name) {
        conf.clear_use_number_conversion();
    } else if ("use_history_suggest" == name) {
        conf.clear_use_history_suggest();
    } else if ("use_dictionary_suggest" == name) {
        conf.clear_use_dictionary_suggest();
    } else if ("suggestions_size" == name) {
        conf.clear_suggestions_size();
    } else {
        return;
    }

    ConfigHandler::SetConfig(conf);
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
        get(names[i]);
}

void print_modifier() {
    Config conf;

    ConfigHandler::GetConfig(&conf);
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

    string flg = argv[1];

    if (flg == "-a") {
        print_all();
    } else if (flg == "-m") {
        print_modifier();
    } else if (flg == "-g") {
        if (argc > 2)
            get((string)argv[2]);
    } else if (flg == "-s") {
        if (argc > 3)
            set((string)argv[2], (string)argv[3]);
    } else if (flg == "-c") {
        if (argc > 2)
            clear((string)argv[2]);
    } else if (flg == "-h") {
        print_help();
        return -1;
    }

    return 0;
}
