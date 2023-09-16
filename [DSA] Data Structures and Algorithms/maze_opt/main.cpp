#include <iostream>
#include <vector>
#include <algorithm>

#define ERROR_RECTANGLE "Error: Bludiste neni obdelnikove!"
#define ERROR_TOP_LEFT "Error: Vstup neni vlevo nahore!"
#define ERROR_DOWN_RIGHT "Error: Vystup neni vpravo dole!"
#define ERROR_MAX_WIDTH "Error: Sirka bludiste je mimo rozsah!"
#define ERROR_MAX_LENGTH "Error: Delka bludiste je mimo rozsah!"
#define ERROR_CHARS "Error: Bludiste obsahuje nezname znaky!"
#define ERROR_FENCED "Error: Bludiste neni oplocene!"

static std::vector<std::string> maze;
static std::vector<std::pair<size_t, size_t>> path;
static size_t rows = 0;
static size_t cols = 0;
static bool first = true;

int parse() {
    std::string line;
    bool first_time = true;
    while (std::getline(std::cin, line)) {
        if (first_time) {
            cols = line.size();
            first_time = false;
        }
        if (line.size() != cols) {
            std::cerr << ERROR_RECTANGLE << '\n';
            return 1;
        }
        maze.push_back(line);
    }
    rows = maze.size();

    if (maze[0][1] != '.') {
        std::cerr << ERROR_TOP_LEFT << '\n';
        return 1;
    } else if (maze[rows - 1][cols - 2] != '.') {
        std::cerr << ERROR_DOWN_RIGHT << '\n';
        return 1;
    } else if (!(5 <= cols && cols <= 100)) {
        std::cerr << ERROR_MAX_WIDTH << '\n';
        return 1;
    } else if (!(5 <= rows && rows <= 50)) {
        std::cerr << ERROR_MAX_LENGTH << '\n';
        return 1;
    }

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            if (!(maze[row][col] == '#' || maze[row][col] == '.')) {
                std::cerr << ERROR_CHARS << '\n';
                return 1;
            }
        }
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1) {
                if ((i == 0 && j == 1) || (i == rows - 1 && j == cols - 2)) {
                    continue;
                }
                if (maze[i][j] != '#') {
                    std::cerr << ERROR_FENCED << '\n';
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool find_path(size_t row, size_t col) {
    if (row == rows - 1 && col == cols - 2) return true;
    if (row >= 0 && col > 0 && row < rows - 1 && col < cols - 1) {
        if (maze[row][col] != 'x' && maze[row][col] != '#') {
            if (first) path.insert(path.begin(), {row, col});

            bool is_exclamation = maze[row][col] == '!';

            maze[row][col] = 'x';
            //DOWN
            if (find_path(row + 1, col)) {
                maze[row][col] = is_exclamation ? '!' : '.';
                return true;
            }
            //RIGHT
            if (find_path(row, col + 1)) {
                maze[row][col] = is_exclamation ? '!' : '.';
                return true;
            }
            //UP
            if (find_path(row - 1, col)) {
                maze[row][col] = is_exclamation ? '!' : '.';
                return true;
            }
            //LEFT
            if (find_path(row, col - 1)) {
                maze[row][col] = is_exclamation ? '!' : '.';
                return true;
            }
        }
    }

    return false;
}

void clear_path() {
    for (auto& row : maze) {
        for (auto& point : row) {
            if (point == 'x') {
                point = '.';
            }
        }
    }
}

void mark_imp() {
    for (const auto& p : path) {
        maze[p.first][p.second] = '#';

        maze[p.first][p.second] = find_path(0, 1) ? '.' : '!';
        clear_path();
    }
    maze[0][1] = '!';
    maze[rows - 1][cols - 2] = '!';
}

int main() {
    if (parse() == 1) return 1;

    find_path(1, 1);
    clear_path();
    first = false;
    mark_imp();

    for (const auto& s : maze) {
        std::cout << s << '\n';
    }
    return 0;
}