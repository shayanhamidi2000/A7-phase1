#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
using namespace std;


class Message{
public:
	Message(string content);
private:
	string content;
	bool isRead;
};


#endif