#include "DependencyGraph.h"
//to_string
DependencyGraph::DependencyGraph(){
	latency = 0;
	operationList = new vector<Operation *>();
	startVertex = new Operation("Nope");
	operationList->push_back(startVertex);
	endVertex = new Operation("Nope");
	operationList->push_back(endVertex);
}

DependencyGraph::DependencyGraph(int latency){
	this->latency = latency;
	operationList = new vector<Operation *>();
	startVertex = new Operation("Nope");
	operationList->push_back(startVertex);
	endVertex = new Operation("Nope");
	operationList->push_back(endVertex);
}

void DependencyGraph::setLatency(int latency){
	this->latency = latency;
}

vector<Operation *> &DependencyGraph::getOperationList(){
	return *operationList;
}

int DependencyGraph::graphSize(){
	return operationList->size();
}

void DependencyGraph::setIntoGraph(Operation *operation){
	operationList->push_back(operation);
}

Operation &DependencyGraph::getVertexFromGraph(int index){
	return *operationList->at(index);
}

Operation *DependencyGraph::getVertexPointerFromGraph(int index){
	return operationList->at(index);
}

void DependencyGraph::connectToSinkVertex(Operation *operation, Port *port){
	for (int i = 0; i < operation->inputListSize(); i++){
		if (operation->getFromInputList(i) == port->getName()){
			startVertex->setNextOperation(operation);
			operation->setPrevOperation(startVertex);
		}		
	}

	if (operation->getOutput() == port->getName()){
		operation->setNextOperation(endVertex);
		endVertex->setPrevOperation(operation);
	}
}

void DependencyGraph::buildGraphConnection(vector<Port *> &portList, vector<Variable *> variableList){
	for (int i = 0; i < operationList->size(); i++){
		for (int j = 0; j < portList.size(); j++){
			connectToSinkVertex(getVertexPointerFromGraph(i), portList.at(j));
		}
	}

	for (int i = 0; i < variableList.size(); i++){
		for (int j = 0; j < variableList.at(i)->outputListSize(); j++){
			variableList.at(i)->getInput()->setNextOperation(variableList.at(i)->getFromOutputList(j));
			variableList.at(i)->getFromOutputList(j)->setPrevOperation(variableList.at(i)->getInput());
		}
	}
}

int DependencyGraph::computeMaximCycles(){
	queue<Operation *> operationQueue;
	initialVertexTotalCycleDelay();
	startVertex->setStartTime(0);
	operationQueue.push(startVertex);
	//Operation *currentOperation = nullptr;
	//Operation *nextOperation = nullptr;
	Operation *currentOperation = NULL;
	Operation *nextOperation = NULL;
	while (!operationQueue.empty()){
		currentOperation = operationQueue.front();
		for (int i = 0; i < currentOperation->nextOperationListSize(); i++){
			nextOperation = currentOperation->getNextOperation(i);
			if (currentOperation->getTotalDelayCycle() + currentOperation->getDelayCycle() > nextOperation->getTotalDelayCycle())
				nextOperation->setTotalDelayCycle(currentOperation->getTotalDelayCycle() + currentOperation->getDelayCycle());
			operationQueue.push(nextOperation);
		}
		operationQueue.pop();
	}

	return endVertex->getTotalDelayCycle() - 1;
}

void DependencyGraph::initialVertexToWhite(){
	for (int i = 0; i < graphSize(); i++){
		getVertexPointerFromGraph(i)->setColorWhite();
	}
}

void DependencyGraph::initialVertexTotalCycleDelay(){
	for (int i = 0; i < graphSize(); i++){
		getVertexPointerFromGraph(i)->setTotalDelayCycle(0);
	}
}

void DependencyGraph::initialOperationsUnscheduled(){
	for (int i = 0; i < operationList->size(); i++)
		operationList->at(i)->setUnscheduled();
}

void DependencyGraph::asSoonAsPosible(){
	queue<Operation *> operationQueue;
	initialVertexTotalCycleDelay();
	startVertex->setStartTime(0);
	operationQueue.push(startVertex);
	//Operation *tempOperation = nullptr;
	Operation *tempOperation = NULL;
	while (!operationQueue.empty()){
		tempOperation = operationQueue.front();
		updateNextOperationStartTime(tempOperation);
		for (int i = 0; i < tempOperation->nextOperationListSize(); i++)
			operationQueue.push(tempOperation->getNextOperation(i));
		operationQueue.pop();
	}
}

void DependencyGraph::asLateAsPosible(){
	stack<Operation *> operationStack;
	initialVertexTotalCycleDelay();
	initialOperationsUnscheduled();
	endVertex->setEndTime(latency + 1);
	endVertex->setScheduled();
	operationStack.push(startVertex);
	//Operation *topOperation = nullptr;
	Operation *topOperation = NULL;
	while (!operationStack.empty()){
		topOperation = operationStack.top();
		if (!topOperation->isAllSuccesserScheduled()){
			for (int i = 0; i < topOperation->nextOperationListSize(); i++){
				if (!topOperation->getNextOperation(i)->isSchedualed()){
					operationStack.push(topOperation->getNextOperation(i));
				}
			}
		}
		else{
			topOperation->scheduleOperationEndTime();
			topOperation->setScheduled();
			operationStack.pop();
		}
	}
}

void DependencyGraph::updateNextOperationStartTime(Operation *operation){
	for (int i = 0; i < operation->nextOperationListSize(); i++){
		if (operation->getStartTime() + operation->getDelayCycle() > operation->getNextOperation(i)->getStartTime())
			operation->getNextOperation(i)->setStartTime(operation->getStartTime() + operation->getDelayCycle());
	}
}

void DependencyGraph::forceDirectedScheduling(vector<Time *> &timeList){
	//Time *tempTime = nullptr;
	Time *tempTime = NULL;
	for (int i = 0; i < latency; i++){
		tempTime = new Time();
		tempTime->timeNumber = i + 1;
		timeList.push_back(tempTime);
	}
	asSoonAsPosible();
	asLateAsPosible();

	vector<Operation *> addList;
	vector<Operation *> subList;
	vector<Operation *> mulList;
	vector<Operation *> divList;
	vector<Operation *> modList;
	vector<Operation *> shrList;
	vector<Operation *> shlList;
	vector<Operation *> ceqList;
	vector<Operation *> cgtList;
	vector<Operation *> cltList;
	vector<Operation *> muxList;

	vector<float> addTotalProbability;
	vector<float> subTotalProbability;
	vector<float> mulTotalProbability;
	vector<float> divTotalProbability;
	vector<float> modTotalProbability;
	vector<float> shrTotalProbability;
	vector<float> shlTotalProbability;
	vector<float> ceqTotalProbability;
	vector<float> cgtTotalProbability;
	vector<float> cltTotalProbability;
	vector<float> muxTotalProbability;

	for (int i = 0; i < operationList->size(); i++){
		operationList->at(i)->computeProbabilityDistribute(latency);
		if (operationList->at(i)->getOperationType() == "+")
			addList.push_back(operationList->at(i));
		if (operationList->at(i)->getOperationType() == "-")
			subList.push_back(operationList->at(i));
		if (operationList->at(i)->getOperationType() == "*")
			mulList.push_back(operationList->at(i));
		if (operationList->at(i)->getOperationType() == "/")
			divList.push_back(operationList->at(i));
		if (operationList->at(i)->getOperationType() == "%")
			modList.push_back(operationList->at(i));
		if (operationList->at(i)->getOperationType() == ">>")
			shrList.push_back(operationList->at(i));
		if (operationList->at(i)->getOperationType() == "<<")
			shlList.push_back(operationList->at(i));
		if (operationList->at(i)->getOperationType() == "==")
			ceqList.push_back(operationList->at(i));
		if (operationList->at(i)->getOperationType() == ">")
			cgtList.push_back(operationList->at(i));
		if (operationList->at(i)->getOperationType() == "<")
			cltList.push_back(operationList->at(i));
		if (operationList->at(i)->getOperationType() == "?")
			muxList.push_back(operationList->at(i));
	}
	
	setOperationSelfForce(addList, addTotalProbability);
	setOperationSelfForce(subList, subTotalProbability);
	setOperationSelfForce(mulList, mulTotalProbability);
	setOperationSelfForce(divList, divTotalProbability);
	setOperationSelfForce(modList, modTotalProbability);
	setOperationSelfForce(shrList, shrTotalProbability);
	setOperationSelfForce(shlList, shlTotalProbability);
	setOperationSelfForce(ceqList, ceqTotalProbability);
	setOperationSelfForce(cgtList, cgtTotalProbability);
	setOperationSelfForce(cltList, cltTotalProbability);
	setOperationSelfForce(muxList, muxTotalProbability);

	setOperationPredecessorForce(*operationList);
	setOperationSuccessorForce(*operationList);
	setOperationTotalForce(*operationList);
	beginScheduling(*operationList, timeList);
}

void DependencyGraph::computeTotalProbability(vector<Operation *> &operationList, vector<float> &totalProbabilityList){
	float sumProbability = 0;
	for (int i = 0; i < latency; i++){
		sumProbability = 0;
		for (int j = 0; j < operationList.size(); j++){
			sumProbability = operationList.at(j)->getProbability(i) + sumProbability;
		}
		totalProbabilityList.push_back(sumProbability);
	}
}

void DependencyGraph::setOperationSelfForce(vector<Operation *> &operationList, vector<float> &probabilityList){
	if (!operationList.empty()){
		computeTotalProbability(operationList, probabilityList);
		for (int i = 0; i < operationList.size(); i++)
			operationList.at(i)->computeSelfForce(probabilityList);
	}
}

void DependencyGraph::setOperationPredecessorForce(vector<Operation *> &operationList){
	for (int i = 0; i < operationList.size(); i++)
		operationList.at(i)->computePredecessorForce(startVertex);
}

void DependencyGraph::setOperationSuccessorForce(vector<Operation *> &operationList){
	for (int i = 0; i < operationList.size(); i++)
		operationList.at(i)->computeSuccessorForce(endVertex);
}

void DependencyGraph::setOperationTotalForce(vector<Operation *> &operationList){
	for (int i = 0; i < operationList.size(); i++)
		operationList.at(i)->computeTotalForce();
}

int DependencyGraph::minimumTotalForceNumber(Operation *operation){
	int minimumTotalForce = 1000;
	int minimumIndex = 0;

	if (operation->getEndTime() == operation->getStartTime()){
		return operation->getStartTime() - 1;
	}
	else{
		for (int i = 0; i < operation->totalForceListSize(); i++){
			if (i < operation->getEndTime() - 1 && i > operation->getStartTime() - 1){
				if (operation->getTotalForce(i) < minimumTotalForce){
					minimumTotalForce = operation->getTotalForce(i);
					minimumIndex = i;
				}
			}
		}
	}
	return minimumIndex;
}

void DependencyGraph::beginScheduling(vector<Operation *> &operationList, vector<Time *> &timeList){
	int timeIndex = 0;
	//Operation *currentOperation = nullptr;
	Operation *currentOperation = NULL;
	for (int i = 0; i < operationList.size(); i++){
		currentOperation = operationList.at(i);
		if (currentOperation != startVertex && currentOperation != endVertex){
			timeIndex = minimumTotalForceNumber(currentOperation);
			timeList.at(timeIndex)->operaionList.push_back(currentOperation);
		}
	}
}

DependencyGraph::~DependencyGraph(){
	//startVertex = nullptr;
	//endVertex = nullptr;
	startVertex = NULL;
	endVertex = NULL;
	for (int i = 0; i < operationList->size(); i++)
		delete operationList->at(i);
	delete operationList;
}