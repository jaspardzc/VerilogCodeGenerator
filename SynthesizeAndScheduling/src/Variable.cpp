#include "Variable.h"

Variable::Variable(){
	name = "";
	//input = nullptr;
	input = NULL;
	verilogExpression = "";
}
//to_string
Variable::Variable(string name, string dataType, int width){
	this->name = name;
	this->dataType = dataType;
	this->width = width;
	//input = nullptr;
	input = NULL;
	verilogExpression = "";
	generateVerilogExpression();
}

void Variable::setName(string name){
	this->name = name;
}

string Variable::getName(){
	return name;
}

void Variable::setDataType(string dataType){
	this->dataType = dataType;
}

string Variable::getDataType(){
	return dataType;
}

void Variable::setWidth(int width){
	this->width = width;
}

int Variable::getWidth(){
	return width;
}

void Variable::setInput(Operation *input){
	this->input = input;
}

Operation *Variable::getInput(){
	return input;
}

void Variable::setIntoOutputList(Operation *output){
	outputList.push_back(output);
}

Operation *Variable::getFromOutputList(int index){
	return outputList.at(index);
}

int Variable::outputListSize(){
	return outputList.size();
}

void Variable::generateVerilogExpression(){
	verilogExpression.append("reg [");
	verilogExpression.append(to_string(static_cast<long long>(width - 1)));
	verilogExpression.append(" : 0]");
	verilogExpression.append(getName());
	verilogExpression.append(";");
}

string Variable::getVerilogExpression(){
	return verilogExpression;
}

Variable::~Variable(){
	//input = nullptr;
	input = NULL;
}