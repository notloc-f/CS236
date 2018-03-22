#ifndef DATABASE_H_
#define DATABASE_H_
#include "datalog.h"
#include "Scheme.h"
#include "Tuples.h"
#include "Relation.h"
#include <map>
#include <set>
class Database {
public:
void Start();
void AddRelation(string namer, vector<string> lister);
void AddFact(string namer,vector<string> help);
Relation EvalQuery(string namer, vector<string> helper);
Relation Projecter(Relation changeable);
private:

map<string,Relation> relations;
vector<Relation> tempor;
};
Relation Database::Projecter(Relation toChange){
  Relation projected;

return projected;
}
void Database::Start(){

  for(unsigned int x =0; x <tempor.size(); x++){
    cout << tempor.at(x).PrintAll() << endl;
  }
}
Relation Database:: EvalQuery(string namer, vector<string> comparer){
  cout << "NEW QUERY  " << namer << endl;
  vector<int> IDspots;
  set<string> IDs;
  set<int> IDindex;
  Relation toAdd = relations[namer];
  for(unsigned int x =0; x < comparer.size(); x++){
    cout << "Comparing " << comparer.at(x) << endl;
    if(comparer.at(x)[0]=='\''){
    toAdd.SpecSelect(x,comparer.at(x));

  }
  else{
    if(x==(comparer.size()-1)){

      IDspots.push_back(x);
      break;
    }
    IDindex.insert(x);
    if(IDs.find(comparer.at(x))== IDs.end()) { //THIS ADDS ID SPOTS TO PROJECT
      IDspots.push_back(x);
    }

    for(unsigned int i = x +1; i < comparer.size(); i++){
      cout << "COMPARING " << comparer.at(x) << " and " << comparer.at(i) << endl;
      if((comparer.at(x) == comparer.at(i))){
        cout << "They da same" << endl;
        toAdd.DupSelect(x,i);
      }
      else{
      }
    }
  }
}
toAdd.Rename(comparer);
toAdd.Project(IDindex);
cout << " SIZE OF THIS Adder is " << toAdd.tupleSize() << endl;
tempor.push_back(toAdd);
//cout << toAdd.Printer(IDspots);
//cout << toAdd.PrintAll() << endl;
return toAdd;
}
void Database::AddRelation(string name, vector<string> list){
Relation tempter;
 tempter.Initial(name,list);
relations.insert(pair<string,Relation>(name,tempter));
}
void Database::AddFact(string namer, vector<string> lister){
  Tuples temp;
  for(unsigned int x=0; x <lister.size(); x++){
    temp.push_back(lister.at(x));
  }
  relations[namer].AddTuple(temp);

}

#endif
