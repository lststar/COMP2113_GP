/**
 * @file checkwin.cpp
 * @version 1.0
 * @author Liu Haitian 3035844314
 * @date 2023-11-26
 * @brief This file can realize the check of the winning condition in the whole work.
 */

#include "checkwin.h"

// Function to check if the current player has won horizontally
// Using two variables
// Let player be digitized
bool checkWinHorizontal(int player, vector<vector<int>> &board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        // Iterate through each row
        int count = 0;
        // Define the viriable
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            // Iterate through each column
            if (board[i][j] == player)
            // Check the postion
            {
                // If the current cell matches the player's number
                count++; // Increment the count
                if (count == 5)
                // The rule of the game is about "5"
                {
                    // If there are five consecutive cells with the player's number
                    return true;
                    // Return true
                    // indicating a win
                }
            }
            else
            {
                count = 0;
                // Reset the count
                // if the current cell doesn't match the player's number
            }
        }
    }
    return false;
    // Return false
    // if no win is found horizontally
}

// Function to check
// if the current player has won vertically
// using two loops
bool checkWinVertical(int player, vector<vector<int>> &board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        // Iterate through each column
        int count = 0;
        // Define the variable
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            // Iterate through each row
            if (board[j][i] == player)
            // Check the position
            {
                // If the current cell matches the player's number
                count++;
                // Increment the count
                if (count == 5)
                {
                    // If there are five consecutive cells with the player's number
                    return true;
                    // Return true
                    // indicating a win
                }
            }
            else
            {
                count = 0;
                // Reset the count
                // if the current cell doesn't match the player's number
            }
        }
    }
    return false;
    // Return false
    // if no win is found vertically
}

// Function to check
// if the current player has won diagonally
bool checkWinDiagonal(int player, vector<vector<int>> &board)
{
    // Check diagonals
    // starting from top-left corner going to the bottom-right corner
    for (int i = 4; i < BOARD_SIZE; i++)
    // The size can not be smaller than 4
    {
        // Start from row 4
        int count = 0;
        // Define the variable
        for (int j = 0; j <= i; j++)

        {
            if (board[i - j][j] == player)
            {
                // If the current cell matches the player's number
                count++;
                // Increment the count
                if (count == 5)
                {
                    // If there are five consecutive cells with the player's number
                    return true;
                    // Return true
                    // indicating a win
                }
            }
            else
            {
                count = 0;
                // Reset the count
                // if the current cell doesn't match the player's number
            }
        }
    }

    // Check diagonals
    // starting from top-right corner going to the bottom-left corner
    for (int i = BOARD_SIZE; i < 2 * BOARD_SIZE - 5; i++)
    {
        // Start from row 15
        int count = 0;
        for (int j = i - BOARD_SIZE + 1; j < BOARD_SIZE; j++)
        {
            if (board[i - j][j] == player)
            {
                // If the current cell matches the player's number
                count++;
                // Increment the count
                if (count == 5)
                {
                    // If there are five consecutive cells with the player's number
                    return true;
                    // Return true
                    // indicating a win
                }
            }
            else
            {
                count = 0;
                // Reset the count
                // if the current cell doesn't match the player's number
            }
        }
    }

    // Check diagonals starting from top-left corner going to the bottom-right corner
    // (excluding the top-right triangle)
    for (int i = 0; i < BOARD_SIZE - 4; i++)
    {
        // Start from row 0
        int count = 0;
        // Define the variable
        for (int j = 0; j < BOARD_SIZE - i; j++)
        {
            if (board[i + j][j] == player)
            {
                // If the current cell matches the player's number
                count++;
                // Increment the count
                if (count == 5)
                {
                    // If there are five consecutive cells with the player's number
                    return true;
                    // Return true
                    // indicating a win
                }
            }
            else
            {
                count = 0;
                // Reset the count
                // if the current cell doesn't match the player's number
            }
        }
    }

    // Check diagonals
    // starting from top-left corner going to the bottom-right corner
    // (continuation)
    // (excluding the bottom-left triangle)
    for (int i = 1; i < BOARD_SIZE - 4; i++)
    {
        // Start from column 1
        int count = 0;
        // Define the variable
        for (int j = 0; j < BOARD_SIZE - i; j++)
        {
            if (board[j][i + j] == player)
            // Check the position
            {
                // If the current cell matches the player's number
                count++;
                // Increment the count
                if (count == 5)
                // check the winning condition
                {
                    // If there are five consecutive cells with the player's number
                    return true;
                    // Return true
                    // Indicating a win
                }
            }
            else
            {
                count = 0;
                // Reset the count
                // If the current cell doesn't match the player's number
            }
        }
    }

    return false;
    // Return false
    // if no win is found diagonally
}

// Function to check
// If the current player has won
bool checkWin(int player, vector<vector<int>> &board)
// Check if there exists a winner
{
    return checkWinHorizontal(player, board) || checkWinVertical(player, board) || checkWinDiagonal(player, board);
    // Check for a win
    // Horizontally
    // Vertically
    // Diagonally
}