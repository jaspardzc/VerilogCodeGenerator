#include "Time.h"

Time::Time(){
	timeNumber = 0;
}
//to_string
void Time::generateVerilogExpression(string spaces){
	string tempVerilogExpression = "";
	for (int i = 0; i < operaionList.size(); i++){
		operaionList.at(i)->generateVerilogExpression();
		tempVerilogExpression.append(spaces);
		tempVerilogExpression.append(operaionList.at(i)->getVerilogExpression());
		verilogExpressionList.push_back(tempVerilogExpression);
		tempVerilogExpression.clear();
	}
}

int Time::verilogExpressionListSize(){
	return verilogExpressionList.size();
}

string Time::getVerilogExpression(int index){
	return verilogExpressionList.at(index);
}

Time::~Time(){
	for (int i = 0; i < operaionList.size(); i++)
		operaionList.at(i) = NULL;
		//operaionList.at(i) = nullptr;
}