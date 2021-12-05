# program to run all python files in the directory of all days

import os
import sys
import glob
import subprocess


def python():
    current_dir = os.getcwd()
    folders = os.listdir(current_dir)
    folders = [x for x in folders if x.startswith("day")]
    for i in folders:
        os.chdir(current_dir+"/"+i+"/Python")
        current_sub_dir = os.getcwd()
        for j in os.listdir(current_sub_dir):
            if j.endswith(".py"):
                subprocess.call(["python3", j])

def cpp():
    current_dir = os.getcwd()
    folders = os.listdir(current_dir)
    folders = [x for x in folders if x.startswith("day")]
    for i in folders:
        os.chdir(current_dir+"/"+i+"/CPP")
        current_sub_dir = os.getcwd()
        for j in os.listdir(current_sub_dir):
            if j.endswith(".out"):
                os.system("./"+j)
if __name__ == "__main__":
    print("""
    1) Run all python files in all days
    2) Run all cpp files in all days
    """)
    choice = input("enter your choice: ")
    if choice == "1":
        python()
    elif choice == "2":
        cpp()
    else:
        print("Invalid choice")