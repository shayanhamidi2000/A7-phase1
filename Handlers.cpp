#include "Handlers.h"
#include "Mininet.h"
#include "Config.h"
#include "Exceptions.h"

using namespace std;

RegisterHandler::RegisterHandler(MiniNet* theMiniNet) : RequestHandler() {
	miniNetAccess = theMiniNet;
}

Response* RegisterHandler::callback(Request* request){
	Response* response = new Response();
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

	//response->setSessionId(request->getBodyParam(USERNAME_KEY) );
	return response->redirect("/");
}

LoginHandler::LoginHandler(MiniNet* theMiniNet) : RequestHandler() {
	miniNetAccess = theMiniNet;
}

Response* LoginHandler::callback(Request* request){
	Response* response = new Response();
	try{
		miniNetAccess->loginUser(request->getBodyParam(USERNAME_KEY) , request->getBodyParam(PASSWORD_KEY) ); 
	}catch(exception& ex){
		throw Server::Exception(ex.what() );
	}
	response->setSessionId(request->getBodyParam(USERNAME_KEY) );
	return response->redirect("/home");
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
    body = accumulateHeadOfHtml(body);
    body = accumulateBodyOfHtml(body);
    body += "</html>";
	response->setBody(body);

	return response;
}

string HomePageHandler::accumulateHeadOfHtml(const string& body){
	string modifiedBody = body;
	modifiedBody += "<head>";
 	modifiedBody += "<title>submit-film</title>";
    modifiedBody += "<style>";
    modifiedBody += "ul { list-style-type: none; margin: 0; padding: 0; overflow: hidden; background-color: #333; }";
	modifiedBody += "li { float: left; }";
    modifiedBody += "li a { display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none; }";
 	modifiedBody += "li a:hover { background-color: #111; }";
    modifiedBody += "</style>";
  	modifiedBody += "</head>";

	return modifiedBody;
}

string HomePageHandler::accumulateBodyOfHtml(const string& body){
	string modifiedBody = body;
	modifiedBody += "<body>";
	modifiedBody = accumulateNavbar(modifiedBody);
	modifiedBody += "<div>"; 
	modifiedBody += miniNetAccess->loadHomePageDatas();
	modifiedBody += "</div>";
	modifiedBody += "</body>";

	return modifiedBody;
}

string HomePageHandler::accumulateNavbar(const string& body){
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