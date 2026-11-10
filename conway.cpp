#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const string MOVE_TOP_LEFT = "\033[H";
const string CLEAR_SCREEN = "\033[2J";
const string HIDE_CURSOR = "\033[?25l";
const string SHOW_CURSOR = "\033[?25h";

const vector<int> dx = {1, 1, 1, -1, -1, -1, 0, 0};
const vector<int> dy = {0, 1, -1, 0, 1, -1, 1, -1};

void display(vector<vector<bool>>& grid) {
    string frame = "";
    frame.append(MOVE_TOP_LEFT);

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j])
                frame.append("■ ");
            else
                frame.append("  ");
        }
        frame.append("\n");
    }

    cout << frame << flush;
}

int getLiveCount(vector<vector<bool>>& grid, int x, int y) {
    int count = 0;
    for (int i = 0; i < dx.size(); i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size()) {
            count += (grid[nx][ny]) ? 1 : 0;
        }
    }

    return count;
}

void iterate(vector<vector<bool>>& grid, vector<vector<bool>>& nextGrid) {
    int n = grid.size();
    int m = grid[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int liveCount = getLiveCount(grid, i, j);

            if (grid[i][j]) {
                if (liveCount == 1) {
                    nextGrid[i][j] = false;
                } else if (liveCount == 4) {
                    nextGrid[i][j] = false;
                } else {
                    nextGrid[i][j] = true;
                }
            } else {
                if (liveCount == 3)
                    nextGrid[i][j] = true;
                else
                    nextGrid[i][j] = false;
            }
        }
    }

    swap(grid, nextGrid);
}
int main() {
    struct winsize ws;

    if (ioctl(0, TIOCGWINSZ, &ws) != 0) {
        fprintf(stderr, "TIOCGWINSZ:%s\n", strerror(errno));
        exit(1);
    }

    int rows = ws.ws_row;
    int cols = ws.ws_col;
    vector<vector<bool>> grid(rows, vector<bool>(cols, false));
    vector<vector<bool>> grid2(rows, vector<bool>(cols, false));

    grid[2][2] = grid[2][3] = grid[2][4] = true;
    grid[4][3] = grid[5][3] = grid[6][3] = true;

    // grid[5][6] = grid[5][7] = grid[6][6] = grid[6][7] = true;
    // grid[1][8] = grid[1][9] = grid[2][8] = grid[2][9] = true;

    cout << CLEAR_SCREEN;
    cout << HIDE_CURSOR;
    for (int i = 0; i < 1000; i++) {
        iterate(grid, grid2);
        display(grid);
        usleep(50000);
    }
    cout << SHOW_CURSOR;
    return 0;
}
