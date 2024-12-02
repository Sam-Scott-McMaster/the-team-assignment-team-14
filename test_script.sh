#!/bin/bash

# Global variables for test tracking. tc = test case number, fails = number of fails 
declare -i tc=0
declare -i fails=0

############################################
# Run a single test by comparing output messages
#
# GLOBALS: tc, fails
# PARAMS: $1 = command
#         $2 = expected stdout
# RETURNS: 0 = success, 1 = failed
############################################
test() {
    tc=tc+1

    local COMMAND=$1
    local EXPECTED_STDOUT=$2

    # Capture actual stdout
    local ACTUAL_STDOUT=$($COMMAND)

    # Compare the output
    if [[ "$ACTUAL_STDOUT" == "$EXPECTED_STDOUT" ]]; then
        echo "Test $tc Passed"
        return 0
    else
        echo "Test $tc Failed"
        echo "   Command: $COMMAND"
        echo "   Expected: $EXPECTED_STDOUT"
        echo "   Got: $ACTUAL_STDOUT"
        fails=$fails+1
        return 1
    fi
}

##########################################
# TEST CASES
##########################################

# Test 1
test "./checkguess Glen" "You Win! Glen is the murderer!"

# Test 2
test "./checkguess Shaun Glen" "Incorrect guess You Win! Glen is the murderer!"

# Test 3
test "./checkguess Shaun Clayton" "Incorrect guess Game Over! You've exhausted your number of tries."


##########################################
# Summary
##########################################

echo "Total Tests: $tc"
echo "Failed Tests: $fails"

exit $fails
