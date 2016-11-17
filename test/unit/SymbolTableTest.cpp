#include "gtest.h"
#include "Symbol.h"
#include "SymbolTable.h"

/**
 * @brief Teste da classe SymbolTable
 */
class SymbolTableTest : public ::testing::Test {

protected:
	virtual void SetUp() {
        symbol = Symbol(Data::INT, Symbol::VARIABLE, false, 0);
	}

	virtual void TearDown() {
	}
    
    Symbol symbol;
    SymbolTable table;
    SymbolTable table2;

};

/**
 * @brief Teste do operador =
 */
TEST_F(SymbolTableTest, operatorAssignTest) {
	EXPECT_FALSE(table.existsSymbol("symbol1", Symbol::VARIABLE));
    table2.addSymbol("symbol1", symbol);
    table = table2;
	EXPECT_TRUE(table.existsSymbol("symbol1", Symbol::VARIABLE));
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
