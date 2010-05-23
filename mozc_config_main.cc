// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <unistd.h>

using namespace std;

#include "session/config.pb.h"
#include "session/config_handler.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"

int atoi(string s) {
    return atoi(s.c_str());
}

int atol(string s) {
    return atol(s.c_str());
}

bool is_bool_str(string value) {
    return (value == "true" || value == "false") ? true : false;
}

bool is_num_str(string value) {
    const char* s = value.c_str();

    for (int i = 0; i < value.length(); i++)
        if (s[i] < '0' || '9' < s[i]) return false;

    return true;
}

bool is_ignore(string name) {
    const string ignores[] = {
        "config_version",
        "last_modified_product_version",
        "last_modified_time",
        "DEPRECATED_log_all_commands",
        "DEPRECATED_upload_usage_stats",
        ""
    };

    for (int i = 0; ignores[i] != ""; i++)
        if (name == ignores[i]) return true;

    return false;
}

void debug_str_to_name(string& s) {
    string list[][2] = {
        {"\"\\343\\202\\242\"", "KATAKANA"},
        {"\"A\"", "ALPHABET"},
        {"\"0\"", "NUMBER"},
        {"\\343\\200\\202\\343\\200\\201", "。、"},
        {"\\343\\203\\273\\343\\200\\214\\343\\200\\215", "・「」"},
        {"", ""}
    };
    string::size_type pos;
    for (int i = 0; list[i][0] != ""; i++) {
        pos = s.find(list[i][0]);
        if (pos != string::npos) {
            s.replace(pos, list[i][0].length(), list[i][1]);
        }
    }
}

void group_to_inner(string& s) {
    string list[][2] = {
        {"KATAKANA", "ア"},
        {"ALPHABET", "A"},
        {"NUMBER", "0"},
        {"", ""},
    };
    string::size_type pos;
    for (int i = 0; list[i][0] != ""; i++) {
        pos = s.find(list[i][0]);
        if (pos != string::npos) {
            s.replace(pos, list[i][0].length(), list[i][1]);
        }
    }
}

void get(string name) {
    mozc::config::Config conf;
    mozc::config::ConfigHandler::GetConfig(&conf);

    const google::protobuf::FieldDescriptor* field =
            mozc::config::Config::descriptor()->FindFieldByName(name);
    const google::protobuf::Reflection* ref = conf.GetReflection();

    if (field == NULL) return;

    stringstream value;

    value << name << ": ";

    const int type = field->type();
    if (type == 4) {
        value << ref->GetUInt64(conf, field);
    } else if (type == 5) {
        value << ref->GetInt32(conf, field);
    } else if (type == 8) {
        value << (ref->GetBool(conf, field) ? "true" : "false");
    } else if (type == 9) {
        value << "\"" << ref->GetString(conf, field) << "\"";
    } else if (type == 11 && name == "character_form_rules") {
        if (conf.character_form_rules_size() <= 0)
            mozc::config::ConfigHandler::GetDefaultConfig(&conf);
        value.clear();
        for (int i = 0; i < conf.character_form_rules_size(); i++) {
            const mozc::config::Config_CharacterFormRule& rule =
                    conf.character_form_rules(i);
            value << name << " {" << endl;
            istringstream is(rule.DebugString());
            string s;
            while (getline(is, s)) {
                debug_str_to_name(s);
                value << "  " << s << endl;
            }
            value << "}" << endl;
        }
    } else if (type == 12) {
        value << "\"" << ref->GetString(conf, field) << "\"";
    } else if (type == 13) {
        value << ref->GetUInt32(conf, field);
    } else if (type == 14) {
        value << ref->GetEnum(conf, field)->name();
    } else {
        value << "/* Not Impl Error!! */";
    }
    cout << value.str();
    if (type != 11)
        cout << endl;
}

void set_character_form_rules(string name, string group, string preedit, string conversion) {
    mozc::config::Config conf = mozc::config::ConfigHandler::GetConfig();

    const google::protobuf::FieldDescriptor* field =
            mozc::config::Config::descriptor()->FindFieldByName(name);
    const google::protobuf::Reflection* ref = conf.GetReflection();

    if (field == NULL) return;

    if (field->type() != 11 || name != "character_form_rules") return;

    group_to_inner(group);

    mozc::config::Config conf2;
    mozc::config::ConfigHandler::GetDefaultConfig(&conf2);

    for (int i = 0; i < conf2.character_form_rules_size(); i++) {
        const mozc::config::Config_CharacterFormRule& rule2 =
                conf2.character_form_rules(i);

        mozc::config::Config_CharacterFormRule* rule;
        if (i >= conf.character_form_rules_size()) {
            rule = conf.add_character_form_rules();
            rule->CopyFrom(rule2);
        } else {
            rule = conf.mutable_character_form_rules(i);
        }

        if (rule->group() == group) {
            const google::protobuf::Descriptor* rule_desc =
                    rule->GetDescriptor();
            const google::protobuf::Reflection* rule_ref =
                    rule->GetReflection();

            const google::protobuf::FieldDescriptor* field1 =
                   rule_desc->FindFieldByName("preedit_character_form");
            const google::protobuf::EnumValueDescriptor* desc1 =
                    field1->enum_type()->FindValueByName(preedit);
            if (desc1 == NULL) return;

            const google::protobuf::FieldDescriptor* field2 =
                   rule_desc->FindFieldByName("conversion_character_form");
            const google::protobuf::EnumValueDescriptor* desc2 =
                    field2->enum_type()->FindValueByName(conversion);
            if (desc2 == NULL) return;

            rule_ref->SetEnum(rule, field1, desc1);
            rule_ref->SetEnum(rule, field2, desc2);
        }
    }

    mozc::config::ConfigHandler::SetConfig(conf);
}

void set(string name, string value) {
    if (is_ignore(name)) return;

    mozc::config::Config conf;
    mozc::config::ConfigHandler::GetConfig(&conf);

    const google::protobuf::FieldDescriptor* field =
            mozc::config::Config::descriptor()->FindFieldByName(name);
    const google::protobuf::Reflection* ref = conf.GetReflection();

    if (field == NULL) return;

    const int type = field->type();
    if (type == 4) {
        if (!is_num_str(value)) return;
        ref->SetUInt64(&conf, field, atol(value));
    } else if (type == 5) {
        if (!is_num_str(value)) return;
        ref->SetInt32(&conf, field, atoi(value));
    } else if (type == 8) {
        if (!is_bool_str(value)) return;
        ref->SetBool(&conf, field, (value == "true") ? true : false);
    } else if (type == 9) {
        ref->SetString(&conf, field, value);
    } else if (type == 12) {
        ref->SetString(&conf, field, value);
    } else if (type == 13) {
        if (!is_num_str(value)) return;
        ref->SetUInt32(&conf, field, atol(value));
    } else if (type == 14) {
        const google::protobuf::EnumValueDescriptor* enum_value_desc =
                field->enum_type()->FindValueByName(value);
        if (enum_value_desc == NULL) return;
        ref->SetEnum(&conf, field, enum_value_desc);
    } else {
        cout << "/* Not Impl Error!! */" << endl;
        return;
    }

    mozc::config::ConfigHandler::SetConfig(conf);
}

void clear(string name) {
    if (is_ignore(name)) return;

//    mozc::config::Config conf;
  //  mozc::config::ConfigHandler::GetConfig(&conf);

    mozc::config::Config conf = mozc::config::ConfigHandler::GetConfig();

    const google::protobuf::FieldDescriptor* field =
            conf.GetDescriptor()->FindFieldByName(name);
//            mozc::config::Config::descriptor()->FindFieldByName(name);

    if (field == NULL) return;

    conf.GetReflection()->ClearField(&conf, field);

    mozc::config::ConfigHandler::SetConfig(conf);
}

int reboot() {
    const char *path = "/usr/bin/ibus-daemon";
    char *const argv[] = {
        (char *)"/usr/bin/ibus-daemon",
        (char *)"-xrd",
        (char *)NULL
    };

    return execv(path, argv);
}

void print_modifier() {
    mozc::config::Config conf;

    mozc::config::ConfigHandler::GetConfig(&conf);

    istringstream is(conf.DebugString());

    string s;
    while (getline(is, s)) {
        debug_str_to_name(s);
        cout << s << endl;
    }
}

void print_all() {
//    mozc::config::Config conf;
//    mozc::config::ConfigHandler::GetConfig(&conf);

    mozc::config::Config conf = mozc::config::ConfigHandler::GetConfig();

    const google::protobuf::Descriptor* desc = conf.GetDescriptor();//mozc::config::Config::descriptor();
    const google::protobuf::Reflection* ref = conf.GetReflection();

    for (int i = 0; i < desc->field_count(); i++) {
        const google::protobuf::FieldDescriptor* field = desc->field(i);
        const string name = field->name();

        stringstream value;

        value << name << ": ";

        const int type = field->type();
        if (type == 4) {
            value << ref->GetUInt64(conf, field);
        } else if (type == 5) {
            value << ref->GetInt32(conf, field);
        } else if (type == 8) {
            value << (ref->GetBool(conf, field) ? "true" : "false");
        } else if (type == 9) {
            value << "\"" << ref->GetString(conf, field) << "\"";
        } else if (type == 11 && name == "character_form_rules") {
            value.clear();
            mozc::config::Config conf2;
            if (conf.character_form_rules_size() > 0)
                conf2 = conf;
            else
                mozc::config::ConfigHandler::GetDefaultConfig(&conf2);

            for (int i = 0; i < conf2.character_form_rules_size(); i++) {
                const ::mozc::config::Config_CharacterFormRule& rule =
                        conf2.character_form_rules(i);

                value << name << " {" << endl;
                istringstream is(rule.DebugString());
                string s;
                while (getline(is, s)) {
                    debug_str_to_name(s);
                    value << "  " << s << endl;
                }
                value << "}" << endl;
            }
        } else if (type == 12) {
            value << "\"" << ref->GetString(conf, field) << "\"";
        } else if (type == 13) {
            value << ref->GetUInt32(conf, field);
        } else if (type == 14) {
            value << ref->GetEnum(conf, field)->name();
        } else {
            value << "/* Not Impl Error!! */";
        }
        cout << value.str();
        if (type != 11) cout << endl;
    }
}

void print_help() {
    cout << "Usage:" << endl;
    cout << "    mozc-config [ -h | -a | -m | -g <NAME> | -s <NAME> <VALUE> | -c <NAME> ]" << endl;
    cout << "        -h                - ヘルプを表示する" << endl;
    cout << "        -a                - すべてのプロパティを表示する" << endl;
    cout << "        -m                - 変更されたプロパティを表示する" << endl;
    cout << "        -g <NAME>         - <NAME> プロパティを表示する" << endl;
    cout << "        -s <NAME> <VALUE> - <NAME> プロパティに <VALUE> 値をセットする" << endl;
    cout << "        -c <NAME>         - <NAME> プロパティをクリアする" << endl;
    cout << "        -r                - 強制的に再起動する" << endl;
    cout << endl;
    cout << "Properties:" << endl;
    cout << "    config_version = <uint32 default=0>" << endl;
    cout << "        設定DBのバージョン - 自動設定" << endl;
    cout << "    last_modified_product_version = <string default=\"0.0.0.0\">" << endl;
    cout << "        バージョン - 自動設定" << endl;
    cout << "    last_modified_time = <uint64 default=0>" << endl;
    cout << "        最終変更日時 - 自動設定" << endl;
    cout << "    platform = <string default=\"\">" << endl;
    cout << "        プラットフォーム名" << endl;
    cout << "    ui_locale = <string default=\"\">" << endl;
    cout << "        UIのロケール" << endl;
    cout << "    verbose_level = <int32 default=0>" << endl;
    cout << "        ログレベル" << endl;
    cout << "    DEPRECATED_log_all_commands = <bool default=false>" << endl;
    cout << "        無効値" << endl;
    cout << "    incognito_mode = <bool default=false>" << endl;
    cout << "        詳細不明" << endl;
    cout << "    DEPRECATED_upload_usage_stats = <bool default=false>" << endl;
    cout << "        無効値" << endl;
    cout << "    check_default = <bool default=true>" << endl;
    cout << "        詳細不明" << endl;
    cout << "    preedit_method = <enum default=ROMAN>" << endl;
    cout << "        ROMAN - ローマ字入力" << endl;
    cout << "        KANA  - かな入力" << endl;
    cout << "    session_keymap = <enum default=NONE>" << endl;
    cout << "        NONE    - 無効" << endl;
    cout << "        CUSTOM  - カスタムキーマップ" << endl;
    cout << "        ATOK    - ATOKスタイル" << endl;
    cout << "        MSIME   - MSIMEスタイル" << endl;
    cout << "        KOTOERI - ことえりスタイル" << endl;
    cout << "    custom_keymap_table = <bytes>" << endl;
    cout << "        キーマップテーブル - 詳細不明" << endl;
    cout << "    custom_roman_table = <bytes>" << endl;
    cout << "        ローマ字テーブル - 詳細不明" << endl;
    cout << "    punctuation_method = <enum default=KUTEN_TOUTEN>" << endl;
    cout << "        KUTEN_TOUTEN - 「、」「。」の組み合わせ" << endl;
    cout << "        COMMA_PERIOD - 「，」「．」" << endl;
    cout << "        KUTEN_PERIOD - 「、」「．」" << endl;
    cout << "        COMMA_TOUTEN - 「，」「。」" << endl;
    cout << "    symbol_method = <enum default=CORNER_BRACKET_MIDDLE_DOT>" << endl;
    cout << "        CORNER_BRACKET_MIDDLE_DOT - '[' -> '「', '/' -> '・'" << endl;
    cout << "        SQUARE_BRACKET_SLASH      - '[' -> '［', '/' -> '／'" << endl;
    cout << "        CORNER_BRACKET_SLASH      - '[' -> '「', '/' -> '／'" << endl;
    cout << "        SQUARE_BRACKET_MIDDLE_DOT - '[' -> '［', '/' -> '・'" << endl;
    cout << "    space_character_form = <enum default=FUNDAMENTAL_INPUT_MODE>" << endl;
    cout << "        FUNDAMENTAL_INPUT_MODE - 空白の幅をモードによって変える" << endl;
    cout << "        FUNDAMENTAL_FULL_WIDTH - 常に全角幅" << endl;
    cout << "        FUNDAMENTAL_HALF_WIDTH - 常に半角幅" << endl;
    cout << "    history_learning_level = <enum default=DEFAULT_HISTORY>" << endl;
    cout << "        DEFAULT_HISTORY - ヒストリを使用" << endl;
    cout << "        READ_ONLY       - 読みのみ" << endl;
    cout << "        NO_HISTORY      - 使わない" << endl;
    cout << "    selection_shortcut = <enum default=SHORTCUT_123456789>" << endl;
    cout << "        NO_SHORTCUT        - 候補選択ショートカットなし" << endl;
    cout << "        SHORTCUT_123456789 - 数字キーをショートカットにする" << endl;
    cout << "        SHORTCUT_ASDFGHJKL - A〜Lをショートカットにする" << endl;
    cout << "    character_form_rules = <repeated message>" << endl;
    cout << "        詳細不明" << endl;
    cout << "    use_auto_ime_turn_off = <bool default=true>" << endl;
    cout << "        詳細不明" << endl;
    cout << "    use_cascading_window = <bool default=true>" << endl;
    cout << "        デバッグ用 - 詳細不明" << endl;
    cout << "    shift_key_mode_switch = <enum default=ASCII_INPUT_MODE>" << endl;
    cout << "        OFF                 - ひらがなのまま" << endl;
    cout << "        ASCII_INPUT_MODE    - Shift + キーで英字入力" << endl;
    cout << "        KATAKANA_INPUT_MODE - 同じく　　カタカナ入力" << endl;
    cout << "    numpad_character_form = <enum default=NUMPAD_HALF_WIDTH>" << endl;
    cout << "        NUMPAD_INPUT_MODE   - テンキー入力を入力モードで変える" << endl;
    cout << "        NUMPAD_FULL_WIDTH   - 常に全角" << endl;
    cout << "        NUMPAD_HALF_WIDTH   - 常に半角" << endl;
    cout << "        NUMPAD_DIRECT_INPUT - 直接入力" << endl;
    cout << "    use_date_conversion = <bool default=true>" << endl;
    cout << "        日付変換のON・OFF" << endl;
    cout << "    use_single_kanji_conversion = <bool default=true>" << endl;
    cout << "        単漢字変換のON・OFF" << endl;
    cout << "    use_symbol_conversion = <bool default=true>" << endl;
    cout << "        記号変換のON・OFF" << endl;
    cout << "    use_number_conversion = <bool default=true>" << endl;
    cout << "        数字変換のON・OFF" << endl;
    cout << "    use_history_suggest = <bool default=true>" << endl;
    cout << "        ヒストリを使用するサジェスト機能のON・OFF" << endl;
    cout << "    use_dictionary_suggest = <bool default=true>" << endl;
    cout << "        辞書を使用するサジェスト機能のON・OFF" << endl;
    cout << "    suggestions_size = <uint32 default=3>" << endl;
    cout << "        サジェストウインドウの項目数" << endl;
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
        if ((string)argv[2] == "character_form_rules" && argc > 5) {
            set_character_form_rules((string)argv[2], (string)argv[3],
                                     (string)argv[4], (string)argv[5]);
        } else if (argc > 3) {
            set((string)argv[2], (string)argv[3]);
        }
    } else if (flg == "-c") {
        if (argc > 2)
            clear((string)argv[2]);
    } else if (flg == "-r") {
        reboot();
    } else {
        print_help();
    }

    return 0;
}
