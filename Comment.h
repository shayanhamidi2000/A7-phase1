#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <vector>

using namespace std;

class Comment{
public: 
	Comment(int id , string content);
private:
	int id;
	string content;
	vector<string> replies; 

};


#endif