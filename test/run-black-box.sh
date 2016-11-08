#!/bin/sh -e

# Configs
EXECUTABLE_TREE=../tocTree
EXECUTABLE=../toc
INPUT_EXT='.toc'
OUTPUT_EXT='.exp'
OUTPUT_EXT2='.llvm'
INPUT_FILES=$(find black-box -type f -name "*$INPUT_EXT" | sort)
OUTPUT_FILES=$(find black-box -type f -name "*$OUTPUT_EXT" | sort)
OUTPUT_FILES2=$(find black-box -type f -name "*$OUTPUT_EXT2" | sort)
IFS=$'\r\n' GLOBIGNORE='*' command eval 'INPUT_FILES=($INPUT_FILES)'
IFS=$'\r\n' GLOBIGNORE='*' command eval 'OUTPUT_FILES=($OUTPUT_FILES)'
IFS=$'\r\n' GLOBIGNORE='*' command eval 'OUTPUT_FILES2=($OUTPUT_FILES2)'

# Colors
BLACK='\e[0;30m';       B_BLACK='\e[1;30m';
RED='\e[0;31m';         B_RED='\e[1;31m';
GREEN='\e[0;32m';       B_GREEN="\e[1;32m"
YELLOW='\e[0;33m';      B_YELLOW='\e[1;33m';
BLUE='\e[0;34m';        B_BLUE='\e[1;34m';
PURPLE='\e[0;35m';      B_PURPLE='\e[1;35m';
CYAN='\e[0;36m';        B_CYAN='\e[1;36m';
WHITE='\e[0;37m';       B_WHITE='\e[1;37m';

# Headers
HEAD_INPUT="${WHITE} [  Input   ]"
HEAD_RUN="${GREEN} [   Run    ]"
HEAD_BAD_RUN="${RED} [   Run    ]"
HEAD_RESULT="${B_GREEN} [  Result  ]"
HEAD_BAD_RESULT="${RED} [  Result  ]"
HEAD_EXPECTED="${WHITE} [ Expected ]"
HEAD_OUTPUT="${RED} [  Output  ]"

# Test numbers
TESTS_RUN=0
TESTS_NOT_RUN=0
TESTS_FAILED=0
TESTS_SUCCESS=0

# Tests header
echo -e "${WHITE}----------------------------------------------------------------"
echo -e "                       TOC Compiler Tests                       "
echo -e "----------------------------------------------------------------"
echo -e "${WHITE} Input Files Directory ($INPUT_EXT): ${B_WHITE}black-box/ ${B_BLUE}(${#INPUT_FILES[@]} files)"
echo -e "${WHITE} Expected Output Files Directory ($OUTPUT_EXT): ${B_WHITE}black-box/ ${B_BLUE}(${#OUTPUT_FILES[@]} files)"
echo -e "${WHITE} LLVM Output Files Directory ($OUTPUT_EXT2): ${B_WHITE}black-box/ ${B_BLUE}(${#OUTPUT_FILES2[@]} files)"
echo -e "${WHITE}----------------------------------------------------------------"

# For every input file found in files/
for i in "${INPUT_FILES[@]}"
do
    echo -e "$HEAD_INPUT $i"
    # Get the expected output file name (.out)
    OUTPUT_FILE="${i%.*}$OUTPUT_EXT"
    OUTPUT_FILE2="${i%.*}$OUTPUT_EXT2"

    # If output file exists, then runs the test
    if [[ -f $OUTPUT_FILE ]]
    then
        echo -e "$HEAD_RUN Expected output file: $OUTPUT_FILE"

        # Runs the test and stores the output
        OUTPUT="$($EXECUTABLE_TREE < $i 2>/dev/null)"
        OUTPUT_ERRORS="$($EXECUTABLE_TREE < $i 2>&1 1>/dev/null)"
        EXPECTED_OUTPUT="$(cat $OUTPUT_FILE)"
        TESTS_RUN=$((TESTS_RUN+1))

        # If expected output is equal to the output, then prints success
        if [ "$EXPECTED_OUTPUT" = "$OUTPUT" ] && [$OUTPUT_ERRORS != ""]; then
            TESTS_SUCCESS=$((TESTS_SUCCESS+1))
            echo -e "$HEAD_RESULT SUCCESS!"
        elif [ "$EXPECTED_OUTPUT" = "$OUTPUT_ERRORS" ]; then
            TESTS_SUCCESS=$((TESTS_SUCCESS+1))
            echo -e "$HEAD_RESULT SUCCESS!"
        else
            TESTS_FAILED=$((TESTS_FAILED+1))
            echo -e "$HEAD_BAD_RESULT FAILED!"
            echo -e "$HEAD_EXPECTED"
            echo -e "$EXPECTED_OUTPUT\n"
            echo -e "$HEAD_OUTPUT"
            echo -e "$OUTPUT\n$OUTPUT_ERRORS\n"
        fi

    else
        TESTS_NOT_RUN=$((TESTS_NOT_RUN+1))
        echo -e "$HEAD_BAD_RUN No output file ${B_RED}$OUTPUT_FILE${RED} was found!"
    fi

    if [[ -f $OUTPUT_FILE2 ]]
    then
        echo -e "$HEAD_RUN Expected output file: $OUTPUT_FILE2"

        # Runs the test and stores the output
        OUTPUT="$($EXECUTABLE < $i 2>/dev/null)"
        OUTPUT_ERRORS="$($EXECUTABLE < $i 2>&1 1>/dev/null)"
        EXPECTED_OUTPUT="$(cat $OUTPUT_FILE2)"
        TESTS_RUN=$((TESTS_RUN+1))

        # If expected output is equal to the output, then prints success
        if [ "$EXPECTED_OUTPUT" = "$OUTPUT" ] && [$OUTPUT_ERRORS != ""]; then
            TESTS_SUCCESS=$((TESTS_SUCCESS+1))
            echo -e "$HEAD_RESULT SUCCESS!"
        elif [ "$EXPECTED_OUTPUT" = "$OUTPUT_ERRORS" ]; then
            TESTS_SUCCESS=$((TESTS_SUCCESS+1))
            echo -e "$HEAD_RESULT SUCCESS!"
        else
            TESTS_FAILED=$((TESTS_FAILED+1))
            echo -e "$HEAD_BAD_RESULT FAILED!"
            echo -e "$HEAD_EXPECTED"
            echo -e "$EXPECTED_OUTPUT\n"
            echo -e "$HEAD_OUTPUT"
            echo -e "$OUTPUT\n$OUTPUT_ERRORS\n"
        fi

    else
        TESTS_NOT_RUN=$((TESTS_NOT_RUN+1))
        echo -e "$HEAD_BAD_RUN No output file ${B_RED}$OUTPUT_FILE2${RED} was found!"
    fi

    echo -e ""

done

echo -e "${WHITE}----------------------------------------------------------------"
echo -e "${WHITE} $TESTS_RUN test(s) run!"
if [[ $TESTS_FAILED != 0 ]]; then
    echo -e "  ${GREEN} $((TESTS_RUN-TESTS_FAILED)) test(s) passed!"
    echo -e "  ${RED} $TESTS_FAILED test(s) failed!"
else
    echo -e "  ${B_GREEN} All tests were successful!"
fi

if [[ $TESTS_NOT_RUN != 0 ]]; then
    echo -e "${YELLOW} $TESTS_NOT_RUN test(s) not run! (no output file found)"
fi

echo -e "${WHITE}----------------------------------------------------------------"

exit 0
