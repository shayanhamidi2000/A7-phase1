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
	this->isAdmin = false;
	credit = 0;
}

Customer::~Customer(){
	while(!allMessages.empty() )
		unreadMessages.pop();
	allMessages.clear();
}

string Customer::getUsername() const {
 	return username;
}

bool Customer::hasPassword(const string& assertedPassword) const{
	if(this->password == assertedPassword)
		return true;

	return false;
}

unsigned int Customer::getId() const{ 
	return id;
}

bool Customer::getPublishingState() const { 
	return isPublisher; 
}

bool Customer::getAdminState() const{
	return isAdmin;
}


void Customer::printYourself() const{
	cout << id << " | " << username << " | " << email;
}

void Customer::addToCredit(const unsigned int amount){
	credit += amount;
}

void Customer::withdrawCredit(const int amount){
	if( (credit -  amount) < 0 )
		throw NotEnoughMoneyException();

	credit -= amount;
}

string Customer::showCredit() const {
	return to_string(credit);
}


void Customer::getMessage(Message* newMessage){
	this->unreadMessages.push(newMessage);
}

void Customer::sendMessageTo(Customer* messageReciever , string content) const{
	Message* newMessage = new Message(content);
	messageReciever->getMessage(newMessage);
}

void Customer::sendMessageToCommentedPublisher(const Film* commentedFilm) const{
	string newCommentMessage = "User " + username + " with id " + to_string(id) + " comment on your film " + commentedFilm->getName() + " with id " + to_string(commentedFilm->getId() ) + ".";
	sendMessageTo(commentedFilm->getOwner() , newCommentMessage);
}


void Customer::sendMessageToFollowedPublisher(Publisher* followedPublisher) const{
	string newFollowMessage = "User " + username + " with id " + to_string(id) + " follow you.";
	sendMessageTo(followedPublisher , newFollowMessage);
}

void Customer::sendMessageToBoughtFromPublisher(const Film* boughtFilm) const{
	string newBuyMessage = "User " + username + " with id " + to_string(id) + " buy your film " + boughtFilm->getName() + " with id " + to_string(boughtFilm->getId() ) + ".";
	sendMessageTo(boughtFilm->getOwner() , newBuyMessage);
}

void Customer::sendMessageToRatedPublisher(const Film* ratedFilm) const{
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

void Customer::showUnreadMessages(){
	unsigned int messageCounter = 1;
	vector<Message*> newlyReadMessages;

	cout << "#. Notification Message" << endl;
	while(!unreadMessages.empty()){
		cout << messageCounter << ". ";
		unreadMessages.top()->printYourself();
		cout << endl;
		newlyReadMessages.push_back(unreadMessages.top() );
		unreadMessages.pop();
		messageCounter++;
	}

	transferNewlyReadMessagesToReadMessages(newlyReadMessages);
}

void Customer::transferNewlyReadMessagesToReadMessages(vector<Message*> newlyReadMessages){
	vector<Message*> modifiedAllMessages = newlyReadMessages;
	modifiedAllMessages.insert(modifiedAllMessages.end() , allMessages.begin() , allMessages.end() );
	allMessages = modifiedAllMessages;
}

void Customer::showReadMessages(const unsigned int limit){
	cout << "#. Notification Message" << endl;
	for(unsigned int i = 0 ; i < allMessages.size() ; i++){
		if(i == limit)
			break;
		cout << i + 1 << ". ";
		allMessages[i]->printYourself();
		cout << endl;
	}
}

