#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

using namespace std;

class NotFoundException : public exception {
public:
	virtual const char* what() const throw() { return  "Not Found"; }
};

class BadRequestException : public exception {
public:
	virtual const char* what() const throw() { return "Bad Request"; }
};

class PermissionDenialException : public exception {
public: 
	virtual const char* what() const throw() { return "Permission Denied"; }
};

#endif