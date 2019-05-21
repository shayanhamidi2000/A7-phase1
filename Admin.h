#ifndef ADMIN_H
#define ADMIN_H

#include "Customer.h"
#include "Config.h"
#include <string>
using namespace std;

class MiniNet;

class Admin : public Customer{
public:
	Admin(std::string password , MiniNet* miniNetAccess);
	virtual void showCredit() const;
private: 
	MiniNet* miniNetAccess;
};


#endif