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

void print_modifier() {
    mozc::config::Config conf;

    mozc::config::ConfigHandler::GetConfig(&conf);
    cout << conf.DebugString();
}

void get(string name) {
    mozc::config::Config conf;
    mozc::config::ConfigHandler::GetConfig(&conf);

    const google::protobuf::FieldDescriptor* field =
            mozc::config::Config::descriptor()->FindFieldByName(name);
    const google::protobuf::Reflection* ref = conf.GetReflection();

    if (field == NULL) return;

    stringstream value;

    const int type = field->type();
    if (type == 4) {
        value << ref->GetUInt64(conf, field);
    } else if (type == 5) {
        value << ref->GetInt32(conf, field);
    } else if (type == 8) {
        value << (ref->GetBool(conf, field) ? "true" : "false");
    } else if (type == 9) {
        value << "\"" << ref->GetString(conf, field) << "\"";
//    } else if (type == 11) {
//        value << type;
    } else if (type == 12) {
        value << "\"" << ref->GetString(conf, field) << "\"";
    } else if (type == 13) {
        value << ref->GetUInt32(conf, field);
    } else if (type == 14) {
        value << ref->GetEnum(conf, field)->name();
    } else {
        value << "/* Not Impl Error!! */";
    }
    cout << name << ": " << value.str() << endl;
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
//   } else if (type == 11) {
//            value << type;
    } else if (type == 12) {
        ref->SetString(&conf, field, value);
    } else if (type == 13) {
        if (!is_num_str(value)) return;
        ref->SetUInt64(&conf, field, atol(value));
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

    mozc::config::Config conf;
    mozc::config::ConfigHandler::GetConfig(&conf);

    const google::protobuf::FieldDescriptor* field =
            mozc::config::Config::descriptor()->FindFieldByName(name);

    if (field == NULL) return;

    conf.GetReflection()->ClearField(&conf, field);

    mozc::config::ConfigHandler::SetConfig(conf);
}

void print_all() {
    mozc::config::Config conf;
    mozc::config::ConfigHandler::GetConfig(&conf);

    const google::protobuf::Descriptor* desc = mozc::config::Config::descriptor();
    const google::protobuf::Reflection* ref = conf.GetReflection();

    for (int i = 0; i < desc->field_count(); i++) {
        const google::protobuf::FieldDescriptor* field = desc->field(i);
        const string name = field->name();

        stringstream value;

        const int type = field->type();
        if (type == 4) {
            value << ref->GetUInt64(conf, field);
        } else if (type == 5) {
            value << ref->GetInt32(conf, field);
        } else if (type == 8) {
            value << (ref->GetBool(conf, field) ? "true" : "false");
        } else if (type == 9) {
            value << "\"" << ref->GetString(conf, field) << "\"";
//        } else if (type == 11) {
//            value << type;
        } else if (type == 12) {
            value << "\"" << ref->GetString(conf, field) << "\"";
        } else if (type == 13) {
            value << ref->GetUInt32(conf, field);
        } else if (type == 14) {
            value << ref->GetEnum(conf, field)->name();
        } else {
            value << "/* Not Impl Error!! */";
        }
        cout << name << ": " << value.str() << endl;
    }
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
    } else {
        print_help();
    }

    return 0;
}
