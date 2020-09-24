from __future__ import print_function
from subprocess import call
import os
import glob
import filecmp

test_files_dir = "file_tests/"
input_files_dir = test_files_dir + "input_files/"
command_output_files_dir = test_files_dir + "output_files/"

my_executable = "ikea"
school_executable = "school_ikea"
pre_name_of_my_file = "my_output_"

pre_name_of_school_file = "school_output_"
CLEAN = "make clean"
COMPILATION = "make"

school_command_prompt = "file_tests/input_files/school_prompts.txt"
negative_command_prompt = "file_tests/input_files/negative_prompts.txt"
selling_and_printing_prompt = "file_tests/input_files/selling_and_printing_prompts.txt"
tempfile = "file_tests/input_files/temp_school_prompts.txt"

all_freed = "All heap blocks were freed -- no leaks are possible"



def main():
    if (compileProgram()):

        school_flag = school_given_tests()
        negative_tests_flag = negative_syntax()
        selling_and_printing = selling_and_printing_tests()

        valgrind_flag = False

        if school_flag and negative_tests_flag and selling_and_printing:
            valgrind_flag = checkValgrind()

        else:
            print("failed some tests, stopping tester :/")

        if valgrind_flag:
            print("\nhurray! passed all tests!")






def executeTest(file_name):
    file = getCommandFile(file_name)
    my_code, my_output_file_dir = get_my_file_prefixes(tempfile, file_name)
    school_code, school_output_file_dir = get_school_file_prefixes(tempfile, file_name)
    call_my_code(my_code)
    call(school_code, shell=True)
    return my_output_file_dir, school_output_file_dir


def compareFiles(my_output_file_dir, passedAllTests, school_output_file_dir):
    if filecmp.cmp(school_output_file_dir, my_output_file_dir):
        os.remove(my_output_file_dir)
        os.remove(school_output_file_dir)
        print("\tpassed!  =]")
    else:
        print("problem in file. see difference in: " + os.path.dirname(
            os.path.realpath(__file__)) + "/" + command_output_files_dir)
        passedAllTests = False
    return passedAllTests


def selling_and_printing_tests():
    print()
    passedAllTests = True
    print("======testing selling and printing: ======\n")
    for file_name in glob.glob1(input_files_dir, "selling_and_printing_tests*.txt"):
        print("testing file: " + file_name + " ",end="")
        file = getCommandFile(file_name)
        my_output_file_dir, school_output_file_dir = executeTest(file_name)
        passedAllTests = compareFiles(my_output_file_dir, passedAllTests, school_output_file_dir)
    os.remove(tempfile)
    return passedAllTests


def call_my_code(my_code):
    call(my_code, shell=True)
    # list_of_commands.append(my_code)


def compileProgram():
    print("attempting to compile: ")
    call(CLEAN, shell=True)
    check = call(COMPILATION, shell=True)
    if (check == 0):
        print("compiled successfully!")
    return (check == 0)



def negative_syntax():
    print()
    passedAllTests = True
    print("======testing negative syntax: ======")
    for file_name in glob.glob1(input_files_dir, "negative_test*.txt"):
        print("testing file: " + file_name + " ",end="")
        file = getCommandFile(file_name)
        my_code, my_output_file_dir = get_my_file_prefixes(tempfile, file_name)
        school_code, school_output_file_dir = get_school_file_prefixes(tempfile, file_name)
        call_my_code(my_code)
        call(school_code, shell=True)
        passedAllTests = compareFiles(my_output_file_dir, passedAllTests, school_output_file_dir)
    os.remove(tempfile)
    return passedAllTests



def school_given_tests():
    print()
    passedAllTests = True
    print("======testing school given files: ======\n")
    for file_name in glob.glob1(input_files_dir, "school_example*.txt"):
        print("testing file: " + file_name + " ",end="")
        file = getCommandFile(file_name)
        my_output_file_dir, school_output_file_dir = executeTest(file_name)
        passedAllTests = compareFiles(my_output_file_dir, passedAllTests, school_output_file_dir)
    os.remove(tempfile)
    return passedAllTests


def getCommandFile(file_name):
    command_prompt = ""
    if(file_name.startswith("school_example")): command_prompt = school_command_prompt
    elif file_name.startswith("negative_test"): command_prompt = negative_command_prompt
    elif file_name.startswith("selling_and_printing_tests"): command_prompt = selling_and_printing_prompt
    file = input_files_dir + file_name
    with open(command_prompt, "rt") as fin:
        with open(tempfile, "wt") as fout:
            for line in fin:
                fout.write(line.replace('current_file', file))
    return file


def checkValgrind():
    print()
    print("======valgrind tests======\n")
    passedTests = True
    for file_name in glob.glob1(input_files_dir, "*.txt"):
        if(file_name.endswith("prompts.txt")):
            continue
        print("testing file: " + file_name + " ", end="")
        file = getCommandFile(file_name)
        my_code, my_output_file_dir = get_my_file_prefixes(tempfile, "valgrind_"+file_name)
        my_code = "valgrind " + my_code
        call(my_code, shell=True)
        file_handled_correctly = True
        with open(my_output_file_dir) as myfile:
            if all_freed not in myfile.read():
                file_handled_correctly = False
        if file_handled_correctly:
            os.remove(my_output_file_dir)
            print("\tpassed!  =]")
        else:
            print("\t meh :\ see difference in the output dir: " + os.path.dirname(
                os.path.realpath(__file__)) + "/" + command_output_files_dir)
            passedTests = False
    return passedTests




def get_school_file_prefixes(command_file, test_prefix):
    school_output_file = pre_name_of_school_file
    school_output_file_dir = command_output_files_dir + school_output_file + test_prefix
    school_code = school_executable  +" < "+command_file+ " >& " + school_output_file_dir
    return school_code, school_output_file_dir


def get_my_file_prefixes(command_file, test_prefix):
    my_output_file = pre_name_of_my_file
    my_output_file_dir = command_output_files_dir + my_output_file + test_prefix
    my_code = my_executable +" < "+command_file+ " >& " + my_output_file_dir
    return my_code, my_output_file_dir


def get_input_file_dir(text):
    input_files_values_dir = input_files_dir + text
    return input_files_values_dir



if __name__ == "__main__":
    main()


class TimedOutExc(Exception):
    pass