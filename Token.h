/*
 * Token.h
 *
 *  Created on: Jan 23, 2018
 *      Author: coltonf
 */

#ifndef TOKEN_H_
#define TOKEN_H_
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

enum TOLKTYP{
	COMMA,PERIOD,Q_MARK,LEFT_PAREN,RIGHT_PAREN,COLON,COLON_DASH,MULTIPLY,ADD,SCHEMES,FACTS,RULES,QUERIES,ID,STRING,COMMENT,UNDEFINED,END
	};
class Token {

public:
	Token();
	void CreateToken(TOLKTYP types, int lineNum,string value);
	string PrintToken();
	bool Clean();
	void SingleID();
	void Fine();
	TOLKTYP Type();
	string Value();
	string Typerss(TOLKTYP i);
private:
	TOLKTYP types=UNDEFINED;
	int lineNum=-1;
	string value="void";
	string TOLKSTRING [18]={"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON","COLON_DASH","MULTIPLY","ADD","SCHEMES","FACTS",
	"RULES","QUERIES","ID","STRING","COMMENT","UNDEFINED","EOF"};
};

#endif /* TOKEN_H_ */
