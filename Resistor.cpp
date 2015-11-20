#include "Resistor.h"
#include "Rparser.h"
#include "Node.h"

class Node;

Resistor::Resistor(){
    next=NULL;
}

Resistor::Resistor(string name_, double resistance_, int endpoints_[2]){
        next=NULL;
	name = name_;
	resistance = resistance_;
	endpointNodeIDs[0] = endpoints_[0];
	endpointNodeIDs[1] = endpoints_[1];
}

void Resistor::updateResistor(int rIndex_, string name_, double resistance_, int endpoints_[]){
	rIndex = rIndex_;
	name = name_;
	resistance = resistance_;
	endpointNodeIDs[0] = endpoints_[0];
	endpointNodeIDs[1] = endpoints_[1];   
}
void Resistor::setNext(Resistor* n){
    next = n;
}

string Resistor::getName() const{
	return name;    
}

double Resistor::getResistance() const{
	return resistance;    
}

void Resistor::setResistance(double resistance_){
	resistance=resistance_;
}

void Resistor::print(){
    
    cout<<"  ";
    std::cout.width(20); std::cout << std::left << name <<" ";
    cout << fixed << showpoint;
    cout.precision(2);
    std::cout.width(8); std::cout << std::right << resistance;
    cout << " Ohms ";
    cout << endpointNodeIDs[0] << " -> " <<endpointNodeIDs[1] << endl;  
}

void Resistor::printSingleRes(){
    std::cout.width(20); std::cout << std::left << name <<" ";
    cout << fixed << showpoint;
    cout.precision(2);
    std::cout.width(8); std::cout << std::right << resistance;
    cout << " Ohms ";
    cout << endpointNodeIDs[0] << " -> " <<endpointNodeIDs[1] << endl;  
}

Resistor::~Resistor(){
    if(next != NULL){
        
        delete next;
    }
    next=NULL;    
}

Resistor *Resistor::getNext() const{
    return next;
}

bool Resistor::tailInsert(Resistor* &head, Resistor* &ptr){
    if(head==NULL){
        head = ptr;
    }
        
    else{
        Resistor *tptr = head;
        while(tptr->getNext()!=NULL){
            tptr = tptr->getNext();
        }
        tptr->setNext(ptr);
    }
    return true;
}

bool Resistor::deleteRes(Resistor* &head, string rName){
    
    Resistor *cur = head, *pre=NULL;
    while(cur!=NULL && cur->getName()!=rName){
        pre=cur;
        cur=cur->getNext();
    }
    
    if(cur==NULL) return false;
    if(pre==NULL) head = cur->getNext();
    else
        pre ->setNext(cur->getNext());
    
    cur->next = NULL;
    delete cur;
    return true;
    
}

int Resistor::getEndPoint1(){
    return endpointNodeIDs[0];
}

int Resistor::getEndPoint2(){
    return endpointNodeIDs[1];
}
