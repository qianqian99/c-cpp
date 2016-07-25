#include "../createGraph/adjMatrix.h"
#include <queue>
template <typename Type>
void AdjGraph<Type>::broadTreaverse() const {
    std::vector<bool> over_traverse(vec_size);
    std::queue<size_type> next_index;
    next_index.push(0);
    over_traverse[0] = true;
    while (!next_index.empty()) {
        size_type index = next_index.front();
        next_index.pop();
        std::cout << table[index] << " ";
        for (int i=0; i<vec_size; ++i) {
            if (matrix[index][i] && !over_traverse[i]) {
                next_index.push(i);
                over_traverse[i] = true;
            }
        }
    }
    std::cout << std::endl;
}
int main() {
    AdjGraph<char> graph;
    graph.broadTreaverse();
    return 0;
}
