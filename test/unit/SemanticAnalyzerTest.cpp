#include "gtest.h"
#include "ErrorLogger.h"
#include "SemanticAnalyzer.h"

ErrorLogger* ERROR_LOGGER = new ErrorLogger();

/**
 * @brief Teste da classe SemanticAnalyzer
 */
class SemanticAnalyzerTest : public ::testing::Test {

protected:
	virtual void SetUp() {
        
	}

	virtual void TearDown() {
	}
    
    SemanticAnalyzer analyzer;

};

/**
 * @brief Teste do método analyzeCasting()
 */
TEST_F(SemanticAnalyzerTest, analyzeCastingTest) {
	EXPECT_TRUE(false);
}

/**
 * @brief Teste do método analyzeRelationalOperationCasting()
 */
TEST_F(SemanticAnalyzerTest, analyzeRelationalOperationCastingTest) {
	EXPECT_TRUE(false);
}

/**
 * @brief Teste do método setType()
 */
TEST_F(SemanticAnalyzerTest, setTypeTest) {
	EXPECT_TRUE(false);
}

/**
 * @brief Teste do método declareVariable()
 */
TEST_F(SemanticAnalyzerTest, declareVariableTest) {
	EXPECT_TRUE(false);
}

/**
 * @brief Teste do método assignVariable()
 */
TEST_F(SemanticAnalyzerTest, assignVariableTest) {
	EXPECT_TRUE(false);
}

/**
 * @brief Teste do método declareAssignVariable()
 */
TEST_F(SemanticAnalyzerTest, declareAssignVariableTest) {
	EXPECT_TRUE(false);
}

/**
 * @brief Teste do método useVariable()
 */
TEST_F(SemanticAnalyzerTest, useVariableTest) {
	EXPECT_TRUE(false);
}