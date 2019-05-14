#ifndef FILMREPOSITORY_H
#define FILMREPOSITORY_H

#include <vector>
#include "Film.h"
#include "Publisher.h"

class Customer;

class FilmRepository{
public: 
	FilmRepository();
	void addNewFilm(Publisher* filmOwner , std::string name , unsigned int year , std::string director , std::string summary , unsigned int price , unsigned int length);
	void editFilm(Publisher* filmOwner , unsigned int id , std::string newName , unsigned int newYear , unsigned int newLength , std::string newSummary , std::string newDirector);
	void deleteFilm(Publisher* filmOwner , unsigned int id);
	Film* findFilmById(unsigned int id , std::vector<Film*> listOfFilms);
private:
	unsigned int theIdsAssigned;
	std::vector<Film*> allFilms;
	void goToNextId();	
	void checkFilmOwnership(Publisher* assertedOwner , unsigned int id);
	void checkFilmExistence(unsigned int id);
	unsigned int findPositionById(unsigned int id , std::vector<Film*> listOfFilms);
};


#endif