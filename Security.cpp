#include "Security.h"
#include "Exceptions.h"
using namespace std;

string Security::hashPassword(const string& rawPassword , const string& salt){
	string hashedPassword = rawPassword + salt;
	for(unsigned int i = 0 ; i < hashedPassword.length() ; i++)
		if(i % 2 == 1)
			hashedPassword[i]++;

	return hashedPassword;	
}

void Security::isUsernameMatchingPassword(const vector<Customer*>& allUsers , string username , string password){
	if(!findUserByUsername(allUsers , username)->hasPassword(this->hashPassword(password , username) ) )
		throw PasswordNotMatchingUsernameException();

}

void Security::isUsernameExisted(const vector<Customer*>& allUsers , string username){
	if(findUserByUsername(allUsers , username) == nullptr)
		throw UsernameNotExistedException();

}

Customer* Security::findUserById(const vector<Customer*>& allUsers , unsigned int id){
	for(unsigned int i = 0 ; i < allUsers.size() ; i++)
		if(allUsers[i]->getId() == id)
			return allUsers[i];

	return nullptr;
}

void Security::checkUsernameRepetition(const vector<Customer*>& allUsers , string username){
	if(findUserByUsername(allUsers , username) != nullptr)
		throw RepeatedUsernameException();		
}

void Security::checkIdExistence(const vector<Customer*>& allUsers , unsigned int id){
	if(findUserById(allUsers , id) == nullptr)
		throw NotFoundException();
}

Customer* Security::findUserByUsername(const vector<Customer*>& allUsers , string username){
	for(unsigned int i = 0 ; i < allUsers.size() ; i++)
		if(allUsers[i]->getUsername() == username)
			return allUsers[i];

	return nullptr;
}

