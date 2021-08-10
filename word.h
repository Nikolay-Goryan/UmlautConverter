#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>



class Word {
public:
	Word(std::string init_version) {
		init_version_ = init_version;
	}
	std::string init_version_ = "";
	std::string final_version_ = "";
	std::vector<std::string> possible_variations_;
	std::vector<std::string> word_splitting_; // the word, splitted by Umlauts
	std::set<size_t> umlauts_positions_; // shows the indexes of Umlauts in word_splitting vector
};
