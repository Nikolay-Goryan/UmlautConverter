#include "converter.h"

// Function to generate all binary vectors of size n using recursion
void generateAllBinaryVectors(size_t n, std::vector<size_t>& combination,
							  size_t i, std::vector<std::vector<size_t>>& all_combbinations) {
	if (i == n) {
		all_combbinations.push_back(combination);
		return;
	}
 
	// First assign "0" at ith position
	// and try for all other permutations
	// for remaining positions
	combination[i] = 0;
	generateAllBinaryVectors(n, combination, i + 1, all_combbinations);
 
	// And then assign "1" at ith position
	// and try for all other permutations
	// for remaining positions
	combination[i] = 1;
	generateAllBinaryVectors(n, combination, i + 1, all_combbinations);
}

	
Word& Converter::GenerateVariations(Word& word) {
	word = FindUmlautsPositions(word);
	size_t i = 0;
	if (!binary_combinations_storage.count(word.umlauts_positions_.size())) {
		std::vector<size_t> combination_of_size(word.umlauts_positions_.size(), 0);
		std::vector<std::vector<size_t>> all_combination_of_size;
		generateAllBinaryVectors(word.umlauts_positions_.size(), combination_of_size, 0, all_combination_of_size);
		binary_combinations_storage[word.umlauts_positions_.size()] = all_combination_of_size;
	}
	for (auto& combination: binary_combinations_storage.at(word.umlauts_positions_.size())) {
		std::vector<std::string> word_splitting = word.word_splitting_;
		i = 0; // counter to move through regular combination of ones and zeros
		for (size_t position: word.umlauts_positions_) {
			if (combination[i] == 1) {
				word_splitting[position] = replacements.at(word_splitting[position]);
			}
			++i;
		}
		std::string word_variation = "";
		for (auto& part: word_splitting) {
			word_variation += part;
		}
		word.possible_variations_.push_back(word_variation);
	}
	
	return word;
}

Word& Converter::ConvertToFinalVersion(Word& word) const {
	std::string final_version = word.init_version_;
	size_t current_pos = 0; //to control the place of search in the word
	for (auto replacement: replacements) {
		current_pos = final_version.find(replacement.first, current_pos);
		if (current_pos == std::string::npos) {
			current_pos = 0;
			continue;
		} else {
			while (current_pos != std::string::npos) {
				final_version = final_version.replace(current_pos, 2, replacement.second);
				current_pos = final_version.find(replacement.first, current_pos);
			}
			current_pos = 0;
		}
	}
	word.final_version_ = final_version;
	return word;
}
	

	// this function splits the word by Umlauts and store the result in vector Word.word_splitting_
	// this function also saves the positions of the Umlauts in variable Word.umlauts_positions_
Word& Converter::FindUmlautsPositions (Word& word) const {
	size_t current_pos = 0; //to control the place of search in the word
	std::set<size_t> umlaut_indexes;
	std::string init_version = word.init_version_;
	for (auto replacement: replacements) {
		current_pos = word.init_version_.find(replacement.first, current_pos);
		if (current_pos == std::string::npos) {
			current_pos = 0;
			continue;
		} else {
			while (current_pos != std::string::npos) {
				umlaut_indexes.insert(current_pos);
				current_pos = word.init_version_.find(replacement.first, current_pos + 2);
			}
			current_pos = 0;
		}
	}
	size_t current_index = 0;
	for (auto index: umlaut_indexes) {
		if (index == 0 || index == current_index) {
			word.word_splitting_.push_back(init_version.substr(current_index, 2));
			current_index += 2;
			word.umlauts_positions_.insert(word.word_splitting_.size() - 1);
			continue;
		}
		word.word_splitting_.push_back(init_version.substr(current_index, index - current_index));
		current_index = index;
		word.word_splitting_.push_back(init_version.substr(current_index, 2));
		current_index += 2;
		word.umlauts_positions_.insert(word.word_splitting_.size() - 1);

	}
	if (init_version.size() - current_index > 0) {
		word.word_splitting_.push_back(init_version.substr(current_index, init_version.size() - current_index));
	}
	return word;
}

std::string Converter::GenerateExtendedStatement(const std::string& statement) {
	std::string extended_statement = statement;
	size_t first_quote = statement.find("'");
	size_t second_quote = statement.find("'", first_quote + 1);
	std::string key_word = statement.substr(first_quote + 1, second_quote - first_quote - 1);
	Word word = Word(key_word);
	word = GenerateVariations(word);
	for (auto& variation: word.possible_variations_) {
		if (variation != key_word) {
			extended_statement = extended_statement + " or last_name = '" + variation + "'";
		}
	}
	return extended_statement;
}
