#include "Graph.h"

// Алгоритм Дейкстры
// Вход: граф; вершина, из которой ищем кратчайшие пути
void dijkstra(Graph graph, int starting_vertex) {
    std::cout << "\n======================= АЛГОРИТМ ДЕЙКСТРЫ =======================\n";
    // Проверяем граф на отрицательные веса
    if (checking(graph)) {
        std::cout << "В графе обнаружены ребра с отрицательным весом\n";
        return;
    }
    int n = graph.vertexes; // Количество вершин в графе

    // Выделение памяти и инициализация массивов
    int* pred = new int[n]; // Хранит предшествующие вершины
    int* shortest = new int[n]; // Хранит кратчайшее расстояние до вершины
    for (int i = 0; i < n; i++) {
        shortest[i] = INT_MAX;
        pred[i] = -1;
    }
    shortest[starting_vertex] = 0; // Расстояние до вершины старта равно нулю

    PQueue pqueue; // Очередь с приоритетом
    for (int i = 0; i < n; i++) { // Добавление всех вершин в очередь с приоритетом
        pqueue.insert(i);
    }

    while(!pqueue.empty()) { // Пока очередь не пуста
        int u = pqueue.Delete(shortest); // Записываем в u элемент с наименьшим значением shortest[u]
        // и удаляем его из очереди

        for (int v = 0; v < n; v++) { // Проходим по всем вершинам
            if (graph.matrix[u][v] > 0) { // Если существует ребро
                relax(graph.matrix, pred, shortest, u, v); // Релаксация ребра
            }
        }
    }
    print_result(shortest, pred, n); // Печать массивов shortest и pred
    delete []shortest;
    delete []pred;
}

// Алгоритм Беллмана-Форда
// Вход: граф; вершина, из которой ищем кратчайшие пути
void BF(Graph graph, int starting_vertex) {
    int n = graph.vertexes; // Количество вершин в графе

    // Выделение памяти и инициализация массивов
    int* pred = new int[n]; // Хранит предшествующие вершины
    int* shortest = new int[n]; // Хранит кратчайшее расстояние до вершины
    for (int i = 0; i < n; i++) {
        shortest[i] = INT_MAX;
        pred[i] = -1;
    }
    shortest[starting_vertex] = 0; // Расстояние до вершины старта равно нулю

    for (int i = 0; i < n - 1; i++) { // Проходим по всем вершинам до n - 1
        for (int j = 0; j < graph.edges.size(); j++) {
            // Релаксация всех существующих ребер
            relax(graph.matrix, pred, shortest, graph.edges[j].source, graph.edges[j].destination);
        }
    }
    std::cout << "\n==================== АЛГОРИТМ БЕЛЛМАНА-ФОРДА ====================\n";
    // Если search не обнаружил в графе отрицательный цикл, то печатаем массивы shortest и pred
    if (search(graph, pred, shortest)) print_result(shortest, pred, n);
    delete []shortest;
    delete []pred;
}

// Функция поиска отрицательного цикла в графе
bool search(Graph graph, const int* pred, const int* shortest) {
    int n = graph.vertexes; // Количество вершин в графе
    List list; // Связный список, в который будем записывать вершины, образующие отрицательный цикл
    bool* visited = new bool[n]; // Хранит уже посещенные вершины
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    for (auto & edge : graph.edges) { // Проход по всем ребрам графа
        if (shortest[edge.source] + edge.weight < shortest[edge.destination]) {
            int v = edge.destination;
            int x = v;
            while (!visited[x]) {
                visited[x] = true;
                x = pred[x];
            }
            v = pred[x];
            list.push_front(x);
            while (v != x) {
                list.push_front(v);
                v = pred[v];
            }
            std::cout << "В графе обнаружен цикл с отрицательным весом, состоящий из вершин: ";
            list.print();
            delete []visited;
            return false;
        }
    }
    delete []visited;
    return true;
}

// Алгоритм Флойд-Уоршелла
// Вход: граф
void FU(Graph graph) {
    int n = graph.vertexes; // Количество вершин в графе
    int** shortest = new int* [n];
    int** pred = new int* [n];
    for (int i = 0; i < n; i++) {
        shortest[i] = new int[n];
        pred[i] = new int[n];
        for (int j = 0; j < n; j++) {
            shortest[i][j] = INT_MAX;
            pred[i][j] = -1;
        }
    }

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (graph.matrix[u][v] != 0) {
                shortest[u][v] = graph.matrix[u][v];
                pred[u][v] = u;
            }
            if (u == v) {
                shortest[u][v] = 0;
                pred[u][v] = u;
            }
        }
    }

    for (int x = 0; x < n; x++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (shortest[u][v] > shortest[u][x] + shortest[x][v] && shortest[u][x] != INT_MAX && shortest[x][v] != INT_MAX) {
                    shortest[u][v] = shortest[u][x] + shortest[x][v];
                    pred[u][v] = x;
                }
            }
        }
    }

    std::cout << "\n=================== АЛГОРИТМ ФЛОЙДА-УОРШЕЛЛА ====================\n" <<
              "Минимальные расстояния:" << std::setw(70 - n) << "Предшествующие вершины:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (shortest[i][j] == INT_MAX) {
                std::cout << "*" << std::setw(3);
            } else {
                std::cout << shortest[i][j] << std::setw(3);
            }
        }
        std::cout << std::setw(50 - n * 4);
        for (int j = 0; j < n; j++) {
            std::cout << pred[i][j] << std::setw(3);
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    delete []shortest;
    delete []pred;
}

// Функция релаксации ребра
void relax(int** matrix, int* pred, int* shortest, int u, int v) {
    if (shortest[u] != INT_MAX && shortest[u] + matrix[u][v] < shortest[v]) {
        shortest[v] = shortest[u] + matrix[u][v];
        pred[v] = u;
    }
}

// Функция печати массивов shortest и pred
void print_result(int* shortest, int* pred, int vertex) {
    for (int i = 0; i < vertex; i++) {
        if (shortest[i] == INT_MAX) {
            std::cout << "Пути до вершины " << i << " не существует\n";
        } else {
            std::cout << "Кратчайший путь до вершины " << i << " равен " << shortest[i] << ". Предшествующая вершина: " << pred[i] << "\n";
        }
    }
    std::cout << "\n";
}

// Функция проверки графа на наличие ребер с отрицательным весом
bool checking(Graph graph) {
    for (auto & edge : graph.edges) {
        if (edge.weight < 0) {
            return true;
        }
    }
    return false;
}

// Функция преобразования ориетированного графа в неориентированный посредством зеркального копирования
void mirrored(Graph graph) {
    int n = graph.vertexes; // Количество вершин в графе
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph.matrix[i][j] != 0) {
                graph.matrix[j][i] = graph.matrix[i][j]; // Зеркальное копирование
            }
        }
    }
}

// Алгоритм Прима поиска минимального остовного дерева
// Вход: граф
void primMST(Graph graph) {
    mirrored(graph); // Превращаем ориентированный граф в неориентированный
    int n = graph.vertexes; // Количество вершин в графе
    int result_weight = 0; // Вес минимального остовного дерева

    // Выделение памяти
    bool* visited = new bool[n]; // Хранит уже посещенные вершины
    int* shortest = new int[n]; // Хранит кратчайшее расстояние до вершины
    int* end_edge = new int[n]; // Хранит
    for (int i = 0; i < n; i++) {
        shortest[i] = INT_MAX;
        visited[i] = false;
        end_edge[i] = -1;
    }
    shortest[0] = 0;
    std::cout << "========================= АЛГОРИТМ ПРИМА =========================\n";
    for (int i = 0; i < n; i++) {
        int v = -1;

        // Ищем вершину с минимальным весом, которая ещё не была посещена
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (v == -1 || shortest[j] < shortest[v])) v = j;
        }

        visited[v] = true; // Помечаем её как посещённую

        if (end_edge[v] != -1) {
            std::cout << "Ребро из " << end_edge[v] << " в " << v << " весом " << graph.matrix[v][end_edge[v]] << "\n";
            result_weight += graph.matrix[v][end_edge[v]];
        }

        for (int to = 0; to < n; to++) {
            if (graph.matrix[v][to] != 0 && graph.matrix[v][to] < shortest[to]) {
                shortest[to] = graph.matrix[v][to];
                end_edge[to] = v;
            }
        }
    }
    std::cout << "Вес минимального остовного дерева: " << result_weight << "\n\n";
    delete []shortest;
    delete []visited;
    delete []end_edge;
}


// Если вершина v не имеет родителя (принадлежит корневому элементу), возвращает саму вершину v.
// В противном случае рекурсивно вызывает findSet для родителя вершины v.
int findSet(int* parent, int v) {
    if (v == parent[v])
        return v;
    return findSet(parent, parent[v]);
}

// Затем устанавливает корень множества u в качестве родителя корня множества v.
// Это соединяет два множества в одно, объединяя их корневые элементы.
void unionSets(int* parent, int u, int v) {
    parent[u] = parent[v];
}

void kruskalMST(Graph graph) {
    int n = graph.vertexes; // Количество вершин в графе
    int result_weight = 0; // Вес минимального остовного дерева
    int* parent= new int[n];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // Сортировка массива рёбер.
    for (int i = 0; i < graph.edges.size() - 1; i++) {
        for (int j = 0; j < graph.edges.size() - i - 1; j++) {
            if (graph.edges[j].weight > graph.edges[j + 1].weight) {
                // Обмен элементов, если они стоят в неправильном порядке.
                Graph::edge temp = graph.edges[j];
                graph.edges[j] = graph.edges[j + 1];
                graph.edges[j + 1] = temp;
            }
        }
    }

    // Вывод рёбер минимального остовного дерева
    std::cout << "======================== АЛГОРИТМ КРУСКАЛА ========================\n";
    for (int i = 0; i < graph.edges.size(); ++i) {
        int rootU = findSet(parent, graph.edges[i].source); // определяет первоисходную вершину
        // т.к. изначально была добавлена вершина 3(в ребре 3 - 5), => findSet возвращает
        // первую(главную вершину)
        int rootV = findSet(parent, graph.edges[i].destination);

        if (rootU != rootV) { // Проверка, что вершины ребра edges[i] не имеют общего предка
            // Если имеют, то соединение вершин приведёт к циклу
            std::cout << "Ребро из " << graph.edges[i].source << " в " << graph.edges[i].destination << " весом " << graph.edges[i].weight << "\n";
            result_weight += graph.edges[i].weight;
            unionSets(parent, rootU, rootV);
        }

//        // промежуточные результаты parent
//        for (int j = 0; j < n; j++)
//            std::cout << parent[j] << " ";
//        std::cout << "\n";
    }
    std::cout << "Вес минимального остовного дерева: " << result_weight << "\n\n";
}
