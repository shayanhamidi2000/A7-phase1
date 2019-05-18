#ifndef FILM_H
#define FILM_H

#include <string>
#include <vector>
#include "Comment.h"
#include "Point.h"

class Publisher;
class Customer;

class Film{
public:
	Film(unsigned int id , std::string name , unsigned manufacturedYear , unsigned int length , 
		unsigned int price , std::string summary , std::string directorName , Publisher* filmOwner);

	unsigned int getRatingQuality();
	bool getAvailability() const;
	void beUnavailable();
	unsigned int getId() const;
	double getPoint() const;
	void setName(std::string name);
	std::string getName() const;
	std::string getDirectorName() const;
	unsigned int getYear() const;
	void setYear(unsigned int manufacturedYear);
	void setDuration(unsigned int length);
	unsigned int getPrice() const;
	void setDirectorName(std::string directorName);
	void setSummary(std::string summary);
	Publisher* getOwner() const;
	void printYourself() const;
	void rate(Customer* rater , unsigned int rate);
	void newComment(Customer* commenter , std::string newCommentContent);
	void replyOneComment(unsigned int commentId , std::string replyContent);
	Comment* findCommentById(unsigned int commentId);
private:
	Publisher* filmOwner;
	int theIdsAssignedToComments;
	unsigned int id;
	bool isAvailable;
	double averagePoint;
	std::string name;
	unsigned int manufacturedYear;
	unsigned int length;
	unsigned int price;
	std::vector<Point*> points;
	std::string summary;
	std::string directorName;
	std::vector<Comment*> comments;
	//
	Point* findPointByOwner(Customer* owner);
	void updateAveragePoint();
	void goToNextId();
	void checkCommentExistence(unsigned int commentId);
};

#endif