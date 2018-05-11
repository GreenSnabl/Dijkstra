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
<<<<<<< HEAD
        return (this->x != other.x && this->y != other.y);
=======
        if (this->x != other.x || this->y != other.y) return true;
        return false;
>>>>>>> 3fa900a3840e28a20f690b804c2e7dae371d2721
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

<<<<<<< HEAD
=======
struct Mengen {
        
    static const int m_max_w = 5;
    static const int m_max_h = 10;
    
    set<Edge> edges;
    set<Position> vertices;


>>>>>>> 3fa900a3840e28a20f690b804c2e7dae371d2721

    void addVertices(bool arr[4][3], set<Position>& vertices) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {

<<<<<<< HEAD
                if (arr[i][j] == true) vertices.insert({j, i});
=======
    void addVertices(bool arr[m_max_h][m_max_w])
    {
        for (int i = 0; i < m_max_h; ++i) {
            for (int j = 0; j < m_max_w; ++j) {
                
                if (arr[i][j] == true) vertices.insert({j,i});
>>>>>>> 3fa900a3840e28a20f690b804c2e7dae371d2721
            }
        }
    }

<<<<<<< HEAD
    void addEdges(bool arr[4][3], set<Edge>& edges) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (arr[i][j] == true) {
                    for (int k = i - 1; k < i + 2; ++k) {
                        for (int l = j - 1; l < j + 2; ++l) {
                            if (k < 0 || k >= 4 || l < 0 || l >= 3 || (k == i && l == j)) continue;
                            if (arr[k][l] == true) edges.insert({
                                    {j, i},
                                    {l, k}
                                });
=======
    void addEdges(bool arr[m_max_h][m_max_w]) 
    {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 5; ++j)
            {
                if (arr[i][j] == true) 
                {
                    for (int k = i - 1; k < i + 2; ++k) 
                    {
                        for (int l = j - 1; l < j + 2; ++l) 
                        {
                            if (k < 0 || k >= 10 || l < 0 || l >= 5 || (k == i && l == j)) continue;
                            if (arr[k][l] == true) edges.insert({{j,i},{l,k}});                        
>>>>>>> 3fa900a3840e28a20f690b804c2e7dae371d2721
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

struct CompareSecond {

    bool operator()(const std::pair<Position, int>& left, const std::pair<Position,int>& right) const {
        return left.second < right.second;
    }
};

<<<<<<< HEAD
Position minDistance(map<Position, int>& dist) {
    std::pair<Position, int> min = *std::min_element(dist.begin(), dist.end(), CompareSecond());
    return min.first;
}



void dijkstra(map<Position, map<Position, int> > graph, Position source, Position dest, vector<Position>& shortestPath) {

    map<Position, int> q;
    map<Position, int> dist;
    map<Position, Position> prev;
    for (auto it : graph) {
        Position pos = it.first;
        q.insert({pos, INF});
        dist.insert({pos, INF});
        prev.insert({pos, {-1, -1}});
    }
    q.insert({dest, INF});
    dist.insert({dest, INF});
    prev.insert({dest, {-1,-1}});
     dist[source] = 0;
     q[source] = 0;


    while (!q.empty()) {
        Position v = minDistance(q);
        q.erase(v);
        for (auto it : graph[v]) {
            int alt = dist[v] + it.second;
            if (alt < dist[it.first]) {
                dist[it.first] = alt;
                q[it.first] = alt;
                prev[it.first] = v;
            }
        }
      // if (v == dest) break;
    }

    if (dist[dest] != INF) {
        shortestPath.push_back(dest);
        while (prev[shortestPath[shortestPath.size()-1]].x != -1 && prev[shortestPath[shortestPath.size()-1]].y != -1) {
            shortestPath.push_back(prev[shortestPath[shortestPath.size()-1]]);
        }
    }
}

void addEdges(bool arr[4][3], map<Position, map<Position, int> >& graph) {

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (arr[i][j] == true) {
                for (int k = i; k < i + 2; ++k) {
                    for (int l = j; l < j + 2; ++l) {
                        if (k < 0 || k >= 4 || l < 0 || l >= 3 || (k == i && l == j)) continue;
                        if (arr[k][l] == true) graph[{j, i}][{l, k}] = 1;
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



    bool arr[4][3]{
        {true, false, false},
        {true, false, false},
        {true, false, true},
        {false, true, true}
 
=======

    const int m_max_w = 5;
    const int m_max_h = 10;

int main(int argc, char** argv) {

    bool arr[10][5] {
        {false, false, false, false, true},
        {false, false, true, false, true},
        {true, false, false, true, false},
        {false, true, false, true, false},
        {false, false, true, false, true},
        {false, false, true, true, false},
        {false, true, false, false, false},
        {false, true, true, false, true},
        {true, false, false, true, false},
        {true, false, false, true, false}
>>>>>>> 3fa900a3840e28a20f690b804c2e7dae371d2721
    };

    map<Position, map<Position, int> > graph;
    addEdges(arr, graph);
    
    set<Edge> edges;
    addEdges(arr, edges);
    
    set<Position> vertices;
    addVertices(arr, vertices);
    
    map<Position, map<Position, int> > graph2;
    
    //printEdges(edges);
    
    //printVertices(vertices);
    
    
    for (auto it : vertices)
    {
        for (auto it2 : edges)
        {
            if (it == it2.vertex_1) {
                graph2[it2.vertex_1][it2.vertex_2] = 1;
            }
        }
    
    }
    
    
    
    
    vector<Position> shortestPath;
    dijkstra(graph2, {0,0}, {2,3}, shortestPath);
    
    for (auto it : shortestPath)
        cout << it << endl;
  
    //printGraph(graph2);


    return 0;
}

