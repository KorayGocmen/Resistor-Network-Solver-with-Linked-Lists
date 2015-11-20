#ifndef RPARSER_H
#define    RPARSER_H
#include <iostream>
#include <string>
#include <sstream>
#include "Node.h"
#include "Resistor.h"

using namespace std;

int Rparser();
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
void modify_resistor(string rName, double res);
void resistor_name_exists_error(string rName);
void resarray_full_error();
void node_full_error();
void resistor_name_not_found(string rName);


#endif    /* RPARSER_H */
