#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

#define BOARD_SIZE 15

using namespace std;

// Initalization of an empty game board
vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
int current_player = 1;

void initBoard()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            // Set each position on the board to 0
            board[i][j] = 0;
        }
    }
}

// Function to switch the current player
void changePlayer()
{
    // Multiply the current player by -1 to switch between 1 and -1
    current_player *= -1;
}

// Function to print the current state of the game board
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

// Returns true if the move is successful, false otherwise
bool makeMove(int player, int x, int y)
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

    printBoard(x, y);
    return true;
}

int main()
{
    initBoard();
    // Print the initial state of the game board
    printBoard();

    while (true)
    {
        // Prompt the current player to make a move
        cout << "Player " << (3 - current_player) / 2 << " Make Your Move: ";
        int x, y;
        // Get the player's move
        cin >> x >> y;
        // If the move is valid, update the game board and print it
        if (makeMove(current_player, x - 1, y - 1))
        {
            printBoard();
        }
        else
        {
            // If the move is not valid, skip the rest of this loop iteration
            continue;
        }
        // Switch to the other player
        changePlayer();
    }
    // End of the game
    return 0;
}