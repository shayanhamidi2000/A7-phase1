#ifndef HANDLERS_H
#define HANDLERS_H

#include <string>
#include <vector>
#include <map>
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


#endif
