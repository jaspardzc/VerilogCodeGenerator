#ifndef Operation_H
#define Operation_H
#include <string>
#include <vector>
#include "Constants.h"
using namespace std;
class Operation{
private:
	string operationType;
	int inputPortNumber;
	string inputOne;
	string inputTwo;
	string inputThree;
	string output;
	string expression;
	vector<string> inputList;
	int color; // -1 white, 0 grey, 1 black
	int scheduledFlag;
	int delayCycle;
	int totalDelayCycle;
	int startTime;
	int endTime;
	vector<float> probabilityList;
	vector<Operation *> nextOperationList;
	vector<Operation *> prevOperationList;
	int currentNextOperationIndex;
	int currentPrevOperationIndex;
	vector<float> selfForceList;
	vector<float> predecessorForceList;
	vector<float> successorForceList;
	vector<float> totalForceList;
	string verilogExpression;
public:
	explicit Operation();
	explicit Operation(string operationType);
	explicit Operation(string operationType, string inputOne, string inputTwo, string inputThree, string output, string expression);
	void setOperationType(string operationType);
	string getOperationType();
	int getInputPortNumber();
	void setInputOne(string inputOne);
	string getInputOne();
	void setInputTwo(string inputTwo);
	string getInputTwo();
	void setInputThree(string inputThree);
	string getInputThree();
	void setOutput(string output);
	string getOutput();
	void setExpression(string expression);
	string getExpression();
	void setColorWhite();
	void setColorGray();
	void setColorBlack();
	bool isWhite();
	bool isGray();
	bool isBlack();
	void setUnscheduled();
	void setScheduled();
	bool isSchedualed();
	bool isAllSuccesserScheduled();
	void scheduleOperationEndTime();
	void setDelayCycle(int delayCycle);
	int getDelayCycle();
	void setTotalDelayCycle(int totalDelayCycle);
	int getTotalDelayCycle();
	void setStartTime(int startTime);
	int getStartTime();
	void setEndTime(int endTime);
	int getEndTime();
	int getFrameWidth();
	int inputListSize();
	void setIntoInputList(string input);
	string getFromInputList(int index);
	int probabilityListSize();
	float getProbability(int index);
	void computeProbabilityDistribute(int latency);
	int nextOperationListSize();
	void setNextOperation(Operation *nextOperation);
	Operation *getNextOperation(int index);
	Operation *getNextOperation();
	bool isTraversaledAllNextOperation();
	int prevOperationListSize();
	void setPrevOperation(Operation *prevOperation);
	Operation *getPrevOperation(int index);
	Operation *getPrevOperation();
	bool isTraversaledAllPrevOperation();
	void computeSelfForce(vector<float> &totalProbability);
	float getSelfForce(int index);
	void computePredecessorForce(Operation *startVertex);
	int predecessorForceListSize();
	float getPredecessorForce(int index);
	int successorForceListSize();
	void computeSuccessorForce(Operation *endVertex);
	float getSuccessorForce(int index);
	void computeTotalForce();
	int totalForceListSize();
	float getTotalForce(int index);
	void generateVerilogExpression();
	string getVerilogExpression();
	~Operation();
};
#endif