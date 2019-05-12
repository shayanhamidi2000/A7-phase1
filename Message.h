#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
using namespace std;


class Message{
public:
	Message(string content);
	bool getReadState() const { return isRead; }
	string getContent() const { return content; }
private:
	string content;
	bool isRead;
};


#endif