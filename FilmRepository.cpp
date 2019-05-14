#include "FilmRepository.h"
#include "Config.h"

using namespace std;

FilmRepository::FilmRepository(){
	theIdsAssigned = BASIC_ID_VALUE;
}

void FilmRepository::goToNextId(){
	theIdsAssigned++;
}

Film* FilmRepository::addNewFilm(string name , unsigned int year , string director , string summary , unsigned int price , unsigned int length){
	Film* newFilm = new Film(theIdsAssigned , name , year , length , price , summary , director);
	allFilms.push_back(newFilm);
	this->goToNextId();

	return newFilm;
}

Film* findFilmById(unsigned int id , vector<Film*> listOfFilms){
	for(unsigned int i = 0 ; i < listOfFilms.size() ; i++)
		if(listOfFilms[i]->getId() == id && listOfFilms[i]->getAvailability() )
			return listOfFilms[i];

	return nullptr;		
}