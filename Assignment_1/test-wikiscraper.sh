#!/usr/bin/python3

# This was based on a mastery check-in quiz framework built by Sathya Edamadaka.
# This script runs one or more tests as indicated in the file "test_cases", and
# prints out any information about any test failures. Heavily inspired by the CS111
# autograder. Usage:
# ./test-wikiscraper [test_case_file]
# If test_case_file is provided, it name a file containing test case
# descriptions; otherwise information is read from the file "test_cases."
#
# Format of test cases file: each line is a single command giving a bash command
# to invoke. I've written it this way in order to be able to reuse this autograder
# file across mastery check-ins, exercises, assigments, and more!

import locale
import os
import subprocess
import sys

# compile test script and wikiscraper for files with cmake;
subprocess.run(["sh", "-c", "cd build; ./build-test.sh; cd .."], capture_output=False,
                timeout=10, encoding=locale.getpreferredencoding())

if len(sys.argv) == 2:
    f = open(sys.argv[2], newline='\n')
elif len(sys.argv) == 1:
    f = open("./test-resources/test-cases", newline='\n')
else:
    print("Usage: ./test-wikiscraper [test_case_file]")
    sys.exit(1)

failures = 0
n_tests = 0

while True:
    # Skip blank lines and read command
    while True:
        command = f.readline()
        if not command:
            break
        if command[0] == '#':
            continue
        command = command.rstrip()
        if command:
            break
    if not command:
        break

    # Run the command (with a time limit).
    test_msg = 'Running test: ' + command
    prev_failures = failures
    print(test_msg, end='')
    solution_command = command.replace('./build/test', './test-resources/test')

    try:
        student_result = subprocess.run(["sh", "-c", command], capture_output=True,
                timeout=10, encoding=locale.getpreferredencoding())
        solution_result = subprocess.run(["sh", "-c", solution_command], capture_output=True,
                timeout=10, encoding=locale.getpreferredencoding())
    except subprocess.TimeoutExpired as e:
        print()
        print("Error: '%s' took too long" % (command))
        continue

    # Parse and check the results.
    if student_result.stderr != solution_result.stderr:
        print()
        print(f"Error: incorrect error output; expected output: \n------------------\n{solution_result.stderr}",
                end="")
        print("------------------\nbut actual output was")
        print(f"------------------\n{student_result.stderr}", end="")
        print("------------------")

    student_output = "".join(student_result.stdout.split('\r'))
    solution_output = "".join(solution_result.stdout.split('\r'))
    if (student_output != solution_output):
        print()
        failures += 1
        print(f"Error: wrong student output! First few lines of expected output\n------------------\n{solution_output[:min(5000, len(solution_output))]}",
                end="")
        print("\n------------------\nbut first few lines of student's output were")
        print(f"------------------\n{student_output[:min(5000, len(student_output))]}", end="")
        print("------------------")

    # print confirmation that test finished (delete old message)
    final_message = '\b'*len(test_msg) if failures == prev_failures else '' + 'Finished running test: ' + command
    print(final_message)
    n_tests += 1

if failures:
    print(f"{failures} tests failed out of {n_tests} tests.")
else:
    print(f"All {n_tests} tests passed!")

