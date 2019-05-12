#include "Mininet.h"
#include "Config.h"
#include <iostream>
#include <string>


MiniNet::MiniNet(){
	totalNetCredit = 0;
	theIdsAssigned = BASIC_ID_VALUE; 
	onlineUser = nullptr;
	manageCommand = new CommandHandler(this);
}

void MiniNet::startNet(){
	string line = "";
	while(getline(cin , line)){
		try{
			manageCommand->getRawCommand(line);
		}catch(exception& ex){
			cout << ex.what() << endl;
		}
	}
}

bool Mininet::checkUsernameRepetition(string username){
	for(unsigned int i = 0 ; i < customers.size() ; i++)
		if(customers[i].getUsername() == username)
			return true;

	for(unsigned int i = 0 ; i < publishers.size() ; i++)
		if(publishers[i].getUsername() == username)
			return true;	

	return false;	
}

void registerUser(string email , string username , string password , int age , bool isPublisher){

}