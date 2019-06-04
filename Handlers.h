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
};

class LogoutHandler : public RequestHandler{
public:
	virtual Response* callback(Request* request);
};

class AddFilmHandler : public RequestHandler{
public:
	AddFilmHandler(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private:
	MiniNet* miniNetAccess;	
};

class DeleteFilmHandler : public RequestHandler{
public:
	DeleteFilmHandler(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private:
	MiniNet* miniNetAccess;	
};

class ProfilePageHandler : public RequestHandler {
public:
	ProfilePageHandler(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private:
	MiniNet* miniNetAccess;	
	std::string accumulateBodyOfHtml(const std::string& body);
	std::string makeAccountChargeButton();
	std::string showCredit();
};

class ChargeMoneyHandler : public RequestHandler {
public:
	ChargeMoneyHandler(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private:
	MiniNet* miniNetAccess;	
};

class FilterFilmsHanlder : public RequestHandler {
public:
	FilterFilmsHanlder(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private:
	MiniNet* miniNetAccess;	
};

class MoreInfoPageHandler : public RequestHandler {
public:
	MoreInfoPageHandler(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private:
	MiniNet* miniNetAccess;	
	std::string accumulateBodyOfHtml(const std::string& body , unsigned int filmId);
	std::string makeBuyButton(unsigned int filmId , MiniNet* miniNetAccess);
	std::string makeRateForm(unsigned int filmId);
	std::string makeCommentForm(unsigned int filmId);
};

class BuyFilmHandler : public RequestHandler {
public:
	BuyFilmHandler(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private:
	MiniNet* miniNetAccess;	
};

class RateFilmHandler : public RequestHandler {
public:
	RateFilmHandler(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private:
	MiniNet* miniNetAccess;	
};

class NewCommentHandler : public RequestHandler {
public:
	NewCommentHandler(MiniNet* theMiniNet);
	virtual Response* callback(Request* request);
private:
	MiniNet* miniNetAccess;	
};


#endif
