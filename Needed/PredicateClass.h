#ifndef PREDICATECLASS_H
#define PREDICATECLASS_H
#include "Token.h"
#include "ParameterClass.h"
class PredicateClass{
public:
  PredicateClass();
  void ModID(string IDers);
  void Clear();
  vector<ParameterClass> GetPred();
  string PrintPredicate();
  void AddParam(ParameterClass temp);
  PredicateClass(string IDing,vector<ParameterClass> listPar);
private:
  string IDer;
  vector<ParameterClass> list;
};
vector<ParameterClass> PredicateClass::GetPred(){

  return list;
}
string PredicateClass::PrintPredicate(){
  ostringstream output;
  output << IDer << "(";
  for(unsigned int i=0;i <list.size();i++){
    if(i+1 < list.size()){
    output << list.at(i).GetString() << ",";
  }
  else{
    output << list.at(i).GetString();
  }
  }

  output << ")";
  return output.str();
}
void PredicateClass::AddParam(ParameterClass temp){
  list.push_back(temp);
}
void PredicateClass::Clear(){
  IDer="";
  list.clear();
}
void PredicateClass::ModID(string IDers){
  IDer=IDers;
}
PredicateClass::PredicateClass(){
  IDer = "";
}
PredicateClass::PredicateClass(string IDing, vector<ParameterClass> listPar){
  IDer = IDing;
  list =listPar;
}
#endif
