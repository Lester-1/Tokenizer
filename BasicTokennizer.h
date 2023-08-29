//===- BasicTokennizer--------------------------------------------------------===//
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
// This is a basic tokenizer
//
//===----------------------------------------------------------------------===//



#ifndef TOKENNIZER_BASICTOKENNIZER_H
#define TOKENNIZER_BASICTOKENNIZER_H

#include "Utils.h"


class BasicTokennizer {
private:
    bool do_lower_case;
public:
    BasicTokennizer(){
        do_lower_case = true;
    }

    BasicTokennizer(bool lower) {
        do_lower_case = lower;
    }

    string _clean_text(string text){
        // clean control char
        string output;
        for(int i = 0;i<text.size();i++){
            char s = text[i];
            if(s == 0 or _is_control(s))
                continue;
            if(_is_whitespace(s))
                output.push_back(' ');
            else
                output.push_back(s);
        }
        return output;
    }


    string _tokenize_chinese_chars_and_punc(string text) {
        string output;
        for(int i = 0;i<text.size();i++){
            if(_is_chinese_char(text[i])){
                output.push_back(' ');
                output.append(text,i,3);
                output.push_back(' ');
                i = i + 2;
            } else if(_is_punctuation(text[i])){
                output.push_back(' ');
                output.push_back(text[i]);
                output.push_back(' ');
            }
            else{
                output.push_back(text[i]);
            }
        }
        return output;
    }


    std::vector<string> tokenize(string text){
        // Split words by spaces and punctuation
        text = convert_to_unicode(text);
        text = _clean_text(text);
        text = _tokenize_chinese_chars_and_punc(text);
        if(do_lower_case == true)
            transform(text.begin(),text.end(),text.begin(), tolower);
        std::cout<<text<<std::endl;
        std::vector<string> orig_tokens = whitespace_tokenize(text);
        return orig_tokens;
    }


};


#endif //TOKENNIZER_BASICTOKENNIZER_H
