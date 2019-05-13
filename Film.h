#ifndef FILM_H
#define FILM_H

#include <string>
#include <vector>
#include "Comment.h"
using namespace std;

class Film{
public:
	Film(unsigned int id , string name , unsigned manufacturedYear , unsigned int length , 
		unsigned int price , string summary , string directorName);

	unsigned int getAvailability() const { return isAvailable; }
	unsigned int getId() const { return id; }
	double getPoint() const { return averagePoint; }
	string getName() const { return name; }
	unsigned int getYear() const { return manufacturedYear; }
	unsigned int getDuration() const { return length; }
	unsigned int getPrice() const  { return price; }
	string getDirectorName() const { return directorName; }
	string getSummary() const { return summary; } 
private:
	int theIdsAssignedToComments;
	unsigned int id;
	bool isAvailable;
	double averagePoint;
	unsigned int peopleRatedThisFilm;
	string name;
	unsigned int manufacturedYear;
	unsigned int length;
	unsigned int price;
	string summary;
	string directorName;
	vector<Comment*> comments;
};

#endif