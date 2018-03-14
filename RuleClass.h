#ifndef RULECLASS_H
#define RULECLASS_H
#include "Token.h"
#include "ParameterClass.h"
#include "PredicateClass.h"

class RuleClass{
public:
RuleClass();
RuleClass(PredicateClass initer);
void ModHead(PredicateClass moddy);
void Clear();
void AddPred(PredicateClass modis);
string PrintRule();
private:
  PredicateClass head;
  vector<PredicateClass> params;

};
string RuleClass::PrintRule(){
  ostringstream output;
  output << head.PrintPredicate() <<" :- ";
  for(unsigned int i=0; i < params.size();i++){
    if(i+1 <params.size()){
    output << params.at(i).PrintPredicate() <<",";
  }
  else{
    output << params.at(i).PrintPredicate() <<".";
  }
  }
  return output.str();
}
RuleClass::RuleClass(){

}
RuleClass::RuleClass(PredicateClass initer){
  head=initer;

}
void RuleClass::ModHead(PredicateClass moddy){
head=moddy;
}
void RuleClass::Clear(){
  head.Clear();
  params.clear();
}
void RuleClass::AddPred(PredicateClass modis){
params.push_back(modis);
}
#endif
