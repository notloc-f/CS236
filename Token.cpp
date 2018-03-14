/*
 * Token.cpp
 *
 *  Created on: Jan 23, 2018
 *      Author: coltonf
 */

#include "Token.h"

Token::Token() {
	types = UNDEFINED;
	lineNum= -1;
	value="void";

}
void Token::CreateToken(TOLKTYP typer, int lineNums, string values){
	types = typer;
	lineNum=lineNums;
	value=values;
}

string Token::PrintToken(){
	ostringstream output;
	output << "(" <<TOLKSTRING[types] << "," <<"\"" <<value << "\"," << lineNum << ")";
	return output.str();

}
void Token::SingleID(){
	if((types == ID)&&(value.size() == 1)){
		lineNum = lineNum -1;
	}
}
 void Token::Token::Fine(){
	lineNum=lineNum-1;
}
TOLKTYP Token::Type(){
	return types;
}
string Token::Value(){
	return value;
}
string Token::Typerss(TOLKTYP i){
	return TOLKSTRING[i];
}

bool Token::Clean(){
if((types == ID) && (value=="")){
	return true;
}
else{
	return false;
}
}
