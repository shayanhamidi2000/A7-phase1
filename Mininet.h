#ifndef MININET_H
#define MININET_H

#include <vector>
#include <iostream>
#include "Customer.h" 
#include "FilmRepository.h"
#include "CommandHandler.h"
#include "Publisher.h"
#include "Purchase.h"


class MiniNet{
public:
	MiniNet();
	void startNet();
	bool editAFilm(unsigned int id , std::string newName , unsigned int newYear , unsigned int newLength , std::string newSummary , std::string newDirector);
	void addFilmOnNet(std::string name , unsigned int year , std::string director , std::string summary , unsigned int price , unsigned int length);
	void registerUser(std::string email , std::string username , std::string password , unsigned int age , bool isPublisher);
	void loginUser(std::string username , std::string password);
	Customer* findUserByUsername(std::string username);
	Customer* findUserById(unsigned int id);

private:
	unsigned int totalNetCredit;
	unsigned int theIdsAssigned;
	CommandHandler* manageCommand;
	FilmRepository* films;
	Customer* onlineUser;
	std::vector<Customer*> users;
	std::vector<Purchase*> purchases;
	//
	void goToNextId();
	void checkUsernameRepetition(std::string username);
	void isUsernameMatchingPassword(std::string username , std::string password);
	void isUsernameExisted(std::string username);
	void checkIdExistence(unsigned int id);
	bool isOnlineUserPublisher() { return onlineUser->getPublishingState(); }
	bool isAnyOneOnline() { return (onlineUser != nullptr); }
};



#endif