#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <map>

class Comment{
public: 
	Comment(int id , std::string content);
	unsigned int getId() const { return id; }
	std::string getContent() const { return content; }
private:
	unsigned int id;
	std::string content;
	std::map<std::string , int> replies; 

};


#endif