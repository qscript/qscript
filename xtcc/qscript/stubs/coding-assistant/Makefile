CC = $(CXX)
BUILD_DIR=make-build-dir
BUILT_SOURCES=read_data.c gram.c gram.h
PROF_FLAGS = -pg -fprofile-arcs
CFLAGS = -c -g -I src -Wall -Wno-sign-compare -Weffc++
#CPP_SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
#EXCLUDE_FILE=src/question_disk_data.cpp src/qscript_lib.cpp src/qscript_data.cpp src/read_disk_data.cpp src/question_runtime.cpp src/qtm_data_file.cpp src/XtccDataFile.cpp
#CPP_SOURCES := $(filter-out $(EXCLUDE_FILE),$(CPP_SOURCES))
#OBJECTS = $(subst $(SOURCE_DIR),$(BUILD_DIR),$(CPP_SOURCES))
#OBJECTS := $(OBJECTS:.cpp=.o)
#DEPENDENCIES = $(OBJECTS:.o=.dep)
SOURCE_DIR=src

CODE_ASSISTANT_SOURCES = src/util.cpp src/read_sentiment.cpp src/StringSpectralInfo.cpp
OBJECTS = $(subst $(SOURCE_DIR),$(BUILD_DIR),$(CODE_ASSISTANT_SOURCES))
OBJECTS := $(OBJECTS:.cpp=.o)

#dummy:
#	echo $(OBJECTS)


$(BUILD_DIR)/code_assistant.exe: $(OBJECTS)
	g++ $(PROF_FLAGS) --std=c++0x -o $@ $(OBJECTS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp;
	$(CC) $(PROF_FLAGS) --std=c++0x $(CFLAGS) -o $@ $<

analyzer.exe: $(BUILT_SOURCES)
	g++ --std=c++0x -o $@  $(BUILT_SOURCES)



read_data.c: read_data.l gram.h
	flex -o$@ $<

gram.h gram.c: gram.y
	bison -d gram.y  -o gram.c



