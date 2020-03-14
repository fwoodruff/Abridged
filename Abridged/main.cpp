#include "helpers.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_set>

int main(int argc, const char * argv[]) {
    // open files
    std::ifstream english_dictionary;
    english_dictionary.open("dictionary.txt");
    if (!english_dictionary) {
        std::cerr << "Unable to open input file\n";
        std::exit(1);
    }
    
    std::ofstream word_towers;
    word_towers.open("word_towers.txt");
    if (!word_towers) {
        std::cerr << "Unable to open output file\n";
        std::exit(1);
    }
    
    std::ofstream a_words;
    a_words.open("a_words.txt");
    if (!a_words) {
        std::cerr << "Unable to open output file\n";
        std::exit(1);
    }

    // fill a map
    
    std::unordered_set<std::string> word_set;
    
    std::string line;
    while(!english_dictionary.eof()) {
        // take each word in the dictionary
        std::getline(english_dictionary,line);
        std::string word = line.substr(0,line.size()-1);
        
        // filter out words with apostrophes
        bool bad_letter = false;
        for (char const &c: word) {
            if(c=='\'') bad_letter=true;
        }
        if(!bad_letter) {
            word_set.insert(word);
        }
        
    }
    word_set.insert("a");
    word_set.insert("i");
    

    english_dictionary.clear();
    english_dictionary.seekg (0, std::ios::beg);
    while(!english_dictionary.eof()) {
        std::getline(english_dictionary,line);
        std::string word = line.substr(1,line.size()-2);
        if(word_set.find(word) != word_set.end()) {
            a_words << word << "\n";
        }
        if(lowercase(line).front()!='a') {
            break;
        }
    }
    
    english_dictionary.clear();
    english_dictionary.seekg (0, std::ios::beg);
    
    std::vector<std::vector<std::string>> list_wordpaths;
    while(!english_dictionary.eof()) {
        std::getline(english_dictionary,line);
        std::string word = line.substr(0,line.size()-1);
        
        bool bad_letter = false;
        for (char const &c: word) {
            if(c=='\'') bad_letter=true;
        }
        if(bad_letter) continue;
        
        std::vector<std::string> word_path_0;
        word_path_0.push_back(word);
        find_words(word_path_0,word_set,list_wordpaths);
    }
    
    
    
    for(const auto& wordpath : list_wordpaths) {
        if(wordpath.size()>=wordpath.front().size() and wordpath.front().size()>=9) {
            for(const auto& word : wordpath) {
                if(word=="i") {
                    word_towers << "I\n";
                } else {
                    word_towers << word << "\n";
                }
            }
        }
    }

    english_dictionary.close();
    word_towers.close();
    a_words.close();

}
