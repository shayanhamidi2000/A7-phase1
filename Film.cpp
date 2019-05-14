#include "Film.h"
#include "Config.h"

using namespace std;

Film::Film(unsigned int id , string name , unsigned manufacturedYear , unsigned int length , 
		unsigned int price , string summary , string directorName) {
	this->id = id;
	this->name = name;
	this->manufacturedYear = manufacturedYear;
	this->length = length;
	this->price = price;
	this->summary = summary;
	this->directorName = directorName;
	this->averagePoint = 0;
	this->peopleRatedThisFilm = 0;
	this->theIdsAssignedToComments = BASIC_ID_VALUE;
	this->isAvailable = true;
}

bool Film::getAvailability() const {
	 return isAvailable; 
}

unsigned int Film::getId() const {
 	return id; 
}

double Film::getPoint() const { 
	return averagePoint; 
}

string Film::getName() const {
 	return name;
}

unsigned int Film::getYear() const {
 	return manufacturedYear;
}

unsigned int Film::getDuration() const {
 	return length;
}

unsigned int Film::getPrice() const  {
 	return price; 
}

string Film::getDirectorName() const {
 	return directorName;
}

string Film::getSummary() const {
 	return summary; 
} 