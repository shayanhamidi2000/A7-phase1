#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <map>

using namespace std;

class Comment{
public: 
	Comment(int id , string content);
	unsigned int getId() const { return id; }
	string getContent() const { return content; }
private:
	unsigned int id;
	string content;
	map<string , int> replies; 

};


#endif