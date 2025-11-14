CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -Iinclude
SRC = src/main.cpp src/task.cpp src/utils.cpp src/file_storage.cpp
OUT = taskmgr

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT) *.exe

.PHONY: all clean
