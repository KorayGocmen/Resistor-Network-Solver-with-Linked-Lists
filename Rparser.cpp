#include "Rparser.h"
#include "Resistor.h"
#include "Node.h"

#include <assert.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;


int word_per_line (const string&);
void error_maxval_negative();
void too_many_arguments();
void too_few_arguments();
void resistor_name_all_error();
void invalid_argument();
void negative_resistance();
void node_out_of_bound(int nodeNumber, int maxNodeNumber);
void same_node_numbers(int nodeNumber);
void insert_resistor(string rName, double res, int node1, int node2);
void modify_resistor(string rName, double resbefore, double resafter);
void resistor_name_exists_error(string rName);
void resarray_full_error();
void node_full_error();
void resistor_name_not_found(string rName);
bool findResName(Node* head, string rName);


#define INSERT_VARIABLE_COUNT 5
#define MODIFY_VARIABLE_COUNT 3
#define PRINTR_VARIABLE_COUNT 2
#define PRINTNODE_VARIABLE_COUNT 2
#define DELETER_VARIABLE_COUNT 2
#define SETV_VARIABLE_COUNT 3
#define UNSETV_VARIABLE_COUNT 2
#define SOLVE_VARIABLE_COUNT 1
#define MIN_ITERATION_CHANGE 0.0001


int Rparser (void){
    
    string line, command;
    int wCount;
    
    
    Node *nodeList=NULL;
    
    
    
    //start
    cout << "> ";    
    getline(cin, line);
    
    //Infinite loop
    while(!cin.eof()){
        
        //Get the line put it in
        
        //how many words are there
        wCount = word_per_line(line);
        
        stringstream lineStream (line);
        
        lineStream >> command;
        
        
    	
        
        if(command == "insertR"){
            if(wCount > INSERT_VARIABLE_COUNT)
                too_many_arguments();
            else if(wCount < INSERT_VARIABLE_COUNT)
                too_few_arguments();
            else{
                
            	string rName;
            	double res;
            	int node1, node2;
                
            	//get resistor name
            	lineStream >> rName;

            	//check if we have the same name
            	bool sameResName = false;
            	if(nodeList==NULL)
                    sameResName=false;
                else{
                    sameResName=findResName(nodeList, rName);
                }
                
            	if(rName == "all"){
                    //error reserved word
                    resistor_name_all_error();
            	}else if(sameResName){
                    //rName already exists
                    resistor_name_exists_error(rName);
                    
            	}else{
                    //rName is okay          		 
                    //get resistance value
                    lineStream >> res;
                    
                    if(!(lineStream.peek() == ' ')){
                    	//error: invalid type
                    	invalid_argument();
                        
                        
                    }else if(res < 0){
                    	//error: res is negative
                        negative_resistance();
                    }else{
                        //res value is okay
                        lineStream >> node1;
                        
                        if(!(lineStream.peek() == ' ')){
                            //error: invalid type
                            invalid_argument();                  		 
                        }else{
                            
                            lineStream >> node2;
                            
                            //checking if we have the nodes                            
                            bool haveNode1=false;
                            bool haveNode2=false;
                            
                            if(nodeList==NULL){
                                haveNode1=false;
                                haveNode2=false; 
                            }else{
                                
                                Node *temp = nodeList;
                                while(temp != NULL){

                                    if(temp->getId() == node1)
                                        haveNode1 = true;
                                    if(temp->getId() == node2)
                                        haveNode2 = true;
                                    temp = temp->getNext();
                                }
                            }                         
                            
                            
                            if(!haveNode1){
                            	//creating node1
                                Node *newNode = new Node(node1);
                                nodeList->sortedInsert(nodeList, newNode);
                                haveNode1=true;
                            }
                            if(!haveNode2){
                                //creating node2
                                Node *newNode = new Node(node2);
                                nodeList->sortedInsert(nodeList, newNode);
                                haveNode2 = true;
                            }
                            if(node1 == node2){
                                //error: node numbers are same
                                same_node_numbers(node1);                                
                            }else if(haveNode1 && haveNode2){
                                
                                //nodes are created                                
                                int endpoints[2];
                                endpoints[0] = node1;
                                endpoints[1] = node2;
                                
                                Resistor *newResistor1 = new Resistor(rName, res, endpoints);
                                Resistor *newResistor2 = new Resistor(rName, res, endpoints);
                                //add resistor to node1
                                bool found=false;
                                Node *temp = nodeList;
                                while (temp != NULL && !found ){
                                    if(temp->getId()== node1){
                                        found = true;
                                        temp->updateResNum();                                                                              
                                        temp->addResistor(newResistor1);                                        
                                    }else{
                                        temp = temp->getNext();
                                    }
                                }
                                
                                //add resistor to node2
                                found = false;
                                temp=nodeList;
                                while (temp != NULL && !found ){
                                    if(temp->getId()==node2){
                                        found = true;
                                        temp->updateResNum();                                       
                                        temp->addResistor(newResistor2);                                        
                                    }else{
                                        temp = temp->getNext();
                                    }
                                }
                                insert_resistor(rName, res, node1, node2);
                            }
                        }
                    }          		 
                }
            } 		 
        }//END OF INSERTR          	 
        
        
        else if ( command == "modifyR"){
            
            if(wCount > MODIFY_VARIABLE_COUNT)
                too_many_arguments();
            else if(wCount < MODIFY_VARIABLE_COUNT)
                too_few_arguments();
            else{
                
                string rName;
                //get resistor name
                lineStream >> rName;
                double res;
                if(rName == "all"){
                    //error reserved word
                    resistor_name_all_error();
                }else{
                    //rName is okay          		 
                    //get resistance value
                    lineStream >> res;
                    
                    if(res < 0){
                        //error: res is negative
                        negative_resistance();
                    }else{
                        //res value is okay
                        ///MODIFY FUNC IS OKAY
                        
                    	double resbefore;
                    	//look for resistor in the array
                    	int found = 0;

                        Node *temp = nodeList;
                        while(temp != NULL && found<2){
                            
                            Resistor *currentResList = temp->getResList();
                            while (currentResList != NULL && found<2){
                                if(currentResList->getName() == rName){
                                    found++;
                                    resbefore = currentResList->getResistance();
                                    currentResList->setResistance(res);
                                }
                                currentResList = currentResList->getNext();
                                
                            }
                            temp = temp->getNext();
                        }                  
                        
                    	//print out messages
                    	if(found)
                            modify_resistor(rName,resbefore,res);
                        
                    	else
                            resistor_name_not_found(rName);
                        
                    }  		 
                }
            }  	 
        }//END OF MODIFYR
       
        
        else if( command == "printR" ){
            
            if(wCount > PRINTR_VARIABLE_COUNT)
                too_many_arguments();
            else if(wCount < PRINTR_VARIABLE_COUNT)
                too_few_arguments();
            else{
                
                string rName;
                //get resistor name
                lineStream >> rName;
                
                //look for the correct resistor
                bool found = false;
                Node *temp = nodeList;
                while(temp != NULL && !found){
                    Resistor *currentRes = temp->getResList();
                    while(currentRes!=NULL && !found){
                        if(currentRes->getName()==rName){
                            found=true;
                            cout<<"Print:"<<endl;
                            currentRes->printSingleRes();
                        }else{
                            currentRes=currentRes->getNext();
                        }
                    }
                    temp=temp->getNext();
                }
                
                
                if(!found){                   	 
                    resistor_name_not_found(rName);
                }
                
                
            }
        }//END OF PRINTR
        
        
        else if( command == "printNode" ){
            
            if(wCount > PRINTNODE_VARIABLE_COUNT)
                too_many_arguments();
            else if(wCount < PRINTNODE_VARIABLE_COUNT)
                too_few_arguments();
            else{
                
                string nodeName;
                //get resistor name
                lineStream >> nodeName;
                
            	//turn the name into integer
            	int nodeNameInt;
            	stringstream ss(nodeName);
            	ss >> nodeNameInt;
                
                if(nodeName == "all"){
                    //All nodes
                    cout << "Print:" << endl;

                    bool atLeastOneRes = false;
                    Node *temp = nodeList;
                    while (temp != NULL) {
                        if (temp->getResNum() != 0) {
                            temp->print();
                            Resistor *currentResistor = temp->getResList();
                            while (currentResistor != NULL) {
                                atLeastOneRes = true;
                                currentResistor->print();
                                currentResistor = currentResistor->getNext();
                            }
                        } 
                        else if (temp->getResNum() == 0) {
                            if (temp->getVoltage() != 0 && !atLeastOneRes) {
                                temp->printVoltage();
                            }
                        }
                        temp = temp->getNext();
                    }
                    
                    
                    
                    
                }else{
                    //nodeName is okay
                    //PRINTNODE OKAY

                    cout << "Print:" << endl;
                    
                    Node *temp = nodeList;
                    bool found=false;
                    while(temp != NULL && !found){
                        if(temp->getId()==nodeNameInt){
                            temp->print();
                            Resistor *currentResistor=temp->getResList();
                            while(currentResistor!=NULL){
                                currentResistor->print();
                                currentResistor=currentResistor->getNext();
                            }
                        }
                        temp=temp->getNext();
                    }
                    
                }  		 
            }
        }//END OF PRINTNODE
        
        
        else if( command == "deleteR" ){
            
            if(wCount > DELETER_VARIABLE_COUNT)
                too_many_arguments();
            else if(wCount < DELETER_VARIABLE_COUNT)
                too_few_arguments();
            else{
                
                string rName;
                //get resistor name
                lineStream >> rName;
                if(rName == "all"){
                    //All resistors
                    
                    Node *temp = nodeList;
                    while(temp!=NULL){
                        
                        temp->deleteAllRes();
                        temp->zeroResNum();
                        if(!temp->getSetVolt())
                            temp->setVoltage(0);
                        temp = temp->getNext();
                        
                    }

                    cout << "Deleted: all resistors" <<endl;
                    
                } else {

                    int numFound = 0;

                    Node *temp = nodeList;
                    while (temp != NULL && numFound < 2) {

                        Resistor *currentResList = temp->getResList();
                        while (currentResList != NULL && numFound < 2) {

                            if (currentResList->getName() == rName) {
                                numFound++;
                                temp->deleteRes(rName);
                                temp->decrementResNum();
                            }
                            currentResList = currentResList->getNext(); 
                        }
                        temp = temp->getNext();
                    }

                    assert(numFound == 0 || numFound == 2);

                    if (numFound == 2) {
                        //deleted
                        cout << "Deleted: resistor " << rName << endl;
                    } else {
                        resistor_name_not_found(rName);
                    }
                } 		 
            }
        }//END OF DELETER
        
        
        else if(command == "setV" ){
            if(wCount > SETV_VARIABLE_COUNT)
                too_many_arguments();
            else if(wCount < SETV_VARIABLE_COUNT)
                too_few_arguments();
            else{
                string nodeName;
                //get resistor name
                lineStream >> nodeName;
                
            	//turn the name into integer
            	int nodeNameInt;
            	stringstream ss(nodeName);
            	ss >> nodeNameInt;
                
                double voltage;
                lineStream >> voltage;
                
                bool found = false;
                Node *temp = nodeList;
                while(temp != NULL && !found){
                    if(temp->getId() == nodeNameInt){
                        found = true;
                        temp->setVoltageTrueFalse(true);
                        temp->setVoltage(voltage);
                    }
                    temp=temp->getNext();
                }
                if(!found){
                    Node *newNode = new Node(nodeNameInt);
                    newNode->setVoltageTrueFalse(true);
                    newNode->setVoltage(voltage);
                    nodeList->sortedInsert(nodeList, newNode);
                    found=true;
                }
                
                cout<<"Set: node "<<nodeNameInt<<" to ";
                cout << fixed << showpoint;
                cout.precision(2);
                cout<<voltage<<" Volts"<<endl;
            }
        }
        
        else if(command == "unsetV"){
            if(wCount > UNSETV_VARIABLE_COUNT)
                too_many_arguments();
            else if(wCount < UNSETV_VARIABLE_COUNT)
                too_few_arguments();
            else{
                string nodeName;
                //get resistor name
                lineStream >> nodeName;
                
            	//turn the name into integer
            	int nodeNameInt;
            	stringstream ss(nodeName);
            	ss >> nodeNameInt;
                
                bool found = false;
                Node *temp = nodeList;
                while(temp != NULL && !found){
                    if(temp->getId() == nodeNameInt){
                        found = true;
                        temp->setVoltageTrueFalse(false);
                        temp->setVoltage(0);
                    }
                    temp=temp->getNext();
                }
                if(found){
                    cout << "Unset: the solver will determine the voltage of node " << nodeNameInt<<endl;
                }
                else{
                    cout<<"Error: node "<<nodeNameInt<<" not found"<<endl;
                }
            }
        }
        
        else if (command == "solve"){
            
            if(wCount > SOLVE_VARIABLE_COUNT)
                too_many_arguments();
            else if(wCount < SOLVE_VARIABLE_COUNT)
                too_few_arguments();
            else{
                
                Node *temp1 = nodeList;
                while(temp1 != NULL){
                    if(!(temp1->getSetVolt())) temp1->setVoltage(0);
                    temp1=temp1->getNext();
                }
   
                double newDiff;
                double diff;

                do {
                    diff = 0;
                    Node *temp4 = nodeList;
                    while (temp4 != NULL) {

                        double reqATNode;
                        double iTotalAtNode;
                        double vNode;
                        double voltBefore;
                        
                        if (!temp4->getSetVolt()) {
                            voltBefore = temp4->getVoltage();
                            
                            reqATNode = temp4->reqOfNode();
                            iTotalAtNode = temp4->iOfNode(temp4->getId(), nodeList);
                            vNode = reqATNode*iTotalAtNode;

                            temp4->setVoltage(vNode);
                            newDiff = abs(vNode - voltBefore);

                            if (newDiff > diff)
                                diff = newDiff;
                        }
                        temp4 = temp4->getNext();
                    }
                        
                }while(diff > MIN_ITERATION_CHANGE);

                //Printing the solve function
                bool oneNode = false;
                Node *temp5 = nodeList;
                while(temp5 != NULL && !oneNode){
                    if(temp5->getSetVolt()) oneNode=true;
                    temp5=temp5->getNext();
                }
                
                if(oneNode){
                
                cout<<"Solve:"<<endl;
                Node *temp=nodeList;
                
                while(temp != NULL){
                    if(temp->getVoltage()!=0){
                        cout<<"  Node "<<temp->getId()<<": ";
                        cout << fixed << showpoint;
                        cout.precision(2);
                        cout<<temp->getVoltage()<<" V"<<endl;
                    }
                    temp=temp->getNext();
                }
                }else{
                    cout<<"Error: no nodes have their voltage set"<<endl;
                }
                
            }
        }
        
        else{
            cout << "Error: "
                    << "invalid command" << endl;
        }
        cout << "> ";
        getline(cin, line);
    }
    
    delete nodeList;

    return 0;
}

//how many words are there in the line
int word_per_line(const string &line){
    
    int count=0;
    stringstream str(line);
    string useless;
    
    while(str >> useless){
        count++;
    }
    return count;
    
}

//maxVal is negative
void error_maxval_negative(){
    cout <<"Error: maxVal arguments must be greater than 0" << endl;
}

//error func. too many arguments
void too_many_arguments(){
    //error too many arguments
    cout << "Error: "
            << "too many arguments" << endl;    
}

//error func. too few arguments
void too_few_arguments(){
    //error too few arguments
    cout << "Error: "
            << "too few arguments" << endl;    
}

//error resistor name is all
void resistor_name_all_error(){
    //error reserved keyword
    cout << "Error: "
            << "resistor name cannot be the keyword \"all\""  << endl;
}


void invalid_argument(){
    //error invalid argument
    cout << "Error: "
            << "invalid argument" << endl;
}

void negative_resistance(){
    //error negative resistance
    cout << "Error: "
            << "negative resistance" << endl;  
}

void node_out_of_bound(int nodeNumber, int maxNodeNumber){
    //error: node number is out of bound
    cout << "Error: "
            << "node " << nodeNumber << " is out of permitted range 0-"
            << maxNodeNumber << endl;
}


void same_node_numbers(int nodeNumber){
    //error: same node numbers
    cout << "Error: "
            << "both terminals of resistor connect to node " << nodeNumber <<endl;
}

void insert_resistor(string rName, double res, int node1, int node2){
    cout << "Inserted: resistor "
            << rName << " ";
    cout << fixed << showpoint;
    cout.precision(2);
    cout << res << " Ohms "
            << node1 << " -> " << node2 << endl;
}

void modify_resistor(string rName, double resbefore, double resafter){
    cout << "Modified: resistor "
            << rName << " from ";
    cout << fixed << showpoint;
    cout.precision(2);
    cout << resbefore << " Ohms to ";
    cout << fixed << showpoint;
    cout.precision(2);
    cout<<resafter<<" Ohms" <<endl;
}

void resistor_name_exists_error(string rName){
    cout << "Error: resistor " << rName
            << " already exists" << endl;    
}

void resarray_full_error(){
    cout << "Error: resistor array is full" << endl;
}

void node_full_error(){
    cout << "Error: node is full" << endl;
}

void resistor_name_not_found(string rName){
    cout << "Error: resistor " << rName
            <<" not found" <<endl;
}


bool findResName(Node* head, string rName){
    Node *temp = head;
    while(temp != NULL){
        Resistor *currentResList = temp->getResList();
        while (currentResList != NULL){
            if(currentResList->getName() == rName)
                return true;
            else{
                currentResList = currentResList->getNext();
            }
        }
        temp = temp->getNext();
    }                  
    return false;
}

bool findResInsideResList(Node *currentNode, string rName){
    
    Resistor *currentRes = currentNode->getResList();
    while(currentRes!=NULL){
        if(currentRes->getName()==rName)
            return true;
        else
            currentRes=currentRes->getNext();
    }
    return false;
}
