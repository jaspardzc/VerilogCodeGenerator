#include "CircuitTools.h"

//to_string
void CircuitTools::generateVerilogCode(int latency, vector<Port *> &portList, vector<Variable *> &variableList, vector<Time *> &timeList, string outputVerilogFileName){
	fstream outputStream(outputVerilogFileName, ios::out);
	string tempLine = "";
	tempLine.append("module HLSM (Clk, Rst, Start, Done, ");
	for (int i = 0; i < portList.size() - 1; i++)
		tempLine.append(portList.at(i)->getName() + ", ");
	tempLine.append(portList.at(portList.size() - 1)->getName() + ");");
	outputStream << tempLine << endl;
	tempLine.clear();
	tempLine.append("	parameter S_wait = 0, ");
	for (int i = 0; i < latency; i++){
		tempLine.append("S" + to_string(static_cast<long long>(i + 1)));
		tempLine.append(" = " + to_string(static_cast<long long>(i + 1)));
		tempLine.append(", ");
	}
	tempLine.append("S_final = " + to_string(static_cast<long long>(latency + 1)));
	tempLine.append(";");
	outputStream << tempLine << endl;
	tempLine.clear();
	outputStream << "	input Clk, Rst, Start;" << endl;
	outputStream << "	output reg Done;" << endl;
	for (int i = 0; i < portList.size(); i++){
		outputStream << "	" << portList.at(i)->getVerilogExpression() << endl;
	}	
	for (int i = 0; i < variableList.size(); i++){
		outputStream << "	" << variableList.at(i)->getVerilogExpression() << endl;
	}
	int regMSB = log(latency + 2) / log(2);
	tempLine.append("reg [");
	tempLine.append(to_string(static_cast<long long>(regMSB)));
	tempLine.append(" : 0] state;");
	outputStream << "	" << tempLine << endl;
	tempLine.clear();
	outputStream << "	always @(posedge Clk) begin" << endl;
	outputStream << "		if(Rst == 1) begin" << endl;
	outputStream << "				Done <= 0;" << endl;
	outputStream << "				state <= S_wait;" << endl;
	outputStream << "		end" << endl;
	outputStream << "		else begin" << endl;
	outputStream << "			case(state)" << endl;
	outputStream << "				S_wait: begin" << endl;
	outputStream << "					if(Start == 1)" << endl;
	outputStream << "						state <= S1;" << endl;
	outputStream << "					else" << endl;
	outputStream << "						state <= S_wait;" << endl;
	outputStream << "				end" << endl;
	string nextState = "";
	for (int i = 0; i < latency; i++){
		tempLine.append("S" + to_string(static_cast<long long>(i + 1)));
		tempLine.append(": begin");
		if ((i + 1) == latency)
			nextState.append("S_final");
		else
			nextState.append("S" + to_string(static_cast<long long>(i + 2)));
		outputStream << "				" << tempLine << endl;
		timeList.at(i)->generateVerilogExpression("					");
		for (int j = 0; j < timeList.at(i)->verilogExpressionListSize(); j++)
			outputStream << timeList.at(i)->getVerilogExpression(j) << endl;
		outputStream << "					state <= " << nextState << ";" << endl;
		nextState.clear();
		tempLine.clear();
		outputStream << "				end" << endl;
	}
	outputStream << "				S_final: begin" << endl;
	outputStream << "					Done <= 1;" << endl;
	outputStream << "					state <= S_wait;" << endl;
	outputStream << "				end" << endl;
	outputStream << "			endcase" << endl;
	outputStream << "		end" << endl;
	outputStream << "	end" << endl;
	outputStream << "endmodule" << endl;
	outputStream.close();
}