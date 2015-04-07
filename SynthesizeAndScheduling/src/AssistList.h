#ifndef AssitList_H
#define AssitList_H
#include <vector>
#include "DependencyGraph.h"
#include "Variable.h"
#include "Port.h"
#include "Time.h"

using namespace std;

class AssistList{
private:

public:
	explicit AssistList();
	DependencyGraph dependencyGraph;
	vector<Port *> portList;
	vector<Variable * > variableList;
	vector<Time *> timeList;
	~AssistList();
};
#endif