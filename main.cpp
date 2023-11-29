#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <ncurses.h>

#include "checkwin.h"
#include "ai.h"

#define BOARD_SIZE 15

using namespace std;

vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
int current_player = 1;
// ui_mode: 0 for (x, y) input; 1 for arrow keys input
int ui_mode = 0;
// ai_mode: 0 for player vs. player; 1 for player vs. AI
int ai_mode = 0;
// Initialize coordinates for arrow key ui_mode
int last_x = 7;
int last_y = 7;

// Load current player and game board to "game_state.txt"
void loadGame()
{
    ifstream fin("game_state.txt");
    // game_state.txt follows a consistent format
    // first line: current_player
    // followed by: board state

    if (fin.is_open())
    {
        // Read the current_player from the file
        fin >> current_player;

        // Read the board state from the file
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                fin >> board[i][j];
            }
        }

        fin.close();
    }
    else
    {
        cout << "game_state.txt does not exist yet" << endl;
    }
    cout << "Game successfully loaded from game_state.txt" << endl;
}

// Initialize an empty game board or load an existing game board
// Allow player(s) to select ui_mode and ai_mode
void initBoard(string game_state = "")
{
    // Game board setup
    if (game_state == "")
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                board[i][j] = 0;
            }
        }
    }
    else
    {
        loadGame();
    }

    // Player selection of ui_mode
    while (true)
    {
        cout << "Choose 0 for (x, y) input or 1 for arrow keys input: ";
        cin >> ui_mode;

        if (ui_mode != 0 && ui_mode != 1)
        {
            cout << "Invalid input, try again." << endl;
            continue;
        }
        break;
    }

    // Player selection of ai_mode
    while (true)
    {
        cout << "Choose 0 for player vs. player or 1 for player vs. AI: ";
        cin >> ai_mode;

        if (ai_mode != 0 && ai_mode != 1)
        {
            cout << "Invalid input, try again." << endl;
            continue;
        }
        break;
    }
}

// Switch the current player between 1 and -1
void changePlayer()
{
    current_player *= -1;
}

// (Regular) Print the current state of the game board
void printBoard(int x = -1, int y = -1)
{
    cout << "\033c";

    // Print the column numbers
    for (int i = 0; i <= BOARD_SIZE; i++)
    {
        cout << setw(2) << setfill('0') << i << " ";
    }
    cout << endl;
    // Print each row with its row number and the state of each position
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cout << setw(2) << setfill('0') << i + 1 << " ";
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                cout << "[ ]";
            }
            else if (board[i][j] == 1)
            {
                if (x == i && y == j)
                {
                    cout << "[\033[46mX\033[0m]";
                }
                else
                {
                    cout << "[\033[36mX\033[0m]";
                }
            }
            else if (board[i][j] == -1)
            {
                if (x == i && y == j)
                {
                    cout << "[\033[41mO\033[0m]";
                }
                else
                {
                    cout << "[\033[31mO\033[0m]";
                }
            }
        }
        cout << endl;
    }
}

// (For arrow mode) Print the current state of the game board
void printBoard_in_ncurses(int x = -1, int y = -1)
{
    clear();

    // Print the column numbers
    for (int i = 0; i <= BOARD_SIZE; i++)
    {
        printw("%02d ", i);
    }
    printw("\n");

    // Print each row with its row number and the state of each position
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printw("%02d ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                if (x == i && y == j)
                {
                    printw("[");
                    attron(COLOR_PAIR(3));
                    printw(" ");
                    attroff(COLOR_PAIR(3));
                    printw("]");
                }
                else
                {
                    printw("[ ]");
                }
            }
            else if (board[i][j] == 1)
            {
                if (x == i && y == j)
                {
                    printw("[");
                    attron(COLOR_PAIR(11));
                    printw("X");
                    attroff(COLOR_PAIR(11));
                    printw("]");
                }
                else
                {
                    printw("[");
                    attron(COLOR_PAIR(1));
                    printw("X");
                    attroff(COLOR_PAIR(1));
                    printw("]");
                }
            }
            else if (board[i][j] == -1)
            {
                if (x == i && y == j)
                {
                    printw("[");
                    attron(COLOR_PAIR(22));
                    printw("O");
                    attroff(COLOR_PAIR(22));
                    printw("]");
                }
                else
                {
                    printw("[");
                    attron(COLOR_PAIR(2));
                    printw("O");
                    attroff(COLOR_PAIR(2));
                    printw("]");
                }
            }
        }
        printw("\n");
    }
    refresh();
}

// Returns true if the move is successful, false otherwise
bool makeMove(int player, int x, int y, int ui_mode)
{
    // Check if the player is valid (1 or -1)
    if (player != 1 && player != -1)
    {
        cout << "Error: Player is not defined." << endl;
        return false;
    }
    // Check if the move is within the boundaries of the board
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
    {
        cout << "Error: Position out of boundary." << endl;
        return false;
    }
    // Check if the position on the board is already occupied
    if (board[x][y] != 0)
    {
        cout << "Error: This position has been occupied." << endl;
        return false;
    }
    // If all checks pass, make the move and return true
    board[x][y] = player;

    if (ui_mode == 0)
    {
        printBoard(x, y);
    }
    else
    {
        printBoard_in_ncurses(x, y);
    }

    return true;
}

// Saving current player and game board to "game_state.txt"
void saveGame()
{
    ofstream fout("game_state.txt");
    if (fout.is_open())
    {
        fout << current_player << "\n";
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                fout << board[i][j] << " ";
            }
            fout << "\n";
        }
        fout.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
    cout << "Game saved to game_state.txt" << endl;
}

// Main function when ui_mode = 0, in (x, y) input mode
int main_ui_0()
{
    // Print the initial state of the game board
    printBoard();
    // Game loop
    while (true)
    {
        int x, y;

        if (current_player == 1)
        {
            cout << "Player " << (3 - current_player) / 2 << " Make Your Move: ";
            cin >> x >> y;
            // TODO: save the game when xxx is triggered
            if (x == -1 && y == -1)
            {
                saveGame();
                return 0;
            }
            x -= 1;
            y -= 1;
        }
        else
        {
            if (ai_mode == 1)
            {
                cout << "AI is thinking..." << endl;
                tuple<int, int, int> ai_result = getAiMove(current_player, board, 4);
                x = get<0>(ai_result);
                y = get<1>(ai_result);
            }
            else
            {
                cout << "Player " << (3 - current_player) / 2 << " Make Your Move: ";
                cin >> x >> y;
                // TODO: save the game when xxx is triggered
                if (x == -1 && y == -1)
                {
                    saveGame();
                    return 0;
                }
                x -= 1;
                y -= 1;
            }
        }

        // If the move is valid, update the game board and print it
        // If the move is not valid, skip the rest of this loop iteration
        if (!makeMove(current_player, x, y, 0))
        {
            continue;
        }

        if (checkWin(current_player, board))
        {
            cout << "Player " << (3 - current_player) / 2 << " Win!!!" << endl;
            return 0;
        }

        changePlayer();
    }
}

// Main function when ui_mode = 1, in arrow keys input mode
int main_ui_1()
{
    // ncurses.h activation
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    start_color();
    use_default_colors();
    // Initializing color pairs
    init_pair(1, COLOR_CYAN, -1);
    init_pair(11, COLOR_CYAN, COLOR_WHITE);
    init_pair(2, COLOR_RED, -1);
    init_pair(22, COLOR_RED, COLOR_WHITE);
    init_pair(3, -1, COLOR_WHITE);

    int x = last_x;
    int y = last_y;
    // Print the initial state of the game board
    printBoard_in_ncurses(x, y);

    int ch;
    // Game loop
    while (true)
    {
        if (current_player == 1)
        {
            printw("Player %d Make Your Move: ", (3 - current_player) / 2);
            // Use Enter key to finish moving the piece
            while ((ch = getch()) != '\n')
            {
                // Saving the game
                if (ch == 's')
                {
                    endwin();
                    saveGame();
                    return 0;
                }

                switch (ch)
                {
                case KEY_UP:
                    if (x > 0)
                        x -= 1;
                    break;
                case KEY_DOWN:
                    if (x < 14)
                        x += 1;
                    break;
                case KEY_LEFT:
                    if (y > 0)
                        y -= 1;
                    break;
                case KEY_RIGHT:
                    if (y < 14)
                        y += 1;
                    break;
                default:
                    break;
                }
                printBoard_in_ncurses(x, y);
                printw("Player %d Make Your Move: ", (3 - current_player) / 2);
            }
        }
        else
        {
            if (ai_mode == 1)
            {
                printw("AI is thinking...");
                tuple<int, int, int> ai_result = getAiMove(current_player, board, 4);
                x = get<0>(ai_result);
                y = get<1>(ai_result);
            }
            else
            {
                printw("Player %d Make Your Move: ", (3 - current_player) / 2);
                // Use Enter key to finish moving the piece
                while ((ch = getch()) != '\n')
                {
                    // Saving the game
                    if (ch == 's')
                    {
                        endwin();
                        saveGame();
                        return 0;
                    }

                    switch (ch)
                    {
                    case KEY_UP:
                        if (x > 0)
                            x -= 1;
                        break;
                    case KEY_DOWN:
                        if (x < 14)
                            x += 1;
                        break;
                    case KEY_LEFT:
                        if (y > 0)
                            y -= 1;
                        break;
                    case KEY_RIGHT:
                        if (y < 14)
                            y += 1;
                        break;
                    default:
                        break;
                    }
                    printBoard_in_ncurses(x, y);
                    printw("Player %d Make Your Move: ", (3 - current_player) / 2);
                }
            }
        }

        if (!makeMove(current_player, x, y, 1))
        {
            last_x = x;
            last_y = y;
            continue;
        }

        if (checkWin(current_player, board))
        {
            endwin(); // Safely closing ncurses.h
            printBoard();
            cout << "Player " << (3 - current_player) / 2 << " Win!!!" << endl;
            return 0;
        }

        changePlayer();
    }
}

// Initialize the game board with / without game_state.txt
// Run the game with ui_mode and ai_mode set by users
int main(int argc, char *argv[])
{
    // Initializing board with or without game_state.txt
    if (argc == 2)
    {
        initBoard(argv[1]);
    }
    else
    {
        initBoard();
    }

    if (ui_mode == 0)
    {
        return main_ui_0();
    }
    else
    {
        return main_ui_1();
    }
}