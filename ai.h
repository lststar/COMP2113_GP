/**
 * @file ai.h
 * @version 1.0
 * @author Liu Sitong 3035844479
 * @date 2023-11-25
 * @brief This file is the header file of ai.cpp .
 */

#ifndef AI_H
#define AI_H

#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

// Define some constants including the size of the board and the score for each shape.
#define BOARD_SIZE 15

#define FIVE 20000
#define LIVE_FOUR 2500
#define BLOCKED_FOUR 250
#define BLANK_FOUR 333
#define LIVE_THREE 333
#define BLOCKED_THREE 33
#define BLANK_THREE 50
#define LIVE_TWO 50
#define BLOCKED_TWO 5
#define BLANK_TWO 5
#define LIVE_ONE 10
#define BLOCKED_ONE 1

// Define a struct Line to carry the information of a point, and it left 4 and right 4 neighbor.
struct Line
{
    int data[9];
};

// Pre declare all functions
int evalBoardAll(int player, vector<vector<int>> &board);
int evalBoard(int player, vector<vector<int>> &board);
int evalPoint(int x, int y, int player, vector<vector<int>> &board);
Line getPointLine(int x, int y, pair<int, int> direction, int player, vector<vector<int>> &board);
int evalPointLine(Line &line);
int checkPositionStatus(Line &line, int index);
tuple<int, int, int> getAiMove(int player, vector<vector<int>> &board, int depth, int alpha = -1000000, int beta = 1000000);
void initLineDict();
bool checkNeighbor(int x, int y, int distance, vector<vector<int>> &board);
bool comparePointVector(vector<int> x, vector<int> y);

#endif