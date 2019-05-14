#ifndef MININET_H
#define MININET_H

#include <vector>
#include <iostream>
#include "Customer.h" 
#include "FilmRepository.h"
#include "CommandHandler.h"
#include "Publisher.h"
#include "Purchase.h"

using namespace std;

class MiniNet{
public:
	MiniNet();
	void startNet();
	bool isOnlineUserPublisher() { return onlineUser->getPublishingState(); }
	bool isAnyOneOnline() { return (onlineUser != nullptr); }
	void addFilmOnNet(string name , unsigned int year , string director , string summary , unsigned int price , unsigned int length);
	void registerUser(string email , string username , string password , unsigned int age , bool isPublisher);
	void loginUser(string username , string password);
	Customer* findUserByUsername(string username);
	Customer* findUserById(unsigned int id);

private:
	unsigned int totalNetCredit;
	unsigned int theIdsAssigned;
	CommandHandler* manageCommand;
	FilmRepository* films;
	Customer* onlineUser;
	vector<Customer*> users;
	vector<Purchase*> purchases;
	void goToNextId() { theIdsAssigned++; }
	void checkUsernameRepetition(string username);
	void isUsernameMatchingPassword(string username , string password);
	void isUsernameExisted(string username);
	void checkIdExistence(unsigned int id);
};



#endif