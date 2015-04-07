#ifndef CircuitTools_H
#define CircuitTools_H
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include "Port.h"
#include "Variable.h"
#include "Time.h"
#include "Parser.h"
#include "AssistList.h"
using namespace std;

class CircuitTools{
public:
	static void generateVerilogCode(int latency, vector<Port *> &portList, vector<Variable *> &variableList, vector<Time *> &timeList, string outputVerilogFileName);
};
#endif