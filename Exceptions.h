#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class NotFoundException : public exception {
public:
	virtual const char* const throw() { return  "Not Found"; }
};

class BadRequestException : public exception {
public:
	virtual const char* const throw() { return "Bad Request"; }
};

class PermissionDenialException : public exception {
public: 
	virtual const char* const throw() { return "Permission Denied"; }
};

#endif