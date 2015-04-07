#ifndef Variable_H
#define Variable_H
#include <vector>
#include <string>
#include "Operation.h"
using namespace std;

class Variable{
private:
	string name;
	int width;
	string dataType;
	Operation *input;
	vector<Operation *> outputList;
	string verilogExpression;
public:
	explicit Variable();
	explicit Variable(string name, string dataType, int width);
	void setName(string name);
	string getName();
	void setDataType(string dataType);
	string getDataType();
	void setWidth(int width);
	int getWidth();
	void setInput(Operation *input);
	Operation *getInput();
	void setIntoOutputList(Operation *output);
	Operation *getFromOutputList(int index);
	int outputListSize();
	void generateVerilogExpression();
	string getVerilogExpression();
	~Variable();
};
#endif