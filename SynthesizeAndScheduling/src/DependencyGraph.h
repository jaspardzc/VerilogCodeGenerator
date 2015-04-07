#ifndef DependencyGraph_H
#define DependencyGraph_H
#include <vector>
#include <queue>
#include <stack>
#include "Variable.h"
#include "Operation.h"
#include "Time.h"
#include "Port.h"
using namespace std;

class DependencyGraph{
private:
	vector<Operation *> *operationList;
	Operation *startVertex;
	Operation *endVertex;
	int latency;
	void initialVertexToWhite();
	void initialVertexTotalCycleDelay();
	void initialOperationsUnscheduled();
	void connectToSinkVertex(Operation *operation, Port *port);
	void updateNextOperationStartTime(Operation *operation);
	void setOperationSelfForce(vector<Operation *> &operationList, vector<float> &probabilityList);
	void setOperationPredecessorForce(vector<Operation *> &operationList);
	void setOperationSuccessorForce(vector<Operation *> &operationList);
	void setOperationTotalForce(vector<Operation *> &operationList);
	int minimumTotalForceNumber(Operation *operation);
	void beginScheduling(vector<Operation *> &operationList, vector<Time *> &timeList);
public:
	explicit DependencyGraph();
	explicit DependencyGraph(int latency);
	void setLatency(int latency);
	vector<Operation *> &getOperationList();
	int graphSize();
	void setIntoGraph(Operation *operation);
	Operation &getVertexFromGraph(int index);
	Operation *getVertexPointerFromGraph(int index);
	void buildGraphConnection(vector<Port *> &portList, vector<Variable *> variableList);
	int computeMaximCycles();
	void asSoonAsPosible();
	void asLateAsPosible();
	void forceDirectedScheduling(vector<Time *> &timeList);
	void computeTotalProbability(vector<Operation *> &operationList, vector<float> &totalProbabilityList);
	//void leftEdge();
	~DependencyGraph();
};
#endif