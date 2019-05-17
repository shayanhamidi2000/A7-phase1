#ifndef POINT_H
#define POINT_H

class Customer;

class Point{
private:
	unsigned int score;
	Customer* scoreOwner;
public:	
	Point(unsigned int score , Customer* scoreOwner);
	unsigned int getScore() const;
	Customer* getScoreOwner() const;
	void editScore(const unsigned int newScore);
};


#endif