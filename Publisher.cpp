#include "Publisher.h"
#include "Exceptions.h"
#include <iostream>
#include <algorithm>

using namespace std;

Publisher::Publisher(string username , string password , string email , unsigned int id , unsigned int age)
	: Customer(username , password , email , id , age) {
		isPublisher = true;
}

void Publisher::notifyFollowersOnNewUpload() const{

}

void Publisher::addToUploadedFilms(Film* newFilm) { 
	uploadedFilms.push_back(newFilm);
	notifyFollowersOnNewUpload();
}

void Publisher::addToFollowers(Customer* newFollower) { 
	if(newFollower == this)
		throw BadRequestException();
	if(!checkFollowerRepitition(newFollower->getId() ) ){
		followers.push_back(newFollower); 
		sortFollowersById();
	}	
}

bool Publisher::checkFollowerRepitition(unsigned int newFollowerId){
	for(unsigned int i = 0 ; i < followers.size() ; i++)
		if(followers[i]->getId() == newFollowerId)
			return true;

	return false;		
}

bool idComparator(const Customer* customer1 , const Customer* customer2){
	return (customer1->getId() < customer2->getId() );
}

void Publisher::sortFollowersById(){
	sort(followers.begin() , followers.end() , idComparator);
}

void Publisher::deleteMyFilm(unsigned int elementPosition){
	uploadedFilms.erase(uploadedFilms.begin() + elementPosition);
}

vector<Film*> Publisher::getUploadedFilms() const { 
	return uploadedFilms;
}

void Publisher::printYourFollowers() const{
	cout << "List of Followers" << endl;
	cout << "#. User Id | User Username | User Email" << endl;
	for(unsigned int i = 0 ; i < followers.size() ; i++){
		cout << i + 1 << ". ";
		followers[i]->printYourself();
		cout << endl;
	}
}