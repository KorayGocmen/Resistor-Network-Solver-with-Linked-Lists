#ifndef NODE_H
#define NODE_H
#include "Resistor.h"
#define MAX_RESISTORS_PER_NODE 5

class Node {
private:
	int resNum;
        int id;
        double voltage;
        Node *next;
        Resistor *resList;
        bool setVolt;

public:
    
        Node(int n);
	Node();
	~Node();
        Node *getNext() const;
        Resistor* getResList() const;
        void updateHeadofRes(Resistor *ptr);
        bool sortedInsert(Node* &head,Node* &ptr);
        void setNext(Node *n);
        int getId() const;
	void addResistor(Resistor *newResistor);
	void print ();
	int getResNum();
	void updateResNum();
	void zeroResNum();
        void printVoltage();
        void setVoltage(double volt);
        double getVoltage();
        bool deleteAllRes();
        void deleteRes(string rName);
        void decrementResNum();
        void setVoltageTrueFalse(bool setVolt_);
        bool getSetVolt();
        double reqOfNode();
        double iOfNode(int idOfCaller, Node *nodeList);
};


#endif /* NODE_H */
