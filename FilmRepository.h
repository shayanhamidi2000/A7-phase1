#ifndef FILMREPOSITORY_H
#define FILMREPOSITORY_H

#include <vector>
#include "Film.h"

using namespace std;

class FilmRepository{
public: 
	FilmRepository();
	Film* addNewFilm(string name , unsigned int year , string director , string summary , unsigned int price , unsigned int length);
private:
	unsigned int theIdsAssigned;
	vector<Film*> allFilms;
	void goToNextId() { theIdsAssigned++; }	
};


#endif