#include "crusoe.hpp"

#include <utility>
#include <queue>

vertex::vertex() = default;

vertex::vertex(std::string str, int x, int y, std::string col) :
        name(std::move(str)), xy(x, y), c_forward(std::move(col)){}

bool vertex::add_neighbour(size_t vv, const std::string &col) {
    for(const std::pair<size_t, std::string>& n : neighbours) {
        if (n.first == vv) {
            return false;
        }
    }
    std::pair<size_t, std::string> vertex_to_add(vv, col);
    neighbours.push_back(vertex_to_add);
    return true;
}

std::vector<std::pair<size_t, std::string>> vertex::get_neighbour() const {
    return neighbours;
}

std::pair<int, int> vertex::get_xy() const {
    return xy;
}

void vertex::set_color(const std::string &col) {
    c_forward.assign(col);
}

std::string vertex::get_color() const {
    return c_forward;
}

void vertex::set_edge_color(size_t vv, const std::string &col) {
    for(std::pair<size_t, std::string>& n : neighbours) {
        if (n.first == vv) {
            n.second.assign(col);
        }
    }
}

std::string vertex::get_edge_color(size_t vv) {
    for (std::pair<size_t, std::string> &n: neighbours) {
        if (n.first == vv) {
            return n.second;
        }
    }
    return "#FFFFFF";
}

void graph::add_vertex(int x, int y, const std::string &col) {
    vertex v(std::to_string(num_elem), x, y, col);
    vertices.push_back(v);
    num_elem++;
}

void graph::add_edge(size_t v1, size_t v2, const std::string &col) {
    if (v1 < num_elem && v2 < num_elem) {
        vertices[v1].add_neighbour(v2, col);
        vertices[v2].add_neighbour(v1, col);
    }
}

bool graph::is_edge(size_t v1, size_t v2) const {
    if (v1 < num_elem) {
        for(const std::pair<size_t, std::string>& v : vertices[v1].get_neighbour()) {
            if(v.first == v2) {
                return true;
            }
        }
    }
    return false;
}

std::string graph::edge_color(size_t v1, size_t v2) const {
    for(const std::pair<size_t, std::string>& v : vertices[v1].get_neighbour()) {
        if(v.first == v2) {
            return v.second;
        }
    }
    return "#FFFFFF";
}

std::string graph::vertex_color(size_t v1) const {
    if (v1 < num_elem) {
        return vertices[v1].get_color();
    }
    return "#FFFFFF";
}

void graph::set_vertex_color(size_t v1, const std::string &col) {
    if (v1 < num_elem) {
        vertices[v1].set_color(col);
    }
}

void graph::set_edge_color(size_t v1, size_t v2, const std::string &col) {
    if (v1 < num_elem && v2 < num_elem) {
        vertices[v1].set_edge_color(v2, col);
        vertices[v2].set_edge_color(v1, col);
    }
}

bool graph::empty() const {
    if (num_elem == 0) {
        return true;
    }
    return false;
}

size_t graph::size() const {
    return num_elem;
}

size_t graph::num_edge() const {
    size_t count = 0;
    for(const vertex& v : vertices) {
        count += v.get_neighbour().size();
    }
    return count/2;
}

// ------------------- stage 2 -------------------

vertex graph::get_vertex(size_t num) const {
    return vertices[num];
}

void graph::is_achievable(size_t from, std::vector<size_t> &achieved) {
    achieved.push_back(from);
    for(const std::pair<size_t, std::string>& n : vertices[from].get_neighbour()) {
        if(!(std::find(achieved.begin(), achieved.end(), n.first) != achieved.end())) {
            graph::is_achievable(n.first, achieved);
        }
    }
} // DFS

void graph::color_component(std::vector<size_t> cmp, const std::string &col) {
    for(size_t v : cmp) {
        vertices[v].set_color(col);
        for(const std::pair<size_t, std::string>& n : vertices[v].get_neighbour()) {
            if(edge_color(v, n.first) != col){
                set_edge_color(v, n.first, col);
            }
        }
    }
} // ###########################

std::vector<size_t> graph::path(size_t v1, size_t v2) {
    std::vector<bool> visited(num_elem, false);
    std::vector<int> parent(num_elem, -1);
    std::vector<size_t> shortest_path;
    std::queue<size_t> queue;
    visited[v1] = true;
    queue.push(v1);
    while(!queue.empty()) {
        size_t v = queue.front();
        queue.pop();
        for(const std::pair<size_t, std::string>& n : vertices[v].get_neighbour()) {
            if(!visited[n.first]) {
                visited[n.first] = true;
                queue.push(n.first);
                parent[n.first] = (int)v;
                if(n.first == v2) {
                    while(parent[v2] != -1) {
                        shortest_path.push_back(v2);
                        v2 = parent[v2];
                    }
                    shortest_path.push_back(v1);
                    std::reverse(shortest_path.begin(), shortest_path.end());
                }
            }
        }
    }
    return shortest_path;
} // BFS

void graph::color_path(std::vector<size_t> pth, const std::string &col) {
    for(size_t& p : pth) {
        for(auto& n : vertices[p].get_neighbour()) {
            if(n.second != col) {
                set_edge_color(p, n.first, col);
            }
        }
    }
}

// ------------------- stage 3 -------------------

graph::graph_comp::graph_comp(graph& gg) : gg(gg) {
    std::vector<size_t> comp;
    std::vector<bool> visited(gg.num_elem, false);
    for(size_t i = 0; i < gg.num_elem; i++) {
        comp.clear();
        if(!visited[i]) {
            gg.is_achievable(i, comp);
            for(size_t& c : comp) {
                visited[c] = true;
            }
            components.push_back(comp);
        }
    }
}

void graph::graph_comp::color_componennts() {
    std::vector<std::string> colors{"red", "olive", "orange", "lightblue", "yellow", "pink", "cyan", "purple", "brown", "magenta"};
    size_t i = 0;
    for(auto& comp : components) {
        if(comp.size() > 1) {
            gg.color_path(comp, colors[i]);
            for(auto& c : comp) {
                gg.set_vertex_color(c, colors[i]);
            }
            i++;
            if(i == colors.size()) {
                i = 0;
            }
        }
    }
}

size_t graph::graph_comp::count() const {
    return components.size();
}

size_t graph::graph_comp::count_without_one() const {
    size_t count = 0;
    for(const std::vector<size_t>& c : components) {
        if(c.size() > 1) {
            count++;
        }
    }
    return count;
}

size_t graph::graph_comp::max_comp() const {
    size_t size = components[0].size();
    size_t index_of_max = 0;
    for(size_t i = 1; i < components.size(); i++) {
        if(size < components[i].size()) {
            index_of_max = i;
            size = components[i].size();
        }
    }
    return index_of_max;
}

size_t graph::graph_comp::size_of_comp(size_t i) const {
    return components[i].size();
}

std::vector<size_t> graph::graph_comp::get_component(size_t i) const {
    return components[i];
}

bool graph::graph_comp::same_comp(size_t v1, size_t v2) const {
    bool in_same_comp = false;
    for(const auto& component : components) {
        if(std::find(component.begin(), component.end(), v1) != component.end()) {
            in_same_comp = (std::find(component.begin(), component.end(), v2) != component.end());
            return in_same_comp;
        }
    }
    return in_same_comp;
}

graph::graph_fence::graph_fence(graph &gg, size_t vv, size_t distance)
        : gg(gg){
    std::vector<size_t> achieved;
    std::vector<size_t> path;
    fence.push_back(vv);
    gg.is_achievable(vv, achieved);
    for(size_t v : achieved) {
        path = gg.path(vv, v);
        if(path.size() - 1 <= distance) {
            fence.push_back(v);
        }
    }
}

void graph::graph_fence::color_fence(const std::string &col) {
    for(size_t v : fence) {
        gg.set_vertex_color(v, col);
    }
}

size_t graph::graph_fence::count_stake() const {
    return fence.size();
}

size_t graph::graph_fence::get_stake(size_t i) const {
    if(i < fence.size()) {
        return fence[i];
    }
    return false;
}