#include <map>
#include <string>
#include <utility>
#include <functional>
#include <queue>
#include <vector>
#include <iostream>
 
typedef std::string Nodelabel;
typedef std::map<Nodelabel, int> Nodelist;
typedef std::map<Nodelabel, Nodelist> Graph;
typedef std::pair<Nodelabel, Nodelist> Node;
typedef std::pair<int, Nodelabel> Edg;
 
bool operator>(const Edg r, const Edg k){ return r.first>k.first; }
 
void dijkstra(Graph &graph, Nodelabel source, Nodelist &distance){
  distance.clear();
  std::priority_queue<Edg, std::vector<Edg>, std::greater<Edg> > que;
  que.push(Edg(0, source));
 
  while(!que.empty()){
    Edg tmped=que.top();
    Nodelabel tmpnl=tmped.second;
    que.pop();
    if(distance.count(tmpnl)==0){
      int dist=tmped.first;
      distance[tmpnl]=dist;
      Nodelist tempgraph=graph[tmpnl];
      Nodelist::iterator it;
      for(it=tempgraph.begin(); it!=tempgraph.end(); ++it){
        int distint=it->second;
        Nodelabel distlabel=it->first;
        que.push(Edg(dist+distint, distlabel));
      }
    }
  }
}
/*
int main(){
  Graph test;
  test["japan"]["usa"]=12;
  test["usa"]["kanada"]=14;
  test["usa"]["kuba"]=3;
  test["kuba"]["kanada"]=4;
 
  Nodelist strecke;
 
  dijkstra(test, "japan", strecke);
 
  Nodelist::iterator it;
  for(it=strecke.begin(); it!=strecke.end(); ++it){
    std::cout<<it->second<<" <=> "<<it->first<<std::endl;
  }
  return 1;
}
*/