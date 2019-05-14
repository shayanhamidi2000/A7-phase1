#include "FilmRepository.h"
#include "Config.h"

FilmRepository::FilmRepository(){
	theIdsAssigned = BASIC_ID_VALUE;
}

Film* FilmRepository::addNewFilm(string name , unsigned int year , string director , string summary , unsigned int price , unsigned int length){
	Film* newFilm = new Film(theIdsAssigned , name , year , length , price , summary , director);
	allFilms.push_back(newFilm);
	this->goToNextId();

	return newFilm;
}