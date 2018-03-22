/*
 *
 *
 *  Created on: Jan 19, 2018
 *      Author: coltonf
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Token.h"
#include "datalog.h"

using namespace std;
char charz;
char process='n';
int lineNum=1;
vector<Token> Tokens;
int beginLine;
bool beginString=true;
string babyString="";
bool prevSymbol=false;
string Identity;
int Apost=0;
bool col=false;
string comment="";
//bool hasher=false;
int finalLine=0;
bool IDbegin=true;
int extraLine=0;
bool hasher=false;
bool newLine=true;
void CommentType();
void SingleComment();
void BlockComment();
void Identifier();
void StringCreate();
void ColDash();
void Scanner(){
	Token temp;
	string non;
	TOLKTYP typer;
	if(isalpha(charz)){
		process = 'i';
		Identifier();

		return;
	}
	if(isdigit(charz)){
		typer = UNDEFINED;
		non.push_back(charz);
		temp.CreateToken(typer,lineNum,non);
		Tokens.push_back(temp);
		non="";
		return;
	}
	switch(charz){
				case ',':
					typer = COMMA;
					temp.CreateToken(typer,lineNum,",");
					Tokens.push_back(temp);
					break;
				case '.':
					typer = PERIOD;
					temp.CreateToken(typer,lineNum,".");
					Tokens.push_back(temp);
					break;
				case '?':
					typer = Q_MARK;
					temp.CreateToken(typer,lineNum,"?");
					Tokens.push_back(temp);
					break;
				case '(':
					typer = LEFT_PAREN;
					temp.CreateToken(typer,lineNum,"(");
					Tokens.push_back(temp);
					break;
				case ')':
					typer = RIGHT_PAREN;
					temp.CreateToken(typer,lineNum,")");
					Tokens.push_back(temp);
					break;
				case ':':
					process = 'd';
					ColDash();

					break;
				case '*':
					typer = MULTIPLY;
					temp.CreateToken(typer,lineNum,"*");
					Tokens.push_back(temp);
					break;
				case '+':
					typer = ADD;
					temp.CreateToken(typer,lineNum,"+");
					Tokens.push_back(temp);
					break;
				case '\'':
					//cout << "Starting string creation" << endl;
					process = 's';
					StringCreate();
					break;
				case '#':
					process='c';
					CommentType();
					break;
				default:
					if((charz!=' ')&&(charz!= '\n')){
					process = 'n';
					typer = UNDEFINED;
					non.push_back(charz);
					temp.CreateToken(typer,lineNum,non);
					Tokens.push_back(temp);
					non="";
					break;
					}
					break;
				}
}
bool StringHelper(){
	// if(newLine && (charz!='\'')&&(!prevSymbol)){
	// 	cout << "helped here" << endl;
	// 		babyString.push_back('\n');
	// 	}

	if(beginString){
			beginLine = lineNum;
			beginString = false;
			babyString ="'";
			return true;
		}
	else {
		return false;
	}
}
void DestroySpace(){
	if(prevSymbol&&newLine){
		babyString.pop_back();
	}
}
void StringCreate(){
	Token creater;
	TOLKTYP typer= STRING;
	/*if(newLine && (charz!='\'')&&(!prevSymbol)){
		babyString.push_back('\n');
	}
	if(beginString){
		beginLine = lineNum;
		beginString = false;
		babyString ="'";
		return;
	}*/
	if(StringHelper()){
		return;
	}
	if(charz!= '\''){
		DestroySpace();
		if(prevSymbol){
			string temp = babyString;
		//	temp.append(" line #");
			//temp.push_back(beginLine);
		babyString.push_back('\'');
			creater.CreateToken(typer,beginLine,babyString);
			Tokens.push_back(creater);
			process = 'n';
			babyString = "";
			beginString = true;
			prevSymbol = false;
			Scanner();
			return;
		}
		else{
			babyString.push_back(charz);
		}

	}
	else{
		if(prevSymbol){
			if(newLine){
				DestroySpace();
				string temp = babyString;
							temp.append(" line #");
							temp.push_back(beginLine);
							babyString.push_back('\'');

							creater.CreateToken(typer,beginLine,babyString);
							Tokens.push_back(creater);
							process = 'n';
							babyString = "";
							beginString = true;
							prevSymbol = false;
							Scanner();
							return;
			}
			prevSymbol = false;
			babyString.append("''");
		}
		else{
			prevSymbol = true;
		}
	return;
	}
}
void ColDash(){
	Token temp;
	TOLKTYP typer;
	if(newLine){
		//cout << "New line in colon!!" << endl;
		if(col){
			//cout << "Making a colon" << endl;
			typer = COLON;
			temp.CreateToken(typer,lineNum-1,":");
			Tokens.push_back(temp);
			col = false;
			process ='n';
			Scanner();
			return;


		}
		else{
			col = true;
			return;
		}
	}
	if(col){
		if(charz == '-'){
			typer = COLON_DASH;
			temp.CreateToken(typer,lineNum,":-");
			Tokens.push_back(temp);
			process='n';
			col = false;
			return;

		}
		else if(charz==':'){
			typer = COLON;
			temp.CreateToken(typer,lineNum,":");
			Tokens.push_back(temp);
		//	Tokens.push_back(temp);
			return;


		}
		else{
			typer = COLON;
			temp.CreateToken(typer,lineNum,":");
			Tokens.push_back(temp);
			process = 'n';
			col = false;
			Scanner();
			return;
		}
		process ='n';
	}
	else{
		col = true;
		process = 'd';
		beginLine = lineNum;
		return;
	}
	col = false;
}
bool KeyCheck(){
	Token temp;
	TOLKTYP typer;

	if(Identity == "Queries"){
		typer = QUERIES;
		temp.CreateToken(typer,beginLine,Identity);
		Tokens.push_back(temp);
		Identity ="";
		IDbegin = true;
		return true;
	}
	if(Identity=="Rules"){
		typer = RULES;
		temp.CreateToken(typer,beginLine,Identity);
		Tokens.push_back(temp);
		Identity ="";
		IDbegin = true;
		return true;
	}
	if(Identity=="Facts"){
		typer = FACTS;
		//cout << "Making facts" << endl;
		temp.CreateToken(typer,beginLine,Identity);
		Tokens.push_back(temp);
		Identity ="";
		IDbegin = true;
		return true;
	}
	if(Identity=="Schemes"){
		typer = SCHEMES;
		temp.CreateToken(typer,beginLine,Identity);
		Tokens.push_back(temp);
		Identity ="";
		IDbegin = true;
		return true;
	}
	return false;
}
void IDhelper(){
	if(IDbegin){
			beginLine = lineNum;
			IDbegin = false;
		}
}
// void KeyProbs(){
// 	if(Tokens){
// 	if((Tokens.at(Tokens.size()-2).Typers()=="Schemes")
// 		||(Tokens.at(Tokens.size()-2).Typers()=="Queries")
// 		||(Tokens.at(Tokens.size()-2).Typers()=="Facts")
// 		||(Tokens.at(Tokens.size()-2).Typers()=="Rules")){
// 		Tokens.at(Tokens.size()-1).Fine();
// 	}
// 	}
// }
void Identifier(){
	//IDhelper();
	if(newLine){
		if(KeyCheck()){
			Identity="";
	//		cout << "CURRENT LINE::" <<lineNum << " BEGIN LINE " << beginLine << endl;
		//	IDhelper();
		}
		else if(Identity!=""){
		//	KeyProbs();
			TOLKTYP typer = ID;
			Token temp;
			temp.CreateToken(typer,beginLine,Identity);//USED TO BE lineNum -1
			Tokens.push_back(temp);
	//		cout << "\" " << Identity << "\" Got created Here 1" << endl;

			Identity="";
			IDbegin=true;

		}

	}
	IDhelper();
	if((isalpha(charz)|| isdigit(charz))){
		Identity.push_back(charz);
		process = 'i';
		return;
	}
	else{
		if(KeyCheck()){
			Identity ="";
			process = 'n';
			Scanner();
			return;
		}
		else{
			TOLKTYP typer = ID;
			Token temp;
			temp.CreateToken(typer,beginLine,Identity);
			Tokens.push_back(temp);
			//cout << "\" " << Identity << "\" Got created Here 2" << endl;
			Identity="";
			process= 'n';
			IDbegin = true;
			Scanner();
			return;

		}
	}
}
void CommentType(){
	if((charz=='#')&&!hasher){
		beginLine =lineNum;
		comment="#";
		process='c';
	        hasher = true;
	}
	else if(charz=='|'){
		beginLine = lineNum;
		comment="#|";
		process='b';
	}
	else{
		process ='l';
		SingleComment();
                hasher=false;
	}
}
void SingleComment(){
	TOLKTYP typer = COMMENT;
	Token temp;
	if(newLine){
		temp.CreateToken(typer,beginLine,comment);
		Tokens.push_back(temp);
		comment="#";
		process= 'n';
		Scanner();
	}
	else{
		comment.push_back(charz);
	}
}
void BlockComment(){
	TOLKTYP typer = COMMENT;
	Token temp;
	if(newLine){
		comment.push_back('\n');
	}
	if(hasher){
		if(charz=='#'){
			comment.push_back('|');
			comment.push_back('#');
			temp.CreateToken(typer,beginLine,comment);
			Tokens.push_back(temp);
			//comment="#|";
			hasher=false;
			process='n';
		}
		else{
	//		comment.push_back('#');
			comment.push_back(charz);
			hasher=false;
		}
	}
	else{
		if(charz=='|'){
			hasher=true;
		}
		else{
			comment.push_back(charz);
		}
	}
}
void Cleaner(){
	for(unsigned int i=0; i <Tokens.size();i++){
		if(Tokens.at(i).Clean()){
			Tokens.erase(Tokens.begin() + i);
		}
	}
}
void WriteFile(vector<Token>Tokens){
	ofstream outputFile;
	outputFile.open("outfile1.txt");
	for(unsigned int i=0; i <Tokens.size();i++){
		if(Tokens.at(i).Clean()){
			Tokens.erase(Tokens.begin() + i);
		}
	}
	for(unsigned int i=0; i <Tokens.size();i++){
		outputFile << Tokens.at(i).PrintToken() << endl;
//		cout << Tokens.at(i).PrintToken() << endl;
		}
	outputFile <<"Total Tokens = " << Tokens.size() << endl;
	//cout <<"Total Tokens = " << Tokens.size() << endl;
	outputFile.close();
}
void EndCheck(){
	Token temp;
       unsigned int mather;
	TOLKTYP typer = UNDEFINED;
	switch(process){
	case 'n':
		break;
	case 's':
		if(prevSymbol){
			/*mather = lineNum - beginLine;
			for(int i=0; mather > i; i++){
				babyString.push_back('\n');
			}*/

			typer = STRING;
			// if(Apost-(lineNum-1)==0){
			// 	babyString.push_back('\n');
			// }
				//babyString.push_back('\n');
			babyString.push_back('\'');
			temp.CreateToken(typer,beginLine,babyString);
			Tokens.push_back(temp);
		//	StringCreate();
			return;
		}
		else if(newLine){
			mather = lineNum - beginLine;
						for(unsigned int i=1; mather > i; i++){
							babyString.push_back('\n');
						}
						babyString.push_back('\n');
						temp.CreateToken(typer,beginLine,babyString);
								Tokens.push_back(temp);
			return;
		}
		/*if((beginLine -lineNum)==0){
			babyString.push_back('\n');
		}*/
		babyString.push_back('\n');
		temp.CreateToken(typer,beginLine,babyString);
		Tokens.push_back(temp);
		break;
	case 'i':
		typer = ID;
		if(KeyCheck()){
			;
		}
		else{
		temp.CreateToken(typer,beginLine,Identity);
		Tokens.push_back(temp);
		}
		break;
	case 'd':
		typer = COLON;
		temp.CreateToken(typer,beginLine,":");
		Tokens.push_back(temp);
		break;
	case 'c':
		temp.CreateToken(typer,beginLine,"#");
		Tokens.push_back(temp);
		break;
	case 'l':
	typer = COMMENT;
		temp.CreateToken(typer,beginLine,comment);
		Tokens.push_back(temp);
		break;
	case 'b':
		temp.CreateToken(typer,beginLine,comment);
		Tokens.push_back(temp);
		break;
	default:
		Tokens.push_back(temp);
		break;
	}
}
void Parser(){
	vector<Token> TokInverted;
	while(!Tokens.empty()){
		if((Tokens.back().Type()==COMMENT) ||(Tokens.back().Type()==UNDEFINED)){
			Tokens.pop_back();
		}
		else{
		TokInverted.push_back(Tokens.back());
		Tokens.pop_back();
	}
	}

	// for(unsigned int x=0; x < TokInverted.size(); x++){
	// 	if(TokInverted.at(x).Type()==UNDEFINED){
	// 		cout << "erasing" << TokInverted.at(x).PrintToken() << endl;
	// 		TokInverted.erase(TokInverted.begin(),TokInverted.begin() +x);
	// 	}
	// }
	// cout << "TOkINVERTED SIZE " << TokInverted.size();
	// for(unsigned int x=0; x < TokInverted.size(); x++){
	// 	cout << TokInverted.at(x).PrintToken() << endl;
	// }
	datalog sorter(TokInverted);

	try{
	sorter.Begin();
	}
	catch(Token Prob){
		ofstream outter;
	  outter.open("outfile2.txt");
		cout << "Failure!" <<endl;
		cout<<"  "<< Prob.PrintToken() << endl;
		outter << "Failure!"<<endl;
		outter <<"  "<< Prob.PrintToken();
		outter.close();
	}

}
int main(int argc, char *argv[]){
Token creater;
ifstream inFile;
istringstream lineStream;
string currLine;
string tester;
string something = "Nothing";

inFile.open(argv[1]);
while(getline(inFile,currLine)){
	lineStream.str(currLine);
	newLine = true;
	while(lineStream >>noskipws >>charz){
		if(charz=='\''){
			Apost=lineNum;
		}
		if(process=='n'&&(isalpha(charz))){
			process ='i';
			Identifier();
		}
		else{
		switch(process){
			case 'n':
				Scanner();
				break;
			case 's':
			if(newLine){
				babyString.push_back('\n');
			}
				StringCreate();
				break;
			case 'i':
				Identifier();
				break;
			case 'd':
				ColDash();
				break;
			case 'c':
				CommentType();
				break;
			case 'l':
				SingleComment();
				break;
			case 'b':
				BlockComment();
				break;
			default:
				break;

			}
		}
		newLine = false;
	}
	finalLine = lineNum;
	lineStream.clear();
	lineNum++;
}//S
EndCheck();
TOLKTYP typer = END;
Token temp;
temp.CreateToken(typer,lineNum,"");
Tokens.push_back(temp);
WriteFile(Tokens);
Cleaner();
Parser();

// for(int i=0; i < TokInverted.size(); i++){
// 	cout << TokInverted.at(i).Typerss(TokInverted.at(i).Type()) << endl;
// }

	return 0;
}
