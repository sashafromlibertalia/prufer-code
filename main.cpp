// Описание алгоритма - http://sashafromlibertalia.herokuapp.com/projects/pruferCode

#include "iostream"
#include "vector"
#include "set"
#include "algorithm"

using namespace std;

class Prufer {
private:
    int INF = INT16_MAX;
    vector<int> path;
    vector<vector<int>> graph;
    vector<pair<int, int>> edges;
    set<int> vertices;

    // Find minimal vertex
    int min() {
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

    // Find minimal vertex which is NOT in Prufer code
    int minForDecoding() {
        int min = INF;
        for(auto vertex : vertices) {
            for (int i = 0; i < path.size(); i++) {
                if (find(path.begin(), path.end(), vertex) == path.end() && vertex < min) {
                    min = vertex;
                }
            }
        }
        return min;
    }

    // Find the second vertex of the edge
    int parent(int vertex) {
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                if (graph[i][j] == vertex) {
                    return i;
                }
            }
        }
    }

    void startCoding(int minVertex) {
        while (graph.size() - 1 - path.size() != 1) {
            path.push_back(parent(minVertex));
            graph[minVertex].erase(find(graph[minVertex].begin(), graph[minVertex].end(), parent(minVertex)));
            graph[parent(minVertex)].erase(find(graph[parent(minVertex)].begin(), graph[parent(minVertex)].end(), minVertex));
            startCoding(min());
        }
    }

    void startDecoding() {
        while (!path.empty()) {
            int u = path[0];
            int v = minForDecoding();
            edges.emplace_back(u, v);
            path.erase(path.begin());
            vertices.erase(v);
        }
        edges.emplace_back(*vertices.begin(), *--vertices.end());
    }
public:
    void resize(int n) {
        graph.resize(n);
    };

    void fillGraph() {
        int start, finish;
        for (int i = 0; i < graph.size() - 1; ++i) {
            cin >> start >> finish;
            vertices.insert(start - 1);
            vertices.insert(finish - 1);
            graph[start - 1].push_back(finish - 1);
            graph[finish - 1].push_back(start - 1);
        }
    }

    void code() {
        startCoding(min());
        cout << "Prufer code: \n";
        for (int path : path) {
            cout << path + 1 << " ";
        }
    }

    void decode() {
        if (path.empty()) {
            throw logic_error("Unable to decode: Prufer code is empty.");
        }
        cout << endl;
        startDecoding();
        cout << "\nEdges:\n";
        for (auto & edge : edges) {
            cout << edge.first + 1 << " " << edge.second + 1 << endl;
        }
    }
};

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    Prufer prufer;
    prufer.resize(n);
    prufer.fillGraph();
    prufer.code();
    prufer.decode();
    return 0;
}

