#include "gtest.h"
#include "SymbolTable.h"

/**
 * @brief Teste da classe SymbolTable
 */
class SymbolTableTest : public ::testing::Test {

protected:
	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
    
    SymbolTable table;

};

/**
 * @brief Teste do operador =
 */
TEST_F(SymbolTableTest, operatorAssignTest) {
	EXPECT_FALSE(true);
}

/**
 * @brief Teste do método existsSymbol()
 */
TEST_F(SymbolTableTest, existsSymbolTest) {
	EXPECT_FALSE(true);
}

/**
 * @brief Teste do método getSymbol()
 */
TEST_F(SymbolTableTest, getSymbolTest) {
	EXPECT_FALSE(true);
}

/**
 * @brief Teste do método getUninitializedFunctions()
 */
TEST_F(SymbolTableTest, getUninitializedFunctionsTest) {
	EXPECT_FALSE(true);
}

/**
 * @brief Teste do método addSymbol()
 */
TEST_F(SymbolTableTest, addSymbolTest) {
	EXPECT_FALSE(true);
}

/**
 * @brief Teste do método setInitializedSymbol()
 */
TEST_F(SymbolTableTest, setInitializedSymbolTest) {
	EXPECT_FALSE(true);
}

/**
 * @brief Teste do método setSymbolData()
 */
TEST_F(SymbolTableTest, setSymbolDataTest) {
	EXPECT_FALSE(true);
}
