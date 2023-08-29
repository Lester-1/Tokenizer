//===- Test.cpp --------------------------------------------------------===//
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
// This is a test file.
//
//===----------------------------------------------------------------------===//
#include <iostream>
#include "FullTokenizer.h"
#include "Utils.h"
#include "Container.h"

const int size = 100;

int main() {
    Vocab vocab;
    //Refering to https://huggingface.co/prajjwal1/bert-tiny/blob/main/vocab.txt
    //convert to your path
    vocab.load_vacab("/Users/lester/CLionProjects/Tokennizer/vocab.txt");
    // Test a string entered by the user.
    string test = "I am very happy";
    FullTokenizer *fullTokenizer = new FullTokenizer(vocab, true);
    std::vector<string> token = fullTokenizer->tokenize(test);
    std::vector<i64> id = convert_tokens_to_ids(vocab.token_to_id, token);
    for (int i = 0; i < token.size(); i++) {
              std::cout<<token[i]<<" "<<id[i]<<std::endl;
    }
    //convert to your path
    string fs = "/Users/lester/CLionProjects/Tokennizer/sample_text.txt";
    std::ifstream fin(fs.c_str());
    getline(fin, test);
    int index = 0;
    while (index < 3) {
        token = fullTokenizer->tokenize(test);
        convert_tokens_to_ids(vocab.token_to_id, token, id);
        /* for (int i = 0; i < token.size(); i++) {
               std::cout << token[i] << " " << id[i] << std::endl;
        }*/
        getline(fin, test);
        index++;
    }
    intptr_t sizes[2] = {1, size};

    MemRef<i64, 2> mem(id, sizes);
    i64 *data = mem.getData();
    std::vector<string> tokens = convert_ids_to_tokens(vocab, data, size);
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << ' ' << tokens[i] << std::endl;
    }
    return 0;
}
