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
	delete films;
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
    server.get("/css" , new ShowPage("static/MYCSS.css") );
    server.post("/home" , new FilterFilmsHanlder(this) );
    server.get("/logout" , new LogoutHandler() );
    server.get("/addFilm" , new ShowPage("static/addFilm.html") );
    server.post("/addFilm" , new AddFilmHandler(this) );
    server.post("/deleteFilm" , new DeleteFilmHandler(this) );
    server.get("/profile" , new ProfilePageHandler(this) );
    server.post("/chargeAccount" , new ChargeMoneyHandler(this) );
    server.post("/seeFurther" , new MoreInfoPageHandler(this) );
    server.post("/buyFilm" , new BuyFilmHandler(this) );
    server.post("/rateFilm" , new RateFilmHandler(this) );
    server.post("/newComment" , new NewCommentHandler(this) );
    server.run();
  	} catch (Server::Exception e) {
    	cerr << e.getMessage() << endl;
  	}
}

string MiniNet::showCredit(){
	return requestingUser->showCredit();
}

bool MiniNet::hasRequestingUserMoneyForFilm(unsigned int id){
	return requestingUser->hasMoney(films->findFilmByIdInDatabase(id)->getPrice() );
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

string MiniNet::loadHomePageDatas(string director){
	string homePageDatas;
	if(isRequestingUserPublisher() ){
		homePageDatas += getPublishedList(director , 0 , 0 , 0 , 0 , "");
		homePageDatas += "<br><br><br>";
	}

	homePageDatas += searchFilmsInDatabase(director , 0 , 0 , 0 , 0 , "");
	return homePageDatas;
}

bool MiniNet::hasRequestingUserBoughtThisFilm(unsigned int id){
	return films->checkFilmPurchased(requestingUser , id);
}



void MiniNet::addFilmOnNet(string name , unsigned int year , string director , string summary , unsigned int price , unsigned int length){
	films->addNewFilm((Publisher*) this->requestingUser , name , year , director , summary , price , length);
}

void MiniNet::editAFilm(unsigned int id , string newName , unsigned int newYear , unsigned int newLength , string newSummary , string newDirector){
	films->editFilm((Publisher*) this->requestingUser , id , newName , newYear , newLength , newSummary , newDirector);

}

void MiniNet::deleteAFilm(unsigned int id){
	films->deleteFilm((Publisher*) this->requestingUser , id );
}

string MiniNet::getPublishedList(string directorName , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned int maxYear , string name){
	string publishedFilmsDatas = "<table id='Films'>";
	publishedFilmsDatas += "<caption>The Films You have Uploaded</caption>";
	publishedFilmsDatas += films->getPublihsedList( ((Publisher*) requestingUser)->getUploadedFilms() , name , minPoint , minYear , price , maxYear , directorName);
	publishedFilmsDatas += "</table>";
	return publishedFilmsDatas;
}

void MiniNet::getFollowersList(){
	((Publisher*) requestingUser)->printYourFollowers();
}

void MiniNet::follow(unsigned int id){
	systemSecurity->checkIdExistence(users , id);
	Publisher* followed = (Publisher*) systemSecurity->findUserById(users , id);
	followed->addToFollowers(requestingUser);
	requestingUser->sendMessageToFollowedPublisher(followed);
}

void MiniNet::addMoney(unsigned int amount){
	requestingUser->addToCredit(amount);
}

void MiniNet::buyFilm(unsigned int filmId){
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
	requestingUser->addToCredit(getPublisherSoldFilmsMoney() );
}

string MiniNet::getPurchasedList(string name , unsigned int minYear , unsigned int price , unsigned int maxYear , string directorName){
	string purchasedFilmsDatas = "<table id='Films'>";
	purchasedFilmsDatas += "<caption>The Films You Bought</caption>";
	purchasedFilmsDatas += films->getPurchasedList( requestingUser->getPurchasedFilms() , name , NOT_A_FACTOR , minYear , price , maxYear , directorName);
	purchasedFilmsDatas += "</table>";
	return purchasedFilmsDatas;
}

void MiniNet::rateFilm(unsigned int filmId , unsigned int score){
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->rate(requestingUser , score);
	requestingUser->sendMessageToRatedPublisher(desiredFilm);
}

void MiniNet::comment(unsigned int filmId , string commentContent){
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->newComment(requestingUser , commentContent);
	requestingUser->sendMessageToCommentedPublisher(desiredFilm);
}

void MiniNet::replyComment(unsigned int filmId , unsigned int commentId , string content){
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->replyOneComment(commentId , content);
	((Publisher*) requestingUser)->notifyCommenterOnReply(desiredFilm->findCommentById(commentId)->getCommentOwner() );
}

void MiniNet::deleteComment(unsigned int filmId , unsigned int commentId){
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	desiredFilm->deleteOneComment(commentId);
}

void MiniNet::getUnreadMessages(){
	requestingUser->showUnreadMessages();
}

void MiniNet::getAllMessages(unsigned int limit){
	requestingUser->showReadMessages(limit);
}

string MiniNet::searchFilmsInDatabase(string directorName  , unsigned int minPoint , unsigned int minYear  , unsigned int price , unsigned int maxYear , string name ){
	string searchedFilmsDatas = "<table id='Films'>";
	searchedFilmsDatas += "<caption>The Films On The Net</caption>";
	searchedFilmsDatas += films->getSearchedDatabaseList(name , minPoint , minYear , price , maxYear , directorName);
	searchedFilmsDatas += "</table>";
	return searchedFilmsDatas;
}

string MiniNet::showFurtherInfo(unsigned int filmId){
	string filmFurtherInfo;
	Film* desiredFilm = films->findFilmByIdInDatabase(filmId);
	filmFurtherInfo += desiredFilm->printDetailedVersionOfYourself();
	filmFurtherInfo += "<br><br><br>";
	filmFurtherInfo += "<center><table id='Films2'>";
	filmFurtherInfo += "<caption>Recommended Films</caption>";
	filmFurtherInfo += films->giveRecommendation(requestingUser , desiredFilm);
	filmFurtherInfo += "</table></center><br><br>";
	return filmFurtherInfo;
}