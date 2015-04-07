#ifndef Constants_H
#define Constants_H
#include <cstring>
#include <string>
using namespace std;

#define	ADD_CYCLE_DELAY		1
#define	SUB_CYCLE_DELAY		1
#define MUL_CYCLE_DELAY		2
#define	COMPGT_CYCLE_DELAY	1
#define	COMPLT_CYCLE_DELAY	1
#define	COMPEQ_CYCLE_DELAY	1
#define	MUX2X1_CYCLE_DELAY	1
#define	SHR_CYCLE_DELAY		1
#define	SHL_CYCLE_DELAY		1
#define	DIV_CYCLE_DELAY		3
#define	MOD_CYCLE_DELAY		3
#define NOPE_CYCLE_DELAY	1


class Constants{
public:
	static int setDelayCycles(string operationType);
};

#endif