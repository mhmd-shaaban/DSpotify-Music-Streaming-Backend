# DSpotify – Music Streaming Backend

A Spotify-style music streaming backend implemented in **C++** using custom data structures.

This project focuses on efficient backend operations for songs, playlists, genres, and song grouping using from-scratch data structures such as **AVL Trees**, **Hash Tables**, and **Union-Find**.

---

## Project Description

DSpotify is a data-structures-based music streaming backend.

The project is divided into two parts:

1. **Part 1 – AVL Trees and Playlists**
   - Manages songs and playlists.
   - Uses custom AVL trees for efficient ordered storage and searching.
   - Supports playlist/song operations and playlist merging logic.

2. **Part 2 – Hash Tables and Union-Find**
   - Manages songs and genres.
   - Uses a chained hash table implementation.
   - Uses Union-Find concepts for efficient grouping and merging.

---

## Data Structures Used

- AVL Trees
- Chained Hash Tables
- Union-Find / Disjoint Set Union
- Path Compression
- Union by Size
- Custom Pair / Node structures
- Object-Oriented C++ classes

---

## Repository Structure

```text
DSpotify-Music-Streaming-Backend/
│
├── README.md
├── .gitignore
│
├── part1-avl-playlists/
│   ├── AVL_Tree.h
│   ├── PlayList.h
│   ├── Song.h
│   ├── myPair.h
│   ├── dspotify25b1.h
│   ├── dspotify25b1.cpp
│   └── metadata.yml
│
└── part2-hash-union-find/
    ├── AVLTree.h
    ├── Genre.h
    ├── HashTableP.h
    ├── Song.h
    ├── dspotify25b2.h
    ├── dspotify25b2.cpp
    └── metadata.yml
```

---

## Files

### Part 1 – AVL Trees and Playlists

| File | Description |
|---|---|
| `AVL_Tree.h` | Custom AVL tree implementation |
| `PlayList.h` | Playlist class and playlist-related data |
| `Song.h` | Song class |
| `myPair.h` | Custom pair/helper structure |
| `dspotify25b1.h` | Public interface for Part 1 |
| `dspotify25b1.cpp` | Implementation of Part 1 backend operations |

### Part 2 – Hash Tables and Union-Find

| File | Description |
|---|---|
| `AVLTree.h` | AVL tree implementation used in Part 2 |
| `Genre.h` | Genre class |
| `HashTableP.h` | Chained hash table implementation |
| `Song.h` | Song class |
| `dspotify25b2.h` | Public interface for Part 2 |
| `dspotify25b2.cpp` | Implementation of Part 2 backend operations |

---

## Technologies

- C++
- Object-Oriented Programming
- Data Structures
- AVL Trees
- Hash Tables
- Union-Find
- Algorithmic complexity optimization

---

## How to Build

This project may depend on a course-provided tester or framework.

A general compile example for Part 1:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic-errors part1-avl-playlists/dspotify25b1.cpp -o dspotify_part1
```

A general compile example for Part 2:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic-errors part2-hash-union-find/dspotify25b2.cpp -o dspotify_part2
```

If the project does not compile alone, compile it together with the official tester files provided by the course.

---

## Notes

- The implementation uses custom data structures instead of STL containers for the main backend logic.
- Some files may require external test files or course-provided interfaces.
- Keep the source files in GitHub, not only the original `.zip` files.

---

## Suggested CV Description

**DSpotify – Music Streaming Backend (C++ / AVL Trees, Hash Tables, Union-Find):**  
Spotify-style streaming backend built with custom AVL trees, chained hash tables, and Union-Find with path compression and union-by-size.

---

## Author

Mohamed Shaaban  
Electrical and Computer Engineering Student  
Technion – Israel Institute of Technology
