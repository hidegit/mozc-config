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

using namespace mozc;
using namespace config;

int atoi(string s) {
    return atoi(s.c_str());
}

int atol(string s) {
    return atol(s.c_str());
}

void print_modifier() {
    Config conf;

    ConfigHandler::GetConfig(&conf);
    cout << conf.DebugString();
}

void get(string name) {
    Config conf;
    ConfigHandler::GetConfig(&conf);

    const google::protobuf::FieldDescriptor* field =
            Config::descriptor()->FindFieldByName(name);
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
    Config conf;
    ConfigHandler::GetConfig(&conf);

    const google::protobuf::FieldDescriptor* field =
            Config::descriptor()->FindFieldByName(name);
    const google::protobuf::Reflection* ref = conf.GetReflection();

    if (field == NULL) return;

    const int type = field->type();
    if (type == 4) {
        ref->SetUInt64(&conf, field, atol(value));
    } else if (type == 5) {
        ref->SetInt32(&conf, field, atoi(value));
    } else if (type == 8) {
        ref->SetBool(&conf, field, (value == "true") ? true : false);
    } else if (type == 9) {
        ref->SetString(&conf, field, value);
//   } else if (type == 11) {
//            value << type;
    } else if (type == 12) {
        ref->SetString(&conf, field, value);
    } else if (type == 13) {
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

    ConfigHandler::SetConfig(conf);
}

void clear(string name) {
    Config conf;
    ConfigHandler::GetConfig(&conf);

    const google::protobuf::FieldDescriptor* field =
            Config::descriptor()->FindFieldByName(name);

    if (field == NULL) return;

    conf.GetReflection()->ClearField(&conf, field);

    ConfigHandler::SetConfig(conf);
}

void print_all() {
    Config conf;
    ConfigHandler::GetConfig(&conf);

    const google::protobuf::Descriptor* desc = Config::descriptor();
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
//    } else if (flg == "-v") {
//        if (argc > 2)
//            print_value((string)argv[2]);
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
        return -1;
    }

    return 0;
}
