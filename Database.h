#ifndef DATABASE_H_
#define DATABASE_H_
#include "datalog.h"
#include "Scheme.h"
#include "Tuples.h"
#include "Relation.h"
class Database {
public:
void practice();
void Start();
void AddRelation(string namer, vector<string> lister);
private:

vector<Relation> temp;
};
void Database::practice(){
  cout << "Made it here" << endl;
  Schemes practiceGuy;
  practiceGuy.push_back("chocoTaco");
  Tuples secondPractice;
  secondPractice.push_back("greenShirtGuy");

  cout << practiceGuy.at(0) << endl << secondPractice[0] << endl;
  cout << "Just for funnsies" << endl;
}
void Database::Start(){
cout << "I am done with Schemes. Schemes size is " << temp.size();
}
void Database::AddRelation(string name, vector<string> list){
Relation tempter;
tempter.Initial(name,list);
temp.push_back(tempter);
}

#endif
