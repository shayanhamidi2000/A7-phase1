#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <map>

class Customer;

class Comment{
public: 
	Comment(int id , std::string content);
	unsigned int getId() const;
	std::string getContent() const;
private:
	Customer* commentOwner;
	unsigned int id;
	std::string content;
	std::map<std::string , int> replies; 

};


#endif