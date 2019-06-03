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
	requestingUser = nullptr;
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

void MiniNet::updateRequestingUser(string newRequestingUsername){
	this->requestingUser = systemSecurity->findUserByUsername(users , newRequestingUsername);
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

bool MiniNet::isRequestingUserPublisher() { 
	return requestingUser->getPublishingState();
}

bool MiniNet::isrequestingUserAdmin(){
	return requestingUser->getAdminState();
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
    server.post("/" , new LoginHandler(this));
    server.get("/home" , new HomePageHandler(this) );
    server.get("/logout" , new LogoutHandler() );
    server.get("/addFilm" , new ShowPage("static/addFilm.html") );
    server.post("/addFilm" , new AddFilmHandler(this) );
    server.post("/deleteFilm" , new DeleteFilmHandler(this) );
    server.get("/profile" , new ProfilePageHandler(this) );
    server.post("/chargeAccount" , new ChargeMoneyHandler(this) );
    server.run();
  	} catch (Server::Exception e) {
    	cerr << e.getMessage() << endl;
  	}
}

string MiniNet::showCredit(){
	return requestingUser->showCredit();
}


void MiniNet::registerUser(string email , string username , string password , unsigned int age , bool isPublisher){
	systemSecurity->checkUsernameRepetition(users , username);
	Customer* newUser;
	if(isPublisher)
		newUser = new Publisher(username , systemSecurity->hashPassword(password , username) , email , theIdsAssigned , age);
	else
		newUser = new Customer(username , systemSecurity->hashPassword(password , username) , email , theIdsAssigned , age);

	this->requestingUser = newUser;
	users.push_back(newUser);
	this->goToNextId();
}

void MiniNet::loginUser(string username , string password){
	systemSecurity->isUsernameExisted(users , username);
	systemSecurity->isUsernameMatchingPassword(users , username , password);
	this->requestingUser = systemSecurity->findUserByUsername(users , username);

}

string MiniNet::loadHomePageDatas(){
	string homePageDatas;
	if(isRequestingUserPublisher() )
		homePageDatas += getPublishedList("" , 0 , 0 , 0 , 0 , "");

	homePageDatas += searchFilmsInDatabase("" , 0 , 0 , 0 , 0 , "");
	return homePageDatas;
}


void MiniNet::addFilmOnNet(string name , unsigned int year , string director , string summary , unsigned int price , unsigned int length){
	if(!isRequestingUserPublisher() || isrequestingUserAdmin())
		throw PermissionDenialException();

	films->addNewFilm((Publisher*) this->requestingUser , name , year , director , summary , price , length);
}

void MiniNet::editAFilm(unsigned int id , string newName , unsigned int newYear , unsigned int newLength , string newSummary , string newDirector){
	if(!isRequestingUserPublisher() || isrequestingUserAdmin())
		throw PermissionDenialException();

	films->editFilm((Publisher*) this->requestingUser , id , newName , newYear , newLength , newSummary , newDirector);

}

void MiniNet::deleteAFilm(unsigned int id){
	if(!isRequestingUserPublisher() || isrequestingUserAdmin() )
		throw PermissionDenialException();

	films->deleteFilm((Publisher*) this->requestingUser , id );
}

string MiniNet::getPublishedList(string directorName , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned int maxYear , string name){
	if(!isRequestingUserPublisher() || isrequestingUserAdmin() )
		throw PermissionDenialException();

	string publishedFilmsDatas = "<h1>The Films You have Uploaded</h1> <br>";
	publishedFilmsDatas += films->getPublihsedList( ((Publisher*) requestingUser)->getUploadedFilms() , name , minPoint , minYear , price , maxYear , directorName);
	return publishedFilmsDatas;
}

void MiniNet::getFollowersList(){
	if(!isRequestingUserPublisher() || isrequestingUserAdmin() )
		throw PermissionDenialException();

	((Publisher*) requestingUser)->printYourFollowers();
}

void MiniNet::follow(unsigned int id){
	if(isrequestingUserAdmin() )
		throw PermissionDenialException();

	systemSecurity->checkIdExistence(users , id);
	if(!systemSecurity->findUserById(users , id)->getPublishingState() )
		throw PermissionDenialException();

	Publisher* followed = (Publisher*) systemSecurity->findUserById(users , id);
	followed->addToFollowers(requestingUser);
	requestingUser->sendMessageToFollowedPublisher(followed);
}

void MiniNet::addMoney(unsigned int amount){
	if(isrequestingUserAdmin() )
		throw PermissionDenialException();
	requestingUser->addToCredit(amount);
}

void MiniNet::buyFilm(unsigned int filmId){
	if(isrequestingUserAdmin() )
		throw PermissionDenialException();

	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);

	if(!requestingUser->hasFilm(desiredFilm) ){
		vector<Film*> purchasedFilmsTillNow = requestingUser->getPurchasedFilms();
		requestingUser->buyNewFilm(desiredFilm);
		films->updateFilmsGraph(desiredFilm ,  purchasedFilmsTillNow);
		addToNetCredit(desiredFilm->getPrice() );
		purchases.push_back(new Purchase(desiredFilm->getPrice() , desiredFilm->getRatingQuality() , desiredFilm->getOwner() ) );
	}

}

unsigned int MiniNet::getPublisherSoldFilmsMoney(){
	double earnedMoney = 0;
	vector<unsigned int> publisherPurchases;
	for(unsigned int i = 0 ; i < purchases.size() ; i++){
		if(purchases[i]->getFilmOwner() == this->requestingUser){
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
	if(!isRequestingUserPublisher() || isrequestingUserAdmin() )
		throw PermissionDenialException();

	requestingUser->addToCredit(getPublisherSoldFilmsMoney() );
}

string MiniNet::getPurchasedList(string name , unsigned int minYear , unsigned int price , unsigned int maxYear , string directorName){
	if(isrequestingUserAdmin() )
		throw PermissionDenialException();

	string purchasedFilmsDatas = "<h1> The Films You Bought</h1><br>";
	purchasedFilmsDatas += films->getPurchasedList( requestingUser->getPurchasedFilms() , name , NOT_A_FACTOR , minYear , price , maxYear , directorName);
	return purchasedFilmsDatas;
}

void MiniNet::rateFilm(unsigned int filmId , unsigned int score){
	if(isrequestingUserAdmin() )
		throw PermissionDenialException();

	films->checkFilmPurchased(requestingUser , filmId);
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->rate(requestingUser , score);
	requestingUser->sendMessageToRatedPublisher(desiredFilm);
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::comment(unsigned int filmId , string commentContent){
	if(isrequestingUserAdmin() )
		throw PermissionDenialException();

	films->checkFilmPurchased(requestingUser , filmId);
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->newComment(requestingUser , commentContent);
	requestingUser->sendMessageToCommentedPublisher(desiredFilm);
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::replyComment(unsigned int filmId , unsigned int commentId , string content){
	if(!isRequestingUserPublisher() || isrequestingUserAdmin() )
		throw PermissionDenialException();

	films->checkFilmOwnership( (Publisher*)requestingUser , filmId);
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->replyOneComment(commentId , content);
	((Publisher*) requestingUser)->notifyCommenterOnReply(desiredFilm->findCommentById(commentId)->getCommentOwner() );
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::deleteComment(unsigned int filmId , unsigned int commentId){
	if(!isRequestingUserPublisher() || isrequestingUserAdmin() )
		throw PermissionDenialException();

	films->checkFilmOwnership( (Publisher*) requestingUser , filmId);
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->deleteOneComment(commentId);
	cout << SUCCESS_MESSAGE << endl;
}

void MiniNet::getUnreadMessages(){
	if(isrequestingUserAdmin() )
		throw PermissionDenialException();

	requestingUser->showUnreadMessages();
}

void MiniNet::getAllMessages(unsigned int limit){
	if(isrequestingUserAdmin() )
		throw PermissionDenialException();

	requestingUser->showReadMessages(limit);
}

string MiniNet::searchFilmsInDatabase(string directorName  , unsigned int minPoint , unsigned int minYear  , unsigned int price , unsigned int maxYear , string name ){
	if(isrequestingUserAdmin() )
		throw PermissionDenialException();

	string searchedFilmsDatas = "<h1>The Films On The Net</h1> <br>";
	searchedFilmsDatas += films->getSearchedDatabaseList(name , minPoint , minYear , price , maxYear , directorName);
	return searchedFilmsDatas;
}

void MiniNet::showFurtherInfo(unsigned int filmId){
	if(isrequestingUserAdmin() )
		throw PermissionDenialException();

	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->printDetailedVersionOfYourself();
	cout << endl;
	films->giveRecommendation(requestingUser , desiredFilm);
}