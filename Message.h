#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>

class Message{
public:
	Message(std::string content);
	void printYourself();
private:
	std::string content;
	bool isRead;
	void beRead();
};


#endif