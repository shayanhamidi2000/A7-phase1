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
private:
	unsigned int id;
	unsigned int averagePoint;
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