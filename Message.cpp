#include "Message.h"
using namespace std;

Message::Message(string content){
	this->content  = content;
	this->isRead = false;
}