#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include "Message.h"
#include "Film.h"


class Customer{
public:
	Customer(std::string username , std::string password , std::string email , unsigned int id , unsigned int age);
	virtual std::string getUsername() const;
	virtual std::string getPassword() const;
	virtual std::string getEmail() const;
	virtual unsigned int getId() const;
	virtual unsigned int getAge() const;
	virtual unsigned int getCredit() const;
	virtual bool getPublishingState() const;
	//
protected:
	bool isPublisher;
	std::string username;
	std::string password;
	std::string email;
	unsigned int id;
	unsigned int age;
	unsigned int credit;
	std::vector<Message*> messages;
	std::vector<Film*> purchases;
};

#endif