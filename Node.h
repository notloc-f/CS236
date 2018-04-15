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
private:
  set<int> links;
  bool visited = false;
  bool self=false;
};
set<int> Node::allLinks(){
  return links;
}
string Node::PrintLinks(){
  ostringstream ss;
  for(set<int>::iterator it= links.begin(); it!= links.end(); it++){
    ss << *it << " ";
  }
  return ss.str();
}
void Node::addLink(int newLink){
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
