#ifndef Parser_H
#define	Parser_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include "Constants.h"
#include "Operation.h"
#include "Variable.h"
#include "Port.h"
using namespace std;

class Parser{
private:
	static void setGrammer(vector<string> &declarations, vector<string> &dataTypesAndWidth, vector<string> &operations);
	static bool isDeclaration(vector<string> declarations, vector<string> tokens);
	static bool isOperation(vector<string> operationTypes, vector<string> tokens);
	static bool isdataTypesAndWidth(vector<string> dataTypesAndWidth, vector<string> tokens);
	static int setDataWidth(string token);
	static string setDataType(string token);
	static void setVariableDependency(Operation *operation, vector<Variable *> &variableList);
	static void generatePort(int width, string portType, string dataType, string &lineBuffer, vector<Port *> &portList);
	static void setToVariableList(string &lineBuffer, vector<Variable *> &variableList);
public:
	static void splitString(string &lineBuffer, vector<string> &tokens);
	static void parsingCFile(string inputCircuitFileName, vector<Port *> &portList, vector<Variable *> &variableList, vector<Operation *> &operationList);
};
#endif