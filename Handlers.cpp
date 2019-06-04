#include "Handlers.h"
#include "Mininet.h"
#include "Config.h"
#include "Exceptions.h"

using namespace std;

RegisterHandler::RegisterHandler(MiniNet* theMiniNet) : RequestHandler() {
	miniNetAccess = theMiniNet;
}

Response* RegisterHandler::callback(Request* request){
	try{
		if(request->getBodyParam(PASSWORD_KEY) != request->getBodyParam(CONFIRMED_PASSWORD_KEY) )
			throw Server::Exception("Password was retyped incorrectly!");

		bool isPublisher = false;
		if(request->getBodyParam(PUBLISHINGSTATE_KEY) == PUBLISHER )
			isPublisher = true;
			
		miniNetAccess->registerUser(request->getBodyParam(EMAIL_KEY) , request->getBodyParam(USERNAME_KEY) , request->getBodyParam(PASSWORD_KEY) 
			, stoi(request->getBodyParam(AGE_KEY)) , isPublisher);
	}catch(RepeatedUsernameException ex) {
		throw Server::Exception(ex.what() );
	}

	Response* response = Response::redirect("/home");
	response->setSessionId(request->getBodyParam(USERNAME_KEY) );
	return response;
}

LoginHandler::LoginHandler(MiniNet* theMiniNet) : RequestHandler() {
	miniNetAccess = theMiniNet;
}

Response* LoginHandler::callback(Request* request){
	try{
		miniNetAccess->loginUser(request->getBodyParam(USERNAME_KEY) , request->getBodyParam(PASSWORD_KEY) ); 
	}catch(exception& ex){
		throw Server::Exception(ex.what() );
	}

	Response* response = Response::redirect("/home");
	response->setSessionId(request->getBodyParam(USERNAME_KEY) );
	return response;
}

string accumulateHeadOfHtml(const string& body , const string& title){
	string modifiedBody = body;
	modifiedBody += "<head>";
 	modifiedBody += ("<title>" + title + "</title>");
    modifiedBody += "<style>";
    modifiedBody += "ul { list-style-type: none; margin: 0; padding: 0; overflow: hidden; background-color: #333; }";
	modifiedBody += "li { float: left; }";
    modifiedBody += "li a { display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none; }";
 	modifiedBody += "li a:hover { background-color: #111; }";
    modifiedBody += "</style>";
  	modifiedBody += "</head>";

	return modifiedBody;
}

string accumulateNavbar(const string& body , MiniNet* miniNetAccess){
	string modifiedBody = body;
	modifiedBody += "<ul>";
	modifiedBody += "<li><a class='active' href='/logout'>Logout</a></li>";
    modifiedBody += "<li><a class='active' href='/home'>Home</a></li>";
    modifiedBody += "<li><a class='active' href='/profile'>My Profile</a></li>";
    if(miniNetAccess->isRequestingUserPublisher() )
    	modifiedBody += "<li><a class='active' href='/addFilm'>Add Film On Net</a></li>";
	modifiedBody += "</ul>";

	return modifiedBody;
}

string makeFilterForm(){
	string filterForm;
	filterForm += "<form action='/home' method='post'>";
	filterForm += "<input type='text' placeholder='Director Name' name='director' value='' />";
	filterForm += "<button type='submit'> Filter </button>";
	filterForm += "</form>";
	filterForm += "<br>";

	return filterForm;
}

string accumulateBodyOfHtmlForHomePage(const string& body , const string& director , MiniNet* miniNetAccess){
	string modifiedBody = body;
	modifiedBody += "<body>";
	modifiedBody = accumulateNavbar(modifiedBody , miniNetAccess);
	modifiedBody += makeFilterForm();
	modifiedBody += "<div>"; 
	modifiedBody += miniNetAccess->loadHomePageDatas(director);
	modifiedBody += "</div>";
	modifiedBody += "</body>";

	return modifiedBody;
}

HomePageHandler::HomePageHandler(MiniNet* theMiniNet) : RequestHandler() {
	miniNetAccess = theMiniNet;
}

Response* HomePageHandler::callback(Request* request){
	Response* response = new Response();
	response->setHeader("Content-Type", "text/html");
	miniNetAccess->updateRequestingUser(request->getSessionId() );
	string body;
	body += "<!DOCTYPE html>";
    body += "<html>";
    body = accumulateHeadOfHtml(body , "Home");
    body = accumulateBodyOfHtmlForHomePage(body , "" , miniNetAccess);
    body += "</html>";
	response->setBody(body);

	return response;
}

Response* LogoutHandler::callback(Request* request){
	Response* response = Response::redirect("/");
	response->setSessionId("");
	return response;
}

AddFilmHandler::AddFilmHandler(MiniNet* theMiniNet) : RequestHandler() {
	miniNetAccess = theMiniNet;
}

Response* AddFilmHandler::callback(Request* request){
	miniNetAccess->updateRequestingUser(request->getSessionId() );
	miniNetAccess->addFilmOnNet(request->getBodyParam(FILM_NAME_KEY) , stoi(request->getBodyParam(FILM_YEAR_KEY) ) , request->getBodyParam(FILM_DIRECTOR_KEY) 
	, request->getBodyParam(FILM_SUMMARY_KEY) , stoi(request->getBodyParam(FILM_PRICE_KEY) ) , stoi(request->getBodyParam(FILM_LENGTH_KEY) ) );

	Response* response = Response::redirect("/home");
	return response;
}

DeleteFilmHandler::DeleteFilmHandler(MiniNet* theMiniNet) : RequestHandler() {
	miniNetAccess = theMiniNet;
}

Response* DeleteFilmHandler::callback(Request* request){
	miniNetAccess->updateRequestingUser(request->getSessionId() );
	miniNetAccess->deleteAFilm(stoi(request->getBodyParam(FILM_ID_KEY) ) );

	Response* response = Response::redirect("/home");
	return response;
}

ProfilePageHandler::ProfilePageHandler(MiniNet* theMiniNet) : RequestHandler() {
	miniNetAccess = theMiniNet;
}

Response* ProfilePageHandler::callback(Request* request){
	Response* response = new Response();
	response->setHeader("Content-Type", "text/html");
	miniNetAccess->updateRequestingUser(request->getSessionId() );
	string body;
	body += "<!DOCTYPE html>";
    body += "<html>";
    body = accumulateHeadOfHtml(body , "profile");
    body = accumulateBodyOfHtml(body);
    body += "</html>";

	response->setBody(body);
	return response;
}

std::string ProfilePageHandler::accumulateBodyOfHtml(const std::string& body){
	string modifiedBody = body;
	modifiedBody += "<body>";
	modifiedBody = accumulateNavbar(modifiedBody , miniNetAccess);
	
	
	modifiedBody += showCredit();
	modifiedBody += makeAccountChargeButton();
	modifiedBody += "<div>"; 
	modifiedBody += miniNetAccess->getPurchasedList("" , 0 , 0 , 0 , "");
	modifiedBody += "</div>";
	modifiedBody += "</body>";

	return modifiedBody;
}

string ProfilePageHandler::makeAccountChargeButton(){
	string chargeButton;
	chargeButton += "<form style='align = center;' action='/chargeAccount' method='post'>";
	chargeButton += "<input type='number' value='0' min='0' name='amount' placeholder='Charge Your Account!' />";
	chargeButton += "<button type='submit'>charge</button>";
	chargeButton += "</form>";
	chargeButton += "<br>";
	return chargeButton;
}

string ProfilePageHandler::showCredit(){
	string credit;
	credit += "<p style='align = center;'>";
	credit += "Your Credit:  ";
	credit += miniNetAccess->showCredit();
	credit += "</p>";
	credit += "<br>";
	return credit;
}

ChargeMoneyHandler::ChargeMoneyHandler(MiniNet* theMiniNet){
	miniNetAccess = theMiniNet;
}

Response* ChargeMoneyHandler::callback(Request* request){
	miniNetAccess->updateRequestingUser(request->getSessionId() );
	miniNetAccess->addMoney(stoi(request->getBodyParam(MONEY_AMOUNT_KEY) ) );

	Response* response = Response::redirect("/profile");
	return response;
}

FilterFilmsHanlder::FilterFilmsHanlder(MiniNet* theMiniNet){
	miniNetAccess = theMiniNet;
}

Response* FilterFilmsHanlder::callback(Request* request){
	Response* response = new Response();
	response->setHeader("Content-Type", "text/html");
	miniNetAccess->updateRequestingUser(request->getSessionId() );
	string body;
	body += "<!DOCTYPE html>";
    body += "<html>";
    body = accumulateHeadOfHtml(body , "Home");
    body = accumulateBodyOfHtmlForHomePage(body , request->getBodyParam(FILM_DIRECTOR_KEY) , miniNetAccess );
    body += "</html>";
	response->setBody(body);

	return response;
}

MoreInfoPageHandler::MoreInfoPageHandler(MiniNet* theMiniNet){
	miniNetAccess = theMiniNet;
}

Response* MoreInfoPageHandler::callback(Request* request){
	Response* response = new Response();
	response->setHeader("Content-Type" , "text/html");
	miniNetAccess->updateRequestingUser(request->getSessionId() );
	string body;
	body += "<!DOCTYPE html>";
    body += "<html>";
    body = accumulateHeadOfHtml(body , "See Further Info!");
    body = accumulateBodyOfHtml(body , stoi(request->getBodyParam(FILM_ID_KEY) ) );
    body += "</html>";
	response->setBody(body);
	return response;
}

string MoreInfoPageHandler::makeBuyButton(unsigned int id , MiniNet* miniNetAccess){
	string buyButton;	
	buyButton += "<form action='/buyFilm' method='post' >";
	buyButton += ("<input type='hidden' name='film_id' value='" + to_string(id) + "'/>" );
	buyButton += "<button type='submit'";
	if(!miniNetAccess->hasRequestingUserMoneyForFilm(id) )
		buyButton += "disabled='disabled'";

	buyButton += ">Buy This Film</button> ";
	buyButton += "</form>";
	buyButton += "<br>";
	return buyButton;
}

string MoreInfoPageHandler::makeRateForm(unsigned int id){
	string rateForm;	
	rateForm += "<form action='/rateFilm' method='post' >";
	rateForm += ("<input type='hidden' name='film_id' value='" + to_string(id) + "'/>" );
	rateForm += "<input type='number' name='score' min='1' max='10'/>";
	rateForm += "<button type='submit'>Rate This Film</button> ";
	rateForm += "</form>";
	rateForm += "<br>";
	return rateForm;
}	

string MoreInfoPageHandler::accumulateBodyOfHtml(const string& body , unsigned int filmId){
	string modifiedBody = body;
	modifiedBody += "<body>";
	modifiedBody = accumulateNavbar(modifiedBody , miniNetAccess);
	modifiedBody += makeBuyButton(filmId , miniNetAccess);
	if(miniNetAccess->hasRequestingUserBoughtThisFilm(filmId) )
		modifiedBody += makeRateForm(filmId);
	modifiedBody += "<div>"; 
	modifiedBody += miniNetAccess->showFurtherInfo(filmId);
	modifiedBody += "</div>";
	modifiedBody += "</body>";

	return modifiedBody;
}

BuyFilmHandler::BuyFilmHandler(MiniNet* theMiniNet){
	miniNetAccess = theMiniNet;
}

Response* BuyFilmHandler::callback(Request* request){
	miniNetAccess->updateRequestingUser(request->getSessionId() );
	miniNetAccess->buyFilm(stoi(request->getBodyParam(FILM_ID_KEY) ) );

	Response* response = Response::redirect("/profile");
	return response;
}

