#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <limits> 
#include <set>
#include <utility>
#include <algorithm> 
#include <iterator>


// Dijkstra ist eine abgewandelte Version aus Kommentar von Samuel auf
// https://stackoverflow.com/questions/3447566/dijkstras-algorithm-in-c


using namespace std;

struct Position;
typedef Position vertex_t;
typedef int weight_t;

const weight_t max_weight = numeric_limits<int>::max();


struct Position {
    int x;
    int y;

    bool operator!=(const Position &other) const {
        return (this->x != other.x && this->y != other.y);
    }
    bool operator==(const Position &other) const {
        return (this->x == other.x && this->y == other.y);
    }
    bool operator<(const Position& pos) const {
        if (this->y != pos.y) return this->y < pos.y;
        return this->x < pos.x;
    }
    friend ostream& operator<<(ostream& os, const Position& pos) {
        os << "{" << pos.x << "," << pos.y << "}";
    }
    
    Position& operator=(const Position& other) {this->x = other.x; this->y = other.y; return *this;}
};


struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};

//typedef vector<vector<neighbor> > adjacency_list_t;
typedef map<vertex_t, map<vertex_t, weight_t> > adjacency_list_t;

// Computing the shortest pathway

void DijkstraComputePaths(vertex_t source,
                     adjacency_list_t &adjacency_list,
                     map<vertex_t, weight_t> &min_distance,
                     map<vertex_t, vertex_t> &previous)
{
    min_distance.clear();
    previous.clear();
    for (auto it : adjacency_list)
        min_distance[it.first] = max_weight;
    
    min_distance[source] = 0;
    previous.clear();
    set<pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        // Visit each edge exiting u
        for (auto neighbor_iter : adjacency_list[u])
        {
            vertex_t v = neighbor_iter.first;
            weight_t weight = neighbor_iter.second;
            weight_t distance_through_u = dist + weight;
            if (distance_through_u < min_distance[v]) {
                vertex_queue.erase(make_pair(min_distance[v], v));

                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.insert(make_pair(min_distance[v], v));

            }
        }
    } // while
}



void addEdges(bool arr[6][6], map<Position, map<Position, int> >& graph) {

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (arr[i][j] == true) {
                for (int k = i - 1; k < i + 2; ++k) {
                    for (int l = j - 1; l < j + 2; ++l) {
                        if (k < 0 || k >= 6 || l < 0 || l >= 6 || (k == i && l == j)) continue;
                        if (arr[k][l] == true) graph[{j, i}][{l, k}] = 1;
                    }
                }
            }
        }
    }
}


bool getShortestPath(map<vertex_t, vertex_t>& previous, vertex_t source, vertex_t dest, vector<vertex_t>& shortestPath) {
    
    if (previous.find(dest) == previous.end()) return false;
    
    shortestPath.push_back(dest);
    
    while (true) {
        shortestPath.push_back(previous[shortestPath[shortestPath.size() - 1]]);
        if (shortestPath[shortestPath.size() - 1] == source) break;
    } 
    std::reverse(shortestPath.begin(), shortestPath.end());
}

int main(int argc, char** argv) {


    bool arr[6][6]{
        {true, false, false, true, false, true},
        {true, false, false, false, true, false},
        {true, false, false, true, false, false},
        {false, true, false, false, true, false},
        {false, false, true, false, false, true},
        {true, true, false, true, true, false}
    };
    
    map<vertex_t, weight_t> min_distance;
    map<vertex_t, vertex_t> previous;

    //map<Position, set<Position> > graph;
    //addEdges(arr, graph);
    
    map<Position, map<Position, int> > graph2;
    addEdges(arr, graph2);

    DijkstraComputePaths({0,0}, graph2, min_distance, previous);

    for (auto it : graph2)
    {
        cout << it.first;
        for (auto it2 : it.second)
            cout << it2.first;
        cout << endl;
    } 
    
    for (auto it : min_distance)
        cout << it.first << " " << it.second << endl;
    
    for (auto it : previous)
        cout << it.first << " " << it.second << endl;
    
    vector<vertex_t> shortestPath;
    
    getShortestPath(previous, {0,0}, {5,0}, shortestPath);
    

    
    for (auto it : shortestPath)
    {
        cout << it;    
    }
    

    return 0;
}