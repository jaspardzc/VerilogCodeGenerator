#include "Main.h"
//to_string
void usage(){
	cout << "The using format is:" << endl;
	cout << "	hlsyn cFile latency verilogFile" << endl;
}

int main(int argc, char *argv[]){
	if (argc != 4){
		usage();
		exit(1);
	}

	AssistList assistList;
	cout << "Start Parsing the file!" << endl;
	Parser::parsingCFile(string(argv[1]), assistList.portList, assistList.variableList, assistList.dependencyGraph.getOperationList());
	assistList.dependencyGraph.buildGraphConnection(assistList.portList, assistList.variableList);
	string inputLatency(argv[2]);
	int minLatency = assistList.dependencyGraph.computeMaximCycles();
	if (stoi(inputLatency) < minLatency){
		cout << "Latency cannot less than " << to_string(static_cast<long long>(minLatency)) << endl;
		exit(1);
	}
	assistList.dependencyGraph.setLatency(stoi(inputLatency));
	cout << "Start FDS scheduling!" << endl;
	assistList.dependencyGraph.forceDirectedScheduling(assistList.timeList);
	cout << "Generating the HLSM verilog code!" << endl;
	CircuitTools::generateVerilogCode(stoi(inputLatency), assistList.portList, assistList.variableList, assistList.timeList, string(argv[3]));
	cout << "Perfectly Done!" << endl;
	return 0;
}