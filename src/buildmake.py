import os
OutputFile = open("Android.mk",'w')

def PrintFiles(files,prefix):
    OutputFile.write("\t")
    for f in files:
        if(f.endswith("cpp")):
            OutputFile.write(prefix+f)
            OutputFile.write(" ")
    OutputFile.write("\\\n")
    for f in files:
        if(os.path.isdir(f)):
           PrintFiles(os.listdir(f),(f+"/"))
           

def Main():
    
    OutputFile.write('LOCAL_PATH := $(call my-dir)\n\n')
    OutputFile.write('include $(CLEAR_VARS)\n\n')
    OutputFile.write('LOCAL_MODULE := main\n\n')
    OutputFile.write('SDL_PATH := ../SDL\n\n')
    OutputFile.write('LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include\n\n')
    OutputFile.write('# Add your application source files here... \n')
    OutputFile.write('LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \\\n')

    PrintFiles(os.listdir('.'),"")

    OutputFile.write('\n')
    OutputFile.write('LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf SDL2_mixer\n\n')
    OutputFile.write('LOCAL_LDLIBS := -lGLESv1_CM -llog\n\n')
    OutputFile.write('include $(BUILD_SHARED_LIBRARY)\n\n')

    OutputFile.close()

Main()
