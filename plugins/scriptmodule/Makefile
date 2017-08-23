##############################################
# Name of your plugin.                       #
# (output file: lib<PLUGIN_NAME>.so or .dll) #
##############################################
PLUGIN_NAME=scriptmodule
#######################################################
# Header files include directory for Windows and UNIX #
#######################################################
INCLUDEDIR_UNIX=
INCLUDEDIR_WIN32=
#################################################
# Additional static libraries needs to be added #
#################################################
ADDITIONALLIBS_UNIX=
ADDITIONALLIBS_WIN32=




#################################
# Common definitions            #
# (rarely needed to be changed) #
#################################
CC=g++
# Noteworthy: server compiled against libgcc and libstdc++ statically, so
#   dynamic linking will cause crash at exit.
CFLAGS=-m32 -O3 -Wall -s --pedantic -std=c++11 -static-libgcc -static-libstdc++ -I../../src/phandler
C_MODULES=$(wildcard *.c)
CPP_MODULES=$(wildcard *.cpp)
C_OBJECTS=$(patsubst %.c,obj/%.o,$(C_MODULES))
CPP_OBJECTS=$(patsubst %.cpp,obj/%.o,$(CPP_MODULES))
OBJECTS=$(C_OBJECTS) $(CPP_OBJECTS)

TARGET_OS = $(shell $(CC) -dumpmachine)

ifeq      ($(TARGET_OS),mingw32)
INCLUDEDIR=$(INCLUDEDIR_WIN32)
ADDITIONALLIBS=$(ADDITIONALLIBS_WIN32)
else ifeq ($(TARGET_OS),i686-w64-mingw32)
INCLUDEDIR=$(INCLUDEDIR_WIN32)
ADDITIONALLIBS=$(ADDITIONALLIBS_WIN32)
else
CFLAGS += -fPIC
INCLUDEDIR=$(INCLUDEDIR_UNIX)
ADDITIONALLIBS=$(ADDITIONALLIBS_UNIX)
endif


############
# Recipies #
############
ifeq      ($(TARGET_OS),mingw32)
all: win32
else ifeq ($(TARGET_OS),i686-w64-mingw32)
all: win32
else
all: unix
endif
	@echo Done


obj/%.o: %.cpp
	@echo $(CC)    "$^ -> $@"
	@$(CC) $(CFLAGS) $(INCLUDEDIR) -o $@ -c $<

obj/%.o: %.c
	@echo $(CC)    "$^ -> $@"
	@$(CC) $(CFLAGS) $(INCLUDEDIR) -o $@ -c $<

ifeq      ($(TARGET_OS),mingw32)
clean: clean_win32
else
clean: clean_unix
endif
	@echo Clean done


#####################
# Recipies: Windows #
#####################
win32: bin/lib$(PLUGIN_NAME).dll

bin/lib$(PLUGIN_NAME).dll: $(OBJECTS)
	@echo $(CC)    "$@"
	@$(CC) -shared $(CFLAGS) -o $@ $^ -L./.. -lcom_plugin $(ADDITIONALLIBS)

clean_win32:
	@del $(subst /,\\,$(OBJECTS))


##################
# Recipies: UNIX #
##################
unix: bin/lib$(PLUGIN_NAME).so

bin/lib$(PLUGIN_NAME).so: $(OBJECTS)
	@echo $(CC)    "$@"
	@$(CC) -shared $(CFLAGS) -o $@ $^ $(ADDITIONALLIBS)

clean_unix:
	@rm -r $(OBJECTS)
