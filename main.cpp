#include "test_runner.h"
#include "converter.h"


void TestFinalVersionConversion() {
	Word word1("KOESTNER");
	Word word2("RUESSWURM");
	Word word3("DUERMUELLER");
	Word word4("JAEAESKELAEINEN");
	Word word5("GROSSSCHAEDL");
	
	Converter converter;
	
	Word converted_word1 = converter.ConvertToFinalVersion(word1);
	Word converted_word2 = converter.ConvertToFinalVersion(word2);
	Word converted_word3 = converter.ConvertToFinalVersion(word3);
	Word converted_word4 = converter.ConvertToFinalVersion(word4);
	Word converted_word5 = converter.ConvertToFinalVersion(word5);

	ASSERT_EQUAL(converted_word1.final_version_, "KÖSTNER");
	ASSERT_EQUAL(converted_word2.final_version_, "RÜßWURM");
	ASSERT_EQUAL(converted_word3.final_version_, "DÜRMÜLLER");
	ASSERT_EQUAL(converted_word4.final_version_, "JÄÄSKELÄINEN");
	ASSERT_EQUAL(converted_word5.final_version_, "GROßSCHÄDL");
}

void TestFindUmlautsPositions() {
	Word word1("KOESTNER");
	Word word2("RUESSWURM");
	Word word3("DUERMUELLER");
	Word word4("JAEAESKELAEINEN");
	Word word5("GROSSSCHAEDL");

	Converter converter;
	
	Word converted_word1 = converter.FindUmlautsPositions(word1);
	Word converted_word2 = converter.FindUmlautsPositions(word2);
	Word converted_word3 = converter.FindUmlautsPositions(word3);
	Word converted_word4 = converter.FindUmlautsPositions(word4);
	Word converted_word5 = converter.FindUmlautsPositions(word5);
	
	ASSERT_EQUAL(converted_word1.umlauts_positions_, std::set<size_t>({1}));
	ASSERT_EQUAL(converted_word2.umlauts_positions_, std::set<size_t>({1, 2}));
	ASSERT_EQUAL(converted_word3.umlauts_positions_, std::set<size_t>({1, 3}));
	ASSERT_EQUAL(converted_word4.umlauts_positions_, std::set<size_t>({1, 2, 4}));
	ASSERT_EQUAL(converted_word5.umlauts_positions_, std::set<size_t>({1, 3}));
	
	ASSERT_EQUAL(converted_word1.word_splitting_, std::vector<std::string>({"K", "OE", "STNER"}));
	ASSERT_EQUAL(converted_word2.word_splitting_, std::vector<std::string>({"R", "UE", "SS", "WURM"}));
	ASSERT_EQUAL(converted_word3.word_splitting_, std::vector<std::string>({"D", "UE", "RM", "UE", "LLER"}));
	ASSERT_EQUAL(converted_word4.word_splitting_, std::vector<std::string>({"J", "AE", "AE", "SKEL", "AE", "INEN"}));
	ASSERT_EQUAL(converted_word5.word_splitting_, std::vector<std::string>({"GRO", "SS", "SCH", "AE", "DL"}));
}

void TestGenerateVariations() {
	Word word1("KOESTNER");
	Word word2("RUESSWURM");
	Word word3("DUERMUELLER");
	Word word4("JAEAESKELAEINEN");
	Word word5("GROSSSCHAEDL");
	
	Converter converter;
	
	Word converted_word1 = converter.GenerateVariations(word1);
	Word converted_word2 = converter.GenerateVariations(word2);
	Word converted_word3 = converter.GenerateVariations(word3);
	Word converted_word4 = converter.GenerateVariations(word4);
	Word converted_word5 = converter.GenerateVariations(word5);
	
	ASSERT_EQUAL(converted_word1.possible_variations_, std::vector<std::string>({"KOESTNER", "KÖSTNER"}));
	ASSERT_EQUAL(converted_word2.possible_variations_, std::vector<std::string>({"RUESSWURM", "RUEßWURM",
		"RÜSSWURM", "RÜßWURM"}));
	ASSERT_EQUAL(converted_word3.possible_variations_, std::vector<std::string>({"DUERMUELLER", "DUERMÜLLER",
		"DÜRMUELLER", "DÜRMÜLLER"}));
	ASSERT_EQUAL(converted_word4.possible_variations_, std::vector<std::string>({"JAEAESKELAEINEN", "JAEAESKELÄINEN",
		"JAEÄSKELAEINEN", "JAEÄSKELÄINEN", "JÄAESKELAEINEN", "JÄAESKELÄINEN", "JÄÄSKELAEINEN", "JÄÄSKELÄINEN"}));
	ASSERT_EQUAL(converted_word5.possible_variations_, std::vector<std::string>({"GROSSSCHAEDL", "GROSSSCHÄDL",
		"GROßSCHAEDL", "GROßSCHÄDL"}));
}

void TestGenerateExtendedStatement() {

	Converter converter;

	string extended_statement1 = converter.GenerateExtendedStatement("SELECT * FROM tbl_phonebook WHERE last_name = 'KOESTNER'");
	string extended_statement2 = converter.GenerateExtendedStatement("SELECT * FROM tbl_phonebook WHERE last_name = 'RUESSWURM'");
	string extended_statement3 = converter.GenerateExtendedStatement("SELECT * FROM tbl_phonebook WHERE last_name = 'DUERMUELLER'");
	string extended_statement4 = converter.GenerateExtendedStatement("SELECT * FROM tbl_phonebook WHERE last_name = 'JAEAESKELAEINEN'");
	string extended_statement5 = converter.GenerateExtendedStatement("SELECT * FROM tbl_phonebook WHERE last_name = 'GROSSSCHAEDL'");
	
	
	ASSERT_EQUAL(extended_statement1, "SELECT * FROM tbl_phonebook WHERE last_name = 'KOESTNER' or last_name = 'KÖSTNER'");
	
	ASSERT_EQUAL(extended_statement2, "SELECT * FROM tbl_phonebook WHERE last_name = 'RUESSWURM' or last_name = 'RUEßWURM' or last_name = 'RÜSSWURM' or last_name = 'RÜßWURM'");
	
	ASSERT_EQUAL(extended_statement3, "SELECT * FROM tbl_phonebook WHERE last_name = 'DUERMUELLER' or last_name = 'DUERMÜLLER' or last_name = 'DÜRMUELLER' or last_name = 'DÜRMÜLLER'");
	
	ASSERT_EQUAL(extended_statement4, "SELECT * FROM tbl_phonebook WHERE last_name = 'JAEAESKELAEINEN' or last_name = 'JAEAESKELÄINEN' or last_name = 'JAEÄSKELAEINEN' or last_name = 'JAEÄSKELÄINEN' or last_name = 'JÄAESKELAEINEN' or last_name = 'JÄAESKELÄINEN' or last_name = 'JÄÄSKELAEINEN' or last_name = 'JÄÄSKELÄINEN'");
	
	ASSERT_EQUAL(extended_statement5, "SELECT * FROM tbl_phonebook WHERE last_name = 'GROSSSCHAEDL' or last_name = 'GROSSSCHÄDL' or last_name = 'GROßSCHAEDL' or last_name = 'GROßSCHÄDL'");
	
}


int main() {
	
	TestRunner tr;
	
	RUN_TEST(tr, TestFinalVersionConversion);
	RUN_TEST(tr, TestFindUmlautsPositions);
	RUN_TEST(tr, TestGenerateVariations);
	RUN_TEST(tr, TestGenerateExtendedStatement);
	
	return 0;
}
