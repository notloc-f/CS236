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
  string getID();
  void AddParam(ParameterClass temp);
  vector<string> allParams();
  PredicateClass(string IDing,vector<ParameterClass> listPar);
private:
  string IDer;
  vector<ParameterClass> list;
};
string PredicateClass::getID(){
  return IDer;
}
vector<string> PredicateClass::allParams(){
  vector<string> paramer;
  for(unsigned i =0; i <list.size(); i++){
    cout << "adding " << list.at(i).GetString();
    paramer.push_back(list.at(i).GetString());
  }
  return paramer;
}
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
