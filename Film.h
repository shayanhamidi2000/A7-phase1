#ifndef FILM_H
#define FILM_H

#include <string>
#include <vector>
#include "Comment.h"

class Film{
public:
	Film(unsigned int id , std::string name , unsigned manufacturedYear , unsigned int length , 
		unsigned int price , std::string summary , std::string directorName);

	bool getAvailability() const;
	unsigned int getId() const;
	double getPoint() const;
	std::string getName() const;
	unsigned int getYear() const;
	unsigned int getDuration() const;
	unsigned int getPrice() const;
	std::string getDirectorName() const;
	std::string getSummary() const;
private:
	int theIdsAssignedToComments;
	unsigned int id;
	bool isAvailable;
	double averagePoint;
	unsigned int peopleRatedThisFilm;
	std::string name;
	unsigned int manufacturedYear;
	unsigned int length;
	unsigned int price;
	std::string summary;
	std::string directorName;
	std::vector<Comment*> comments;
};

#endif