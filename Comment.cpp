#include "Comment.h"
#include "Customer.h"
#include <iostream>

using namespace std;

Comment::Comment(unsigned int id , std::string content , Customer* commentOwner){
	this->id = id;
	this->content = content;
	this->commentOwner = commentOwner;
}

Customer* Comment::getCommentOwner() const{
	return commentOwner;
}


unsigned int Comment::getId() const { 
	return id; 
}

string Comment::getContent() const { 
	return content; 
}

void Comment::addReply(const string newRepliedMessage){
	replies.push_back(newRepliedMessage);
}

void Comment::printYourself() const{
	cout << id << ". " << content << endl;
	printReplies();
}

void Comment::printReplies() const{
	for(unsigned int i = 0 ; i < replies.size() ; i++)
		cout << id << "." << i + 1 << ". " << replies[i] << endl;
}