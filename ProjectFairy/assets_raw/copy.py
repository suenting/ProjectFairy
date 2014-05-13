import os
import shutil

dest = "../assets/"
src = "."

def copy(files,prefix):
    for f in files:
        if(os.path.isdir(prefix+f)):
           copy(os.listdir(prefix+f),prefix+f+"/")
        else:
            if( not f.endswith(".py")):
                shutil.copyfile((prefix+f),dest+f)

def main():
    copy(os.listdir('.'),"")

main()


