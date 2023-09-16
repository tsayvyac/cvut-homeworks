#include "telescope.hpp"
#include <sstream>
#include <iomanip>

std::pair<size_t, size_t> parse_matrix(std::istream& in) {
    std::pair<size_t, size_t> size_of_matrix;
    int num;
    size_t rows = 0, cols = 0;
    std::string line;
    while (std::getline(in, line)) {
        rows++;
        std::stringstream ss(line);
        do {
            ss >> num;
            cols++;
        } while (!ss.eof());
    }
    if (rows != 0) {
        if (cols % rows != 0) {
            throw std::invalid_argument("");
        }
        cols /= rows;
    }
    size_of_matrix.first = rows;
    size_of_matrix.second = cols;
    return size_of_matrix;
}

std::vector<int> parse_matrix(std::istream& in, const std::pair<size_t, size_t>& m_size) {
    std::vector<int> matrix;
    int num;
    size_t all_nums = 0, dim = m_size.first * m_size.second;
    std::string line;
    while (std::getline(in, line)) {
        std::stringstream  ss(line);
        do {
            ss >> num;
            matrix.push_back(num);
            all_nums++;
        } while (!ss.eof());
    }
    if (dim != all_nums) {
        throw std::invalid_argument("");
    }
    return matrix;
}

void print_matrix(std::ostream& out, const std::pair<size_t, size_t>& m_size, const std::vector<int>& vec) {
    size_t count = 0;
    int width = 0;
    const int COLS = (int) m_size.second;
    int amount_of_lines = 0;
    for(int n : vec) {
        std::string s = std::to_string(n);
        if ((int) s.size() > width) {
            width = (int) s.size();
        }
    }
    if (COLS != 0) {
        amount_of_lines = ((width + 2) * COLS) + COLS + 2;
    }
    out << std::setw(amount_of_lines) << std::setfill('-');
    if (COLS != 0) {
        out << '\n';
    }
    for (int i : vec) {
        if (count == 0) {
            out << "|";
        }
        out << std::setw(width + 1) << std::setfill(' ') << i;
        out << " |";
        count++;
        if (count == m_size.second) {
            count = 0;
            out << std::endl;
        }
    }
    out << std::setw(amount_of_lines) << std::setfill('-');
    if (COLS != 0) {
        out << '\n';
    }
}

std::vector<unsigned char> parse_stream(std::istream& in, const std::pair<size_t, size_t>& m_size) {
    std::vector<unsigned char> matrix;
    size_t count = 0;
    unsigned char ch;
    size_t dim = m_size.first * m_size.second;
    std::noskipws(in);
    while (in >> ch) {
        matrix.push_back(ch);
        count++;
    }
    if (count != dim) {
        throw std::invalid_argument("");
    }
    return matrix;
}

void rotate_down(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec) {
    std::vector<unsigned char> copy = vec;
    size_t curr_col = 1, curr_row = 1, new_row, i = 0;
    bool is_last;
    while (i < copy.size()) {
        if (curr_col % m_size.second == 0) {
            is_last = true;
        } else {
            is_last = false;
        }
        new_row = (curr_row + 1 - 1) % m_size.first;
        if (new_row == 0) new_row = 0;
        std::swap(vec[(new_row * m_size.second) + curr_col - 1], copy[i++]);
        if (is_last) {
            curr_col = 1;
            curr_row++;
        } else {
            curr_col++;
        }
    }
}

void rotate_down(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, int step) {
    if (step < 0) {
        step = (step % (int) m_size.first) + (int) m_size.first;
    } else if (step > 0) {
        step %= (int) m_size.first;
    } else {
        return;
    }
    std::vector<unsigned char> copy = vec;
    size_t curr_col = 1, curr_row = 1, new_row, i = 0;
    bool is_last;
    while (i < copy.size()) {
        if (curr_col % m_size.second == 0) {
            is_last = true;
        } else {
            is_last = false;
        }
        new_row = (curr_row + step - 1) % m_size.first;
        if (new_row == 0) new_row = 0;
        std::swap(vec[(new_row * m_size.second) + curr_col - 1], copy[i++]);
        if (is_last) {
            curr_col = 1;
            curr_row++;
        } else {
            curr_col++;
        }
    }
}

void rotate_right(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec) {
    std::vector<unsigned char> copy = vec;
    size_t current_col = 1, current_row = 1, new_col, i = 0;
    bool is_last;
    while (i < copy.size()) {
        if (current_col % m_size.second == 0) {
            is_last = true;
        } else {
            is_last = false;
        }
        new_col = (current_col + 1) % m_size.second;
        if (new_col == 0) new_col = m_size.second;
        std::swap(vec[(current_row * m_size.second) - (m_size.second - new_col) - 1], copy[i++]);
        if (is_last) {
            current_col = 1;
            current_row++;
        } else {
            current_col++;
        }
    }

}

void rotate_right(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, int step) {
    std::vector<unsigned char> copy = vec;
    size_t current_col = 1, current_row = 1, new_col, i = 0;
    bool is_last;
    if (step < 0) {
        step = (step % (int) m_size.second) + (int) m_size.second;
    } else if (step > 0) {
        step %= (int) m_size.second;
    } else {
        return;
    }
    while (i < copy.size()) {
        if (current_col % m_size.second == 0) {
            is_last = true;
        } else {
            is_last = false;
        }
        new_col = (current_col + step) % m_size.second;
        if (new_col == 0) new_col = m_size.second;
        std::swap(vec[(current_row * m_size.second) - (m_size.second - new_col) - 1], copy[i++]);
        if (is_last) {
            current_col = 1;
            current_row++;
        } else {
            current_col++;
        }
    }
}

void swap_points(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, const Point& p1, const Point& p2) {
    if (p1.x > m_size.first - 1 || p2.x > m_size.first - 1 || p1.y > m_size.second - 1 || p2.y > m_size.second - 1) {
        throw std::invalid_argument("");
    }
    std::swap(vec[p1.y * m_size.second + p1.x], vec[p2.y * m_size.second + p2.x]);
}

void swap_points(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, const Point& p1, const Point& p2, const Point& delta) {
    size_t index_of_ch1, index_of_ch2;
    size_t dim = m_size.first * m_size.second;
    size_t ul = m_size.second * p1.y + p1.x; //up left
    size_t dl = ul + (delta.y - 1) * m_size.second; // down left
    size_t ur = ul + delta.x - 1; // up right
    size_t dr = ur + (delta.y - 1) * m_size.second; // down right
    for (size_t i = 0; i < delta.x; i++) {
        for (size_t j = 0; j < delta.y; j++) {
            index_of_ch1 = m_size.second * (p1.y + j) + p1.x + i;
            index_of_ch2 = m_size.second * (p2.y + j) + p2.x + i;
            if (ul == index_of_ch2 || dl == index_of_ch2 || ur == index_of_ch2 || dr == index_of_ch2 || index_of_ch2 > dim || index_of_ch1 > dim) {
                throw std::invalid_argument("");
            }
            std::swap(vec[index_of_ch1],vec[index_of_ch2]);
        }
    }
}

void decode_picture(const std::string& file, const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec) {
    std::fstream file_to_decode;
    std::string line;
    int num, num1, num2, num3, num4, num5;
    unsigned char operation;
    file_to_decode.open(file);
    while (std::getline(file_to_decode, line)) {
        std::stringstream ss(line);
        num = 1, num1 = 1, num2 = 1, num3 = 1, num4 = 1, num5 = 1;
        do {
            ss >> operation >> num >> num1 >> num2 >> num3 >> num4 >> num5;
        } while(!ss.eof());
        switch (operation) {
            case 'l':
                rotate_right(m_size, vec, -1 * num);
                break;
            case 'r':
                rotate_right(m_size, vec, num);
                break;
            case 'u':
                rotate_down(m_size, vec, -1 * num);
                break;
            case 'd':
                rotate_down(m_size, vec, num);
                break;
            case 's':
                swap_points(m_size, vec, Point(num, num1), Point(num2, num3), Point(num4, num5));
                break;
            default:
                return;
        }
    }
}