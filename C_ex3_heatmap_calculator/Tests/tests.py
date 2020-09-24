from __future__ import print_function
from subprocess import call
import os
import glob
import filecmp

GENERIC_ERROR_MSG = 'Error with file format: '

test_files_dir = "test_files/"
input_files_dir = test_files_dir + "input_files/"
command_output_files_dir = test_files_dir + "output_files/"

my_executable = "my_reader"
school_executable = "school_reader"
pre_name_of_my_file = "my_output_"

pre_name_of_school_file = "school_output_"
FILES = "calculator.c calculator.h reader.c heat_eqn.c heat_eqn.h"
COMPILATION = "gcc -Wall -Wvla -std=c99 " + FILES + " -o " + my_executable


extract_to_tar = "tar cvf ex3.tar reader.c calculator.c Makefile"

def main():
    compileProgram()
    a = checkByValues()
    b = checkBySyntax()
    if a and b:
        print("hurray! creating tar file: ")
        call(extract_to_tar,shell=True)


def compileProgram():
    print("attempting to compile: ")
    call(COMPILATION, shell=True)
    print("compilation successfull\n")


def checkBySyntax():
    print()
    print("checking syntax reading files: ")
    create_tar = True
    input_files_values_dir = input_files_dir + "testing_by_syntax/"
    for file in glob.glob1(input_files_values_dir, "*.txt"):
        print("testing file: " + file + " ", end="")
        my_code, my_output_file_dir = get_my_file_prefixes_error(file, input_files_values_dir)
        call(my_code, shell=True)
        fileHandledCorrectly = True
        with open(my_output_file_dir) as myfile:
            if GENERIC_ERROR_MSG not in myfile.read():
                fileHandledCorrectly = False
        if fileHandledCorrectly:
            os.remove(my_output_file_dir)
            print("\tpassed!=]")
        else:
            print("\t meh :\ see difference in the output dir: " + os.path.dirname(os.path.realpath(__file__)) + "/" + command_output_files_dir)
            school_code, school_output_file_dir = get_school_file_prefixes_error(file,input_files_values_dir)
            call(school_code, shell=True)
            create_tar = False
    return create_tar



def get_school_file_prefixes_error(file, input_files_values_dir):
    school_output_file = pre_name_of_school_file + file
    school_output_file_dir = command_output_files_dir + school_output_file
    school_code = school_executable + " " + input_files_values_dir + file + " >&" + school_output_file_dir
    return school_code, school_output_file_dir


def get_my_file_prefixes_error(file, input_files_values_dir):
    my_output_file = pre_name_of_my_file + file
    my_output_file_dir = command_output_files_dir + my_output_file
    my_code = my_executable + " " + input_files_values_dir + file + " >&" + my_output_file_dir
    return my_code, my_output_file_dir




def checkByValues():
    print("checking value files: ")
    input_files_values_dir = input_files_dir + "testing_by_values/"
    create_tar = True
    for file in glob.glob1(input_files_values_dir, "*.txt"):
        print("testing file: " + file + " ", end="")
        my_code, my_output_file_dir = get_my_file_prefixes(command_output_files_dir, file, input_files_values_dir,
                                                           my_executable, pre_name_of_my_file)

        school_code, school_output_file_dir = get_school_file_prefixes(command_output_files_dir, file,
                                                                       input_files_values_dir, pre_name_of_school_file,
                                                                       school_executable)
        call(school_code, shell=True)
        call(my_code, shell=True)
        if filecmp.cmp(school_output_file_dir, my_output_file_dir):
            os.remove(my_output_file_dir)
            os.remove(school_output_file_dir)
            print("\tpassed!=]")
        else:
            print("problem in file: " + file + ",see difference in the output dir: " + os.path.dirname(
                os.path.realpath(__file__)) + "/" + command_output_files_dir)
            create_tar = False
    return create_tar



def get_school_file_prefixes(command_output_files_dir, file, input_files_values_dir, pre_name_of_school_file,
                             school_executable):
    school_output_file = pre_name_of_school_file + file
    school_output_file_dir = command_output_files_dir + school_output_file
    school_code = school_executable + " " + input_files_values_dir + file + " >" + school_output_file_dir
    return school_code, school_output_file_dir


def get_my_file_prefixes(command_output_files_dir, file, input_files_values_dir, my_executable, pre_name_of_my_file):
    my_output_file = pre_name_of_my_file + file
    my_output_file_dir = command_output_files_dir + my_output_file
    my_code = my_executable + " " + input_files_values_dir + file + " >" + my_output_file_dir
    return my_code, my_output_file_dir



if __name__ == "__main__":
    main()
