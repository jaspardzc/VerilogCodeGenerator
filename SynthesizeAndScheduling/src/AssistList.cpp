#include "AssistList.h"

AssistList::AssistList(){

}

AssistList::~AssistList(){
	for (int i = 0; i < portList.size(); i++)
		delete portList.at(i);

	for (int i = 0; i < variableList.size(); i++)
		delete variableList.at(i);

	for (int i = 0; i < timeList.size(); i++)
		delete timeList.at(i);
}