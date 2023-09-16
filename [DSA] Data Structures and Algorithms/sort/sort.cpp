#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>

#define ERROR_MAX "Error: Maximum neni kladne!"
#define ERROR_UNKNOWN "Error: Neznamy typ razeni posloupnosti!"
#define ERROR_VIRUS "Error: Nelze urcit, zda posloupnost napadl virus!"
#define ERROR_OUT "Error: Prvek posloupnosti je mimo rozsah!"
#define ERROR_SORTED "Error: Posloupnost neni usporadana!"
#define ERROR_1K "Error: Posloupnost ma mene nez 1000 prvku!"
#define ERROR_1M "Error: Posloupnost ma vic nez 1000000 prvku!"

static bool first_line = true;
static std::vector<int> vec;
static int size_vec = 0, max = 0, type = 0, virus = 0;

//template <typename TimePoint>
//std::chrono::milliseconds to_ms(TimePoint tp) {
//    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
//}

int parse() {
    int prev;
    int number = -1;
    int temp_size = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream stream(line);
        if (first_line) {
            stream >> max >> type >> virus;
            if (max <= 0) {
                std::cerr << ERROR_MAX << '\n';
                return 1;
            }
            if (!(0 <= type && type < 3)) {
                std::cerr << ERROR_UNKNOWN << '\n';
                return 1;
            }
            if (virus != 0 && virus != 1) {
                std::cerr << ERROR_VIRUS << '\n';
                return 1;
            }
            first_line = false;
            prev = type == 2 ? max : -1;
            continue;
        }

        stream >> number;
        if (number > max) {
            std::cerr << ERROR_OUT << '\n';
            return 1;
        }
        if (type == 1 && virus == 0) {
            if (prev > number) {
                std::cerr << ERROR_SORTED << '\n';
                return 1;
            }
        }
        if (type == 2 && virus == 0) {
            if (prev < number) {
                std::cerr << ERROR_SORTED << '\n';
                return 1;
            }
        }
        prev = number;
        temp_size++;
        if (temp_size > 1'000'000) {
            std::cerr << ERROR_1M << '\n';
            return 1;
        }
        vec.push_back(number);
    }
    size_vec = (int)vec.size();
    if (size_vec < 1000) {
        std::cerr << ERROR_1K << '\n';
        return 1;
    }

    return 0;
}

void swap_n(int& a, int& b) {
    auto temp = a;
    a = b;
    b = temp;
}

void heapify(const int& size, const int& cur_idx) {
    int largest_idx;
    int left_idx = 2 * cur_idx + 1;
    int right_idx = 2 * cur_idx + 2;

    if (left_idx < size && vec[left_idx] > vec[cur_idx])
        largest_idx = left_idx;
    else
        largest_idx = cur_idx;
    if (right_idx < size && vec[right_idx] > vec[largest_idx])
        largest_idx = right_idx;

    if (largest_idx != cur_idx) {
        swap_n(vec[largest_idx], vec[cur_idx]);
        heapify(size, largest_idx);
    }
}

void build_max_heap() {
    for (int i = (size_vec / 2) - 1; i >= 0; i--)
        heapify(size_vec, i);
}

void heap_s() {
    build_max_heap();
    for (int j = size_vec - 1; j > 0; j--) {
        swap_n(vec[j], vec[0]);
        heapify(j, 0);
    }
}

void merge(int low, int mid, int high) {
    std::vector<int> temp(high - low + 1);
    int i = low;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= high) {
        if (vec[i] <= vec[j]) {
            temp[k] = vec[i];
            i++;
        } else {
            temp[k] = vec[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp[k] = vec[i];
        i++;
        k++;
    }

    while (j <= high) {
        temp[k] = vec[j];
        j++;
        k++;
    }

    for (int n = low; n <= high; n++) {
        vec[n] = temp[n - low];
    }
}

void merge_s(int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        merge_s(low, mid);
        merge_s(mid + 1, high);
        merge(low, mid, high);
    }
}

void rev() {
    for (int f = 0, l = size_vec - 1; f < l; f++, l--)
        swap_n(vec[f], vec[l]);
}

void insertion_s() {
    if (type == 2) {
        rev();
    }
    for (int i = 1; i < size_vec; i++) {
        int key = vec[i];
        int j = i - 1;
        while (j >= 0 && key < vec[j]) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
}

int main() {
//    auto start = std::chrono::high_resolution_clock::now();
    if (parse() == 1)
        return 1;
    if (type == 2 && virus == 0)
        rev();
    if (type == 0) {
        if (size_vec < 200'000)
            heap_s();
        else
            merge_s(0, size_vec - 1);
    }
    if ((type == 1 || type == 2) && virus == 1)
        insertion_s();
    for (const auto& n : vec)
        std::cout << n << '\n';
//    auto end = std::chrono::high_resolution_clock::now();
//    std::cout << "Needed " << to_ms(end - start).count() << " mcs to finish.\n";

    return 0;
}