#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <stack>
#include "Message.h"
#include "Film.h"


class Customer{
public:
	Customer(std::string username , std::string password , std::string email , unsigned int id , unsigned int age);
	~Customer();
	virtual std::string getUsername() const;
	virtual bool hasPassword(const std::string& assertedPassword) const;
	virtual bool hasMoney(const unsigned int amount) const;
	virtual std::vector<Film*> getPurchasedFilms() const; 
	virtual unsigned int getId() const;
	virtual bool getPublishingState() const;
	virtual bool getAdminState() const;
	virtual void printYourself() const;
	virtual void addToCredit(const unsigned int amount);
	virtual void getMessage(Message* newMessage);
	virtual void sendMessageToFollowedPublisher(Publisher* followedPublisher) const;
	virtual void sendMessageToRatedPublisher(const Film* ratedFilm) const;
	virtual void sendMessageToCommentedPublisher(const Film* commentedFilm) const;
	virtual void buyNewFilm(Film* newFilm);
	virtual bool hasFilm(Film* newFilm);
	virtual void showUnreadMessages();
	virtual void showReadMessages(const unsigned int limit);
	virtual std::string showCredit() const;
protected:
	bool isPublisher;
	bool isAdmin;
	std::string username;
	std::string password;
	std::string email;
	unsigned int id;
	unsigned int age;
	int credit;
	std::stack<Message*> unreadMessages;
	std::vector<Message*> allMessages;
	std::vector<Film*> purchasedFilms;
	//
	virtual void sendMessageToBoughtFromPublisher(const Film* boughtFilm) const;
	virtual void sendMessageTo(Customer* messageReciever , std::string content) const;
	virtual void withdrawCredit(const int amount);
	virtual void transferNewlyReadMessagesToReadMessages(std::vector<Message*> newlyReadMessages);

};

#endif