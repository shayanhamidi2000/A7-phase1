#include "Customer.h"
#include "Exceptions.h"
#include <iostream>
#include <algorithm>
#include "Publisher.h"

using namespace std;

Customer::Customer(string username , string password , string email , unsigned int id , unsigned int age){
	this->username = username;
	this->password = password;
	this->email = email;
	this->id = id;
	this->age = age;
	this->isPublisher = false;
	credit = 0;
}

string Customer::getUsername() const {
 	return username;
}

string Customer::getPassword() const { 
	return password; 
}

string Customer::getEmail() const {
 	return email;
 }

unsigned int Customer::getId() const{ 
	return id;
}

unsigned int Customer::getAge() const {
 	return age;
}

unsigned int Customer::getCredit() const { 
	return credit; 
}

bool Customer::getPublishingState() const { 
	return isPublisher; 
}

void Customer::printYourself() const{
	cout << id << " | " << username << " | " << email;
}

void Customer::addToCredit(const unsigned int amount){
	credit += amount;
}

void Customer::withdrawCredit(const int amount){
	if( (credit -  amount) < 0 )
		throw PermissionDenialException();

	credit -= amount;
}

void Customer::getMessage(Message* newMessage){
	this->unreadMessages.push(newMessage);
}

void Customer::sendMessageTo(Customer* messageReciever , string content){
	Message* newMessage = new Message(content);
	messageReciever->getMessage(newMessage);
}

void Customer::sendMessageToFollowedPublisher(Publisher* followedPublisher){
	string newFollowMessage = "User " + username + " with id " + to_string(id) + " follow you.";
	sendMessageTo(followedPublisher , newFollowMessage);
}

void Customer::sendMessageToBoughtFromPublisher(const Film* boughtFilm){
	string newBuyMessage = "User " + username + " with id " + to_string(id) + " buy your film " + boughtFilm->getName() + " with id " + to_string(boughtFilm->getId() ) + ".";
	sendMessageTo(boughtFilm->getOwner() , newBuyMessage);
}

void Customer::sendMessageToRatedPublisher(const Film* ratedFilm){
	string newRateMessage = "User " + username + " with id " + to_string(id) + " rate your film " + ratedFilm->getName() + " with id " + to_string(ratedFilm->getId() ) + ".";
	sendMessageTo(ratedFilm->getOwner() , newRateMessage);
}


void Customer::buyNewFilm(Film* newFilm){
	withdrawCredit(newFilm->getPrice() );
	purchasedFilms.push_back(newFilm);
	sendMessageToBoughtFromPublisher(newFilm);
}

bool Customer::hasFilm(Film* newFilm){
	if(find(purchasedFilms.begin() , purchasedFilms.end() , newFilm) == purchasedFilms.end() )
		return false;
	return true;
}

vector<Film*> Customer::getPurchasedFilms() const{
	return purchasedFilms;
} 
