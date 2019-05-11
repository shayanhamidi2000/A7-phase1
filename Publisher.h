#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include <vector>
#include "Customer.h"

using namespace std;

class Publisher : public Customer {
private:
	vector<Film*> uploadedFilms;
	vector<Customer*> followers;
public:
	Publisher(string username , string password , string email , unsigned int id , unsigned int age);
};

#endif