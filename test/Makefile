INCLUDES = -I./$(GTEST_DIR)
CC = g++
CPPFLAGS = -DGTEST_HAS_PTHREAD=0
CXXFLAGS = -g
UNIT_EXECUTABLE = tocTest
BLACK_BOX_SCRIPT = run-black-box.sh
COMPILER = ../toc

GTEST_DIR = gtest
SRC_DIR = unit

TEST_SRCS += $(wildcard $(SRC_DIR)/*.cpp)
OBJS += $(TEST_SRCS:.cpp=.o)

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gtest: ./$(GTEST_DIR)/gtest-all.o

black-box: FORCE
	@bash ./$(BLACK_BOX_SCRIPT)

unit:	gtest $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(UNIT_EXECUTABLE) $(OBJS) ./$(GTEST_DIR)/gtest-all.o
	@echo 'Build complete!'
	@echo ' '
	@echo 'Executing tests...'
	./$(UNIT_EXECUTABLE)
	@echo 'Done!'

clean:
	rm -rf ./$(SRC_DIR)/*.o $(UNIT_EXECUTABLE)

veryclean: clean
	rm -rf ./$(GTEST_DIR)/*.o
    
FORCE:
