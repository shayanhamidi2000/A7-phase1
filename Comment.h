#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <map>

class Customer;

class Comment{
public: 
	Comment(unsigned int id , std::string content , Customer* commentOwner);
	unsigned int getId() const;
	std::string getContent() const;
	Customer* getCommentOwner() const;
	void reply(const std::string newRepliedMessage);
private:
	Customer* commentOwner;
	unsigned int id;
	std::string content;
	std::string repliedMessage; 

};


#endif