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
#include <unistd.h>

using namespace std;

#include "dictionary/user_dictionary_util.h"
#include "dictionary/user_dictionary_storage.h"
#include "dictionary/user_dictionary.h"

class MozcDict {
  public:
    MozcDict();
    void set_entry(string key, string value, string pos, string comment);
    void debug_print();
    bool save();

  protected:
    int dic_num();
    int new_dic(string name);

  private:
    mozc::UserDictionaryStorage* stor;
};
inline int MozcDict::dic_num() {return stor->dictionaries_size();}

MozcDict::MozcDict() {
    string name = mozc::UserDictionaryUtil::GetUserDictionaryFileName();
    stor = new mozc::UserDictionaryStorage(name);
    stor->Load();
}

void MozcDict::set_entry(string key, string value, string pos, string comment) {
    if (dic_num() < 1)
        if (new_dic("ユーザー辞書 1")) return;

    mozc::UserDictionaryStorage::UserDictionary* dic =
            stor->mutable_dictionaries(0);
    if (dic == NULL) return;

    mozc::UserDictionaryStorage::UserDictionaryEntry* entry =
            dic->add_entries();
    if (entry == NULL) return;
    entry->set_key(key);
    entry->set_value(value);
    entry->set_pos(pos);
    entry->set_comment(comment);
}

void MozcDict::debug_print() {
    for (int i = 0; i < dic_num(); i++) {
        mozc::UserDictionaryStorage::UserDictionary* dic =
                stor->mutable_dictionaries(i);
        if (dic == NULL) continue;
        cout << "name = " << dic->name() << endl;
        for (int j = 0; j < dic->entries_size(); j ++) {
            mozc::UserDictionaryStorage::UserDictionaryEntry* entry =
                    dic->mutable_entries(j);
            if (entry == NULL) continue;
            cout << "\t" << entry->key() << "\t" << entry->value()
                 << "\t" << entry->pos() << "\t" << entry->comment() << endl;
        }
    }
}

int MozcDict::new_dic(string name) {
    mozc::UserDictionaryStorage::UserDictionary* dic = stor->add_dictionaries();
    if (dic == NULL) return 1;
    dic->set_name(name);
    return 0;
}

bool MozcDict::save() {
    if (stor->Lock()) {
        stor->Save();
        stor->UnLock();
        return true;
    }
    return false;
}

int reboot() {
    const char *path = "/usr/bin/killall";
    char *const argv[] = {
        (char *)"/usr/bin/killall",
        (char *)"ibus-daemon",
        (char *)NULL
    };

    return execv(path, argv);
}
 
void print_help() {
    cout << "Usage:" << endl;
    cout << "    mozc-dict [ -h | -a | -s <よみ> <単語> <品詞> ]" << endl;
    cout << "        -h                      - ヘルプを表示する" << endl;
    cout << "        -a                      - 辞書の内容をすべて表示する" << endl;
    cout << "        -s <よみ> <単語> <品詞> - 単語を登録する" << endl;
    cout << "        -r                      - 強制的に再起動する" << endl;
}

int main(int argc, char **argv) {
    MozcDict md;

    if (argc <= 1) {
        print_help();
        return -1;
    }

    string flg = argv[1];

    if (flg == "-a") {
        md.debug_print();
    } else if (flg == "-s") {
        if (argc > 3) {
            md.set_entry(argv[1], argv[2], argv[3], "");
            md.save();
        }
    } else if (flg == "-r") {
        reboot();
    } else {
        print_help();
    }

    return 0;
}
