#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include <vector>
#include "Customer.h"
#include "Film.h"

class Publisher : public Customer {
private:
	std::vector<Film*> uploadedFilms;
	std::vector<Customer*> followers;
public:
	Publisher(std::string username , std::string password , std::string email , unsigned int id , unsigned int age);
	virtual void addToUploadedFilms(Film* newFilm);
	virtual void addToFollowers(Customer* newFollower);
	virtual std::vector<Film*> getUploadedFilms() const;
	virtual void deleteMyFilm(unsigned int elementPosition);
	virtual void notifyFollowersOnNewUpload();
};

#endif