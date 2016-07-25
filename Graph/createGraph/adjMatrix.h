#ifndef _ADJMATRIX_H_
#define _ADJMATRIX_H_
#include <iostream>
#include <vector>
/*#define _DIREACTION_*/
template <typename Type>
class AdjGraph{
    private:
        std::vector<Type> table;
        std::vector<std::vector<bool> > matrix;
        typedef int size_type;
        size_type vec_size;
        size_type edge_size;
    public:
        AdjGraph() {
            std::cout << "input the size of vec : ";
            std::cin >> vec_size;
            std::cout << "input the size of edge : ";
            std::cin >> edge_size;
            std::cout << "input the msg of vec : ";
            table.resize(vec_size);
            for (size_type i=0; i<vec_size; ++i) {
                std::cin >> table[i];
            }
            matrix.resize(vec_size);
            for (size_type i=0; i<vec_size; ++i) {
                matrix[i].resize(vec_size);
            }
            std::cout << "input the edge msg\n";
            for (size_type i=0; i<edge_size; ++i) {
                size_type first, last;
                std::cin >> first >> last;
                matrix[first][last] = true;
#ifndef _DIREACTION_
                matrix[last][first] = true;
#endif
            }
        }
        void showGraph() const{
            for (int i=0; i<vec_size; ++i) {
                for (int j=0; j<vec_size; ++j) {
                    if (matrix[i][j]) {
                        std::cout << table[i] << "-----" << table[j] << std::endl;
                    }
                }
            }
        }
    public:
        /*finish in other file*/
        void deepTraverse() const;
        void dfsShow() const;
        void broadTreaverse() const;
    private:
        void dfs(int, std::vector<bool> &) const;
};
#endif
