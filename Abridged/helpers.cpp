

#include "helpers.hpp"

std::string lowercase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){
                       return std::tolower(c);
                   });
    return str;
}

std::vector<std::string> shorterwords(std::string word, const std::unordered_set<std::string>& wordset) {
    unsigned long stringlength = word.size();
    std::vector<std::string> output;
    for(int i=0;i<stringlength;i++) {
        auto wordcpy = word;
        wordcpy.erase(i,1);
        if(wordset.find(wordcpy) != wordset.end()) {
            output.push_back(wordcpy);
        }
    }
    return output;
}



void find_words(const std::vector<std::string>& words, const std::unordered_set<std::string>& wordset, std::vector<std::vector<std::string>>& wordpaths) {
    std::string parent_word = words.back();
    auto child_words = shorterwords(parent_word, wordset);
    if(child_words.size()==0) {
        wordpaths.push_back(words);
    } else {
        for(const auto& word : child_words) {
            auto words_copy = words;
            words_copy.push_back(word);
            find_words(words_copy, wordset, wordpaths);
        }
    }
}
