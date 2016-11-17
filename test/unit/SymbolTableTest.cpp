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
	EXPECT_FALSE(table.existsSymbol("symbol1"));
    table2.addSymbol("symbol1", symbol);
    table = table2;
	EXPECT_TRUE(table.existsSymbol("symbol1"));
}

/**
 * @brief Teste do método newScope()
 */
TEST_F(SymbolTableTest, newScopeTest) {
    table.addSymbol("symbol1", symbol);
	EXPECT_TRUE(table.existsSymbol("symbol1", false));
    table.newScope();
	EXPECT_FALSE(table.existsSymbol("symbol1", false));
	EXPECT_TRUE(table.existsSymbol("symbol1", true));
}

/**
 * @brief Teste do método returnScope()
 */
TEST_F(SymbolTableTest, returnScopeTest) {
    table.newScope();
    table.addSymbol("symbol1", symbol);
	EXPECT_TRUE(table.existsSymbol("symbol1", false));
    table.returnScope();
	EXPECT_FALSE(table.existsSymbol("symbol1"));
}

/**
 * @brief Teste do método existsSymbol()
 */
TEST_F(SymbolTableTest, existsSymbolTest) {
    table.addSymbol("symbol1", symbol);
	EXPECT_TRUE(table.existsSymbol("symbol1", false));
}

/**
 * @brief Teste do método getSymbol()
 */
TEST_F(SymbolTableTest, getSymbolTest) {
    table.addSymbol("symbol1", symbol);
	EXPECT_EQ(table.getSymbol("symbol1", false).getDataType(), Data::INT);
}

/**
 * @brief Teste do método isSymbolInitialized()
 */
TEST_F(SymbolTableTest, isSymbolInitializedTest) {
    table.addSymbol("symbol1", symbol);
	EXPECT_FALSE(table.isSymbolInitialized("symbol1", false));
    table.setInitializedSymbol("symbol1");
    table.newScope();
	EXPECT_TRUE(table.isSymbolInitialized("symbol1", true));
    
}

/**
 * @brief Teste do método addSymbol()
 */
TEST_F(SymbolTableTest, addSymbolTest) {
	EXPECT_FALSE(table.existsSymbol("symbol1", false));
    table.addSymbol("symbol1", symbol);
	EXPECT_TRUE(table.existsSymbol("symbol1", false));
}

/**
 * @brief Teste do método setInitializedSymbol()
 */
TEST_F(SymbolTableTest, setInitializedSymbolTest) {
    table.addSymbol("symbol1", symbol);
	EXPECT_FALSE(table.isSymbolInitialized("symbol1", false));
    table.setInitializedSymbol("symbol1");
	EXPECT_TRUE(table.isSymbolInitialized("symbol1", false));
}

/**
 * @brief Teste do método setSymbolData()
 */
TEST_F(SymbolTableTest, setSymbolDataTest) {
    table.addSymbol("symbol1", symbol);
	EXPECT_EQ(table.getSymbol("symbol1", false).getData(), (TreeNode*) 0);
    table.setSymbolData("symbol1", (TreeNode*) 15);
	EXPECT_EQ(table.getSymbol("symbol1", false).getData(), (TreeNode*) 15);
}
