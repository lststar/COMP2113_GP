/**
 * @file ai.cpp
 * @version 1.0
 * @author Liu Sitong 3035844479
 * @date 2023-11-25
 * @brief This file provides Gomoku with AI capabilities to help complete the man-machine battle function.
 */

#include "ai.h"

// Define a line dictionary and whether it has been initialised, so that the program can get the score of line faster by getting it from the ram.
int line_dict[3][3][3][3][3][3][3][3];
bool init = false;

/**
 * @brief Eval the board and get overall score for the indicated player (overall score = score for the indicated player - score for the other player).
 * @param player The indicated player for evaluation.
 * @param board The board for evaluation.
 * @return score The overall score of the board for the indicated player.
 */
int evalBoardAll(int player, vector<vector<int>> &board)
{
    return evalBoard(player, board) - evalBoard(-player, board);
}

/**
 * @brief Eval the board and get partial score for the indicated player.
 * @param player The indicated player for evaluation.
 * @param board The board for evaluation.
 * @return score The partial score of the board for the indicated player.
 */
int evalBoard(int player, vector<vector<int>> &board)
{
    int score = 0;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            if (board[x][y] == player)
            {
                score += evalPoint(x, y, player, board);
            }
        }
    }
    return score;
}

/**
 * @brief Eval one point on the board.
 * @param x The x coordinate of the point.
 * @param y The y coordinate of the point.
 * @param player The indicated player for evaluation.
 * @param board The board for evaluation.
 * @return score The score of the point for the indicated player.
 */
int evalPoint(int x, int y, int player, vector<vector<int>> &board)
{
    vector<pair<int, int>> direction_list = {{0, 1}, {1, 0}, {-1, 1}, {1, 1}};
    int score = 0;
    for (auto &direction : direction_list)
    {
        Line line = getPointLine(x, y, direction, player, board);
        score += line_dict[line.data[0] + 1][line.data[1] + 1][line.data[2] + 1][line.data[3] + 1][line.data[5] + 1][line.data[6] + 1][line.data[7] + 1][line.data[8] + 1];
    }
    return score;
}

/**
 * @brief Get the line passing the point in indicated direction (if the point is occupied by the player, return 1; by the other player, return -1; otherwise, return 0).
 * @param x The x coordinate of the point.
 * @param y The y coordinate of the point.
 * @param direction The indicated direction of the line (horizontal, vertical, top-left to bottom-right, or top-right to bottom-left).
 * @param player The indicated player for evaluation.
 * @param board The board for evaluation.
 * @return line The line centered at the point with length 9.
 */
Line getPointLine(int x, int y, pair<int, int> direction, int player, vector<vector<int>> &board)
{
    Line line;
    int dx = x + (-5) * direction.first;
    int dy = y + (-5) * direction.second;
    for (int i = 0; i <= 8; i++)
    {
        dx += direction.first;
        dy += direction.second;
        if (dx < 0 || dx >= BOARD_SIZE || dy < 0 || dy >= BOARD_SIZE)
        {
            line.data[i] = -1;
        }
        else
        {
            line.data[i] = board[dx][dy] * player;
        }
    }
    return line;
}

/**
 * @brief Eval the line by analysing the shape of the pieces.
 * @param line The line for evaluation.
 * @return score The score of the line.
 */
int evalPointLine(Line &line)
{
    int score = 0;

    int left_index = 4;
    while (left_index > 0)
    {
        if (line.data[left_index - 1] != 1)
        {
            break;
        }
        left_index--;
    }

    int right_index = 4;
    while (right_index < 8)
    {
        if (line.data[right_index + 1] != 1)
        {
            break;
        }
        right_index++;
    }
    int piece_count = right_index - left_index + 1;

    if (piece_count == 1)
    {
        int left_1_result = checkPositionStatus(line, left_index - 1);

        if (left_1_result == 0 && checkPositionStatus(line, left_index - 2) == 1)
        {
            score += BLANK_TWO;
        }
        else
        {
            int right_1_result = checkPositionStatus(line, right_index + 1);

            if (right_1_result == 0 && checkPositionStatus(line, right_index + 2) == 1)
            {
                score += BLANK_TWO;
            }
            else if (left_1_result == 0 && right_1_result == 0)
            {
                score += LIVE_ONE;
            }
            else if (left_1_result == 0 || right_1_result == 0)
            {
                score += BLOCKED_ONE;
            }
        }
    }
    else if (piece_count == 2)
    {
        int left_1_result = checkPositionStatus(line, left_index - 1);

        if (left_1_result == 0 && checkPositionStatus(line, left_index - 2) == 1)
        {
            score += BLANK_THREE;
        }
        else
        {
            int right_1_result = checkPositionStatus(line, right_index + 1);

            if (right_1_result == 0 && checkPositionStatus(line, right_index + 2) == 1)
            {
                score += BLANK_THREE;
            }
            else if (left_1_result == 0 && right_1_result == 0)
            {
                score += LIVE_TWO;
            }
            else if (left_1_result == 0 || right_1_result == 0)
            {
                score += BLOCKED_TWO;
            }
        }
    }
    else if (piece_count == 3)
    {
        int left_1_result = checkPositionStatus(line, left_index - 1);

        if (left_1_result == 0 && checkPositionStatus(line, left_index - 2) == 1)
        {
            score += BLANK_FOUR;
        }
        else
        {
            int right_1_result = checkPositionStatus(line, right_index + 1);

            if (right_1_result == 0 && checkPositionStatus(line, right_index + 2) == 1)
            {
                score += BLANK_FOUR;
            }
            else if (left_1_result == 0 && right_1_result == 0)
            {
                score += LIVE_THREE;
            }
            else if (left_1_result == 0 || right_1_result == 0)
            {
                score += BLOCKED_THREE;
            }
        }
    }
    else if (piece_count == 4)
    {
        int left_1_result = checkPositionStatus(line, left_index - 1);
        int right_1_result = checkPositionStatus(line, right_index + 1);

        if (left_1_result == 0 && right_1_result == 0)
        {
            score += LIVE_FOUR;
        }
        else if (left_1_result == 0 || right_1_result == 0)
        {
            score += BLOCKED_FOUR;
        }
    }
    else if (piece_count >= 5)
    {
        score += FIVE;
    }

    return score;
}

/**
 * @brief Get the position status of a point on a line (use this function to avoid index out of range).
 * @param line The line to get a point.
 * @param index The index of the point.
 * @return statue The status of the point (if the index is out of range, consider it as a point occupied by the other player).
 */
int checkPositionStatus(Line &line, int index)
{
    if (index < 0 || index >= 9)
    {
        return -1;
    }
    else
    {
        return line.data[index];
    }
}

/**
 * @brief Go through all the points on the board to get the best move.
 * @param player The current player to make the move.
 * @param board The current board.
 * @param depth The number of steps to be evaluated (if depth = 2, this function considers a move by AI and then a move by human to get the best situation).
 * @param alpha The alpha for alpha beta pruning.
 * @param beta The beta for alpha beta pruning.
 * @return (x, y, score) The x, y coordinate of the best move and the score of this move.
 */
tuple<int, int, int> getAiMove(int player, vector<vector<int>> &board, int depth, int alpha, int beta)
{

    if (!init)
        initLineDict();

    int max_score = -1000000;
    int max_x = -1;
    int max_y = -1;

    vector<vector<int>> point_list;

    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            // We only consider the point that hasn't been occupied and has another piece in its 1-neighbor.
            if (board[x][y] == 0 && checkNeighbor(x, y, 1, board))
            {
                point_list.push_back({x, y, evalPoint(x, y, player, board)});
            }
        }
    }

    // If the first move is made by AI, choose to move in the middle of the board.
    if (point_list.size() == 0)
    {
        return make_tuple(BOARD_SIZE / 2, BOARD_SIZE / 2, 0);
    }

    // Heuristically search, sort the point list by point score to improve the speed of alpha beta pruning.
    sort(point_list.begin(), point_list.end(), comparePointVector);

    for (int i = 0; i < point_list.size(); i++)
    {
        int x = point_list[i][0];
        int y = point_list[i][1];
        board[x][y] = player;

        // Minimax search, find the best move considering both AI's move and human's reaction.
        int score;
        if (depth == 1)
        {
            score = evalBoardAll(player, board);
        }
        else
        {
            // Since the score for human is -1 * the score for AI, we stick to find the max by multiplying human's score with -1.
            tie(ignore, ignore, score) = getAiMove(-player, board, depth - 1, -beta, -alpha);
            score = -score;
        }
        board[x][y] = 0;

        int count = 0;
        if (score > max_score)
        {
            max_score = score;
            max_x = x;
            max_y = y;
        }

        // Alpha beta pruning, decrease the number of nodes that are evaluated by the minimax search.
        alpha = max(alpha, score);
        if (alpha >= beta)
        {
            break;
        }
    }

    return make_tuple(max_x, max_y, max_score);
}

/**
 * @brief Initialise the line dictionary, afterwards the program can get the score of line faster by getting it from the ram.
 */
void initLineDict()
{
    for (int a = 0; a <= 2; a++)
    {
        for (int b = 0; b <= 2; b++)
        {
            for (int c = 0; c <= 2; c++)
            {
                for (int d = 0; d <= 2; d++)
                {
                    for (int e = 0; e <= 2; e++)
                    {
                        for (int f = 0; f <= 2; f++)
                        {
                            for (int g = 0; g <= 2; g++)
                            {
                                for (int h = 0; h <= 2; h++)
                                {
                                    Line line{a - 1, b - 1, c - 1, d - 1, 1, e - 1, f - 1, g - 1, h - 1};
                                    line_dict[a][b][c][d][e][f][g][h] = evalPointLine(line);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    init = true;
}

/**
 * @brief Check whether there exits a piece in the neighbor of the point.
 * @param x The x coordinate of the point.
 * @param y The y coordinate of the point.
 * @param distance The distance of the neighbor.
 * @param board The current board.
 * @return result Whether the first vector‘s score is larger than the second vector's score.
 */
bool checkNeighbor(int x, int y, int distance, vector<vector<int>> &board)
{
    int dx = x - 1 - distance;

    for (int i = 0; i <= 2 * distance; i++)
    {
        dx++;
        int dy = y - 1 - distance;

        for (int j = 0; j <= 2 * distance; j++)
        {
            dy++;
            if (dx >= 0 && dx < BOARD_SIZE && dy >= 0 && dy < BOARD_SIZE && board[dx][dy] != 0)
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Compare two vector by comparing their score.
 * @param x The first vector to be compared.
 * @param y The second vector to be compared.
 * @return result Whether the first vector‘s score is larger than the second vector's score.
 */
bool comparePointVector(vector<int> x, vector<int> y)
{
    return x[2] > y[2];
}