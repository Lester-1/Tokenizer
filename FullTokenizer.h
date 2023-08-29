//===- FullTokenizer.h --------------------------------------------------------===//
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
// This is an integrated class
//
//===----------------------------------------------------------------------===//

#ifndef TOKENNIZER_FULLTOKENIZER_H
#define TOKENNIZER_FULLTOKENIZER_H

#include "BasicTokennizer.h"
#include "WordpieceTokenizer.h"

class FullTokenizer {
private:
    Vocab vocab;
    bool lower_case;
    BasicTokennizer* basic_tokenizer;
    WordpieceTokenizer* worldpiece_tokenizer;
public:
    FullTokenizer(){
        lower_case = true;
    }
    FullTokenizer(Vocab _vocab,bool _lower_case = true){
        vocab = _vocab;
        lower_case = _lower_case;
        basic_tokenizer = new BasicTokennizer(lower_case);
        worldpiece_tokenizer = new WordpieceTokenizer(vocab);
    }

    std::vector<string> tokenize(string text){
        std::vector token = basic_tokenizer->tokenize(text);
        token = worldpiece_tokenizer->tokenize(token);
        return token;
    }


};


#endif //TOKENNIZER_FULLTOKENIZER_H
