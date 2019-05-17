#include "Customer.h"
#include <iostream>

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

void Customer::getMessage(Message* newMessage){
	this->unreadMessages.push(newMessage);
}

void Customer::sendMessageTo(Customer* messageReciever , string content){
	Message* newMessage = new Message(content);
	messageReciever->getMessage(newMessage);
}

void Customer::sendMessageToFollowedPublisher(Customer* followedPublisher){
	string newFollowMessage = "User " + username + " with id " + to_string(id) + " follow you.";
	sendMessageTo(followedPublisher , newFollowMessage);
}

void Customer::sendMessageToBoughtFromPublisher(Customer* boughtFromPublisher , const Film* boughtFilm){
	string newBuyMessage = "User " + username + " with id " + to_string(id) + " buy your film " + boughtFilm->getName() + " with id " + to_string(boughtFilm->getId() ) + ".";
	sendMessageTo(boughtFromPublisher , newBuyMessage);
}
