CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -Iinclude -IC:/tools/curl-8.17.0_2-win64-mingw/include
LDFLAGS = -LC:/tools/curl-8.17.0_2-win64-mingw/lib -lcurl
SRC = src/main.cpp src/task.cpp src/utils.cpp src/file_storage.cpp
OUT = taskmgr.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

clean:
	del /f $(OUT)

.PHONY: all clean