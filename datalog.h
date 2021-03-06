#ifndef DATALOG_H_
#define DATALOG_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include "Token.h"
#include "RuleClass.h"
#include "Database.h"
#include "Graph.h"
#include "Node.h"
//#include "ParameterClass.h"
#include "PredicateClass.h"
using namespace std;

class datalog{
public:
  datalog();
  datalog(vector<Token> intial);
  void Fix();
  string ToString();
  void Querator();
  void Factor();
  void Transfer();
  void Ruler();
  void RuleFactor();
  void Begin();
  void Match(TOLKTYP typy);
  string test(unsigned int i);
  void schemeList();
  void factList();
  void ruleList();
  void queryList();

  void scheme();
  void fact();
  void rule();
  void query();

  void headPredicate(TOLKTYP typly);
  void predicate(TOLKTYP necessary);

  void predicateList(TOLKTYP AlsoNecessary);
  void parameterList();
  void stringList();
  void idList();

  void parameter();

  void expression();
  void operators();
  void End();
  void MakeDomain();
  void MakeDependency();
  void MakeReverse();
  void Finish();
  void Ruler(set<int> places);
private:
  vector<Token> tokStack;
  string TOLKSTRING [18]={"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON","COLON_DASH","MULTIPLY","ADD","SCHEMES","FACTS",
	"RULES","QUERIES","ID","STRING","COMMENT","UNDEFINED","EOF"};
  PredicateClass tempPred;
  ParameterClass tempParam;
  string expressor;
  vector<PredicateClass> Schemess;
  vector<PredicateClass> Factss;
  vector<PredicateClass> Queriess;
  vector<RuleClass> Ruless;
  set <string> Domainss;
  Database nextStep;
  Graph dependency;
  Graph reverseDepend;
  map<int,Node> finalMap;
  int count=1;
  vector<set<int>> order;
  int counting=0;
  bool used = false;

};

datalog::datalog(){
}

datalog::datalog(vector<Token> init){
tokStack=init;

}
/*
COMMA-0
PERIOD-1
Q_Mark-2
LEFT_PAREN-3
RIGHT_PAREN-4
COLON-5
COLON_DASH-6
MULTIPLY-7
ADD-8
Schemes-9
Facts-10
RULES-11
QUERIES-12
ID-13
STRING-14
COMMENT-15
UNDEFINED-16
EOF-17
*/
void datalog::schemeList(){
 if(tokStack.back().Type()==ID){
   scheme(); schemeList();
 }
}
void datalog::factList(){
if(tokStack.back().Type()==ID){
  fact();factList();
}

}
void datalog::ruleList(){
  if(tokStack.back().Type()==ID){
  rule();ruleList();
}
}
void datalog::queryList(){
  if(tokStack.back().Type()==ID){
  query();queryList();
}

}

void datalog::scheme(){
  headPredicate(SCHEMES);
}
void datalog::fact(){
  if(!tokStack.empty()){
    tempPred.ModID(tokStack.back().Value());
  }
  Match(ID);Match(LEFT_PAREN);
tempParam.ChangeParam(tokStack.back().Value());
  Match(STRING);
  tempPred.AddParam(tempParam);
  stringList();
  Factss.push_back(tempPred);
  tempPred.Clear();
  tempParam.Clear();
  Match(RIGHT_PAREN);Match(PERIOD);
}
void datalog::rule(){
  headPredicate(RULES); Match(COLON_DASH);
  predicate(RULES);
expressor="";
  predicateList(RULES); Match(PERIOD);
}
void datalog::query(){
  predicate(QUERIES);Match(Q_MARK);
}

void datalog::headPredicate(TOLKTYP typly){//Could jump out of range here
if(!tokStack.empty()){
tempPred.ModID(tokStack.back().Value());
}
  Match(ID);
  Match(LEFT_PAREN);
  tempParam.ChangeParam(tokStack.back().Value());
  Match(ID);
  tempPred.AddParam(tempParam);
  idList();Match(RIGHT_PAREN);
  if(typly==SCHEMES){
    Schemess.push_back(tempPred);
  }
  else if(typly==FACTS){
    Factss.push_back(tempPred);
  }
  else if(typly == RULES){
    RuleClass temp(tempPred);
    Ruless.push_back(temp);
  }
  tempParam.Clear();
  tempPred.Clear();
}
void datalog::predicate(TOLKTYP typly){
  expressor="";
  string Idents = tokStack.back().Value();
  tempPred.ModID(Idents);
  Match(ID);
  Match(LEFT_PAREN);
  parameter();
  tempPred.AddParam(tempParam);
  parameterList();
  if(typly==RULES){
    Ruless.back().AddPred(tempPred);
  }
  else if(typly==QUERIES){
    Queriess.push_back(tempPred);
  }
  Match(RIGHT_PAREN);
  tempParam.Clear();
  tempPred.Clear();
  expressor="";
}

void datalog::predicateList(TOLKTYP typly){
  expressor="";
  if(tokStack.back().Type()==COMMA){
  Match(COMMA); predicate(typly);

   predicateList(typly);
}
}
void datalog::parameterList(){
  if(tokStack.back().Type()==COMMA){
  Match(COMMA);parameter();
  tempPred.AddParam(tempParam);
  parameterList();
}

}
void datalog::stringList(){
  if(tokStack.back().Type()==COMMA){
  Match(COMMA);
  tempParam.ChangeParam(tokStack.back().Value());
  Match(STRING);
  tempPred.AddParam(tempParam);
  stringList();
}
}
void datalog::idList(){
  if(tokStack.back().Type()==COMMA){
      Match(COMMA);
    tempParam.ChangeParam(tokStack.back().Value());
    Match(ID);
    tempPred.AddParam(tempParam);

  idList();
}
}

void datalog::parameter(){
  if(tokStack.back().Type()==STRING){
    tempParam=tokStack.back().Value();
    Match(STRING);
  }
  else if(tokStack.back().Type()==ID){
    tempParam=tokStack.back().Value();
    Match(ID);
  }
  else{
    expression();
  //  expressor = '(' + expressor +')';
    tempParam=expressor;
  //  cout << "Expressor is: " << expressor << endl;
    expressor="";
  }
}

void datalog::expression(){
Match(LEFT_PAREN);
//cout << "Expressor is: " << expressor << endl;
parameter();
expressor+= '('+ tempParam.GetString();
operators();
expressor+= tempParam.GetString();
parameter();
expressor+= tempParam.GetString() + ')';
Match(RIGHT_PAREN);
}
void datalog::operators(){
  if(tokStack.back().Type()==ADD){
    tempParam= tokStack.back().Value();
    Match(ADD);
  }
  else if(tokStack.back().Type()==MULTIPLY){
    tempParam= tokStack.back().Value();
    Match(MULTIPLY);
  }
  else{
//    cout << "THROWING HERE2" << endl;
    throw(tokStack.back());
  }
}
void datalog::Match(TOLKTYP typer){
  // if(tokStack.back().Type()== UNDEFINED){
  //   tokStack.pop_back();
  // }
  if(typer == tokStack.back().Type()){
    tokStack.pop_back();
    return;
  }
  else{
  //  cout << "THROWING HERE1" << endl;
    throw(tokStack.back());
  }
}
void datalog::End(){
  if(tokStack.back().Type()!=END){
  //  cout << "Last symbol: " << tokStack.back().PrintToken();
  while((tokStack.size()>2)){
    tokStack.pop_back();
  }
  //cout << "THROWING HERE4" << endl;
  throw(tokStack.back());
}
}
string datalog::ToString(){
  ostringstream output;
  output.clear();
  output<< "Schemes(" << Schemess.size() <<"):"<<endl;
  cout << "Schemes(" << Schemess.size() <<"):"<<endl;
  for(unsigned int i=0; i <Schemess.size();i++){
    output <<"  "<< Schemess.at(i).PrintPredicate() << endl;
    cout <<"  "<< Schemess.at(i).PrintPredicate() << endl;
  }
  output<<"Facts(" << Factss.size() <<"):" << endl;
  cout <<"Facts(" << Factss.size() <<"):" << endl;
  for(unsigned int i=0;i < Factss.size();i++){
    output <<"  "<< Factss.at(i).PrintPredicate()<<"." << endl;
    cout <<"  "<< Factss.at(i).PrintPredicate()<<"." << endl;
  }
  output<< "Rules(" << Ruless.size() <<"):" << endl;
  cout << "Rules(" << Ruless.size() <<"):" << endl;
  for(unsigned int i=0; i <Ruless.size(); i++){
    output <<"  "<< Ruless.at(i).PrintRule() << endl;
    cout <<"  "<< Ruless.at(i).PrintRule() << endl;
  }
  output<< "Queries(" << Queriess.size() <<"):" << endl;
  cout << "Queries(" << Queriess.size() <<"):" << endl;
  for(unsigned int i=0; i <Queriess.size();i++){
    output<<"  "<< Queriess.at(i).PrintPredicate() << "?"<<endl;
    cout <<"  "<< Queriess.at(i).PrintPredicate() << "?"<<endl;
  }
  cout<<"Domain(" <<Domainss.size() <<"):" <<endl;
  output<<"Domain(" <<Domainss.size() <<"):" <<endl;
  for(set<string>::iterator it=Domainss.begin();it!=Domainss.end();++it){
    output << "  "<< *it << endl;
    cout<<"  " << *it << endl;
  }
  return output.str();
}
void datalog::MakeDomain(){

for(unsigned int i=0; i <Factss.size();i++){
vector<ParameterClass> temp = Factss.at(i).GetPred();
  for(unsigned int j=0; j < temp.size();j++){
    Domainss.insert(temp.at(j).GetString());
  }
}
}
void datalog::Fix(){
//  int temp= tokStack.size();
  for(unsigned int x=0; x < tokStack.size(); x++){
    if(tokStack.at(x).Type()==UNDEFINED){
      cout << "erasing" << tokStack.at(x).PrintToken() << endl;
      tokStack.erase(tokStack.begin(),tokStack.begin() +x);
    }
  }
}
void datalog::Begin(){
if(tokStack.back().Type()==SCHEMES){
  Match(SCHEMES);Match(COLON);scheme();schemeList();
  Match(FACTS);Match(COLON);factList();
  Match(RULES);Match(COLON);ruleList();
  Match(QUERIES); Match(COLON);query();queryList();
  End();
//  cout <<"Success!"<< endl; //<< ToString();
  MakeDomain();
  ofstream outter;
  outter.open("outfile2.txt");
  //outter <<"Success!"<< endl << "  "<< ToString() << endl;
  outter.close();
}
else{
//  cout << "THROWING HERE3" << endl;
  throw(tokStack.back());
}
Transfer();
Factor();
MakeDependency();
MakeReverse();
reverseDepend.DepthFirst();
dependency.SSC(reverseDepend.getStack());
order =dependency.getSSC();
//dependency.PrintSSC();
finalMap = dependency.getMap();
Finish();
cout << endl;
//Ruler();
Querator();
//nextStep.Start();

}
void datalog::MakeReverse(){
//  cout << "REVERSE" << endl;
  vector<Node> nodes;
  nodes.resize(Ruless.size());
  map<int,Node> depGraph = dependency.getMap();
  for(map<int,Node>::iterator it =depGraph.begin(); it!=depGraph.end(); it++){
    set<int> temp = it->second.allLinks();
    for(set<int>::iterator setter = temp.begin(); setter!=temp.end(); setter++){
  //  cout << "Adding to R" <<*setter << " link to R" << it->first << endl;
      nodes.at(*setter).addLink(it->first);
      if(*setter == it->first){
        nodes.at(*setter).Selfie();
    //    cout << "Just set self 'true'" << endl;
      }
      //reverseDepend.addNode(it->first,tempNode);
    }
  }
  for(unsigned int x =0; x < nodes.size(); x++){ // CAN BE DELETED FOR BETTER ALGORITHM, ADD TO TOP

    reverseDepend.addNode(x,nodes.at(x));
  }
  // cout << "Reverse Dependency" << endl;
//   reverseDepend.PrintAll();

}
// void datalog::MakeReverse(){
//   vector<Node> nodes;
//   nodes.resize(Ruless.size());
//   cout << "size of nodes is " << nodes.size() << endl;
//   for(unsigned int x=0; Ruless.size(); x++){
//     for(unsigned int i=0; Ruless.returnParams.size(); i++){
//       nodes.at()
//     }
//   }
// }
void datalog::MakeDependency(){
  for(unsigned int x=0; x <Ruless.size(); x++){
  // cout << "Rule" << x << endl;
    Node tempNode;
    for(unsigned int i=0; i < Ruless.at(x).returnParams().size(); i++){
    //  cout << "Param" <<i << endl;
      for(unsigned int y=0;y < Ruless.size(); y++){
      //  cout << "Comparing Rule"<<y << endl;
        if(Ruless.at(y).returnHead().getID() == Ruless.at(x).returnParams().at(i).getID()){
          tempNode.addLink(y);
  //        cout << "Adding to R" << x << " link to R" << y << endl;
          if(y == x){
            tempNode.Selfie();
        //    cout << "Just set self to 'true'" << endl;
          }
        }
  //      dependency.addNode(x,tempNode);
      }
  //    cout << "About to add Node of size " << tempNode.getSize() << endl;
  //    dependency.addNode(x,tempNode);
//    cout << "Size of dependent " <<  dependency.getSize() << endl;
    //ORIGINAL  tempNode.clearAll();
    }
      dependency.addNode(x,tempNode);
  //  tempNode.clearAll();
  }

  // tempNode.clearAll();
  dependency.PrintAll();
}
string datalog::test(unsigned int j){
  return tokStack.at(j).PrintToken();
}
void datalog:: Querator(){
  cout << "Query Evaluation" << endl;
  vector<string> lister;
  string name;
  for(unsigned int x =0; x <Queriess.size(); x++){
    lister = Queriess.at(x).allParams();
    name = Queriess.at(x).getID();
    nextStep.EvalQuery(name,lister);
  }
}
void datalog::Factor(){
  vector<string> lister;
  string name;
  for(unsigned int x =0; x <Factss.size(); x++){
    lister = Factss.at(x).allParams();
    name = Factss.at(x).getID();
    nextStep.AddFact(name,lister);
  }
}

void datalog::Transfer(){
  //Database nextStep;
  for(unsigned i =0; i < Schemess.size(); i++){
    vector<string> lister;
    string name;
    lister = Schemess.at(i).allParams();
    name = Schemess.at(i).getID();
    nextStep.AddRelation(name,lister);

  }
}
void datalog::Ruler(){
  bool restart = false;
  vector<string> headlister;
  string headname;
  vector<vector<string>> lists;
  vector<string> names;
  cout << "Rule Evaluation" << endl;
  for(unsigned int x =0; x <Ruless.size();x++){
    cout << Ruless.at(x).PrintRule() << endl;
    headname =Ruless.at(x).returnHead().getID();
    headlister = Ruless.at(x).returnHead().allParams();
  //  cout <<"NUMBER OF PARAMS " << Ruless.at(x).returnParams().size() << endl;
    for(unsigned int i=0; i <Ruless.at(x).returnParams().size();i++){
      names.push_back(Ruless.at(x).returnParams().at(i).getID());
      lists.push_back(Ruless.at(x).returnParams().at(i).allParams());
    }
    if(nextStep.RuleEval(headname,headlister,names,lists)){
      restart = true;
    }
    lists.clear();
    names.clear();
    if( (x== Ruless.size()-1)&&restart){
      x=-1;
      count++;
      restart = false;
    }
  }
  cout<< endl<< "Schemes populated after " <<count <<" passes through the Rules." << endl << endl;
}
void datalog::Ruler(set<int>places){
  bool restart = false;
  vector<string> headlister;
  string headname;
  vector<vector<string>> lists;
  vector<string> names;
  counting++;
  for(set<int>::iterator it= places.begin(); it!=places.end();it++){

    //if(counting ==1){
    cout << Ruless.at(*it).PrintRule() << endl;
  //}
    headname =Ruless.at(*it).returnHead().getID();
    headlister = Ruless.at(*it).returnHead().allParams();
    for(unsigned int i=0; i <Ruless.at(*it).returnParams().size();i++){
      names.push_back(Ruless.at(*it).returnParams().at(i).getID());
      lists.push_back(Ruless.at(*it).returnParams().at(i).allParams());
    }
    // if(finalMap.at(*it).getSelf()){
    //   cout << "I have myself" << endl;
    // }
    // if(nextStep.RuleEval(headname,headlister,names,lists) &&(places.size()>1)){
    //   cout << "here1" << endl;
    //   restart = true;
    // }
    // else if(finalMap.at(*it).getSelf() && (counting == 1)){
    //   cout << "here2" << endl;
    //   restart = true;
    //   used = true;
    // }
    // else if(finalMap.at(*it).getSelf() && (!used)){
    //   cout << "here3" << endl;
    //   restart = true;
    // }
    bool tool = nextStep.RuleEval(headname,headlister,names,lists);
  if(tool){
    restart = true;
  }
  if(tool && (places.size() ==1 ) && (!(finalMap.at(*it).getSelf())) ){
    restart = false;
  }
    lists.clear();
    names.clear();
    // if((it.next() == places.end())&&restart){
    //
    //   it=places.begin();
    //   count++;
    //   restart = false;
    // }
  }
  if(restart){
    Ruler(places);
  }
  used = false;
}
void datalog::Finish(){
  cout << endl;
  cout << "Rule Evaluation" << endl;
  for(unsigned int x =0; x < order.size(); x++){
  //  cout << "Again" << endl;
  cout << "SCC: ";
unsigned  int format =0;
    for(set<int>::iterator it = order.at(x).begin(); it!= order.at(x).end(); it++){
      cout << "R" << *it;
      if(format != (order.at(x).size() -1)){
        cout << ",";
      }
      format++;
    }
    format =0;
    cout << endl;
    Ruler(order.at(x));
    cout << counting << " passes: ";
    counting = 0;

      for(set<int>::iterator it = order.at(x).begin(); it!= order.at(x).end(); it++){
        cout << "R" << *it;
        if(format != (order.at(x).size() -1)){
          cout << ",";
        }
        format++;
      }
      format = 0;
      cout << endl;
  }
}
#endif /* DATALOG_CPP*/
