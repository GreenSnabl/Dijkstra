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
#include <ostream>
#include <iostream>

using std::cout; 
using std::endl;
using std::set;
using std::ostream;

struct Position {
    int x;
    int y;
    
    bool operator!=(const Position &other) const {
        if (this->x != other.x && this->y != other.y) return true;
    }
    
    bool operator<(const Position& pos) const
    {
        if (this->y != pos.y) return this->y < pos.y;
        return this->x < pos.x;
    }
    
    friend ostream& operator<<(ostream& os, const Position& pos)
    {
        os << "{" << pos.x << "," << pos.y << "}";
    }
    
};


struct Edge {
    Edge(Position v1, Position v2) {
        if (v1 < v2) {
            vertex_1 = v1; 
            vertex_2 = v2;
        }
        else {
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
    
    friend ostream& operator<<(ostream& os, const Edge& edge) 
    {
        os << edge.vertex_1 << "<->" << edge.vertex_2; 
    } 
    
};

struct Mengen {
    set<Edge> edges;
    set<Position> vertices;




    void addVertices(bool arr[10][5])
    {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 5; ++j) {
                
                if (arr[i][j] == true) vertices.insert({j,i});
            }
        }
                
    }

    void addEdges(bool arr[10][5]) 
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
                        }
                    }
                        
                }
            }
        }                
    }

    void printVertices() 
    {
        for (auto it : vertices)
            cout << it << endl;
    }
    
    void printEdges()
    {
        for (auto it : edges)
           cout << it << endl;    
    }
};

int main(int argc, char** argv) {

    bool arr[10][5] {
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
    
    Mengen m;
    
    m.addVertices(arr);
    m.addEdges(arr);

    
    m.printVertices();
    m.printEdges();
    
    return 0;
}
