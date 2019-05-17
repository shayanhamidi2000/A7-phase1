#include "FilmRepository.h"
#include "Config.h"
#include "Exceptions.h"
#include <iostream>

using namespace std;

FilmRepository::FilmRepository(){
	theIdsAssigned = BASIC_ID_VALUE;
}

void FilmRepository::goToNextId(){
	theIdsAssigned++;
}

unsigned int FilmRepository::findPositionById(unsigned int id , vector<Film*> listOfFilms){
	for(unsigned int i = 0 ; i < listOfFilms.size() ; i++)
		if(listOfFilms[i]->getId() == id)
			return i;

	return 0;		
}

void FilmRepository::addNewFilm(Publisher* filmOwner , string name , unsigned int year , string director , string summary , unsigned int price , unsigned int length){
	Film* newFilm = new Film(theIdsAssigned , name , year , length , price , summary , director , filmOwner);
	allFilms.push_back(newFilm);
	filmOwner->addToUploadedFilms(newFilm);
	this->goToNextId();
}

Film* FilmRepository::findFilmById(unsigned int id , vector<Film*> listOfFilms){
	for(unsigned int i = 0 ; i < listOfFilms.size() ; i++)
		if(listOfFilms[i]->getId() == id && listOfFilms[i]->getAvailability() )
			return listOfFilms[i];

	return nullptr;		
}

Film* FilmRepository::findFilmByIdInDatabase(unsigned int id){
	checkFilmExistence(id);
	return findFilmById(id , this->allFilms);
}

void FilmRepository::checkFilmExistence(unsigned int id){
	if(findFilmById(id , this->allFilms) == nullptr)
		throw NotFoundException();
}

void FilmRepository::checkFilmOwnership(Publisher* assertedOwner , unsigned int id){
	if(findFilmById(id , assertedOwner->getUploadedFilms() ) == nullptr)
		throw PermissionDenialException();
}

void FilmRepository::deleteFilm(Publisher* filmOwner , unsigned int id){
	checkFilmExistence(id);
	checkFilmOwnership(filmOwner , id);
	Film* deletedFilm = findFilmById(id , allFilms);
	deletedFilm->beUnavailable();
	filmOwner->deleteMyFilm(findPositionById(id , filmOwner->getUploadedFilms() ) );
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

void FilmRepository::searchFilmWithFactorsInDatabase(string name  , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , string directorName){
	searchFilmWithFactorsInAList(this->allFilms , name , minPoint , minYear , price , maxYear , directorName);
}

void FilmRepository::searchFilmWithFactorsInAList(vector<Film*> givenList , string name  , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , string directorName){
	vector<Film*> filteredList = givenList;
	filteredList = filterFilmsByName(filteredList , name);
	filteredList = filterFilmsByDirector(filteredList , directorName);
	filteredList = filterFilmsByPrice(filteredList , price);
	filteredList = filterFilmsByMinPoint(filteredList , minPoint);
	filteredList = filterFilmsMaxYear(filteredList , maxYear);
	filteredList = filterFilmsByMinYear(filteredList , minYear);
	
	printFilmList(filteredList);
}

vector<Film*> FilmRepository::filterFilmsByMinPoint(vector<Film*> givenFilmList , unsigned int minPoint){
	if(minPoint == 0)
		return givenFilmList;

	vector<Film*> filteredListByMinPoint;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getPoint() >= minPoint && givenFilmList[i]->getAvailability() )
			filteredListByMinPoint.push_back(givenFilmList[i]);

	return filteredListByMinPoint;	
}

vector<Film*> FilmRepository::filterFilmsByName(vector<Film*> givenFilmList , string name){
	if(name == "")
		return givenFilmList;

	vector<Film*> filteredListByName;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getName() == name && givenFilmList[i]->getAvailability() )
			filteredListByName.push_back(givenFilmList[i]);

	return filteredListByName;
}

vector<Film*> FilmRepository::filterFilmsByDirector(vector<Film*> givenFilmList , string directorName){
	if(directorName == "")
		return givenFilmList;

	vector<Film*> filteredListByDirectorName;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getDirectorName() == directorName && givenFilmList[i]->getAvailability() )
			filteredListByDirectorName.push_back(givenFilmList[i]);

	return filteredListByDirectorName;
}

vector<Film*> FilmRepository::filterFilmsByMinYear(vector<Film*> givenFilmList , unsigned int minYear){
	if(minYear == 0)
		return givenFilmList;

	vector<Film*> filteredListByMinYear;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getYear() >= minYear && givenFilmList[i]->getAvailability() )
			filteredListByMinYear.push_back(givenFilmList[i]);

	return filteredListByMinYear;
}

vector<Film*> FilmRepository::filterFilmsByPrice(vector<Film*> givenFilmList , unsigned int price){
	if(price == 0)
		return givenFilmList;

	vector<Film*> filteredListByPrice;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getPrice() == price && givenFilmList[i]->getAvailability() )
			filteredListByPrice.push_back(givenFilmList[i]);

	return filteredListByPrice;
}

vector<Film*> FilmRepository::filterFilmsMaxYear(vector<Film*> givenFilmList , unsigned int maxYear){
	if(maxYear == 0)
		return givenFilmList;

	vector<Film*> filteredListByMaxYear;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getYear() <= maxYear && givenFilmList[i]->getAvailability() )
			filteredListByMaxYear.push_back(givenFilmList[i]);

	return filteredListByMaxYear;
}

void FilmRepository::printFilmList(vector<Film*> desiredList){
	cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << endl;
	for(unsigned int i = 0 ; i < desiredList.size() ; i++){
		cout << i + 1 << ". ";
		desiredList[i]->printYourself();
		cout << endl;
	}
}
