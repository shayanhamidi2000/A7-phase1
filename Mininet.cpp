#include "Mininet.h"
#include "Config.h"
#include "Exceptions.h"
#include "Film.h"
#include "Admin.h"
#include "Handlers.h"
#include <iostream>
#include <string>


MiniNet::MiniNet(){
	totalNetCredit = 0;
	theIdsAssigned = BASIC_ID_VALUE; 
	onlineUser = nullptr;
	systemSecurity = new Security();
	films = new FilmRepository();
	users.push_back(new Admin(systemSecurity->hashPassword(ADMIN_DEFAULT_PASSWORD , ADMIN_DEFAULT_USERNAME) , this) );
}

MiniNet::~MiniNet(){
	delete systemSecurity;
	films->~FilmRepository();
	purchases.clear();
	users.clear();
}

unsigned int MiniNet::getTotalNetCredit() const{
	return totalNetCredit;
}


void MiniNet::addToNetCredit(unsigned int amount){
	totalNetCredit += amount;
}

void MiniNet::withdrawNetCredit(unsigned int amount){
	totalNetCredit -= amount;
}

bool MiniNet::isOnlineUserPublisher() { 
	return onlineUser->getPublishingState();
}

bool MiniNet::isOnlineUserAdmin(){
	return onlineUser->getAdminState();
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
	try {
    Server server(PORT_SERVER_RUNNING);
    server.setNotFoundErrPage("static/404.html");
    server.get("/" , new ShowPage("static/login.html") );
    server.get("/register" , new ShowPage("static/register.html") );
    server.post("/register" , new RegisterHandler(this));
    server.run();
  	} catch (Server::Exception e) {
    	cerr << e.getMessage() << endl;
  	}
}

void MiniNet::showCredit(){
	if(!isAnyOneOnline() )
		throw PermissionDenialException();
	onlineUser->showCredit();

}


void MiniNet::registerUser(string email , string username , string password , unsigned int age , bool isPublisher){
	if(isAnyOneOnline() )
		throw BadRequestException();
	systemSecurity->checkUsernameRepetition(users , username);
	Customer* newUser;
	if(isPublisher)
		newUser = new Publisher(username , systemSecurity->hashPassword(password , username) , email , theIdsAssigned , age);
	else
		newUser = new Customer(username , systemSecurity->hashPassword(password , username) , email , theIdsAssigned , age);

	users.push_back(newUser);
	this->goToNextId();
}

void MiniNet::loginUser(string username , string password){
	if(isAnyOneOnline() )
		throw BadRequestException();
	systemSecurity->isUsernameExisted(users , username);
	systemSecurity->isUsernameMatchingPassword(users , username , password);
	this->onlineUser = systemSecurity->findUserByUsername(users , username);

}

void MiniNet::logout(){
	if(!isAnyOneOnline() )
		throw BadRequestException();
	onlineUser = nullptr;
}


void MiniNet::addFilmOnNet(string name , unsigned int year , string director , string summary , unsigned int price , unsigned int length){
	if(!isAnyOneOnline() || !isOnlineUserPublisher() || isOnlineUserAdmin())
		throw PermissionDenialException();

	films->addNewFilm((Publisher*) this->onlineUser , name , year , director , summary , price , length);
}

void MiniNet::editAFilm(unsigned int id , string newName , unsigned int newYear , unsigned int newLength , string newSummary , string newDirector){
	if(!isAnyOneOnline() || !isOnlineUserPublisher() || isOnlineUserAdmin())
		throw PermissionDenialException();

	films->editFilm((Publisher*) this->onlineUser , id , newName , newYear , newLength , newSummary , newDirector);

}

void MiniNet::deleteAFilm(unsigned int id){
	if(!isAnyOneOnline() || !isOnlineUserPublisher() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	films->deleteFilm((Publisher*) this->onlineUser , id );
}

void MiniNet::getPublishedList(string name , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , string directorName){
	if(!isAnyOneOnline() || !isOnlineUserPublisher() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	films->getPublihsedOrPurchasedList( ((Publisher*) onlineUser)->getUploadedFilms() , name , minPoint , minYear , price , maxYear , directorName);
}

void MiniNet::getFollowersList(){
	if(!isAnyOneOnline() || !isOnlineUserPublisher() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	((Publisher*) onlineUser)->printYourFollowers();
}

void MiniNet::follow(unsigned int id){
	if(!isAnyOneOnline() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	systemSecurity->checkIdExistence(users , id);
	if(!systemSecurity->findUserById(users , id)->getPublishingState() )
		throw PermissionDenialException();

	Publisher* followed = (Publisher*) systemSecurity->findUserById(users , id);
	followed->addToFollowers(onlineUser);
	onlineUser->sendMessageToFollowedPublisher(followed);
}

void MiniNet::addMoney(unsigned int amount){
	if(!isAnyOneOnline() || isOnlineUserAdmin() )
		throw PermissionDenialException();
	onlineUser->addToCredit(amount);
}

void MiniNet::buyFilm(unsigned int filmId){
	if(!isAnyOneOnline() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);

	if(!onlineUser->hasFilm(desiredFilm) ){
		vector<Film*> purchasedFilmsTillNow = onlineUser->getPurchasedFilms();
		onlineUser->buyNewFilm(desiredFilm);
		films->updateFilmsGraph(desiredFilm ,  purchasedFilmsTillNow);
		addToNetCredit(desiredFilm->getPrice() );
		purchases.push_back(new Purchase(desiredFilm->getPrice() , desiredFilm->getRatingQuality() , desiredFilm->getOwner() ) );
	}

}

unsigned int MiniNet::getPublisherSoldFilmsMoney(){
	double earnedMoney = 0;
	vector<unsigned int> publisherPurchases;
	for(unsigned int i = 0 ; i < purchases.size() ; i++){
		if(purchases[i]->getFilmOwner() == this->onlineUser){
			earnedMoney += purchases[i]->calculateFilmOwnerShare();
			publisherPurchases.push_back(i);
		}
	}
	withdrawNetCredit((int) earnedMoney);
	deleteOverduedPurchases(publisherPurchases);
	return (int) earnedMoney;
}

void MiniNet::deleteOverduedPurchases(vector<unsigned int> overduedPurchases){
	for(unsigned int i = 0 ; i < overduedPurchases.size() ; i++){
		delete purchases[overduedPurchases[i] ];
		purchases.erase(purchases.begin() + overduedPurchases[i] );
		overduedPurchases = decreaseEachIndexByOne(overduedPurchases);
	}
}

vector<unsigned int> MiniNet::decreaseEachIndexByOne(vector<unsigned int> anIndexVector){
	vector<unsigned int> modifiedVector = anIndexVector;
	for(unsigned int i = 0 ; i < modifiedVector.size() ; i++)
		modifiedVector[i]--;

	return modifiedVector;
}

void MiniNet::getMoneyFromNet(){
	if(!isAnyOneOnline() || !isOnlineUserPublisher() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	onlineUser->addToCredit(getPublisherSoldFilmsMoney() );
}

void MiniNet::getPurchasedList(string name , unsigned int minYear , unsigned int price , unsigned maxYear , string directorName){
	if(!isAnyOneOnline() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	films->getPublihsedOrPurchasedList( onlineUser->getPurchasedFilms() , name , NOT_A_FACTOR , minYear , price , maxYear , directorName);
}

void MiniNet::rateFilm(unsigned int filmId , unsigned int score){
	if(!isAnyOneOnline() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	films->checkFilmPurchased(onlineUser , filmId);
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->rate(onlineUser , score);
	onlineUser->sendMessageToRatedPublisher(desiredFilm);
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::comment(unsigned int filmId , string commentContent){
	if(!isAnyOneOnline() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	films->checkFilmPurchased(onlineUser , filmId);
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->newComment(onlineUser , commentContent);
	onlineUser->sendMessageToCommentedPublisher(desiredFilm);
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::replyComment(unsigned int filmId , unsigned int commentId , string content){
	if(!isAnyOneOnline() || !isOnlineUserPublisher() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	films->checkFilmOwnership( (Publisher*)onlineUser , filmId);
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->replyOneComment(commentId , content);
	((Publisher*) onlineUser)->notifyCommenterOnReply(desiredFilm->findCommentById(commentId)->getCommentOwner() );
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::deleteComment(unsigned int filmId , unsigned int commentId){
	if(!isAnyOneOnline() || !isOnlineUserPublisher() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	films->checkFilmOwnership( (Publisher*) onlineUser , filmId);
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->deleteOneComment(commentId);
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::getUnreadMessages(){
	if(!isAnyOneOnline() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	onlineUser->showUnreadMessages();
}

void MiniNet::getAllMessages(unsigned int limit){
	if(!isAnyOneOnline() || isOnlineUserAdmin() )
		throw PermissionDenialException();

	onlineUser->showReadMessages(limit);
}

void MiniNet::searchFilmsInDatabase(string name , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , string directorName){
	if(!isAnyOneOnline()|| isOnlineUserAdmin() )
		throw PermissionDenialException();

	films->getSearchedDatabaseList(name , minPoint , minYear , price , maxYear , directorName);
}

void MiniNet::showFurtherInfo(unsigned int filmId){
	if(!isAnyOneOnline()|| isOnlineUserAdmin() )
		throw PermissionDenialException();

	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->printDetailedVersionOfYourself();
	cout << endl;
	films->giveRecommendation(onlineUser , desiredFilm);
}