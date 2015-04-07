#include "Operation.h"
//to_string
Operation::Operation(){
	operationType = "";
	inputPortNumber = 0;
	inputOne = "";
	inputTwo = "";
	inputThree = "";
	output = "";
	color = -1;
	scheduledFlag = 0;
	delayCycle = 0;
	totalDelayCycle = 0;
	startTime = 0;
	endTime = 0;
	currentNextOperationIndex = 0;
	currentPrevOperationIndex = 0;
	verilogExpression = "";
}

Operation::Operation(string operationType){
	this->operationType = operationType;
	inputPortNumber = 0;
	inputOne = "";
	inputTwo = "";
	inputThree = "";
	output = "";
	color = -1;
	scheduledFlag = 0;
	setDelayCycle(Constants::setDelayCycles(operationType));
	totalDelayCycle = 0;
	startTime = 0;
	endTime = 0;
	currentNextOperationIndex = 0;
	currentPrevOperationIndex = 0;
	verilogExpression = "";
}

Operation::Operation(string operationType, string inputOne, string inputTwo, string inputThree, string output, string expression){
	this->operationType = operationType;
	this->inputOne = inputOne;
	this->inputTwo = inputTwo;
	this->inputThree = inputThree;
	this->output = output;
	this->expression = expression;
	color = -1;
	scheduledFlag = 0;
	setDelayCycle(Constants::setDelayCycles(operationType));
	totalDelayCycle = 0;
	startTime = 0;
	endTime = 0;
	if (inputOne != ""){
		inputList.push_back(inputOne);
		inputPortNumber++;
	}
		
	if (inputTwo != ""){
		inputList.push_back(inputTwo);
		inputPortNumber++;
	}
		
	if (inputThree != ""){
		inputList.push_back(inputThree);
		inputPortNumber++;
	}
		
	currentNextOperationIndex = 0;
	currentPrevOperationIndex = 0;
	verilogExpression = "";
}

void Operation::setOperationType(string operationType){
	this->operationType = operationType;
}

string Operation::getOperationType(){
	return operationType;
}

int Operation::getInputPortNumber(){
	return inputPortNumber;
}

void Operation::setInputOne(string inputOne){
	this->inputOne = inputOne;
}

string Operation::getInputOne(){
	return inputOne;
}

void Operation::setInputTwo(string inputTwo){
	this->inputTwo = inputTwo;
}

string Operation::getInputTwo(){
	return inputTwo;
}

void Operation::setInputThree(string inputThree){
	this->inputThree = inputThree;
}

string Operation::getInputThree(){
	return inputThree;
}

void Operation::setOutput(string output){
	this->output = output;
}

string Operation::getOutput(){
	return output;
}

void Operation::setExpression(string expression){
	this->expression = expression;
}

string Operation::getExpression(){
	return expression;
}

void Operation::setColorWhite(){
	color = -1;
}

void Operation::setColorGray(){
	color = 0;
}

void Operation::setColorBlack(){
	color = 1;
}

bool Operation::isWhite(){
	if (color == -1)
		return true;
	return false;
}

bool Operation::isGray(){
	if (color == 0)
		return true;
	return false;
}

bool Operation::isBlack(){
	if (color == 1)
		return true;
	return false;
}

void Operation::setUnscheduled(){
	scheduledFlag = 0;
}

void Operation::setScheduled(){
	scheduledFlag = 1;
}

bool Operation::isSchedualed(){
	if (scheduledFlag == 0)
		return false;
	return true;
}

bool Operation::isAllSuccesserScheduled(){
	if (nextOperationList.size() == 0)
		return true;
	for (int i = 0; i < nextOperationList.size(); i++){
		if (!nextOperationList.at(i)->isSchedualed())
			return false;
	}
	return true;
}

void Operation::scheduleOperationEndTime(){
	int minSuccessorEndTime = 1000;
	for (int i = 0; i < nextOperationList.size(); i++){
		if (nextOperationList.at(i)->getEndTime() < minSuccessorEndTime)
			minSuccessorEndTime = nextOperationList.at(i)->getEndTime();
	}
	endTime = minSuccessorEndTime - delayCycle;
}

void Operation::setDelayCycle(int delayCycle){
	this->delayCycle = delayCycle;
}

int Operation::getDelayCycle(){
	return delayCycle;
}

void Operation::setTotalDelayCycle(int totalDelayCycle){
	this->totalDelayCycle = totalDelayCycle;
}

int Operation::getTotalDelayCycle(){
	return totalDelayCycle;
}

void Operation::setStartTime(int startTime){
	this->startTime = startTime;
}

int Operation::getStartTime(){
	return startTime;
}

void Operation::setEndTime(int endTime){
	this->endTime = endTime;
}

int Operation::getEndTime(){
	return endTime;
}

int Operation::inputListSize(){
	return inputList.size();
}

void Operation::setIntoInputList(string input){
	inputList.push_back(input);
}

string Operation::getFromInputList(int index){
	return inputList.at(index);
}

int Operation::probabilityListSize(){
	return probabilityList.size();
}

void Operation::computeProbabilityDistribute(int latency){
	if (startTime == endTime){
		for (int i = 0; i < latency; i++){
			if (i == startTime - 1)
				probabilityList.push_back(1);
			else
				probabilityList.push_back(0);
		}
	}
	else{
		for (int i = 0; i < latency; i++){
			if (i == startTime - 1){
				while (i != endTime - 1){
					probabilityList.push_back(1 / (float)(endTime - startTime + 1));
					i++;
				}
				probabilityList.push_back(1 / (float)(endTime - startTime + 1));
			}
			else{
				probabilityList.push_back(0);
			}
		}
	}
}

float Operation::getProbability(int index){
	return probabilityList.at(index);
}

int Operation::nextOperationListSize(){
	return nextOperationList.size();
}

void Operation::setNextOperation(Operation *nextOperation){
	nextOperationList.push_back(nextOperation);
}

Operation *Operation::getNextOperation(int index){
	return nextOperationList.at(index);
}

Operation *Operation::getNextOperation(){
	if (currentNextOperationIndex != nextOperationList.size()){
		Operation *tempOperation = nextOperationList.at(currentNextOperationIndex);
		currentNextOperationIndex++;
		return tempOperation;
	}
	//return nullptr;
	return NULL;
}

bool Operation::isTraversaledAllNextOperation(){
	if (currentNextOperationIndex == nextOperationList.size())
		return true;
	return false;
}

int Operation::prevOperationListSize(){
	return prevOperationList.size();
}

void Operation::setPrevOperation(Operation *prevOperation){
	prevOperationList.push_back(prevOperation);
}

Operation *Operation::getPrevOperation(int index){
	return prevOperationList.at(index);
}

Operation *Operation::getPrevOperation(){
	if (currentPrevOperationIndex != prevOperationList.size()){
		Operation *tempOperation = prevOperationList.at(currentPrevOperationIndex);
		currentPrevOperationIndex++;
		return tempOperation;
	}
}

bool Operation::isTraversaledAllPrevOperation(){
	if (currentPrevOperationIndex == prevOperationList.size())
		return true;
	return false;
}

int Operation::getFrameWidth(){
	return endTime - startTime;
}

void Operation::computeSelfForce(vector<float> &totalProbability){
	float tempSelfForce = 0;
	for (int i = 0; i < probabilityList.size(); i++){
		tempSelfForce = 0;
		if (probabilityList.at(i) != 0){
			for (int j = 0; j < probabilityList.size(); j++){
				if (j != i)
					tempSelfForce = tempSelfForce + (0 - probabilityList.at(j)*totalProbability.at(j));
				else
					tempSelfForce = tempSelfForce + (1 - probabilityList.at(j))*totalProbability.at(j);
			}
		}
		selfForceList.push_back(tempSelfForce);
	}
}

float Operation::getSelfForce(int index){
	return selfForceList.at(index);
}

void Operation::computePredecessorForce(Operation *startVertex){
	float tempTotalPrededessorForce = 0;
	for (int i = 0; i < selfForceList.size(); i++){
		tempTotalPrededessorForce = 0;
		if (selfForceList.at(i) != 0){
			for (int j = 0; j < prevOperationList.size(); j++){
				if (prevOperationList.at(j) != startVertex)
					tempTotalPrededessorForce = tempTotalPrededessorForce + prevOperationList.at(j)->getSelfForce(i);
			}	
		}
		predecessorForceList.push_back(tempTotalPrededessorForce);
	}
}

int Operation::predecessorForceListSize(){
	return predecessorForceList.size();
}

float Operation::getPredecessorForce(int index){
	return predecessorForceList.at(index);
}

void Operation::computeSuccessorForce(Operation *endVertex){
	float tempTotalSuccessorForce = 0;
	for (int i = 0; i < selfForceList.size(); i++){
		tempTotalSuccessorForce = 0;
		if (selfForceList.at(i) != 0){
			for (int j = 0; j < nextOperationList.size(); j++){
				if (nextOperationList.at(j) != endVertex)
					tempTotalSuccessorForce = tempTotalSuccessorForce + nextOperationList.at(j)->getSelfForce(i);
			}			
		}
		successorForceList.push_back(tempTotalSuccessorForce);
	}
}

int Operation::successorForceListSize(){
	return successorForceList.size();
}

float Operation::getSuccessorForce(int index){
	return successorForceList.at(index);
}

void Operation::computeTotalForce(){
	float tempTotalForce = 0;
	for (int i = 0; i < selfForceList.size(); i++){
		if (!selfForceList.empty() 
			&& !successorForceList.empty()
			&& !predecessorForceList.empty())
			tempTotalForce = selfForceList.at(i) + successorForceList.at(i) + predecessorForceList.at(i);
		if (!selfForceList.empty()
			&& successorForceList.empty()
			&& !predecessorForceList.empty())
			tempTotalForce = selfForceList.at(i) + predecessorForceList.at(i);
		if (!selfForceList.empty()
			&& !successorForceList.empty()
			&& predecessorForceList.empty())
			tempTotalForce = selfForceList.at(i) + successorForceList.at(i);
		totalForceList.push_back(tempTotalForce);
	}	
}

int Operation::totalForceListSize(){
	return totalForceList.size();
}

float Operation::getTotalForce(int index){
	return totalForceList.at(index);
}

void Operation::generateVerilogExpression(){
	verilogExpression.append(output);
	verilogExpression.append(" <= ");
	
	if (inputList.size() == 2 
		&& operationType != ">"
		&& operationType != "<"
		&& operationType != "=="){
		verilogExpression.append(inputOne);
		if (operationType == "+")
			verilogExpression.append(" + ");
		if (operationType == "-")
			verilogExpression.append(" - ");
		if (operationType == "*")
			verilogExpression.append(" * ");
		if (operationType == "/")
			verilogExpression.append(" / ");
		if (operationType == "%")
			verilogExpression.append(" % ");
		if (operationType == "<<")
			verilogExpression.append(" << ");
		if (operationType == ">>")
			verilogExpression.append(" >> ");

		verilogExpression.append(inputTwo);
	}

	if (inputList.size() == 2
		&& (operationType == ">"
		|| operationType == "<"
		|| operationType == "==")){
		verilogExpression.append("(");
		verilogExpression.append(inputOne);
		if (operationType == ">")
			verilogExpression.append(" > ");
		if (operationType == "<")
			verilogExpression.append(" < ");
		if (operationType == "==")
			verilogExpression.append(" == ");
		verilogExpression.append(inputTwo);
		verilogExpression.append(") ");
		verilogExpression.append("? ");
		verilogExpression.append(to_string(static_cast<long long>(1)));
		verilogExpression.append(" : ");
		verilogExpression.append(to_string(static_cast<long long>(0)));
	}

	if (inputList.size() == 3){
		verilogExpression.append(inputOne);
		if (operationType == "?"){
			verilogExpression.append(" ? ");
			verilogExpression.append(inputTwo);
			verilogExpression.append(" : ");
			verilogExpression.append(inputThree);
		}
	}
	verilogExpression.append(";");
}

string Operation::getVerilogExpression(){
	return verilogExpression;
}

Operation::~Operation(){
	for (int i = 0; i < nextOperationList.size(); i++)
		nextOperationList.at(i) = NULL;
		//nextOperationList.at(i) = nullptr;
	for (int i = 0; i < prevOperationList.size(); i++)
		prevOperationList.at(i) = NULL;
		//prevOperationList.at(i) = nullptr;
}

