#include "Parcer.hpp"

int main(){
	std::vector<std::string> messageVec;
	Parcer parcer("Invite        sveta       :42  gggg  fff 			");
	parcer.splitMessage(messageVec);
	if (!parcer.isValidCommand(messageVec.front()));
		return 1;
	if (!parcer.isValidParam(messageVec));
		return 1;
	


}