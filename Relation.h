#ifndef RELATION_H_
#define RELATION_H_
class Relation{
public:
Relation();
Relation(string namer, vector<string> list);
void Initial(string namely, vector<string> lister);
private:
  string name;
  Schemes Schemer;
  set<Tuples> Tupler;
};
Relation::Relation(){

}
Relation::Relation(string namely, vector<string> lister){
  name = namely;
  for(unsigned int i=0; i < lister.size(); i++){
    Schemer.push_back(lister.at(i));
  }
}
void Relation::Initial(string namely, vector<string> lister){
  name = namely;
  for(unsigned int i=0; i < lister.size(); i++){
    Schemer.push_back(lister.at(i));
  }
}
#endif
