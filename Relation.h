#ifndef RELATION_H_
#define RELATION_H_

class Relation{
public:
Relation();
Relation(string namer, vector<string> list);
void Initial(string namely, vector<string> lister);
void AddTuple(Tuples adder);
void SpecSelect(int pos, string value);
void DupSelect(int first, int second);
void Project(set<int> lister);
void Rename(vector<string> lister);
string Printer(vector<int> IDspots);
string PrintAll();
string Extra();
int tupleSize();
void Rename();
private:
  string name;
  Schemes Schemer;
  set<Tuples> Tupler;

};
Relation::Relation(){

}
int Relation::tupleSize(){
  return Tupler.size();
}
string Relation::Printer(vector<int> IDspots){
  ostringstream blah;

  // for(unsigned int x=0; x<Schemer.size(); x++){
  //   if((x +1) ==Schemer.size()){
  //     blah << Schemer.at(x) << ")? ";
  //     if(Tupler.size()== 0){
  //       blah <<"No" << endl;
  //       return blah.str();
  //     }
  //     else{
  //       blah <<"Yes(" <<Tupler.size()<<")";
  //     }
  //   }
  //   else{
  //   blah << Schemer.at(x) << ",";
  // }
  // }

  blah << Extra();

  blah << endl;
   for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
     for(unsigned int x=0; x <IDspots.size();x++){
       if(x==0){
         blah << "  ";
       }
//Last spot
    //   cout <<"temper" << temper <<"temper"<< endl;

       blah <<Schemer.at((IDspots.at(x)));
       // cout << "Made it here" << endl;
       // cout << "IDspot is " << IDspots.at(x) << endl;
       // cout << "Number of indices in *it " << (*it).size() << endl;
       // return blah.str();
    blah   << "=" <<(*it).at(IDspots.at(x));

       if(Tupler.size()==1){
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

  //    if(Tupler.size()!=1){
  //  blah <<endl;
  // }
   }
   string tempor = blah.str();
   if(tempor.at(tempor.size()-2) == '\n'){
     tempor.resize(tempor.size()-1);
   }
   return tempor;
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
  void Relation::SpecSelect(int pos, string value){
    Tuples temp;
    set<Tuples> tempSet;
    for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
      cout <<value << " and " <<(*it).at(pos);
      if(((*it).at(pos)!= value) && ((*it).at(pos)[0]=='\'')){                             //NOTE YOU WILL NEED TO MODIFY THIS TO ALLOW FOR VARIABLES
        Tupler.erase(it);
        cout << " Erased" <<endl;
      }
      else {
      }
      cout << endl;
    }
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
      for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
        cout << (*it).at(first) << " and " << (*it).at(second) << endl;
        if((*it).at(first) != (*it).at(second)){
          cout << "erased"<<endl;
          Tupler.erase(it);
        }
      }
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

    // ostringstream blah;
    // blah <<name << "(";
    // for(unsigned int x=0; x<Schemer.size(); x++){
    //   if((x +1) ==Schemer.size()){
    //     blah << Schemer.at(x) << ")? ";
    //     if(Tupler.size()== 0){
    //       blah <<"No" << endl;
    //     }
    //     else{
    //       blah <<"Yes(" <<Tupler.size() <<")" << endl;
    //     }
    //   }
    //   else{
    //   blah << Schemer.at(x) << ",";
    // }
    // }
    // cout << blah.str();

  unsigned int toIterate= lister.size() +1;
    for(set<Tuples>::iterator it= Tupler.begin(); it!=Tupler.end(); ++it){
      for(unsigned int x=0; x < toIterate; x++){
        if(lister.find(x)!=lister.end()){
        //  cout << Schemer.at(x) << "=" << (*it).at(x);
          tempTuple.push_back((*it).at(x));
        }
      }
      if(Tupler.size() >1){
  //    cout << endl;
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

#endif
