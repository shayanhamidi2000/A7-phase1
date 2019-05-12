#ifndef MININET_H
#define MININET_H

#include <vector>
#include "Customer.h" 
#include "CommandHandler.h"
#include "Publisher.h"
#include "Purchase.h"

using namespace std;

class MiniNet{
public:
	MiniNet();
	void startNet();

	void registerUser(string email , string username , string password , int age , bool isPublisher);
	bool checkUsernameRepetition(string username);
	Customer* findCustomerById(unsigned int id);
	
private:
	int totalNetCredit;
	int theIdsAssigned;
	CommandHandler* manageCommand;
	Customer* onlineUser;
	vector<Customer*> customers;
	vector<Publisher*> publisher;
	vector<Purchase*> purchases;

};



#endif