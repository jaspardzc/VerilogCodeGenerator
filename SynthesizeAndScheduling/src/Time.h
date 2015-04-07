#ifndef Time_H
#define Time_H
#include <vector>
#include "Operation.h"
using namespace std;

class Time{
private:
	vector<string> verilogExpressionList;
public:
	explicit Time();
	int timeNumber;
	vector<Operation *> operaionList;
	void generateVerilogExpression(string spaces);
	int verilogExpressionListSize();
	string getVerilogExpression(int index);
	~Time();
};
#endif