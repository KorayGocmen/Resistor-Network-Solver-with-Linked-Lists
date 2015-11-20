#ifndef RESISTOR_H
#define RESISTOR_H
#include <string>
#include <iostream>
using namespace std;
class Resistor {
    
private:
	double resistance; 
	string name; 
	int endpointNodeIDs[2]; 
	int rIndex;
        Resistor *next;
    
public:
	Resistor();
	Resistor(string name_,double resistance_,int endpoints_[2]);
	~Resistor();
        Resistor *getNext() const;
        void setNext(Resistor *n);
        bool tailInsert(Resistor* &head,Resistor* &ptr);     
	void updateResistor(int rIndex_,string name_,double resistance_,int endpoints_[2]);
	string getName() const; 
	double getResistance() const;
	void setResistance (double resistance_);
	void print ();
	void printSingleRes();
        bool findResistor(string name);
        bool deleteRes(Resistor* &head, string rName);
        int getEndPoint1();
        int getEndPoint2();
    
};

#endif /* RESISTOR_H */
