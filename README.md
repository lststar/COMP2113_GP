# Gomoku-Overlord

**Gomoku-Overlord** is a text-based Gomoku *(also called Five in a Row)* game written in C++.

In **two-player mode**, you can play with your friend and take turns dropping pieces to compete. You can adopt any rules you like, with one goal in mind: to be the first to connect five pieces.

In **single-player mode**, you can play alone and spar with our powerful AI. Our AI offers three levels of difficulty: easy, normal and hard. Please note that our AI adopts a no-ban rule, which means that even if the AI goes first, it can win any way it wants.

So what are you waiting for, come and start playing the **Gomoku-Overlord** !

## For players

### Video demo

[![asciicast](https://asciinema.org/a/SO9VsXGXpa0kA4OZLPWmaHYOg.svg)](https://asciinema.org/a/SO9VsXGXpa0kA4OZLPWmaHYOg)

### Start gaming

In just a few simple steps, you can start playing this game!

```
git clone https://github.com/lststar/Gomoku-Overlord.git
```

```
cd Gomoku-Overlord
```

```
make
```

```
./main
```

That's all! Take your time and enjoy gaming!

### Keyboard settings

```
#include <ncurses.h> // enabling keyboard manipulations
```

- Press **Up/Left/Down/Right** arrow keys (or **W/A/S/D** for player 2 in two-player mode) to move your piece.
- Press **Enter** (or **G** for player 2 in two-player mode) to confirm your move.
- Press **ESC** to pause the game and show the menu, where 3 options are available: press **S** for save and quit, **Q** for quit without saving, or **any other key** to return to the game.

## Coding requirements

1. **Generation of random game sets or events:** refer to Gomoku-Overlord AI
2. **Data structures for storing game status:** game board, a two-dimensional vector
3. **Dynamic memory management:** game board, a two-dimensional vector
4. **File input/output (e.g., for loading/saving game status):** loadGame() and saveGame() in main.cpp
5. **Program codes in multiple files:**
   1. **ai.cpp, ai.h:** game-AI design
   2. **checkwin.cpp, checkwin.h:** check for winning conditions
   3. **main.cpp:** main functions and user interface

## Gomoku-Overlord UI

![](https://i.boatonland.com/HKU/post/wmQzw6bS8pmFwPFny7zn4TZzwSGH4BeH.png)

When the executable is run, it automatically detects if there's a **previously saved game** inside the same folder. If yes, you'll be prompted to choose to **load that game** or to **start a fresh game**; if no, then **a fresh game** will be prepared.

Then, you'll be prompted to choose your desired **game mode**, and **AI difficulty** and **who goes first** if you choose to play against AI.

![](https://i.boatonland.com/HKU/post/kGKiSNixHTSMxR5iPECZKFkrk5HQjcJy.png)

**Gaming state:** where player(s) take turns to move the piece and confirm a move.

![](https://i.boatonland.com/HKU/post/cK4C5k5ByERhSSjSGYESthYi2TJsZdbT.png)

**Pausing state:** where player(s) can choose to continue/save/quit a game.

![](https://i.boatonland.com/HKU/post/7jYHSYYteK8bJD6ejew6XA3fHtCskhiC.png)

**Winning state:** where the winning game state is displayed to player(s).

## Gomoku-Overlord AI

**Gomoku-Overlord** has a powerful built-in AI. All AI related codes can be found in `ai.cpp` and `ai.h` . You can use function `getAiMove` to get the best move suggested by AI , and use function `evalBoard` to get standard score for the current situation.

We shall introduce the main algorithm we used.

### Minimax

[Minimax - Wikipedia](https://en.wikipedia.org/wiki/Minimax)

Our AI uses the **minimax algorithm** to consider both AI's move and human's and obtain possible optimal solutions. We use the following fake codes to call the `getAiMove` function in a recursion way:

```
getAiMove (player, board, depth) {
    for (point_list as point) {
        // Minimax search, find the best move considering both AI's move and human's reaction.
        if (depth == 1) {
            score = getScore(player, board)
        } else {
            // Since the score for human is -1 * the score for AI, we stick to find the max by multiplying human's score with -1.
            board = makeMove(player, board, point)
            score = getAiMove(-player, board, depth - 1) * -1
            board = unmakeMove(player, board, point)
        }

        if (score > max_score) {
            max_score = score
        }
    }

    return score
}
```

### Alpha-beta pruning

[Alpha-beta pruning - Wikipedia](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)

Our AI uses the **alpha-beta pruning algorithm** to improve the speed of minimax search by decrease the number of nodes that are evaluated without affecting the outcome. Example fake codes is as following:

```
getAiMove (player, board, depth) {
    for (point_list as point) {
        // Minimax search, find the best move considering both AI's move and human's reaction.
        if (depth == 1) {
            score = getScore(player, board)
        } else {
            // Since the score for human is -1 * the score for AI, we stick to find the max by multiplying human's score with -1.
            board = makeMove(player, board, point)
            score = getAiMove(-player, board, depth - 1) * -1
            board = unmakeMove(player, board, point)
        }

        if (score > max_score) {
            max_score = score
        }

        // Alpha beta pruning, decrease the number of nodes that are evaluated by the minimax search.
        alpha = max(alpha, score)
        if (alpha >= beta) {
            break
        }
    }

    return score
}
```

In our 4-depth 30-step standard test, the alpha-beta pruning improves the speed by **558%** .

> The test was running on a Macbook Air 2022 with Apple M2 chip and 8GB memory.

| Depth | Step | Alpha-beta pruning | Running time |
| ----- | ---- | ------------------ | ------------ |
| 4     | 30   | with               | 154.42s      |
| 4     | 30   | without            | 1015.98s     |

### Heuristically search

[Heuristically search - Wikipedia](https://en.wikipedia.org/wiki/Heuristic_%28computer_science%29#Search)

Our AI uses the **heuristically search algorithm** to accelerate the speed of alpha-beta pruning search by sort the point according to a fast evaluation function. Example fake codes is as following:

```
getAiMove (player, board, depth) {
    // Heuristically search, sort the point list by point score to improve the speed of alpha beta pruning.
    sort(point_list, eval(point), desc)

    for (point_list as point) {
        // Minimax search, find the best move considering both AI's move and human's reaction.
        if (depth == 1) {
            score = getScore(player, board)
        } else {
            // Since the score for human is -1 * the score for AI, we stick to find the max by multiplying human's score with -1.
            board = makeMove(player, board, point)
            score = getAiMove(-player, board, depth - 1) * -1
            board = unmakeMove(player, board, point)
        }

        if (score > max_score) {
            max_score = score
        }

        // Alpha beta pruning, decrease the number of nodes that are evaluated by the minimax search.
        alpha = max(alpha, score)
        if (alpha >= beta) {
            break
        }
    }

    return score
}
```

In our 4-depth 30-step standard test, the heuristically search improves the speed by **1582%** .

> The test was running on a Macbook Air 2022 with Apple M2 chip and 8GB memory.

| Depth | Step | Heuristically search | Running time |
| ----- | ---- | -------------------- | ------------ |
| 4     | 30   | with                 | 9.18s        |
| 4     | 30   | without              | 154.42s      |

### Performance

We adopt a 30-step standard test to evaluate the performance of our AI.

> The test was running on a Macbook Air 2022 with Apple M2 chip and 8GB memory.

| Game Difficulty | Depth | Step | Running time |
| --------------- | ----- | ---- | ------------ |
| Easy            | 2     | 30   | 0.17s        |
| Normal          | 4     | 30   | 9.18s        |
| Hard            | 6     | 30   | 375.85s      |

## Authors

We are Group 19 of COMP2113 2023 Fall at HKU.

- [Liu Sitong](https://github.com/lststar) (3035844479)
    - Worked on AI related parts.
- [Yi Qianzheng](https://github.com/fatcatmini) (3035834864)
    - Worked on main functions and user interface.
- [Liu Haitian](https://github.com/LiuHaitian815) (3035844314)
    - Worked on the winning condition part.
