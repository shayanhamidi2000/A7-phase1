#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include <vector>
#include "Customer.h"
#include "Film.h"

using namespace std;

class Publisher : public Customer {
private:
	vector<Film*> uploadedFilms;
	vector<Customer*> followers;
public:
	Publisher(string username , string password , string email , unsigned int id , unsigned int age);
	virtual void addToUploadedFilms(Film* newFilm) { uploadedFilms.push_back(newFilm); }
	virtual void addToFollowers(Customer* newFollower) { followers.push_back(newFollower); }
	virtual void notifyFollowersOnNewUpload();
};

#endif