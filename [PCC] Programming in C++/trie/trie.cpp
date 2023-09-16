#include "trie.hpp"

#include <utility>
#include <algorithm>
#include <cassert>
#include <stack>
#include <iostream>

// STAGE 1

trie::trie() = default;

void del(trie_node* node) {
    if (node != nullptr) {
        for (auto& child : node->children) {
            del(child);
        }
        delete node;
    }
}

trie::~trie() {
    del(m_root);
}

bool trie::insert(const std::string &str) {
    if (m_root == nullptr) m_root = new trie_node();
    trie_node* current = m_root;
    const char* sptr = str.c_str();
    while (*sptr) {
        if (current->children[*sptr] == nullptr) {
            current->children[*sptr] = new trie_node();
            current->children[*sptr]->payload = *sptr;
            current->children[*sptr]->parent = current;
        }
        current = current->children[*sptr];
        sptr++;
    }
    if (!current->is_terminal) {
        m_size++;
        current->is_terminal = true;
        return true;
    }
    return false;
}

bool trie::contains(const std::string &str) const {
    if (m_root == nullptr) return false;
    trie_node* current = m_root;
    const char* sptr = str.c_str();
    while (*sptr) {
        if (current->children[*sptr] == nullptr)
            return false;
        current = current->children[*sptr];
        sptr++;
    }
    return current != nullptr && current->is_terminal;
}

bool trie::erase(const std::string &str) {
    trie_node* current = m_root;
    const char* sptr = str.c_str();
    while (*sptr) {
        if (current->children[*sptr] == nullptr)
            return false;
        current = current->children[*sptr];
        sptr++;
    }
    if (current->is_terminal) {
        current->is_terminal = false;
        m_size--;
        while (current->parent != nullptr) {
            for (const auto& child : current->children) {
                if (child != nullptr)
                    return true;
            }
            auto to_delete = current;
            current = current->parent;
            current->children[to_delete->payload] = nullptr;
            delete to_delete;
        }
    } else return false;
    return true;
}

trie::trie(const std::vector<std::string> &strings) {
    m_root = new trie_node();
    for (const auto& s : strings) {
        insert(s);
    }
}

size_t trie::size() const {
    return m_size;
}

bool trie::empty() const {
    return m_size == 0;
}

// STAGE 2

trie::const_iterator trie::begin() const {
    trie_node* current = m_root;
    while (m_root != nullptr && !current->is_terminal) {
        for (auto& child : current->children) {
            if (child != nullptr) {
                current = child;
                break;
            }
        }
    }
    return {current};
}

trie::const_iterator trie::end() const {
    return {nullptr};
}

trie::const_iterator::const_iterator(const trie_node *node) {
    current_node = node;
}

//prefix
trie::const_iterator &trie::const_iterator::operator++() {
    if (current_node == nullptr) return *this;
    const trie_node* current = current_node;
    for (const auto& child : current->children) {
        if (child != nullptr) {
            current = child;
            while (!current->is_terminal) {
                for (const auto& c_child : current->children) {
                    if (c_child != nullptr) {
                        current = c_child;
                        break;
                    }
                }
            }
            current_node = current;
            return *this;
        }
    }
    char visited;
    while (current->parent != nullptr) {
        visited = current->payload;
        current = current->parent;
        for (size_t i = visited + 1; i < num_chars; ++i) {
            if (current->children[i] != nullptr) {
                current = current->children[i];
                while (!current->is_terminal) {
                    for (const auto& child : current->children) {
                        if (child != nullptr) {
                            current = child;
                            break;
                        }
                    }
                }
                current_node = current;
                return *this;
            }
        }
    }
    current_node = nullptr;
    return *this;
}

//postfix
trie::const_iterator trie::const_iterator::operator++(int) {
    trie::const_iterator temp(*this);
    ++*this;
    return temp;
}

bool trie::const_iterator::operator==(const trie::const_iterator &rhs) const {
    return current_node == rhs.current_node;
}

bool trie::const_iterator::operator!=(const trie::const_iterator &rhs) const {
    return current_node != rhs.current_node;
}

trie::const_iterator::reference trie::const_iterator::operator*() const {
    const trie_node* current = current_node;
    std::string to_return;
    while (current != nullptr && current->parent != nullptr) {
        to_return += current->payload;
        current = current->parent;
    }
    std::reverse(to_return.begin(), to_return.end());
    return to_return;
}

// STAGE 3

trie::trie(const trie &rhs) {
    m_root = new trie_node();
    const_iterator iter = rhs.begin();
    while (iter != end()) {
        insert(*iter++);
    }
}

void trie::swap(trie &rhs) {
    std::swap(m_root, rhs.m_root);
    std::swap(m_size, rhs.m_size);
}

void swap(trie& lhs, trie& rhs) {
    lhs.swap(rhs);
}

trie &trie::operator=(const trie &rhs) {
    trie temp(rhs);
    swap(temp);
    return *this;
}

trie::trie(trie &&rhs) {
    swap(rhs);
}

trie &trie::operator=(trie &&rhs) {
    swap(rhs);
    return *this;
}

bool trie::operator==(const trie &rhs) const {
    if (m_size != rhs.m_size) return false;
    const_iterator lhs_iter = begin();
    while (lhs_iter != end()) {
        if (!rhs.contains(*lhs_iter))
            return false;
        lhs_iter++;
    }
    return true;
}

bool operator!=(const trie& lhs, const trie& rhs) {
    return !(lhs == rhs);
}

bool trie::operator<(const trie &rhs) const {
    if (empty() && rhs.empty()) return false;
    const_iterator lhs_iter = begin();
    const_iterator rhs_iter = rhs.begin();
    while (lhs_iter != end()) {
        if (*lhs_iter < *rhs_iter) return true;
        if (*lhs_iter > *rhs_iter) return false;
        lhs_iter++; rhs_iter++;
    }
    return m_size < rhs.m_size;
}

bool operator<=(const trie& lhs, const trie& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const trie& lhs, const trie& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const trie& lhs, const trie& rhs) {
    return (lhs > rhs) || (lhs == rhs);
}

// STAGE 4

std::vector<std::string> trie::search_by_prefix(const std::string &prefix) const {
    const_iterator iter = begin();
    std::vector<std::string> to_return;
    while (iter != end()) {
        if ((*iter).substr(0, prefix.size()) == prefix)
            to_return.push_back(*iter);
        iter++;
    }
    return to_return;
}

std::vector<std::string> trie::get_prefixes(const std::string &str) const {
    if (m_root == nullptr) return {};
    std::vector<std::string> to_return;
    trie_node* current = m_root;
    for (char c : str) {
        if (current->children[c] != nullptr) {
            if (current->children[c]->is_terminal) {
                const_iterator iter(current->children[c]);
                to_return.push_back(*iter);
            }
            current = current->children[c];
        } else {
            break;
        }
    }
    return to_return;
}

trie trie::operator|(const trie &rhs) const {
    trie to_return(rhs);
    const_iterator lhs_iter = begin();
    while (lhs_iter != end()) {
        to_return.insert(*lhs_iter);
        lhs_iter++;
    }
    return to_return;
}

// intersection
trie trie::operator&(const trie &rhs) const {
    trie to_return;
    const_iterator lhs_iter = begin();
    while (lhs_iter != end()) {
        if (rhs.contains(*lhs_iter))
            to_return.insert(*lhs_iter);
        lhs_iter++;
    }
    return to_return;
}

std::ostream& operator<<(std::ostream& out, trie const& trie) {
    return out;
}