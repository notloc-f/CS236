#ifndef DATABASE_H_
#define DATABASE_H_
#include "datalog.h"
#include "Scheme.h"
#include "Tuples.h"
class Database {
public:
void practice();
private:

};
void Database::practice(){
  cout << "Made it here" << endl;
  Schemes practiceGuy;
  practiceGuy.push_back("chocoTaco");
  Tuples secondPractice;
  secondPractice.push_back("greenShirtGuy");

  cout << practiceGuy.at(0) << endl << secondPractice[0] << endl;
}
#endif
