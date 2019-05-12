#ifndef FILMREPOSITORY_H
#define FILMREPOSITORY_H

#include <vector>
#include "Film.h"

using namespace std;

class FilmRepository{
public: 
	FilmRepository();
private:
	int theIdsAssigned;
	vector<Film*> allFilms;	
};


#endif