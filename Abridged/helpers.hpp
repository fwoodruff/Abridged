#ifndef helpers_hpp
#define helpers_hpp

#include <iostream>
#include <vector>
#include <unordered_set>

std::string lowercase(std::string str);
std::vector<std::string> shorterwords(std::string word, const std::unordered_set<std::string>& wordset);
void find_words(const std::vector<std::string>&, const std::unordered_set<std::string>&, std::vector<std::vector<std::string>>&);

#endif
