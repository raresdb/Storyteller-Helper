#©Intellectual property of Butilca Rares-Dumitru

#Note that the Makefile should be in the same folder as /source and /tool text files
#Upon moving the compiled binary file, /tool text files should be moved in the same folder

#setting up the compiler
C++C=g++
C++FLAGS=-std=c++11

#define target and dependencies
TARGET=storyteller_helper
C++FILES=source/storyteller_helper.cpp
HEADERS=source/characters.h

build:$(TARGET)

$(TARGET): $(C++FILES) $(HEADERS)
	$(C++C) $(C++FILES) $(C++FLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./storyteller_helper

.PHONY: clean run build