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
	string getUsername() const { return username; }
	string getPassword() const { return password; }
	string getEmail() const { return email; }
	unsigned int getId() const { return id; }
	unsigned int getAge() const { return age; }
	unsigned int getCredit() const { return credit; }
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