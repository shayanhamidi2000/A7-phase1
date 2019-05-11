#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <map>

using namespace std;

class Comment{
public: 
	Comment(int id , string content);
private:
	int id;
	string content;
	map<string , int> replies; 

};


#endif