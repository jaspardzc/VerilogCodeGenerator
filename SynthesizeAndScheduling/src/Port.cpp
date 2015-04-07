#include "Port.h"
//to_string
Port::Port(){
	this->name = "";
	this->width = 0;
	this->portType = "";
	this->dataType = "";
	verilogExpression = "";
}

Port::Port(string name, int width, string portType, string dataType){
	this->name = name;
	this->width = width;
	this->portType = portType;
	this->dataType = dataType;
	verilogExpression = "";
	generateVerilogExpression();
}

void Port::setName(string name){
	this->name = name;
}

string Port::getName(){
	return name;
}

void Port::setWidth(int width){
	this->width = width;
}

int Port::getWidth(){
	return width;
}

void Port::setPortType(string portType){
	this->portType = portType;
}

string Port::getPortType(){
	return portType;
}

void Port::setDataType(string dataType){
	this->dataType = dataType;
}

string Port::getDataType(){
	return dataType;
}

void Port::generateVerilogExpression(){
	if (portType == "INPUT_PORT"){
		verilogExpression.append("input [");
		verilogExpression.append(to_string(static_cast<long long>(width - 1)));
		verilogExpression.append(" : 0]");
		verilogExpression.append(getName());
		verilogExpression.append(";");
	}

	if (portType == "OUTPUT_PORT"){
		verilogExpression.append("output reg[");
		verilogExpression.append(to_string(static_cast<long long>(width - 1)));
		verilogExpression.append(" : 0]");
		verilogExpression.append(getName());
		verilogExpression.append(";");
	}
}

string Port::getVerilogExpression(){
	return verilogExpression;
}

Port::~Port(){

}