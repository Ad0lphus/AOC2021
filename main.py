# program to run all python files in the directory of all days

import os
import sys
import glob
import subprocess

tree='''
`✿❤✿•*´¯`✿❤❤✿•*´¯❤✿•*´¯`❤✿•*`✿❤✿•*´¯`✿❤❤✿•*´¯❤✿•*´¯`❤✿•*
`✿❤✿•*´¯`✿❤❤✿•*´¯❤✿•*´¯`❤✿•*`✿❤✿•*´¯`✿❤❤✿•*´¯❤✿•*´¯`❤✿•*
*.*★ . ✶•´ ☆´,•*´¨★
☆´¸.•★´ ¸.✶* ☆★
¨¨¨¨¨¨¨¨¨ **¨¨¨¨¨¨¨¨¨
¨¨¨¨¨¨¨¨¨*o*¨¨¨¨¨¨¨¨¨
¨¨¨¨¨¨¨¨*♥*o*¨¨¨¨¨¨¨¨
¨¨¨¨¨¨¨***o***¨¨¨¨¨¨¨
¨¨¨¨¨¨**o**♥*o*¨¨¨¨¨¨          ADVENT OF CODE 2021
¨¨¨¨¨**♥**o**o**¨¨¨¨¨
¨¨¨¨**o**♥***♥*o*¨¨¨¨
¨¨¨*****♥*o**o****¨¨¨
¨¨**♥**o*****o**♥**¨¨
¨******o*****♥**o**¨¨
****o***♥**o***♥*****
¨¨¨¨¨ ____!_!___ _¨¨¨
¨¨¨¨¨ \_________ /¨¨¨
`-'
*.*★v . ✶•´ ☆´,•*´¨★
☆´¸.•★´ ¸.✶* ☆★
`✿❤✿•*´¯`✿❤❤✿•*´¯❤✿•*´¯`❤✿•*`✿❤✿•*´¯`✿❤❤✿•*´¯❤✿•*´¯`❤✿•*
`✿❤✿•*´¯`✿❤❤✿•*´¯❤✿•*´¯`❤✿•*`✿❤✿•*´¯`✿❤❤✿•*´¯❤✿•*´¯`❤✿•*
'''
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
def kotlin():
    current_dir = os.getcwd()
    folders = os.listdir(current_dir)
    folders = [x for x in folders if x.startswith("day")]
    for i in folders:
        os.chdir(current_dir+"/"+i+"/Kotlin")
        current_sub_dir = os.getcwd()
        for j in os.listdir(current_sub_dir):
            if j.endswith(".jar"):
                os.system("java -jar "+j)
if __name__ == "__main__":
    print(tree)
    print("""
    1) Run all python files in all days
    2) Run all cpp files in all days
    3) Run all kotlin files in all days
    """)
    choice = input("enter your choice: ")
    if choice == "1":
        python()
    elif choice == "2":
        cpp()
    elif choice == "3":
        kotlin()
    else:
        print("Invalid choice")