#include "Mininet.h"
#include "Config.h"
#include "Exceptions.h"
#include "Film.h"
#include <iostream>
#include <string>


MiniNet::MiniNet(){
	totalNetCredit = 0;
	theIdsAssigned = BASIC_ID_VALUE; 
	onlineUser = nullptr;
	manageCommand = new CommandHandler(this);
	films = new FilmRepository();
}

bool MiniNet::isOnlineUserPublisher() { 
	return onlineUser->getPublishingState();
}

bool MiniNet::isAnyOneOnline() {
	if(onlineUser != nullptr)
		return true;
	return false;
}

void MiniNet::goToNextId() {
 	theIdsAssigned++; 
}

void MiniNet::startNet(){
	string line = "";
	while(getline(cin , line)){
		try{
			manageCommand->getRawCommand(line);
		}catch(exception& ex){
			cout << ex.what() << endl;
		}
	}
}

void MiniNet::checkIdExistence(unsigned int id){
	if(findUserById(id) == nullptr)
		throw NotFoundException();
}

Customer* MiniNet::findUserByUsername(string username){
	for(unsigned int i = 0 ; i < users.size() ; i++)
		if(users[i]->getUsername() == username)
			return users[i];

	return nullptr;
}

Customer* MiniNet::findUserById(unsigned int id){
	for(unsigned int i = 0 ; i < users.size() ; i++)
		if(users[i]->getId() == id)
			return users[i];

	return nullptr;
}

void MiniNet::checkUsernameRepetition(string username){
	if(findUserByUsername(username) != nullptr)
		throw BadRequestException();		
}

void MiniNet::registerUser(string email , string username , string password , unsigned int age , bool isPublisher){
	checkUsernameRepetition(username);
	if(isPublisher)
		onlineUser = new Publisher(username , password , email , theIdsAssigned , age);
	else
		onlineUser = new Customer(username , password , email , theIdsAssigned , age);

	users.push_back(onlineUser);
	this->goToNextId();
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::isUsernameMatchingPassword(string username , string password){
	if(findUserByUsername(username)->getPassword() != password)
		throw BadRequestException();

}
void MiniNet::isUsernameExisted(string username){
	if(findUserByUsername(username) == nullptr)
		throw BadRequestException();

}

void MiniNet::loginUser(string username , string password){
	isUsernameExisted(username);
	isUsernameMatchingPassword(username , password);
	this->onlineUser = findUserByUsername(username);

	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::addFilmOnNet(string name , unsigned int year , string director , string summary , unsigned int price , unsigned int length){
	if(!isAnyOneOnline() || !isOnlineUserPublisher())
		throw PermissionDenialException();

	films->addNewFilm((Publisher*) this->onlineUser , name , year , director , summary , price , length);
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::editAFilm(unsigned int id , string newName , unsigned int newYear , unsigned int newLength , string newSummary , string newDirector){
	if(!isAnyOneOnline() || !isOnlineUserPublisher())
		throw PermissionDenialException();

	films->editFilm((Publisher*) this->onlineUser , id , newName , newYear , newLength , newSummary , newDirector);
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::deleteAFilm(unsigned int id){
	if(!isAnyOneOnline() || !isOnlineUserPublisher())
		throw PermissionDenialException();

	films->deleteFilm((Publisher*) this->onlineUser , id );
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::getPublishedList(string name , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , string directorName){
	if(!isAnyOneOnline() || !isOnlineUserPublisher())
		throw PermissionDenialException();

	films->searchFilmWithFactorsInAList( ((Publisher*) onlineUser)->getUploadedFilms() , name , minPoint , minYear , price , maxYear , directorName);
}

void MiniNet::getFollowersList(){
	if(!isAnyOneOnline() || !isOnlineUserPublisher())
		throw PermissionDenialException();

	((Publisher*) onlineUser)->printYourFollowers();
}

void MiniNet::follow(unsigned int id){
	if(!isAnyOneOnline())
		throw PermissionDenialException();

	checkIdExistence(id);
	if(!findUserById(id)->getPublishingState() )
		throw BadRequestException();

	Publisher* followed = (Publisher*) findUserById(id);
	followed->addToFollowers(onlineUser);
	cout << SUCCESS_MESSAGE << endl;	
}

void MiniNet::addMoney(unsigned int amount){
	if(!isAnyOneOnline() )
		throw PermissionDenialException();
	onlineUser->addToCredit(amount);
	cout << SUCCESS_MESSAGE << endl;
}

