#include "../createGraph/adjMatrix.h"
#include <stack>
template <typename Type>
void AdjGraph<Type>::deepTraverse() const {
    std::vector<bool> over_traverse(vec_size);
    std::stack<size_type> next_index;
    next_index.push(0);
    over_traverse[0] = true;
    while (!next_index.empty()) {
        size_type index = next_index.top();
        next_index.pop();
        std::cout << table[index] << " ";
        for (int i=vec_size-1; i>=0; --i) {
            if (matrix[index][i] && !over_traverse[i]) {
                next_index.push(i);
                over_traverse[i] = true;
            }
        }
    }
    std::cout << std::endl;
}
template <typename Type>
void AdjGraph<Type>::dfsShow() const {
    std::vector<bool> over_traverse(vec_size);
    dfs(0, over_traverse);
}
template <typename Type>
void AdjGraph<Type>::dfs(int n, std::vector<bool> &over_traverse) const{
    std::cout << table[n] << " ";
    over_traverse[n] = true;
    for (int i=0; i<vec_size; ++i) {
        if (!over_traverse[i] && matrix[n][i]) {
            dfs(i, over_traverse);
        }
    }
}
int main() {
    AdjGraph<char> graph;
    graph.deepTraverse();
    graph.dfsShow();
    std::cout << std::endl;
    return 0;
}
