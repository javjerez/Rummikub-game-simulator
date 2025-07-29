# 📚 Rummikub Game Simulator (C++)

This is a console based implementation of the classic board game **Rummikub**. The game simulates multiple players, uses dynamic memory, linked lists, and features modular design across several `.cpp` and `.h` files.

> Fully written in `C++` using dynamic memory, pointers, and linked lists.

## Gameplay Overview

- 4 players take turns placing tiles from their rack onto the board.
- Tiles can form **groups** (same number, different colors) or **runs** (consecutive numbers of the same color).
- Players can:
  - **Sort** their rack by number or color
  - **Preview possible sets**
  - **Play tiles onto the board**
  - **Draw a tile** if no valid move
- If **all players pass** and the **tile bag is empty**, the player with the **lowest score wins**.

## Concepts Covered

- Modular project structure with headers
- Dynamic memory (`new`/`delete`)
- Use of linked lists 
- Operator overloading
- Use of enums for color and tile types
- Memory leak detection in Visual Studio (`crtdbg.h`)

## Project Structure

```
rummikub/
├── Main.cpp          # Game logic and main loop
├── tTile.cpp/.h      # Tile structure and display logic
├── tSet.cpp/.h       # Linked list implementation for tile sets
├── tRack.cpp/.h      # Player rack (dynamic array of tiles)
├── tRacks.cpp/.h     # All players' racks
├── tBag.cpp/.h       # Tile bag logic
├── tBoard.cpp/.h     # Game board and tile placement
```

## How to Compile and Run

### 🛠️ Requirements

To compile and run the project, a `C++` compiler is required. The project can be compiled with the following instruction:

### Compile using g++

```bash
g++ -std=c++11 -Wall -o rummikub Main.cpp tTile.cpp tSet.cpp tRack.cpp tRacks.cpp tBag.cpp tBoard.cpp

./rummikub
```

### Compile using a Makefile
In order to simplify the build process, a `Makefile` is provided:

```bash
make

./rummikub
```

> **Note for Windows users using Visual Studio codebase**:  
> The file `Main.cpp` includes the header `<crtdbg.h>` to detect memory leaks in Visual Studio.  
> To make the code compatible with `g++`, these lines are wrapped using:

```cpp
#ifdef _MSC_VER
    #include <crtdbg.h>
    _CrtDumpMemoryLeaks();
#endif
```

This makes the memory leak check optional and VS-only.

## Interesting Code Highlights

### Endgame Detection (Main.cpp)

```cpp
if (final_counter == NUM_PLAYERS) {
    player_winner = lowest(racks);
    winner = true;
}
```

This check ensures the game ends **only when no player can make a move and the bag is empty**, mirroring the real-life Rummikub rules.

### Sorting Tiles by Color (tRack.cpp)

```cpp
sortByColor(rack);
```

This function rearranges the rack visually by color, helping players spot potential **runs** easily, improving playability.

### Manual Linked List (tSet.cpp)

```cpp
while (set != NULL) {
    aux = set;
    set = set->next;
    delete aux;
}
```

Memory for the board sets is fully managed using **custom linked lists** and **manual `new` / `delete`**, giving full control over the heap and enforcing good C++ practices.

Additionally, `placeTile()` checks if a tile can be inserted **at the beginning or end** of a sequence, based on number and color:

```cpp
if (tile.number == lastNode->tile.number + 1 && tile.color == lastNode->tile.color) {
    lastNode->next = newNode;
}
```

### Operator Overload (tTile.cpp)

```cpp
bool operator==(tTile left, tTile right) {
    return (left.color == right.color) && (left.number == right.number);
}
```

Allows easy comparison of tiles throughout the code with intuitive `==` syntax.

---

## Author

**Javier Jerez Reinoso**  
Computer Science engineer

> Final Project, Programming Fundamentals

