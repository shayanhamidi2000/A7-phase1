#include "Film.h"
#include "Config.h"

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