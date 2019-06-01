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

	return Response::redirect("/");
}

LoginHandler::LoginHandler(MiniNet* theMiniNet) : RequestHandler() {
	miniNetAccess = theMiniNet;
}

Response* LoginHandler::callback(Request* request){
	
}