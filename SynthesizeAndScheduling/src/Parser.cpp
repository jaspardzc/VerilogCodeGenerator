#include "Parser.h"
//to_string
void Parser::setGrammer(vector<string> &declarations, vector<string> &dataTypesAndWidth, vector<string> &operationTypes){
	declarations.push_back("input");
	declarations.push_back("output");
	declarations.push_back("variable");
	
	dataTypesAndWidth.push_back("Int1");
	dataTypesAndWidth.push_back("Int8");
	dataTypesAndWidth.push_back("Int16");
	dataTypesAndWidth.push_back("Int32");
	dataTypesAndWidth.push_back("Int64");

	dataTypesAndWidth.push_back("UInt1");
	dataTypesAndWidth.push_back("UInt8");
	dataTypesAndWidth.push_back("UInt16");
	dataTypesAndWidth.push_back("UInt32");
	dataTypesAndWidth.push_back("UInt64");
	
	operationTypes.push_back("+");
	operationTypes.push_back("-");
	operationTypes.push_back("*");
	operationTypes.push_back("/");
	operationTypes.push_back("%");
	operationTypes.push_back(">");
	operationTypes.push_back("<");
	operationTypes.push_back("==");
	operationTypes.push_back("?");
	operationTypes.push_back("<<");
	operationTypes.push_back(">>");
}

bool Parser::isDeclaration(vector<string> declarations, vector<string> tokens){
	for (int i = 0; i < tokens.size(); i++){
		for (int j = 0; j < declarations.size(); j++){
			if (tokens.at(i) == declarations.at(j))
				return true;
		}
	}
	//cout << " invalid format of input, output or variable " << endl;
	return false;
	cout << " invalid format of input, output or variable " << endl;
}

bool Parser::isdataTypesAndWidth(vector<string> dataTypesAndWidth, vector<string> tokens){
	for (int i = 0; i < tokens.size(); i++){
		for (int j = 0; j < dataTypesAndWidth.size(); j++){
			if (tokens.at(i) == dataTypesAndWidth.at(j))
				return true;
		}
	}
	//cout << " invalid format of dataType or dataWidth " << endl;
	return false;
	cout << " invalid format of dataType or dataWidth " << endl;
}

bool Parser::isOperation(vector<string> operationTypes, vector<string> tokens){
	for (int i = 0; i < tokens.size(); i++){
		for (int j = 0; j < operationTypes.size(); j++){
			if (tokens.at(i) == operationTypes.at(j))
				return true;
		}
	}
	//cout << " invalid format of operation  " << endl;
	return false;
	cout << " invalid format of operation  " << endl;
}

int Parser::setDataWidth(string token){
	if (token == "Int1" || token == "UInt1")
		return 1;
	if (token == "Int8" || token == "UInt8")
		return 8;
	if (token == "Int16" || token == "UInt16")
		return 16;
	if (token == "Int32" || token == "UInt32")
		return 32;
	if (token == "Int64" || token == "UInt64")
		return 64;
	return 0;
}

string Parser::setDataType(string token){
	if (token == "Int1"
		|| token == "Int8"
		|| token == "Int16"
		|| token == "Int32"
		|| token == "Int64")
		return "Int";

	if (token == "UInt1"
		|| token == "UInt8"
		|| token == "UInt16"
		|| token == "UInt32"
		|| token == "UInt64")
		return "UInt";
	return "";
}

void Parser::parsingCFile(string inputCircuitFileName, vector<Port *> &portList, vector<Variable *> &variableList, vector<Operation *> &operationList){
	fstream inputStream(inputCircuitFileName, ios::in);
	if (!inputStream){
		cout << "Open File " << inputCircuitFileName << " fail." << endl;
		exit(1);
	}

	vector<string> declarations;
	vector<string> dataTypesAndWidth;
	vector<string> operationTypes;
	setGrammer(declarations, dataTypesAndWidth, operationTypes);
	vector<string> tokens;
	//Operation *tempOperation = nullptr;
	Operation *tempOperation = NULL;
	string lineBuffer;
	string dataType = "";
	int width = 0;
	while (!inputStream.eof()){
		getline(inputStream, lineBuffer);
		if (!lineBuffer.empty()){
			splitString(lineBuffer, tokens);
			if (isDeclaration(declarations, tokens)){ // For input, output, variable
				if (tokens.at(0) == "input"){
					if (isdataTypesAndWidth(dataTypesAndWidth, tokens))
					{
						dataType = setDataType(tokens.at(1));
						width = setDataWidth(tokens.at(1));
						generatePort(width, "INPUT_PORT", dataType, lineBuffer, portList);
					}
				}

				if (tokens.at(0) == "output"){
					if (isdataTypesAndWidth(dataTypesAndWidth, tokens))
					{
						dataType = setDataType(tokens.at(1));
						width = setDataWidth(tokens.at(1));
						generatePort(width, "OUTPUT_PORT", dataType, lineBuffer, portList);
					}
				}

				if (tokens.at(0) == "variable"){
					if (isdataTypesAndWidth(dataTypesAndWidth, tokens))
					{
						dataType = setDataType(tokens.at(1));
						width = setDataWidth(tokens.at(1));
						setToVariableList(lineBuffer, variableList);
					}
				}
			}

			if (isOperation(operationTypes, tokens)){ // For different operationTypes
				if (tokens.size() == 5){
					tempOperation = new Operation(tokens.at(3), tokens.at(2), tokens.at(4), "", tokens.at(0), lineBuffer);
					operationList.push_back(tempOperation);
				}

				if (tokens.size() == 7){
					tempOperation = new Operation(tokens.at(3), tokens.at(2), tokens.at(4), tokens.at(6), tokens.at(0), lineBuffer);
					operationList.push_back(tempOperation);
				}

				setVariableDependency(tempOperation, variableList);
			}
			tokens.clear();
		}
		lineBuffer.clear();
	}
	inputStream.close();
}

void Parser::setVariableDependency(Operation *operation, vector<Variable *> &variableList){
	for (int i = 0; i < variableList.size(); i++){
		if (operation->getOutput() == variableList.at(i)->getName()){
			variableList.at(i)->setInput(operation);
		}
	}

	for (int i = 0; i < operation->inputListSize(); i++){
		for (int j = 0; j < variableList.size(); j++){
			if (operation->getFromInputList(i) == variableList.at(j)->getName()){
				variableList.at(j)->setIntoOutputList(operation);
			}
		}
	}
}

void Parser::splitString(string &lineBuffer, vector<string> &tokens){
	//if (lineBuffer.empty())
	//	return;
	int i = 0;
	vector<char> token;
	vector<string> tempTokens;
	while (i != lineBuffer.size()){
		if (lineBuffer[i] == ' '
			|| lineBuffer[i] == '\t'
			|| lineBuffer[i] == ','
			|| lineBuffer[i] == '\\'
			|| lineBuffer[i] == '.'){
			if (!token.empty()){
				tempTokens.push_back(string(token.begin(), token.end()));
			}
			token.clear();
		}
		else{
			if (lineBuffer[i] != ' '
				|| lineBuffer[i] != '\t'
				|| lineBuffer[i] != ','
				|| lineBuffer[i] != '\\'
				|| lineBuffer[i] != '.')
				token.push_back(lineBuffer[i]);
		}
		i++;
	}
	tempTokens.push_back(string(token.begin(), token.end()));

	i = 0;
	while (i != tempTokens.size() && tempTokens.at(i) != "//" && tempTokens.at(i) != ""){
		tokens.push_back(tempTokens.at(i));
		i++;
	}
}

void Parser::generatePort(int width, string portType, string dataType, string &lineBuffer, vector<Port *> &portList){
	vector<char> token;
	vector<string> tokens;
	Port *tempPort;
	splitString(lineBuffer, tokens);
	int i = 2;
	while (i != tokens.size()){
		tempPort = new Port(tokens.at(i), width, portType, dataType);
		portList.push_back(tempPort);
		i++;
	}
}


void Parser::setToVariableList(string &lineBuffer, vector<Variable *> &variableList){
	vector<string> tokens;
	splitString(lineBuffer, tokens);
	string dataType = setDataType(tokens.at(1));
	int width = setDataWidth(tokens.at(1));
	//Variable *tempVariable = nullptr;
	Variable *tempVariable = NULL;
	int i = 2;
	while (i != tokens.size()){
		tempVariable = new Variable(tokens.at(i), dataType, width);
		variableList.push_back(tempVariable);
		i++;
	}
}
