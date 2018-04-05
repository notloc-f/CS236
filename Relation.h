#ifndef RELATION_H_
#define RELATION_H_
#include<map>
class Relation{
public:
Relation();
Relation(string namer, vector<string> list);
Relation(string namer,Schemes schemely, set<Tuples>tupling);
void Initial(string namely, vector<string> lister);
void AddTuple(Tuples adder);
void SpecSelect(int pos, string value);
void DupSelect(int first, int second);
void Project(set<int> lister);
void Rename(vector<string> lister);
string Fixer(string toFix);
string Printer(vector<int> IDspots);
string PrintAll();
string Extra();
Relation Projecting(vector<int> IDspots);
int tupleSize();
Schemes getScheme();
set<Tuples> getTuples();
void Rename();
string getTupleString(Tuples temp);
void Join(Relation adder);
map<unsigned int,unsigned int> SchemeChange(Relation temp);
private:
  string name;
  Schemes Schemer;
  set<Tuples> Tupler;

};
string Relation::getTupleString(Tuples temp){
  ostringstream out;
  out << "(";
  for(unsigned int x=0; x < temp.size();x++){
    out << temp.at(x) << ",";
  }
  out << ")";
  return out.str();
}
void Relation::Join(Relation toAdd){
map<unsigned int, unsigned int> temp_Scheme =SchemeChange(toAdd);
set<Tuples> toAdd_Tuples = toAdd.getTuples();
 for (map<unsigned int,unsigned int>::iterator it=temp_Scheme.begin(); it!=temp_Scheme.end(); ++it){ // GOES THROUGH ALL SPOTS WITH THE SAME VARIABLES
   for(set<Tuples>::iterator it_Tupler= Tupler.begin(); it_Tupler!=Tupler.end(); ++it_Tupler){
     for(set<Tuples>::iterator it_toAdd= toAdd_Tuples.begin(); it_toAdd!=toAdd_Tuples.end(); ++it_toAdd){
       if((*it_Tupler).at(it->second) == (*it_toAdd).at(it->first)){
        cout << "Adding" << getTupleString((*it_toAdd)) << endl;
       }
     } //GOES THROUGH ALL TUPLES IN toADD
   } //GOES THROUGH ALL TUPLES IN EXISTING SET
 }

 }
Relation::Relation(string namer,Schemes schemely, set<Tuples>tupling){
  name = namer;
  Schemer = schemely;
  Tupler = tupling;
}

map<unsigned int, unsigned int> Relation::SchemeChange(Relation toAdd){
map<unsigned int, unsigned int> temp_Scheme;
bool found=false;
Schemes temp = toAdd.getScheme();
unsigned int size_Schemer = (unsigned int)Schemer.size();
for(unsigned int x=0; x < temp.size(); x++){
  for(unsigned int i=0; i <size_Schemer; i++){
    if(Schemer.at(i)==temp.at(x)){
      found =true;
      temp_Scheme.insert(pair<unsigned int,unsigned int>(x,i));
      cout << "Found at Schemer "<<i << " and temp "<<x << endl;
    }
  }
  if(found){
    found = false;
  }
  else{
    Schemer.push_back(temp.at(x));
  }
}
return temp_Scheme;
}


set<Tuples> Relation::getTuples(){
  return Tupler;
}
Schemes Relation::getScheme(){
  return Schemer;
}
Relation::Relation(){

}
int Relation::tupleSize(){
  return Tupler.size();
}
string Relation::Printer(vector<int> IDspots){
  ostringstream blah;
  blah << Extra();

  blah << endl;
   for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
     for(unsigned int x=0; x <IDspots.size();x++){
       if(x==0){
         blah << "  ";
       }
       blah <<Schemer.at((IDspots.at(x)));
       blah   << "=" <<(*it).at(IDspots.at(x));

       if((Tupler.size()==1) && (IDspots.size()== x+1)){
        blah << endl;
         return blah.str();
       }
       if(x != (IDspots.size()-1)){
         blah <<", ";
       }
     }
     if(IDspots.size() != 0){
     blah << endl;
   }
   }
   string tempor = blah.str();
   tempor = Fixer(tempor);
   return tempor;
}
string Relation::Fixer(string toFix){
string toReturn = toFix;
if(toReturn.at(toReturn.size()-2) == '\n'){
  toReturn.resize(toReturn.size()-1);
}
  return toReturn;
}
string Relation:: Extra(){
  ostringstream blah;
  blah <<name << "(";
  for(unsigned int x=0; x<Schemer.size(); x++){
    if((x +1) ==Schemer.size()){
      blah << Schemer.at(x) << ")? ";
      if(Tupler.size()== 0){
        blah <<"No" << endl;
        return blah.str();
      }
      else{
        blah <<"Yes(" <<Tupler.size()<<")";
      }
    }
    else{
    blah << Schemer.at(x) << ",";
  }
  }
  string temp = blah.str();
  return temp;
}
Relation::Relation(string namely, vector<string> lister){
  name = namely;
  for(unsigned int i=0; i < lister.size(); i++){
    Schemer.push_back(lister.at(i));
  }
}
void Relation::Initial(string namely, vector<string> lister){
  name = namely;
  for(unsigned int i=0; i < lister.size(); i++){
    Schemer.push_back(lister.at(i));
  }
}
  void Relation:: AddTuple(Tuples tumple){
    for(unsigned int x=0; x <tumple.size(); x++){
    }

    Tupler.insert(tumple);
  }
  // void Relation::SpecSelect(int pos, string value){
  //   Tuples temp;
  //   set<Tuples> tempSet;
  //   for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
  //     if(((*it).at(pos)!=value) && ((*it).at(pos)[0]=='\'')){                             //NOTE YOU WILL NEED TO MODIFY THIS TO ALLOW FOR VARIABLES
  //       Tupler.erase(it);
  //     }
  //     else {
  //       cout << endl;
  //     }
  //   }
  // }
  void Relation::SpecSelect(int pos, string value){
    set<Tuples> tempSet;
    for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
      if(((*it).at(pos)==value) && ((*it).at(pos)[0]=='\'')){                             //NOTE YOU WILL NEED TO MODIFY THIS TO ALLOW FOR VARIABLES
        tempSet.insert(*it);
      }
      else {
      }
    }
    Tupler = tempSet;
  }
//   void Relation::SpecSelect(int pos, string value){
//     Tuples temp;
//     set<Tuples> tempSet;
//     for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
//       if((*it).at(pos)== value){
//         cout << "Adding" << endl;
//         tempSet.insert((*it));
//     }
//     Tupler=tempSet;
//   }
// }
  void Relation::DupSelect(int first, int second){
    //    cout << "Prior dup select size: " << Tupler.size() << endl;
      for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
    //    cout << (*it).at(first) << " and " << (*it).at(second) << endl;
        if((*it).at(first) != (*it).at(second)){
      //    cout << "erased"<<endl;
          Tupler.erase(it);
        }
      }
        //  cout << "After spec select size: " << Tupler.size() << endl;
  }
  void Relation::Rename(vector<string> lister) {
    Schemes temp;
    for(unsigned int x =0; x <lister.size(); x++){
      temp.push_back(lister.at(x));
    }
    Schemer = temp;
  }
  void Relation::Project(set<int> lister){
    set<Tuples> tempSet;
    Tuples tempTuple;
  unsigned int toIterate= lister.size() +1;
    for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
      for(unsigned int x=0; x < toIterate; x++){
        if(lister.find(x)!=lister.end()){
        //  cout << Schemer.at(x) << "=" << (*it).at(x);
          tempTuple.push_back((*it).at(x));
        }
      }
      if(Tupler.size() >1){
      }
      tempSet.insert(tempTuple);
      tempTuple.clear();
    }
    Tupler= tempSet;
  }
  string Relation::PrintAll(){
 ostringstream blah;
 blah <<name << "(";
 for(unsigned int x=0; x<Schemer.size(); x++){
   if((x +1) ==Schemer.size()){
     blah << Schemer.at(x) << ")? ";
     if(Tupler.size()== 0){
       blah <<"No" << endl;
       return blah.str();
     }
     else{
       blah <<"Yes(" <<Tupler.size() <<")" << endl;
     }
   }
   else{
   blah << Schemer.at(x) << ",";
 }
 }
 for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
   for(unsigned int x =0; x < Tupler.size(); x++){
     for(unsigned int i=0; i <(*it).size(); i++){

     }
   }
 }
 return blah.str();
}
  void Relation::Rename(){}



  Relation Relation::Projecting(vector<int> IDspots){
    Relation projected;
    Schemes tempScheme;
    set<Tuples> tempTupleSet;
    Tuples tempTuple;
    string tempName;
    ostringstream blah;
    blah << Extra();

    blah << endl;
     for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
       tempTuple.clear();
       for(unsigned int x=0; x <IDspots.size();x++){
         if(x==0){
           blah << "  ";
         }
         blah <<Schemer.at((IDspots.at(x)));
         blah   << "=" <<(*it).at(IDspots.at(x));
         tempTuple.push_back((*it).at(IDspots.at(x)));

         if((Tupler.size()==1) && (IDspots.size()== x+1)){
          blah << endl;
           ///////////////////////////////////////////////////////
         }
         if(x != (IDspots.size()-1)){
           blah <<", ";
         }
       }
       tempTupleSet.insert(tempTuple);
       if(IDspots.size() != 0){
       blah << endl;
     }

     }
     string tempor = blah.str();
     tempor = Fixer(tempor);
     return projected;
  }

#endif
