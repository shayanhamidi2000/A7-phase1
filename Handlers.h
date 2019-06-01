#ifndef HANDLERS_H
#define HANDLERS_H

#include <string>
#include <vector>
#include <map>
#include "server/server.hpp"

class MiniNet;

class RegisterHandler : public RequestHandler{
public:
	Response* callback(Request* request);
private:
	MiniNet* miniNetAccess; 
};


#endif
