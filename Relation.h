#ifndef RELATION_H_
#define RELATION_H_

class Relation{
public:
Relation();
Relation(string namer, vector<string> list);
void Initial(string namely, vector<string> lister);
void AddTuple(Tuples adder);
void SpecSelect(int pos, string value);
void DupSelect(int first,second);
string PrintAll();
void Rename();
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
  void Relation:: AddTuple(Tuples tumple){
  //  cout << "Adding: ";
    for(unsigned int x=0; x <tumple.size(); x++){
//      cout << "Value at " << x << " " << tumple.at(x) << " ";
    }

    Tupler.insert(tumple);
  //  cout << "Tupler " << name << " is of size " << Tupler.size() << endl;
  }
  void Relation::SpecSelect(int pos, string value){
  //  cout << "Values at " << pos << " comparing to " << value << endl;
    for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
      if((*it).at(pos)!= value){                             //NOTE YOU WILL NEED TO MODIFY THIS TO ALLOW FOR VARIABLES
        cout << "Erasing " << (*it).at(pos) << endl;
        cout << "Size before " << Tupler.size() << endl;
        Tupler.erase(it);
        cout << "Size after " << Tupler.size() << endl;
      }
    }
  }
  void Relation::DupSelect(int first, int second){
      for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
        if((*it).at(first) != (*it).at(second)){
          Tupler.erase(it);
        }
      }
  }
  string Relation::PrintAll(){

  }
  void Relation::Rename(){}

#endif
