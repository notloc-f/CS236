#ifndef GRAPH_H_
#define GRAPH_H_
#include <map>
#include "Node.h"
#include <stack>
class Graph{
public:
void PrintAll();
void DepthFirst();
void DepthRecursion(Node& temp, int index);
void addNode(int index,Node temp);
map<int,Node> getMap();
private:
  string type;
  map<int,Node> connections;
  stack<int> toUse;
};
map<int,Node> Graph::getMap(){
  return connections;
}
void Graph::addNode(int index,Node temp){
  connections.insert(pair<int,Node>(index,temp));
}
void Graph::PrintAll(){
  for(map<int,Node>::iterator it = connections.begin(); it!= connections.end();it++){
    cout << "R" << it->first << ": " << it->second.PrintLinks() << endl;
  }
}
void Graph::DepthFirst(){
  for(map<int,Node>::iterator it =connections.begin();it!=connections.end(); it++){
    DepthRecursion(it->second, it->first);
  }
}
void Graph::DepthRecursion(Node& recur,int temp){
  if(recur.getVisit()){
    return;
  }
  else{
    if(recur.getSelf()){
      recur.setVisit();
    }
    recur.setVisit();
    set<int> links = recur.allLinks();
    for(set<int>::iterator it =links.begin(); it!= links.end(); it++){
      DepthRecursion(connections.at(*it), *it);
    }
    cout << "Pushing " << temp << endl;
    toUse.push(temp);
    return;

  }
}

#endif
