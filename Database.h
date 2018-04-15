#ifndef DATABASE_H_
#define DATABASE_H_
#include "datalog.h"
#include "Scheme.h"
#include "Tuples.h"
#include "Relation.h"
#include <map>
#include <set>
//#include "Scheme.h"
class Database {
public:
void Start();
vector<int> Projecthelp(vector<string> toProject, Schemes all);
void AddRelation(string namer, vector<string> lister);
void AddFact(string namer,vector<string> help);
Relation EvalQuery(string namer, vector<string> helper);
Relation RuleEvalQuery(string namer, vector<string> helper);
Relation Projecter(Relation changeable);
bool Union(Relation toAdd);
void PrintTuple(Tuples printer, Schemes schemely);
bool RuleEval(string head_name, vector<string> head_list,vector<string> names,vector<vector<string>> lists);
void test(string name, vector<string> lister,vector<string> names,vector<vector<string>> listers);
private:

map<string,Relation> relations;
vector<Relation> tempor;
};
void Database::PrintTuple(Tuples printer, Schemes schemely){
  cout << "  ";
for(unsigned int x = 0; x < printer.size(); x++){
  cout << schemely.at(x) << "=" <<printer.at(x);
  if(x < printer.size()-1){
    cout <<", ";
  }
}
cout << endl;
}
bool Database::Union(Relation toAdd){
set<Tuples> tupSet = toAdd.getTuples();
//toAdd.PrintRule();
string namer = toAdd.getName();
Schemes schemely = relations[namer].getScheme();
int preSize=relations[namer].tupleSize();
//cout << "Pre-Union for: " << namer << " " << preSize<< endl;
  for(set<Tuples>::iterator it=tupSet.begin(); it !=tupSet.end(); ++it){
    int temp = relations[namer].tupleSize();
    relations[namer].AddTuple(*it);
    int temp2 = relations[namer].tupleSize();
    if(temp!=temp2){
      PrintTuple(*it,schemely);
    }

  }
//cout << "After Union " << relations[namer].tupleSize() << endl;
  if(preSize == relations[namer].tupleSize()){
    //cout << "False" << endl;
    return false;
  }
  else{
    //cout << "True" << endl;
    return true;
  }
}
Relation Database::Projecter(Relation toChange){
  Relation projected;

return projected;
}
vector<int> Database::Projecthelp(vector<string> toProject, Schemes all){
  vector<int> idSpots;
for(unsigned int x = 0; x < toProject.size(); x++){
  for(unsigned int i=0; i < all.size(); i++){
    if(toProject.at(x)==all.at(i)){
  //    cout << "Found spot" << endl;
      idSpots.push_back(i);
    }
  }
}
return idSpots;
}
bool Database::RuleEval(string head_name, vector<string> head_list,vector<string> names,vector<vector<string>> lists){
//  cout << "NEW rule" << endl;
Relation first = RuleEvalQuery(names[0],lists[0]);
for(unsigned int x=1; x < lists.size(); x++){
  //cout << "JOINING!" << names.at(x) << endl;
  Relation second;
  second = RuleEvalQuery(names[x],lists[x]);
  first =first.Join(second);
}
Relation addling = first.Projecting(Projecthelp(head_list,first.getScheme()),head_name,head_list );
return Union(addling);
//cout << first.PrintAll() << endl;


//cout <<first.Extrar(head_list,head_name);
//set<Tuples> tempTupler = first.getTuples();
//cout <<first.Printer(Projecthelp(head_list,first.getScheme()));
//Relation toReplace =first.Projecting(Projecthelp(head_list, first.getScheme()));
//first.Renamer(head_list,head_name);
// first.Renamer(head_list,head_name);
// Schemes temper = first.getScheme
// cout << first.Printer(Projecthelp(head_list, first.getScheme()));
// first.

// Make first name and list a relation, evaluate it as a query, then use a for() loop to
// join all other lists to that relation by calling "EvalQuery" and then
// joining the resultant returned relation.
// Lastly, take the resultant full relation and project it to a new relation
// of head_name and projecting columns in the order given in the head_list..
// Finally, once that is working, add in a handshake to tell datalog if  more
// facts were added at any point, if so then you will need to reevaluate all of
// the rules again and count how many times you do so.


}
void Database::test(string head_name, vector<string> head_list,vector<string> names,vector<vector<string>> lists){
Relation Rule;

for(unsigned int x=0; x < lists.size();x++){

}

}
void Database::Start(){

  for(unsigned int x =0; x <tempor.size(); x++){
    cout << tempor.at(x).PrintAll() << endl;
  }
}
Relation Database:: RuleEvalQuery(string namer, vector<string> comparer){
  vector<int> IDspots;
  set<string> IDs;
  set<int> IDindex;
  Relation toAdd = relations[namer];
  for(unsigned int x =0; x < comparer.size(); x++){
    if(comparer.at(x)[0]=='\''){
    toAdd.SpecSelect(x,comparer.at(x));
  }
  else{
    IDindex.insert(x);
    if(IDs.find(comparer.at(x))== IDs.end()) {
      IDspots.push_back(x);
      IDs.insert(comparer.at(x));
    }

    for(unsigned int i = x +1; i < comparer.size(); i++){
      if((comparer.at(x) == comparer.at(i))){
        toAdd.DupSelect(x,i);
      }
      else{
      }
    }
  }
}
toAdd.Rename(comparer);
tempor.push_back(toAdd);
//cout << toAdd.Printer(IDspots);
return toAdd;
}
Relation Database:: EvalQuery(string namer, vector<string> comparer){
  vector<int> IDspots;
  set<string> IDs;
  set<int> IDindex;
  Relation toAdd = relations[namer];
  for(unsigned int x =0; x < comparer.size(); x++){
    if(comparer.at(x)[0]=='\''){
    toAdd.SpecSelect(x,comparer.at(x));
  }
  else{
    IDindex.insert(x);
    if(IDs.find(comparer.at(x))== IDs.end()) {
      IDspots.push_back(x);
      IDs.insert(comparer.at(x));
    }

    for(unsigned int i = x +1; i < comparer.size(); i++){
      if((comparer.at(x) == comparer.at(i))){
        toAdd.DupSelect(x,i);
      }
      else{
      }
    }
  }
}
toAdd.Rename(comparer);
tempor.push_back(toAdd);
cout << toAdd.Printer(IDspots);
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
