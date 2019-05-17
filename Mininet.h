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
	void registerUser(std::string email , std::string username , std::string password , unsigned int age , bool isPublisher);
	void loginUser(std::string username , std::string password);
	void addFilmOnNet(std::string name , unsigned int year , std::string director , std::string summary , unsigned int price , unsigned int length);
	void editAFilm(unsigned int id , std::string newName , unsigned int newYear , unsigned int newLength , std::string newSummary , std::string newDirector);
	void deleteAFilm(unsigned int id);
	void getPublishedList(std::string name , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , std::string directorName);
	void getFollowersList();
	void follow(unsigned int id);
	void addMoney(unsigned int amount);
	void buyFilm(unsigned int filmId);
	void getMoneyFromNet();
	void getPurchasedList(std::string name , unsigned int minYear , unsigned int price , unsigned maxYear , std::string directorName);
	void rateFilm(unsigned int id , unsigned int score);
	void comment(unsigned int id , std::string commentContent);
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
	Customer* findUserByUsername(std::string username);
	Customer* findUserById(unsigned int id);
	bool isOnlineUserPublisher();
	void addToNetCredit(unsigned int amount);
	void withdrawNetCredit(unsigned int amount);
	void checkUsernameRepetition(std::string username);
	void isUsernameMatchingPassword(std::string username , std::string password);
	void isUsernameExisted(std::string username);
	void checkIdExistence(unsigned int id);
	bool isAnyOneOnline();
	unsigned int getPublisherSoldFilmsMoney();
	void deleteOverduedPurchases(std::vector<unsigned int> overduedPurchases);
	std::vector<unsigned int> decreaseEachIndexByOne(std::vector<unsigned int> anIndexVector);
};



#endif