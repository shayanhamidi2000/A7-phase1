#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include "Message.h"
#include "Film.h"

using namespace std;

class Customer{
public:
	Customer(string username , string password , string email , unsigned int id , unsigned int age);
	virtual string getUsername() const { return username; }
	virtual string getPassword() const { return password; }
	virtual string getEmail() const { return email; }
	virtual unsigned int getId() const { return id; }
	virtual unsigned int getAge() const { return age; }
	virtual unsigned int getCredit() const { return credit; }
protected:
	bool isPublisher;
	string username;
	string password;
	string email;
	unsigned int id;
	unsigned int age;
	unsigned int credit;
	vector<Message*> messages;
	vector<Film> purchases;
};

#endif