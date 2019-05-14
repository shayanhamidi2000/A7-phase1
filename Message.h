#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>

class Message{
public:
	Message(std::string content);
	bool getReadState() const { return isRead; }
	std::string getContent() const { return content; }
private:
	std::string content;
	bool isRead;
};


#endif