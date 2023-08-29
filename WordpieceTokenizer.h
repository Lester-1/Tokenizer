//===- WordpieceTokenizer --------------------------------------------------------===//
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
// This is a tokenizer worked by dividing roots and affixes
//
//===----------------------------------------------------------------------===//


#ifndef TOKENNIZER_WORDPIECETOKENIZER_H
#define TOKENNIZER_WORDPIECETOKENIZER_H

#include "Utils.h"

class WordpieceTokenizer {
private:
    Vocab vocab;
    string unk_token;
    i64 max_input_chars_per_word;
public:
    WordpieceTokenizer();

    WordpieceTokenizer(Vocab _vocab, string _unk_token = "[UNK]", i64 _max_input_chars_per_word = 200) {
        vocab = _vocab;
        unk_token = _unk_token;
        max_input_chars_per_word = _max_input_chars_per_word;
    }

    std::vector<string> tokenize(std::vector<string> text) {
        //  Divide roots and affixes
        std::vector<string> token;
        for (int i = 0; i < text.size(); i++) {
            if (text[i].size() > max_input_chars_per_word) {
                token.push_back(unk_token);
                continue;
            }
            bool is_bad = false;
            int start = 0;
            std::vector<string> sub_tokens;
            while (start < text[i].size()) {
                int end = text[i].size();
                string cur_substr = "";
                while (start < end) {
                    string substr;
                    substr.append(text[i], start, end - start);
                    if (start > 0)
                        substr = "##" + substr;
                    if (_is_invocab(vocab.token_to_id, substr)) {
                        cur_substr = substr;
                        break;
                    }
                    end -= 1;
                }
                if (cur_substr == "") {
                    is_bad = true;
                    break;
                }
                sub_tokens.push_back(cur_substr);
                start = end;
            }
            if (is_bad)
                token.push_back(unk_token);
            else {
                for (int i = 0; i < sub_tokens.size(); i++) {
                    token.push_back(sub_tokens[i]);
                }
            }
        }
        return token;
    }




};


#endif //TOKENNIZER_WORDPIECETOKENIZER_H
