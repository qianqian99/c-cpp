#ifndef _ADJMATRIX_H_
#define _ADJMATRIX_H_
#include <iostream>
#include <vector>
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
            for (size_type i=0; i<vec_size; ++i) {
                std::cin >> table[i];
            }
        }
};
#endif
