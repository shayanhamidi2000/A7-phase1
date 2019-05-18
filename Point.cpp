#include "Point.h"
#include "Customer.h"

Point::Point(unsigned int score , Customer* scoreOwner){
	this->score = score;
	this->scoreOwner = scoreOwner;
}

unsigned int Point::getScore() const{
	return score;
}

Customer* Point::getScoreOwner() const{
	return scoreOwner;
}

void Point::editScore(unsigned int newScore){
	score = newScore;
}