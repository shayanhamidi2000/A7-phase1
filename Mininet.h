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
private:
	int totalNetCredit;
	CommandHandler* manageCommand;
	vector<Customer*> customers;
	vector<Publisher*> publisher;
	vector<Purchase*> purchases;

};



#endif