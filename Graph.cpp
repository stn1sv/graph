#include <iostream>
#include <iomanip>

class Graph {
public:
    int vertexes; // Количество вершин графа
    int** matrix; // Матрица смежности графа
    struct edge { // Ребро графа
        int source; // Начальная вершина
        int destination; // Конечная вершина
        int weight; // Вес ребра
    };
    std::vector<edge> edges; // Массив ребер графа

    // Конструктор класса
    explicit Graph(int number_of_vertex) {
        vertexes = number_of_vertex;
        matrix = new int* [vertexes];
        for (int i = 0; i < vertexes; i++) { // Выделяем память для матрицы смежности
            matrix[i] = new int [vertexes];
        }
    }

    // Считывание матрицы смежности из строки input
    void initialization(const char* input) {
        char delimiter;
        int weight;
        const char* ptr = input;
        for (int i = 0; i < vertexes; i++) {
            const char* ptr1 = ptr;
            for (int j = 0; j < vertexes; j++) {
                sscanf(ptr1, "%d%c", &weight, &delimiter);
                add_edge(i, j, weight);
                while (*ptr1 && *ptr1 != ',' && *ptr1 != '\n') {
                    ptr1++;
                }
                if (*ptr1) {
                    ptr1++;
                }
            }
            while (*ptr && *ptr != '\n') {
                ptr++;
            }
            if (*ptr) {
                ptr++;
            }
        }
    }

    // Функция добавления нового ребра графу
    void add_edge(int source, int destination, int weight) {
        matrix[source][destination] = weight;
        if (weight != 0) edges.push_back({source, destination, weight});
    }

    // Функция печати матрицы смежности графа
    void print() const {
        std::cout << "======================= МАТРИЦА СМЕЖНОСТИ =======================\n   ";
        for (int i = 0; i < vertexes; i++) {
            std::cout << std::setw(3) << i << ' ';
        }
        std::cout << "\n\n";
        for (int i = 0; i < vertexes; i++) {
            std::cout << i << "  ";
            for (int j = 0; j < vertexes; j++) {
                if (matrix[i][j] != 0) {
                    std::cout << std::setw(3) << matrix[i][j] << ' ';
                } else {
                    std::cout << std::setw(3) << "*" << " ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
};
