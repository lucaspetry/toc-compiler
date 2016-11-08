INCLUDES = -I./$(GTEST_DIR) -I$(HEADERS_DIR)
CC = g++
CPPFLAGS =  -std=c++11 -DGTEST_HAS_PTHREAD=0
CXXFLAGS = -g
UNIT_EXECUTABLE = tocTest
BLACK_BOX_SCRIPT = run-black-box.sh

HEADERS_DIR = ../include
GTEST_DIR = gtest
TEST_SRC_DIR = unit

SRCS += $(wildcard $(TEST_SRC_DIR)/*.cpp)
SRCS += ../src/Symbol.cpp \
 ../src/SymbolTable.cpp \

OBJS += $(SRCS:.cpp=.o)

%.o: %.cpp
	@echo 'Building file: $<'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"
	@echo ' '

gtest: ./$(GTEST_DIR)/gtest-all.o

black-box: FORCE
	@bash ./$(BLACK_BOX_SCRIPT)

unit: gtest $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(UNIT_EXECUTABLE) $(OBJS) ./$(GTEST_DIR)/gtest-all.o
	@echo ' '
	-@rm -rf ../src/*.o
	@./$(UNIT_EXECUTABLE)

clean:
	rm -rf ./$(TEST_SRC_DIR)/*.o $(UNIT_EXECUTABLE)

veryclean: clean
	rm -rf ./$(GTEST_DIR)/*.o

FORCE:
