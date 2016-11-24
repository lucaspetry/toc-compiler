FLEX = flex
BISON = bison
LLVM=`llvm-config --cflags --ldflags --system-libs --libs core native mcjit engine interpreter`
CC = clang++
CFLAGS = -std=c++11 -fcxx-exceptions -Wno-deprecated-register -Wall -lffi
EXECUTABLE = toc
EXECUTABLE_TREE = tocTree
TYPE = TREE
DUMP = 0

# Directories
SRC_DIR = src
HEADERS_DIR = include

# Bison and Flex Files
PARSER_HEADER = $(HEADERS_DIR)/Parser.h
PARSER = tmp/Parser
SCANNER = tmp/Scanner

# Sources and objects
SRC_FILES += $(wildcard $(SRC_DIR)/*.cpp)
HEADER_FILES += $(wildcard $(HEADERS_DIR)/*.h)
OBJS += $(patsubst src/%, tmp/%, $(SRC_FILES:.cpp=.o))
OBJS += $(PARSER).o \
$(SCANNER).o

# Colors
GREEN=\033[0;32m
LIGHT_GREEN=\033[1;32m
WHITE=\033[0;37m

$(EXECUTABLE): tmp parser scanner $(OBJS)
	@echo "${GREEN}Creating executable...${WHITE}"
ifeq ($(TYPE)$(DUMP), LLVM1)
	${CC} -o ${EXECUTABLE} $(OBJS) ${CFLAGS} -I$(HEADERS_DIR) $(LLVM) -DLLVM -DLLVM_DUMP
else
ifeq ($(TYPE), LLVM)
	${CC} -o ${EXECUTABLE} $(OBJS) ${CFLAGS} -I$(HEADERS_DIR) $(LLVM) -DLLVM
else
	${CC} -o ${EXECUTABLE_TREE} $(OBJS) ${CFLAGS} -I$(HEADERS_DIR) $(LLVM)
endif
endif
	@echo "${GREEN}Creating executable... ${LIGHT_GREEN}Done!${WHITE}"
	@echo ''

superb: tmp parser scanner $(OBJS)
ifeq ($(DUMP), 1)
	${CC} -o ${EXECUTABLE} $(OBJS) ${CFLAGS} -I$(HEADERS_DIR) $(LLVM) -DLLVM -DLLVM_DUMP
else
	${CC} -o ${EXECUTABLE} $(OBJS) ${CFLAGS} -I$(HEADERS_DIR) $(LLVM) -DLLVM
endif
	${CC} -o ${EXECUTABLE_TREE} $(OBJS) ${CFLAGS} -I$(HEADERS_DIR) $(LLVM)

tmp/%.o: src/%.cpp
	@echo 'Building file: $< ($@)'
	@$(CC) $(CFLAGS) -I$(HEADERS_DIR) -O0 -w -c -o "$@" "$<" $(LLVM)

scanner: $(SRC_DIR)/Scanner.l parser
	@echo "${GREEN}Generating lexical analyzer...${WHITE}"
	${FLEX} -o $(SCANNER).cpp $(SRC_DIR)/Scanner.l
	$(CC) $(CFLAGS) -I$(HEADERS_DIR) -O0 -w -c -o $(SCANNER).o $(SCANNER).cpp $(LLVM)
	@echo "${GREEN}Generating lexical analyzer... ${LIGHT_GREEN}Done!${WHITE}"
	@echo ''

parser: $(SRC_DIR)/Parser.y
	@echo "${GREEN}Generating bottom-up parser...${WHITE}"
	${BISON} --defines=$(PARSER_HEADER) --output=$(PARSER).cpp $(SRC_DIR)/Parser.y -v
	$(CC) $(CFLAGS) -I$(HEADERS_DIR) -O0 -w -c -o $(PARSER).o $(PARSER).cpp $(LLVM)
	@echo "${GREEN}Generating bottom-up parser... ${LIGHT_GREEN}Done!${WHITE}"
	@echo ''

all: clean superb test

test: superb
	@echo "${GREEN}Executing tests...${WHITE}"
	@cd test && $(MAKE) black-box && $(MAKE) unit
	@echo "${GREEN}Executing tests... ${LIGHT_GREEN}Done!${WHITE}"
	@echo ''

test-black-box: FORCE
	@echo "${GREEN}Executing tests...${WHITE}"
	@cd test && $(MAKE) black-box
	@echo "${GREEN}Executing tests... ${LIGHT_GREEN}Done!${WHITE}"
	@echo ''

test-unit: tmp $(OBJS)
	@echo "${GREEN}Executing tests...${WHITE}"
	@cd test && $(MAKE) unit
	@echo "${GREEN}Executing tests... ${LIGHT_GREEN}Done!${WHITE}"
	@echo ''

clean:
	@echo "${GREEN}Cleaning project...${WHITE}"
	-@rm -Rf tmp
	-@rm $(PARSER_HEADER) ${EXECUTABLE} ${EXECUTABLE_TREE}
	@cd test && $(MAKE) clean
	@echo "${GREEN}Cleaning project... ${LIGHT_GREEN}Done!${WHITE}"
	@echo ''

veryclean:
	@echo "${GREEN}Cleaning project...${WHITE}"
	-@rm -Rf tmp
	-@rm $(PARSER_HEADER) ${EXECUTABLE} ${EXECUTABLE_TREE}
	@cd test && $(MAKE) veryclean
	@echo "${GREEN}Cleaning project... ${LIGHT_GREEN}Done!${WHITE}"
	@echo ''

tmp:
	@echo "${GREEN}Creating tmp directory...${WHITE}"
	@mkdir tmp
	@echo "${GREEN}Creating tmp directory... ${LIGHT_GREEN}Done!${WHITE}"
	@echo ''

FORCE:
