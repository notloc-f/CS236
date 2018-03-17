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
void EvalQuery(string namer, vector<string> helper);
private:

map<string,Relation> relations;
};

void Database::Start(){
}
void Database:: EvalQuery(string namer, vector<string> comparer){
  cout << "*****Evaluating******** " << namer << endl;
  Relation toAdd = relations[namer];
  for(unsigned int x =0; x < comparer.size(); x++){
        cout <<"Evaluating with " << comparer.at(x) << endl;
    if(comparer.at(x)[0]=='\''){
    toAdd.SpecSelect(x,comparer.at(x));
  }
  else{
    cout << "That is an ID!!" << endl;
    for(unsigned int i = x+1; i <comparer.size(); i++){
      if(comparer.at(x) == comparer.at(i)){
        toAdd.DupSelect(x,i);
      }
    }
  }
  }


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
