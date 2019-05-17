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
	virtual std::string getUsername() const;
	virtual std::string getPassword() const;
	virtual std::string getEmail() const;
	virtual std::vector<Film*> getPurchasedFilms() const; 
	virtual unsigned int getId() const;
	virtual unsigned int getAge() const;
	virtual unsigned int getCredit() const;
	virtual bool getPublishingState() const;
	virtual void printYourself() const;
	virtual void addToCredit(const unsigned int amount);
	virtual void getMessage(Message* newMessage);
	virtual void sendMessageToFollowedPublisher(Publisher* followedPublisher);
	virtual void buyNewFilm(Film* newFilm);
	virtual bool hasFilm(Film* newFilm);
	//
protected:
	bool isPublisher;
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
	virtual void sendMessageToBoughtFromPublisher(Publisher* boughtFromPublisher , const Film* boughtFilm);
	virtual void sendMessageTo(Customer* messageReciever , std::string content);
	virtual void withdrawCredit(const int amount);
};

#endif