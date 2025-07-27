CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = rummikub
SRC = rummikub/Main.cpp rummikub/tTile.cpp rummikub/tSet.cpp rummikub/tRack.cpp rummikub/tRacks.cpp rummikub/tBag.cpp rummikub/tBoard.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	del $(TARGET).exe 2> NUL || rm -f $(TARGET)
