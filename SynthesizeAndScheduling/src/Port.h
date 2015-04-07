#ifndef Port_H
#define Port_H
#include <vector>
#include <string>
#include "Constants.h"
using namespace std;

class Port{
private:
	string name;
	int width;
	string portType;
	string dataType;
	string verilogExpression;
public:
	explicit Port();
	explicit Port(string name, int width, string portType, string dataType);
	void setName(string name);
	string getName();
	void setWidth(int width);
	int getWidth();
	void setPortType(string portType);
	string getPortType();
	void setDataType(string dataType);
	string getDataType();
	void generateVerilogExpression();
	string getVerilogExpression();
	~Port();
};
#endif