#include "Publisher.h"

using namespace std;

Publisher::Publisher(string username , string password , string email , unsigned int id , unsigned int age)
	: Customer(username , password , email , id , age) {
		isPublisher = true;
}

void Publisher::notifyFollowersOnNewUpload(){

}

void Publisher::addToUploadedFilms(Film* newFilm) { 
	uploadedFilms.push_back(newFilm);
}

void Publisher::addToFollowers(Customer* newFollower) { 
	followers.push_back(newFollower); 
}

vector<Film*> Publisher::getUploadedFilms() const { 
	return uploadedFilms;
}