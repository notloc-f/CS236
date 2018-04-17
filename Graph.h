#ifndef GRAPH_H_
#define GRAPH_H_
#include <map>
#include "Node.h"
#include <stack>
class Graph{
public:
void PrintAll();
void DepthFirst();
void SSC(stack<int> depthStack);
void SSCRecursion(Node& noder, int ind);
void DepthRecursion(Node& temp, int index);
void addNode(int index,Node temp);
int getSize();
void PrintSSC();
map<int,Node> getMap();
stack<int> getStack();
vector<set<int>> getSSC();
private:
  string type;
  map<int,Node> connections;
  stack<int> toUse;
  vector<set<int>> sscs;
  set<int> tempSet;
};
void Graph::PrintSSC(){
  cout << "Printing groupings" << endl;
  for(unsigned int x = 0; x <sscs.size(); x++){
    cout << "{";
    for(set<int>::iterator it = sscs.at(x).begin(); it!= sscs.at(x).end(); it++){
      cout << *it << " ";
    }
    cout << "}" << endl;
  }
}
int Graph::getSize(){
  return connections.size();
}
map<int,Node> Graph::getMap(){
  return connections;
}
vector<set<int>> Graph::getSSC(){
  return sscs;
}
void Graph::addNode(int index,Node temp){
  connections.insert(pair<int,Node>(index,temp));
}
stack<int> Graph::getStack(){
  return toUse;
}
void Graph::PrintAll(){
  cout << "Dependency Graph" << endl;
  for(map<int,Node>::iterator it = connections.begin(); it!= connections.end();it++){
    string mustard = it->second.PrintLinks();
    int temp = mustard.size();
    if(temp !=0){
      mustard.resize(temp-1);
    }
    cout << "R" << it->first << ":" << mustard << endl;
  }
}
void Graph::DepthFirst(){
  for(map<int,Node>::iterator it =connections.begin();it!=connections.end(); it++){
    DepthRecursion(it->second, it->first);
  }
}
void Graph::SSC(stack<int> stacker){
  while(!stacker.empty()){
    SSCRecursion(connections.at(stacker.top()), stacker.top());
    stacker.pop();
    if(!tempSet.empty()){
    sscs.push_back(tempSet);
  }
    tempSet.clear();
  }
}

void Graph::SSCRecursion(Node& recur,int temp){
  if(recur.getVisit()){
    return;
  }
  else{
    if(recur.getSelf()){
      recur.setVisit();
    }
    tempSet.insert(temp);
  //  cout << "Inserted " << temp << " Into tempSet" << endl;
    recur.setVisit();
    set<int> links = recur.allLinks();
    for(set<int>::iterator it =links.begin(); it!= links.end(); it++){
      SSCRecursion(connections.at(*it), *it);
    }
  //TO CHANGE  sscs.push_back(tempSet);
  //  cout << "Temp set created with size" << tempSet.size() << endl;
  //TO CHANGE  tempSet.clear();

    return;

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
//    cout << "Pushing " << temp << endl;
    toUse.push(temp);
    return;

  }
}

#endif
