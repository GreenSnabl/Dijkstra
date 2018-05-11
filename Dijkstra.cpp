/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dijkstra_Skiena.cpp
 * Author: snbl
 * 
 * Created on May 11, 2018, 10:00 AM
 */

#include <set>
#include <map>
#include <limits>
#include <ostream>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::set;
using std::map;
using std::ostream;
using std::vector;


const int INF = std::numeric_limits<int>::max();

struct Position {
    int x;
    int y;

    bool operator!=(const Position &other) const {
        if (this->x != other.x && this->y != other.y) return true;
    }
    bool operator==(const Position &other) const {
        if (this->x == other.x && this->y == other.y) return true;
    }
    bool operator<(const Position& pos) const {
        if (this->y != pos.y) return this->y < pos.y;
        return this->x < pos.x;
    }
    friend ostream& operator<<(ostream& os, const Position& pos) {
        os << "{" << pos.x << "," << pos.y << "}";
    }
};

struct Edge {
    Edge(Position v1, Position v2) {
        if (v1 < v2) {
            vertex_1 = v1;
            vertex_2 = v2;
        } else {
            vertex_1 = v2;
            vertex_2 = v1;
        }
    }
    Position vertex_1;
    Position vertex_2;

    bool operator<(const Edge& other) const {
        if (this->vertex_1 != other.vertex_1) return this->vertex_1 < other.vertex_1;
        return this->vertex_2 < other.vertex_2;
    }
    
    friend ostream& operator<<(ostream& os, const Edge& edge) {
        os << edge.vertex_1 << "<->" << edge.vertex_2;
    }
};

struct Graph {

    void addVertices(bool arr[10][5], set<Position>& vertices) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 5; ++j) {

                if (arr[i][j] == true) vertices.insert({j, i});
            }
        }
    }

    void addEdges(bool arr[10][5], set<Edge>& edges) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (arr[i][j] == true) {
                    for (int k = i - 1; k < i + 2; ++k) {
                        for (int l = j - 1; l < j + 2; ++l) {
                            if (k < 0 || k >= 10 || l < 0 || l >= 5 || (k == i && l == j)) continue;
                            if (arr[k][l] == true) edges.insert({
                                    {j, i},
                                    {l, k}
                                });
                        }
                    }
                }
            }
        }
    }

    void printVertices(const set<Position>& vertices) {
        for (auto it : vertices)
            cout << it << endl;
    }

    void printEdges(const set<Edge>& edges) {
        for (auto it : edges)
            cout << it << endl;
    }
};


typedef std::pair<Position, int> MyPairType;

struct CompareSecond {

    bool operator()(const MyPairType& left, const MyPairType& right) const {
        return left.second < right.second;
    }
};



Position minDistance(map<Position, int>& dist) {
    std::pair<Position, int> min = *std::min_element(dist.begin(), dist.end(), CompareSecond());
    return min.first;
}



vector<Position> dijkstra(map<Position, map<Position, int> > graph, Position source, Position dest) {

    set<Position> q;

    for (auto it : graph)
        q.insert(it.first);

    map<Position, int> dist;
    map<Position, Position> prev;
    for (auto it : q) {
        dist.insert({it, INF});
        prev.insert({it,
            {-1, -1}});
    }
    dist[source] = 0;

    while (!q.empty()) {
        Position u = minDistance(dist);
        q.erase(u);
        for (auto it : graph[u]) {
            int alt = dist[u] + it.second;
            if (alt < dist[it.first]) {
                dist[it.first] = alt;
                prev[it.first] = u;
            }
        }
        if (u == dest) break;
    }
    vector<Position> shortestPath;
    if (dist[dest] != INF) {

        shortestPath.push_back(dest);
        while (prev[shortestPath[0]].x != -1 || prev[shortestPath[0]].y != -1) {
            shortestPath.push_back(prev[shortestPath[0]]);

        }
    }
    return shortestPath;
}

void addEdges(bool arr[10][5], map<Position, map<Position, int> >& graph) {

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (arr[i][j] == true) {
                for (int k = i - 1; k < i + 2; ++k) {
                    for (int l = j - 1; l < j + 2; ++l) {
                        if (k < 0 || k >= 10 || l < 0 || l >= 5 || (k == i && l == j)) continue;
                        if (arr[k][l] == true) graph[ {
                            j, i
                        }
                        ][
                        {
                            l, k
                        }
                        ] = 1;
                    }
                }
            }
        }
    }
}

void printGraph(const map<Position, map<Position, int> >& graph) {
    for (auto it : graph)
        for (auto it2 : it.second)
            cout << it.first << "<->" << it2.first << " Distance: " << it2.second << endl;
    ;
}

int main(int argc, char** argv) {



    bool arr[10][5]{
        {true, false, false, false, true},
        {true, false, true, true, true},
        {true, false, false, false, true},
        {true, false, true, true, true},
        {true, false, true, false, true},
        {true, false, true, true, true},
        {true, true, false, false, true},
        {true, false, true, true, true},
        {true, false, false, false, true},
        {true, false, true, true, true}
    };

    map<Position, map<Position, int> > graph;
    addEdges(arr, graph);

    vector<Position> shortestPath;
    shortestPath = dijkstra(graph, {0,0}, {3,9});
    
    for (auto it : shortestPath)
        cout << it << endl;
    
    //printGraph(graph);


    return 0;
}

