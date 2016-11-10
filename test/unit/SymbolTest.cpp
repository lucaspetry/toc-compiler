#include "gtest.h"
#include "Symbol.h"

/**
 * @brief Teste da classe Symbol
 */
class SymbolTest : public ::testing::Test {

protected:
	virtual void SetUp() {
        s = Symbol(Data::INT, Symbol::VARIABLE, false, 0);
	}

	virtual void TearDown() {
	}
    
    Symbol s;

};

/**
 * @brief Teste do método getData()
 */
TEST_F(SymbolTest, getDataTest) {
	EXPECT_FALSE(s.getData());
}

/**
 * @brief Teste do método getDataType()
 */
TEST_F(SymbolTest, getDataTypeTest) {
	EXPECT_EQ(s.getDataType(), Data::INT);
}

/**
 * @brief Teste do método getType()
 */
TEST_F(SymbolTest, getTypeTest) {
	EXPECT_EQ(s.getType(), Symbol::VARIABLE);
}

/**
 * @brief Teste do método isInitialized()
 */
TEST_F(SymbolTest, isInitializedTest) {
	EXPECT_EQ(s.isInitialized(), false);
}

/**
 * @brief Teste do método setDataType()
 */
TEST_F(SymbolTest, setDataTypeTest) {
    s.setDataType(Data::BOO);
	EXPECT_EQ(s.getDataType(), Data::BOO);
}
