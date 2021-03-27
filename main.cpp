#include <iostream>
#include "vector"
#include "algorithm"

using namespace std;

class Prufer {
private:
    int INF = INT16_MAX;
    vector<int> PATH;
    vector<vector<int>> graph;

    // Find minimal vertex
    int MIN() {
        int min = INF;
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].size() == 1) {
                if (i < min) {
                    min = i;
                }
            }
        }
        return min;
    }


    // Find the second vertex of the edge
    int PARENT(int vertex) {
        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph[i].size(); ++j) {
                if (graph[i][j] == vertex) {
                    return i;
                }
            }
        }
    }

public:
    void resize(int n) {
        graph.resize(n);
    };

    // Input
    void fillGraph(int m) {
        int start, finish;
        for (int i = 0; i < m; ++i) {
            cin >> start >> finish;
            graph[start - 1].push_back(finish - 1);
            graph[finish - 1].push_back(start - 1);
        }
    }

    // Start of the algorithm
    void startCoding(int minVertex, int m) {
        while (m - PATH.size() != 1) {
            PATH.push_back(PARENT(minVertex));
            graph[minVertex].erase(find(graph[minVertex].begin(),graph[minVertex].end(), PARENT(minVertex)));
            graph[PARENT(minVertex)].erase(find(graph[PARENT(minVertex)].begin(),graph[PARENT(minVertex)].end(), minVertex));
            startCoding(MIN(), m);
        }
    }


    // Output
    void code(int m) {
        startCoding(MIN(), m);
        for (int path : PATH) {
            cout << path + 1 << " ";
        }
    }
};

int main() {
    freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    Prufer prufer;
    prufer.resize(n);
    prufer.fillGraph(m);
    prufer.code(m);
    return 0;
}
