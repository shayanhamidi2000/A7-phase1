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

void Film::beUnavailable() {
	this->isAvailable = false;
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

void Film::setName(string name){
 	this->name = name;
}

void Film::setYear(unsigned int manufacturedYear) {
 	this->manufacturedYear = manufacturedYear;
}

void Film::setDuration(unsigned int length) {
 	this->length = length;
}

unsigned int Film::getPrice() const{
 	return price; 
}

void Film::setDirectorName(string directorName) {
 	this->directorName = directorName;
}

void Film::setSummary(string summary) {
 	this->summary = summary; 
} 