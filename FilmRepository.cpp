#include "FilmRepository.h"
#include "Config.h"
#include "Exceptions.h"

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

Film* FilmRepository::findFilmById(unsigned int id , vector<Film*> listOfFilms){
	for(unsigned int i = 0 ; i < listOfFilms.size() ; i++)
		if(listOfFilms[i]->getId() == id && listOfFilms[i]->getAvailability() )
			return listOfFilms[i];

	return nullptr;		
}

void FilmRepository::checkFilmExistence(unsigned int id){
	if(findFilmById(id , this->allFilms) == nullptr)
		throw NotFoundException();
}

void FilmRepository::checkFilmOwnership(Publisher* assertedOwner , unsigned int id){
	if(findFilmById(id , assertedOwner->getUploadedFilms() ) )
		throw PermissionDenialException();
}

void FilmRepository::editFilm(Publisher* assertedOwner , unsigned int id , string newName , unsigned int newYear , unsigned int newLength , string newSummary , string newDirector){
	checkFilmExistence(id);
	checkFilmOwnership(assertedOwner , id);
	Film* modifiedFilm = findFilmById(id , allFilms);
	if(newName != "")
		modifiedFilm->setName(newName);
	if(newYear != 0)
		modifiedFilm->setYear(newYear);
	if(newLength != 0)
		modifiedFilm->setDuration(newLength);
	if(newSummary != "")
		modifiedFilm->setSummary(newSummary);
	if(newDirector != "")
		modifiedFilm->setDirectorName(newDirector);

}