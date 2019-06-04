#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

using namespace std;

class NotFoundException : public exception {
public:
	virtual const char* what() const throw() { return  "Not Found"; }
};

class PasswordNotMatchingUsernameException : public exception {
public:
	virtual const char* what() const throw() { return  "Wrong Password!!!"; }
};

class RepeatedUsernameException : public exception {
public:
	virtual const char* what() const throw() { return  "A user with the same username already exists!"; }
};

class UsernameNotExistedException : public exception {
public:
	virtual const char* what() const throw() { return  "This Username is not existed on Server, Have you signed up?!"; }
};

#endif