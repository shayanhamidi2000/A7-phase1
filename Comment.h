#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <vector>

class Customer;

class Comment{
public: 
	Comment(unsigned int id , std::string content , Customer* commentOwner);
	unsigned int getId() const;
	Customer* getCommentOwner() const;
	void addReply(const std::string& newRepliedMessage);
	std::string printYourself() const;
private:
	Customer* commentOwner;
	unsigned int id;
	std::string content;
	std::vector<std::string> replies;
	void printReplies() const;
};


#endif