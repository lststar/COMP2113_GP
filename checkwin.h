/**
 * @file checkwin.h
 * @version 1.0
 * @author Liu Haitian 3035844314
 * @date 2023-11-26
 * @brief This file is the header file of checkwin.cpp .
 */

#ifndef CHECKWIN_H
#define CHECKWIN_H

#include <iostream>
#include <vector>
using namespace std;

const int BOARD_SIZE = 15;

bool checkWinHorizontal(int player, vector<vector<int>> &board);
bool checkWinVertical(int player, vector<vector<int>> &board);
bool checkWinDiagonal(int player, vector<vector<int>> &board);
bool checkWin(int player, vector<vector<int>> &board);
#endif