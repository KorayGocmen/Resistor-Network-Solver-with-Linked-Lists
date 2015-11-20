#include "Node.h"
#include "Resistor.h"
#include "Rparser.h"

class Resistor;

Node::Node(){
    next=NULL;
    resList=NULL;
    resNum=0;
    setVolt=false;
    voltage=0;
}
Node::Node(int n){
    id=n;
    next=NULL;
    resList=NULL;
    resNum=0;
    setVolt=false;
}

void Node::addResistor(Resistor *newResistor){
    
    resList->tailInsert(resList ,newResistor);
}

int Node::getResNum(){
    return resNum;
}

void Node::print(){
    
    cout << "Connections at node " <<id << ": " << resNum <<" resistor(s)" << endl;
    
}

void Node::printVoltage(){
    cout << "Connections at node " <<id << ": ";
    cout << fixed << showpoint;
    cout.precision(2);
    cout<<voltage<<" V" << endl;
}

Node::~Node(){
    if(next != NULL){
        
        delete next;
    }
    next=NULL;
    if( resList != NULL){
        
        delete resList;
    }
    resList=NULL;
    
}

void Node::updateResNum(){
    resNum=resNum+1;
}

void Node::zeroResNum(){
    resNum=0;
}

Node *Node::getNext() const{ 
    return next;
}

void Node::setNext(Node* n){
    next = n;
}

int Node::getId() const{
    return id;
}

Resistor* Node::getResList() const{
    return resList;
}

bool Node::sortedInsert(Node* &head, Node* &ptr){
    int tId = ptr->getId();
    Node *cur = head;
    Node *pre = NULL;
    
    if(head==NULL){
        head = ptr;
        return true;
    }
    
    else if(head->getNext()==NULL){
        if(head->getId()>ptr->getId()){
            ptr->setNext(head);
            head=ptr; 
            return true;
        }else{
            head->setNext(ptr);
            return true;
        }
    }
    
    else if((cur->getId()) > tId){
        ptr->setNext(head);
        head=ptr;
    }
    
    else{
        while(cur != NULL && (cur->getId()) < tId){
            pre = cur;
            cur = cur -> getNext();        
        }
        
        pre->setNext(ptr);
        ptr->setNext(cur);
        
        return true;
    }
}
void Node::updateHeadofRes(Resistor* ptr){
    resList = ptr;
}

void Node::setVoltage(double volt){
        voltage = volt;
}

double Node::getVoltage(){
    return voltage;
}

bool Node::deleteAllRes(){
    
    Resistor *temp = resList;
    while(temp!=NULL){
        //cout<<"deleteres "<<endl;
        Resistor *next = temp->getNext();
        delete temp;
        temp = next;
    }
    resList = NULL;
    return true;
    temp=NULL;
}

void Node::deleteRes(string rName){
    
    resList->deleteRes(resList, rName);
    
}

void Node::decrementResNum(){
    resNum=resNum-1;
}
void Node::setVoltageTrueFalse(bool setVolt_){
    setVolt = setVolt_;
}

bool Node::getSetVolt(){
    return setVolt;
}

double Node::reqOfNode(){
    Resistor *temp = resList;
    double rTotal = 0;
    while(temp != NULL){
        rTotal = rTotal + (1/(temp->getResistance()));
        temp = temp->getNext();
    }
    
    return (1/rTotal);
    temp=NULL;
}

double Node::iOfNode(int idOfCaller, Node* nodeList){
    
    Resistor *temp = resList;
    double iTotal = 0;
    
    
    while (temp != NULL){
        int finalNode = 0;
        int firstNode = temp->getEndPoint1();
        int secondNode = temp->getEndPoint2();
        double resNode = temp->getResistance();
        
        if(firstNode != idOfCaller)
            finalNode = firstNode;
        else
            finalNode = secondNode;
        
        Node *temp2 = nodeList;
        bool found =false;
        while(temp2 != NULL && !found){
            
            if(temp2->getId()==finalNode){
                    found=true;
                    double voltNode = temp2->getVoltage();
                    iTotal = iTotal + (voltNode/resNode);             
            }
            temp2 = temp2->getNext();
        }
        temp = temp->getNext();
    }
    return iTotal;
    temp=NULL;
}
