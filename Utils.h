//===- Utils.h --------------------------------------------------------===//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===----------------------------------------------------------------------===//
//
// This is a utility.
//
//===----------------------------------------------------------------------===//

#ifndef TOKENNIZER_UTILS_H
#define TOKENNIZER_UTILS_H

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>

typedef std::string string;
typedef int64_t i64;


struct Vocab {
    // a struct defined to store vocab
public:
    using Id = i64;
    using Token = std::string;
    Token tok;
    typedef std::map<Token, Id> map;

    void load_vacab(string vacab_file) {
        i64 index = 0;
        string value;
        std::ifstream fin(vacab_file.c_str());
        while (getline(fin, value)) {
            token_to_id.insert(map::value_type(value, index));
            id_to_token.push_back(value);
            index++;
        }
    }

    std::map<Token, Id> token_to_id;
    std::vector<Token> id_to_token;
};


string convert_to_unicode(string text) {
    //todo:implement this function
    return text;
}

static size_t utf8_len(char src) {
    //Judge if a char is decoded by utf-8
    const size_t lookup[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4};
    uint8_t highbits = static_cast<uint8_t>(src) >> 4;
    return lookup[highbits];
}

/*string load_vacab(string vacab_file){
    string vocab;
    int index = 0;
    std::ifstream fin(vacab_file.c_str());
    while (getline(fin, vocab)) std::cout<<vocab<<std::endl;
    return vocab;
}*/

std::vector<Vocab::Id> convert_tokens_to_ids(Vocab::map token_to_id, std::vector<string> token) {
    std::vector<i64> ids;
    ids.push_back(101);
    for (int i = 0; i < token.size(); i++) {
        Vocab::map::iterator target = token_to_id.find(token[i]);
        ids.push_back(target->second);
        /*if (target->second != vocab.end()->second)
            ids.push_back(target->second);
        else
            ids.push_back(100);*/
    }
    ids.push_back(102);
    return ids;
}

void convert_tokens_to_ids(Vocab::map token_to_id, std::vector<string> token, std::vector<Vocab::Id> &ids) {
    if (ids.size() > 0)
        ids.pop_back();
    else
        ids.push_back(101);
    for (int i = 0; i < token.size(); i++) {
        Vocab::map::iterator target = token_to_id.find(token[i]);
        ids.push_back(target->second);
        /*if (target->second != vocab.end()->second)
            ids.push_back(target->second);
        else
            ids.push_back(100);*/
    }
    ids.push_back(102);
}

std::vector<Vocab::Token> convert_ids_to_tokens(Vocab vocab, Vocab::Id *id, int length) {
    std::vector<Vocab::Token> token;
    for (int i = 0; i < length; i++) {
        token.push_back(vocab.id_to_token[id[i]]);
    }
    return token;
}


bool _is_invocab(Vocab::map token_to_id, string token) {
    Vocab::map::iterator target = token_to_id.find(token);
    if (target->second != token_to_id.end()->second)
        return true;
    else
        return false;

}


string strip(const string &str, char ch = ' ') {
    //Remove the ch characters at both ends of str
    int i = 0;
    while (str[i] == ch)
        i++;
    int j = str.size() - 1;
    while (str[j] == ch) //
        j--;
    return str.substr(i, j + 1 - i);
}

std::vector<string> split(const string &str, string ch = " ") {
    //Use ch as the separator character, divide cstr into multiple elements and store them in vector
    std::vector<string> ret;
    int pos = 0;
    int start = 0;
    while ((pos = str.find(ch, start)) != string::npos) {
        if (pos > start)
            ret.push_back(str.substr(start, pos - start));
        start = pos + ch.size();
    }
    if (str.size() > start)
        ret.push_back(str.substr(start));
    return ret;
}


std::vector<string> whitespace_tokenize(string s) {
    s = strip(s);
    return split(s);
}

bool _is_whitespace(char s) {
    if (s == ' ' or s == '\t' or s == '\n' or s == '\r')
        return true;
    return false;
}

bool _is_control(char s) {
    //todo: implement this function
    /*if(s == '\t' or s == '\n' or s == '\r')
        return false;
    if(s )
        return true;
    else*/
    return false;
}

bool _is_punctuation(char s) {
    if ((s >= 33 and s <= 47) or (s >= 58 and s <= 64) or
        (s >= 91 and s <= 96) or (s >= 123 and s <= 126))
        return true;
    return false;
}

bool _is_chinese_char(char s) {
    if (utf8_len(s) == 3)
        return true;
    else
        return false;
}


#endif //TOKENNIZER_UTILS_H
