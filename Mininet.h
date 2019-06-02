#ifndef MININET_H
#define MININET_H

#include <vector>
#include "Customer.h" 
#include "FilmRepository.h"
#include "Publisher.h"
#include "Purchase.h"
#include "Security.h"
#include "server/server.hpp"

class MiniNet{
public:
	MiniNet();
	~MiniNet();
	unsigned int getTotalNetCredit() const;
	//
	void startNet();
	void updateRequestingUser(std::string newRequestingUsername);
	void registerUser(std::string email , std::string username , std::string password , unsigned int age , bool isPublisher);
	void loginUser(std::string username , std::string password);
	void logout();
	void addFilmOnNet(std::string name , unsigned int year , std::string director , std::string summary , unsigned int price , unsigned int length);
	void editAFilm(unsigned int id , std::string newName , unsigned int newYear , unsigned int newLength , std::string newSummary , std::string newDirector);
	void deleteAFilm(unsigned int id);
	void getPublishedList(std::string name , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , std::string directorName);
	void getFollowersList();
	void follow(unsigned int id);
	void addMoney(unsigned int amount);
	void buyFilm(unsigned int filmId);
	void getMoneyFromNet();
	void showCredit();
	void getPurchasedList(std::string name , unsigned int minYear , unsigned int price , unsigned maxYear , std::string directorName);
	void rateFilm(unsigned int filmId , unsigned int score);
	void comment(unsigned int filmId , std::string commentContent);
	void replyComment(unsigned int filmId , unsigned int commentId , std::string content);
	void deleteComment(unsigned int filmId , unsigned int commentId);
	void getUnreadMessages();
	void getAllMessages(unsigned int limit);
	void searchFilmsInDatabase(std::string name , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , std::string directorName);
	void showFurtherInfo(unsigned int filmId);
private:
	unsigned int totalNetCredit;
	unsigned int theIdsAssigned;
	FilmRepository* films;
	Customer* requestingUser;
	Security* systemSecurity;
	std::vector<Customer*> users;
	std::vector<Purchase*> purchases;
	//
	void goToNextId();
	bool isrequestingUserPublisher();
	bool isrequestingUserAdmin();
	void addToNetCredit(unsigned int amount);
	void withdrawNetCredit(unsigned int amount);
	unsigned int getPublisherSoldFilmsMoney();
	void deleteOverduedPurchases(std::vector<unsigned int> overduedPurchases);
	std::vector<unsigned int> decreaseEachIndexByOne(std::vector<unsigned int> anIndexVector);
};



#endif
