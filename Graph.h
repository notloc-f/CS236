#ifndef GRAPH_H_
#define GRAPH_H_
#include <map>
#include "Node.h"
class Graph{
public:
void PrintAll();
void addNode(int index,Node temp);
map<int,Node> getMap();
private:
  string type;
  map<int,Node> connections;
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
#endif
