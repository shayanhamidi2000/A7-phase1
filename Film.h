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
	~Film();
	unsigned int getRatingQuality() const;
	bool getAvailability() const;
	void beUnavailable();
	unsigned int getId() const;
	double getPoint() const;
	void setName(const std::string& name);
	std::string getName() const;
	std::string getDirectorName() const;
	unsigned int getYear() const;
	void setYear(const unsigned int manufacturedYear);
	void setDuration(const unsigned int length);
	unsigned int getPrice() const;
	void setDirectorName(const std::string& directorName);
	void setSummary(const std::string& summary);
	Publisher* getOwner() const;
	std::string printYourself() const;
	std::string printDetailedVersionOfYourself() const;
	std::string printRecommendedEdition() const;
	void rate(Customer* rater , const unsigned int rate);
	void newComment(Customer* commenter , const std::string& newCommentContent);
	void replyOneComment(const unsigned int commentId , const std::string& replyContent);
	void deleteOneComment(const unsigned int commentId);
	Comment* findCommentById(const unsigned int commentId);
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
	Point* findPointByOwner(const Customer* owner);
	void updateAveragePoint();
	void goToNextId();
	void checkCommentExistence(const unsigned int commentId);
	std::string printComments() const;
};

#endif