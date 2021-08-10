#include "word.h"

// Function to generate all binary vectors of size n using recursion
void generateAllBinaryVectors(size_t n, std::vector<size_t>& combination,
							  size_t i, std::vector<std::vector<size_t>>& all_combbinations);

class Converter {
public:
	
	// function for the second part of the problem
	Word& GenerateVariations(Word& word);
	// function for the first part of the problem
	Word& ConvertToFinalVersion(Word& word) const;
	// this function splits the word by Umlauts and store the result in vector Word.word_splitting_
	// this function saves as well the positions of the Umlauts in variable Word.umlauts_positions_
	Word& FindUmlautsPositions (Word& word) const;
	// function for the third part of the problem
	std::string GenerateExtendedStatement(const std::string& statement);
	
private:
	const std::map<std::string, std::string> replacements = {{"AE", "Ä"}, {"UE", "Ü"},
		{"OE", "Ö"}, {"SS", "ß"}};
	// to control if we already created the possible Umlauts combination
	std::map<size_t, std::vector<std::vector<size_t>>> binary_combinations_storage;

};
