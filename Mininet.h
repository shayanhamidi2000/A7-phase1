#ifndef MININET_H
#define MININET_H

#include <vector>
#include <iostream>
#include "Customer.h" 
#include "CommandHandler.h"
#include "Publisher.h"
#include "Purchase.h"

using namespace std;

class MiniNet{
public:
	MiniNet();
	void startNet();
	void registerUser(string email , string username , string password , unsigned int age , bool isPublisher);
	bool checkUsernameRepetition(string username);
	Customer* findCustomerById(unsigned int id);

private:
	unsigned int totalNetCredit;
	unsigned int theIdsAssigned;
	CommandHandler* manageCommand;
	Customer* onlineUser;
	vector<Customer*> customers;
	vector<Customer*> publishers;
	vector<Purchase*> purchases;
	void goToNextId() { theIdsAssigned++; }
};



#endif