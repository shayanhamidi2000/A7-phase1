#ifndef SECURITY_H
#define SECURITY_H

#include <string>
#include <vector>
#include "Customer.h"

class Security{
public:
	std::string hashPassword(const std::string& rawPassword , const std::string& salt);
	Customer* findUserByUsername(const std::vector<Customer*>& allUsers , std::string username);
	Customer* findUserById(const std::vector<Customer*>& allUsers , unsigned int id);
	void checkUsernameRepetition(const std::vector<Customer*>& allUsers , std::string username);
	void isUsernameMatchingPassword(const std::vector<Customer*>& allUsers , std::string username , std::string password);
	void isUsernameExisted(const std::vector<Customer*>& allUsers , std::string username);
	void checkIdExistence(const std::vector<Customer*>& allUsers , unsigned int id);
};


#endif