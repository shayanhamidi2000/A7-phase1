#include "Publisher.h"
#include <algorithm>

using namespace std;

Publisher::Publisher(string username , string password , string email , unsigned int id , unsigned int age)
	: Customer(username , password , email , id , age) {
		isPublisher = true;
}

void Publisher::notifyFollowersOnNewUpload(){

}

void Publisher::addToUploadedFilms(Film* newFilm) { 
	uploadedFilms.push_back(newFilm);
	notifyFollowersOnNewUpload();
}

void Publisher::addToFollowers(Customer* newFollower) { 
	followers.push_back(newFollower); 
}

void Publisher::deleteMyFilm(unsigned int elementPosition){
	uploadedFilms.erase(uploadedFilms.begin() + elementPosition);
}

vector<Film*> Publisher::getUploadedFilms() const { 
	return uploadedFilms;
}