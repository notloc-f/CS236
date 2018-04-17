#ifndef NODE_H_
#define NODE_H_
#include <set>
class Node{
public:
  string PrintLinks();
  void addLink(int newlink);
  void clearAll();
  set<int> allLinks();
  void setLinks(set<int> temp);
  void Selfie();
  bool getSelf();
  void setVisit();
  bool getVisit();
  int getSize();
private:
  set<int> links;
  bool visited = false;
  bool self=false;
};
int Node::getSize(){
  return links.size();
}
set<int> Node::allLinks(){
  return links;
}
bool Node::getVisit(){
  return visited;
}
bool Node::getSelf(){
  return self;
}
void Node::setVisit(){
  visited = true;
}
string Node::PrintLinks(){
  ostringstream ss;
  for(set<int>::iterator it= links.begin(); it!= links.end(); it++){
    ss <<"R" << *it << ",";
  }

  return ss.str();
}
void Node::Selfie(){
  self = true;
}
void Node::addLink(int newLink){
  //cout << "ADDING " << newLink << endl;
  links.insert(newLink);
}
void Node::clearAll(){
  links.clear();
  visited = false;
  self =false;
}
void Node::setLinks(set<int> temp){
links = temp;
}
#endif
