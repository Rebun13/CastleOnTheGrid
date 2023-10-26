#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);
void move(vector<string> grid, int startX, int startY, int goalX, int goalY, int steps, char lastMove, int &minSteps);

/*
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY grid
 *  2. INTEGER startX
 *  3. INTEGER startY
 *  4. INTEGER goalX
 *  5. INTEGER goalY
 */

void printGrid(vector<string> grid)
{
    for (string s : grid)
    {
        cout << s << endl;
    }
}

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY)
{
    int minSteps = INT_MAX;
    move(grid, startX, startY, goalX, goalY, 0, 'N', minSteps);
    return minSteps;
}

void move(vector<string> grid, int startX, int startY, int goalX, int goalY, int steps, char lastMove, int &minSteps)
{
    if (startX == goalX && startY == goalY)
    {
        if(steps < minSteps) {
            minSteps = steps;
        }
        return;
    }

    if(steps >= minSteps) {
        return;
    }

    grid.at(startX).replace(startY, 1, 1, 'X');

    // left
    if (startY > 0 && grid.at(startX).at(startY - 1) != 'X')
    {
        move(grid, startX, startY - 1, goalX, goalY, lastMove != 'L' ? steps + 1 : steps, 'L', minSteps);
    }

    // right
    if (startY < grid.at(0).size() - 1 && grid.at(startX).at(startY + 1) != 'X')
    {
        move(grid, startX, startY + 1, goalX, goalY, lastMove != 'R' ? steps + 1 : steps, 'R', minSteps);
    }

    // up
    if (startX > 0 && grid.at(startX - 1).at(startY) != 'X')
    {
        move(grid, startX - 1, startY, goalX, goalY, lastMove != 'U' ? steps + 1 : steps, 'U', minSteps);
    }

    // down
    if (startX < grid.size() - 1 && grid.at(startX + 1).at(startY) != 'X')
    {
        move(grid, startX + 1, startY, goalX, goalY, lastMove != 'D' ? steps + 1 : steps, 'D', minSteps);
    }

    /*
    cout << "CURRENT STATUS [" << stepsLeft << ", " << stepsRight << ", " << stepsUp << ", " << stepsDown << "]" << endl;
    printGrid(grid);
    cout << endl;

    int best = min({stepsLeft, stepsRight, stepsUp, stepsDown});
    return best;
    */
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> grid(n);

    for (int i = 0; i < n; i++)
    {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int startX = stoi(first_multiple_input[0]);

    int startY = stoi(first_multiple_input[1]);

    int goalX = stoi(first_multiple_input[2]);

    int goalY = stoi(first_multiple_input[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

    cout << result << "\n";

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](int c)
                { return !std::isspace(c); }));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](int c)
                { return !std::isspace(c); })
            .base(),
        s.end());

    return s;
}

vector<string> split(const string &str)
{
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
