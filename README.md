# 🏆 Tournament Management System

A **C-based Data Structures project** that manages an **8-team knockout tournament** using a **Binary Tree, Stack, Dynamic Memory Allocation, and File Handling**.

The system allows users to create tournaments, display the tournament bracket, record match results, undo the last result, recover saved tournament data, and display the current champion.

---

## 📌 Problem Statement

Managing a knockout tournament manually can make it difficult to track match progression, winners, and the movement of teams into upcoming rounds.

This project provides a structured **Tournament Management System** where:

- 8 teams participate in a knockout tournament
- Winners automatically progress to the next round
- The tournament is represented using a binary tree
- Previous match results can be undone
- Tournament data is stored permanently in a binary file
- A champion is determined after the final match

---

## 🎯 Objectives

- Manage an 8-team knockout tournament
- Represent tournament rounds using a Binary Tree
- Automatically move winners to future matches
- Record match results
- Implement an Undo operation using Stack
- Save tournament data using file handling
- Recover previously saved tournament data
- Display the tournament champion

---

## 🧠 Data Structures Used

### 1. Binary Tree 🌳

The tournament bracket is represented using a **binary tree**.

The structure contains:

```text
                Match 7
               /       \
          Match 5       Match 6
          /    \       /    \
      Match 1 Match 2 Match 3 Match 4
```

Where:

- Matches 1–4 → Quarter Finals
- Matches 5–6 → Semi Finals
- Match 7 → Final

Each tree node stores:

- Match ID
- Team 1
- Team 2
- Winner
- Played status
- Left child
- Right child
- Parent pointer

The program dynamically creates these match nodes using `malloc()`.

---

### 2. Stack 📚

A **Stack** is used to implement the **Undo Last Result** functionality.

Before a result is entered, the current tournament state is stored as a snapshot and pushed onto the stack.

```text
              TOP
               ↓
        ┌─────────────┐
        │  Snapshot 3 │
        ├─────────────┤
        │  Snapshot 2 │
        ├─────────────┤
        │  Snapshot 1 │
        └─────────────┘
```

The stack follows the:

**LIFO — Last In, First Out**

The project stores up to **50 snapshots**.

---

### 3. Dynamic Memory Allocation

Each match node is dynamically allocated using:

```c
malloc(sizeof(MatchNode))
```

This allows the tournament tree to be created dynamically during program execution.

Memory is released using `free()` before the program terminates.

---

### 4. File Handling 💾

Tournament data is stored in:

```text
tournament.dat
```

The program uses binary file operations:

```c
fopen()
fwrite()
fread()
fclose()
```

This allows tournament data to persist even after the program is closed.

---

## 🏟️ Tournament Structure

The system supports exactly **8 teams**.

### Quarter Finals

```text
Match 1 → Team 1 vs Team 2
Match 2 → Team 3 vs Team 4
Match 3 → Team 5 vs Team 6
Match 4 → Team 7 vs Team 8
```

### Semi Finals

```text
Match 5 → Winner Match 1 vs Winner Match 2
Match 6 → Winner Match 3 vs Winner Match 4
```

### Final

```text
Match 7 → Winner Match 5 vs Winner Match 6
```

The tree relationships are established through left, right, and parent pointers.

---

## ⚙️ Main Features

### 🆕 Create New Tournament

The user enters the names of 8 teams.

The teams are initially placed into the four quarter-final matches.

After creation, the tournament is automatically saved to the binary file.

---

### 📊 Display Tournament Bracket

The complete tournament bracket is displayed in three rounds:

```text
QUARTER FINALS
        ↓
SEMI FINALS
        ↓
FINAL
```

If the final has been completed, the champion is also displayed.

---

### 🏅 Enter Match Result

The user selects a match and chooses which team won.

The program:

1. Checks whether the match is valid
2. Saves the current state
3. Records the winner
4. Marks the match as played
5. Moves the winner to the parent match
6. Saves the updated tournament

This allows winners to automatically progress through the tournament.

---

### ↩️ Undo Last Result

The Undo feature uses the Stack.

Before recording a result:

```text
Current Tournament State
          ↓
      Push Snapshot
          ↓
    Enter Match Result
```

When Undo is selected:

```text
Pop Snapshot
      ↓
Restore Previous State
```

Therefore, the most recently entered result is recovered first.

---

### 💾 Recover Saved Tournament

The program can load tournament information from `tournament.dat`.

When saved data is recovered, future matches are updated according to previously recorded winners.

---

### 👑 Show Champion

Once Match 7 has been completed, its winner becomes the tournament champion.

Before the final is completed:

```text
Champion not decided yet.
```

After the final:

```text
Current Champion: <Winner>
```



---

## 🔄 System Flow

```text
                  ┌─────────────────────────┐
                  │     MAIN MENU           │
                  └────────────┬────────────┘
                               │
          ┌────────────────────┼────────────────────┐
          │                    │                    │
          ▼                    ▼                    ▼
   Create Tournament    Display Bracket      Enter Result
          │                    │                    │
          │                    │                    ▼
          │                    │               Push Snapshot
          │                    │                    │
          │                    │                    ▼
          │                    │              Store Winner
          │                    │                    │
          │                    │                    ▼
          │                    │           Update Parent Match
          │                    │
          │                    │
          ▼                    ▼                    ▼
      Save Data          View Champion          Undo Result
                                                    │
                                                    ▼
                                             Restore Snapshot

                           ↓

                    Recover Tournament
                           │
                           ▼
                    Load tournament.dat
```

---

## 🖥️ Main Menu

```text
========== TOURNAMENT MANAGEMENT SYSTEM ==========

1. Create New Tournament
2. Display Tournament Bracket
3. Enter Match Result
4. Undo Last Result
5. Recover Saved Tournament
6. Show Champion
7. Exit
```

This menu is implemented directly in the `main()` function.

---

## 🧩 Match Validation

Before entering a result, the program verifies that:

- Both teams are available
- The match has not already been completed

If either condition fails, the result cannot be entered.

---

## 📁 Project Structure

```text
Tournament-Management-System/
│
├── dsa_project.c
├── tournament.dat
└── README.md
```

### File Description

| File | Purpose |
|---|---|
| `dsa_project.c` | Main C source code |
| `tournament.dat` | Saved tournament data |
| `README.md` | Project documentation |

---

## ⚙️ Technologies Used

- **Language:** C
- **Compiler:** GCC / MinGW
- **Data Structures:** Binary Tree, Stack
- **Memory Management:** Dynamic Memory Allocation
- **File Handling:** Binary File I/O
- **Concepts:** Pointers, Structures, Tree Traversal Relationships, LIFO

---

## ▶️ How to Run

### Clone the Repository

```bash
git clone https://github.com/your-username/tournament-management-system.git
```

### Navigate to the Project

```bash
cd tournament-management-system
```

### Compile

```bash
gcc dsa_project.c -o tournament
```

### Run

On Linux/macOS:

```bash
./tournament
```

On Windows:

```bash
tournament.exe
```

---

## ⏱️ Complexity Overview

| Operation | Data Structure | Complexity |
|---|---|---:|
| Create Tournament | Binary Tree | O(n) |
| Display Bracket | Binary Tree | O(n) |
| Enter Result | Tree | O(1) |
| Push Snapshot | Stack | O(n) |
| Undo Result | Stack | O(n) |
| Save Tournament | File | O(n) |
| Load Tournament | File | O(n) |

Here, `n` represents the number of tournament matches/snapshot elements involved.

---

## 🎓 DSA Concepts Demonstrated

This project demonstrates practical implementation of:

- Structures
- Binary Trees
- Parent-child relationships
- Pointers
- Stack
- LIFO principle
- Dynamic Memory Allocation
- File Handling
- Binary File Storage
- State Snapshots
- Undo Operations

---

## 🚀 Future Improvements

Possible improvements include:

- Support for different tournament sizes
- Player statistics
- Match scheduling
- Match dates and timings
- Team rankings
- Score tracking
- Multiple tournament formats
- Graphical user interface
- Online multiplayer tournament management

---

## 👩‍💻 Academic Project

**Project:** Tournament Management System  
**Subject:** Data Structures and Algorithms  
**Language:** C  
**Tournament Type:** 8-Team Knockout Tournament

---

⭐ **A practical implementation of Binary Tree and Stack concepts for tournament management.**
