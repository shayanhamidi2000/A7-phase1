#include "Message.h"
#include <iostream>

using namespace std;

Message::Message(string content){
	this->content  = content;
	this->isRead = false;
}

void Message::beRead(){
	isRead = true;
}

void Message::printYourself(){
	this->beRead();
	cout << content;
}

