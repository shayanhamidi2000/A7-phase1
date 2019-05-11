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
protected:
	string username;
	string password;
	bool isLogedIn;
	string email;
	unsigned int id;
	unsigned int age;
	unsigned int credit;
	vector<Message*> messages;
	vector<Film> purchases;
};

#endif