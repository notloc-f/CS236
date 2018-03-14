#ifndef PARAMETERCLASS_H
#define PARAMETERCLASS_H
#include "Token.h"
using namespace std;

class ParameterClass{
public:
  ParameterClass();
  ParameterClass(string valuer);
  string GetString();
  void ChangeParam(string changer);
  void Clear();
private:
  string valuer;
};
void ParameterClass::Clear(){
  valuer="";
}
string ParameterClass::GetString(){
  return valuer;
}
void ParameterClass::ChangeParam(string changer){
  valuer=changer;
}
ParameterClass::ParameterClass(){
valuer="";
}
ParameterClass::ParameterClass(string valuing){
  valuer=valuing;
}


#endif
