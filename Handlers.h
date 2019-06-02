#ifndef HANDLERS_H
#define HANDLERS_H

#include <string>
#include "server/server.hpp"

class MiniNet;

class RegisterHandler : public RequestHandler{
public:
	RegisterHandler(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private:
	MiniNet* miniNetAccess; 
};

class LoginHandler : public RequestHandler{
public:
	LoginHandler(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private: 
	MiniNet* miniNetAccess;	
};

class HomePageHandler : public RequestHandler{
public:
	HomePageHandler(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private:
	MiniNet* miniNetAccess;	
	std::string accumulateHeadOfHtml(const std::string& body);
	std::string accumulateBodyOfHtml(const std::string& body);
	std::string accumulateNavbar(const std::string& body);
};


#endif
