#include "Mininet.h"
#include "Config.h"
#include "Exceptions.h"
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

void MiniNet::checkIdExistence(unsigned int id){
	if(findUserById(id) == nullptr)
		throw NotFoundException();
}

Customer* MiniNet::findUserByUsername(string username){
	for(unsigned int i = 0 ; i < users.size() ; i++)
		if(users[i]->getUsername() == username)
			return users[i];

	return nullptr;
}

Customer* MiniNet::findUserById(unsigned int id){
	for(unsigned int i = 0 ; i < users.size() ; i++)
		if(users[i]->getId() == id)
			return users[i];

	return nullptr;
}

void MiniNet::checkUsernameRepetition(string username){
	if(findUserByUsername(username) != nullptr)
		throw BadRequestException();		
}

void MiniNet::registerUser(string email , string username , string password , unsigned int age , bool isPublisher){
	checkUsernameRepetition(username);
	if(isPublisher)
		onlineUser = new Publisher(username , password , email , theIdsAssigned , age);
	else
		onlineUser = new Customer(username , password , email , theIdsAssigned , age);

	users.push_back(onlineUser);
	this->goToNextId();
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::isUsernameMatchingPassword(string username , string password){
	if(findUserByUsername(username)->getPassword() != password)
		throw BadRequestException();

}
void MiniNet::isUsernameExisted(string username){
	if(findUserByUsername(username) == nullptr)
		throw BadRequestException();

}

void MiniNet::loginUser(string username , string password){
	isUsernameExisted(username);
	isUsernameMatchingPassword(username , password);
	this->onlineUser = findUserByUsername(username);
	cout << SUCCESS_MESSAGE << endl;
}