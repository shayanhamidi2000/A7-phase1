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
	//
	bool checkFollowerRepitition(unsigned int newFollowerId);
	void sortFollowersById();
public:
	Publisher(std::string username , std::string password , std::string email , unsigned int id , unsigned int age);
	std::vector<Film*> getUploadedFilms() const;
	void addToUploadedFilms(Film* newFilm);
	void addToFollowers(Customer* newFollower);
	void deleteMyFilm(unsigned int elementPosition);
	void notifyFollowersOnNewUpload();
	void printYourFollowers() const;
};

#endif