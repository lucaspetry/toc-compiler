INCLUDES = -I./$(GTEST_DIR) -I$(HEADERS_DIR)
LLVM=`llvm-config --cflags --ldflags --system-libs --libs core native mcjit engine interpreter`
CC = clang++
CPPFLAGS =  -std=c++11 -DGTEST_HAS_PTHREAD=0 -w -lffi
CXXFLAGS = -g
UNIT_EXECUTABLE = tocTest
BLACK_BOX_SCRIPT = run-black-box.sh

HEADERS_DIR = ../include
GTEST_DIR = gtest
TEST_SRC_DIR = unit

SRCS += $(wildcard $(TEST_SRC_DIR)/*.cpp)
OBJS += $(SRCS:.cpp=.o)

OBJS_DIR =  ../tmp
OBJS_TOC += $(wildcard $(OBJS_DIR)/*.o)
OBJS_TOC := $(filter-out $(OBJS_DIR)/Main.o, $(OBJS_TOC))

%.o: %.cpp
	@echo 'Building file: $<'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<" $(LLVM)
	@echo ' '

gtest: ./$(GTEST_DIR)/gtest-all.o

black-box: FORCE
	@bash ./$(BLACK_BOX_SCRIPT)

unit: gtest $(OBJS) FORCE
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(UNIT_EXECUTABLE) $(OBJS) $(OBJS_TOC) ./$(GTEST_DIR)/gtest-all.o $(LLVM)
	@echo ' '
	@./$(UNIT_EXECUTABLE)

clean:
	rm -rf ./$(TEST_SRC_DIR)/*.o $(UNIT_EXECUTABLE)

veryclean: clean
	rm -rf ./$(GTEST_DIR)/*.o

FORCE:
