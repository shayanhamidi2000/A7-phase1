#include "Comment.h"
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

void Comment::reply(const string newRepliedMessage){
	this->repliedMessage = newRepliedMessage;
}
