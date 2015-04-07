#include "Constants.h"

int Constants::setDelayCycles(string operationType){
	if (operationType == "+")
		return ADD_CYCLE_DELAY;
	if (operationType == "-")
		return SUB_CYCLE_DELAY;
	if (operationType == "*")
		return MUL_CYCLE_DELAY;
	if (operationType == ">")
		return COMPGT_CYCLE_DELAY;
	if (operationType == "<")
		return COMPLT_CYCLE_DELAY;
	if (operationType == "==")
		return COMPEQ_CYCLE_DELAY;
	if (operationType == "?")
		return MUX2X1_CYCLE_DELAY;
	if (operationType == ">>")
		return SHR_CYCLE_DELAY;
	if (operationType == "<<")
		return SHL_CYCLE_DELAY;
	if (operationType == "/")
		return DIV_CYCLE_DELAY;
	if (operationType == "%")
		return MOD_CYCLE_DELAY;
	if (operationType == "Nope")
		return NOPE_CYCLE_DELAY;
}