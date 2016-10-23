#include "gtest.h"

/**
 * @brief Teste
 */
class SampleTest : public ::testing::Test {

protected:
	virtual void SetUp() {
		// SetUp()
	}

	virtual void TearDown() {
	}

};

/**
 * @brief Teste 1
 */
TEST_F(SampleTest, TestSample1) {
	EXPECT_STRCASEEQ("Test1", "Test2");
}

/**
 * @brief Teste 2
 */
TEST_F(SampleTest, TestSample2) {
	EXPECT_STRCASEEQ("Test1", "Test1");
}
