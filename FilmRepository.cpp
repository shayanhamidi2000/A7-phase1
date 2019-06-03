#include "FilmRepository.h"
#include "Config.h"
#include "Exceptions.h"
#include <algorithm>
#include <iostream>

using namespace std;

FilmRepository::FilmRepository(){
	theIdsAssigned = BASIC_ID_VALUE;
	graphOfFilms = new FilmGraph();
}

FilmRepository::~FilmRepository(){
	allFilms.clear();
	graphOfFilms->~FilmGraph();
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

void FilmRepository::updateFilmsGraph(Film* boughtFilm , std::vector<Film*> commonlyBoughtFilms){
	graphOfFilms->update(boughtFilm , commonlyBoughtFilms);
}

void FilmRepository::addNewFilm(Publisher* filmOwner , string name , unsigned int year , string director , string summary , unsigned int price , unsigned int length){
	Film* newFilm = new Film(theIdsAssigned , name , year , length , price , summary , director , filmOwner);
	allFilms.push_back(newFilm);
	filmOwner->addToUploadedFilms(newFilm);
	this->goToNextId();
	graphOfFilms->addFilm(newFilm);
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
	checkFilmExistence(id);
	if(findFilmById(id , assertedOwner->getUploadedFilms() ) == nullptr)
		throw PermissionDenialException();
}

void FilmRepository::checkFilmPurchased(Customer* assertedPurchaser , unsigned int id){
	checkFilmExistence(id);
	if(findFilmById(id , assertedPurchaser->getPurchasedFilms()) == nullptr)
		throw PermissionDenialException();
}


void FilmRepository::deleteFilm(Publisher* filmOwner , unsigned int id){
	checkFilmOwnership(filmOwner , id);
	Film* deletedFilm = findFilmById(id , allFilms);
	deletedFilm->beUnavailable();
	filmOwner->deleteMyFilm(findPositionById(id , filmOwner->getUploadedFilms() ) );
	graphOfFilms->deleteFilm(deletedFilm);
}

void FilmRepository::editFilm(Publisher* assertedOwner , unsigned int id , string newName , unsigned int newYear , unsigned int newLength , string newSummary , string newDirector){
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

string FilmRepository::getSearchedDatabaseList(string name  , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , string directorName){
	vector<Film*> filteredList = searchFilmWithFactorsInAList(this->allFilms , name , minPoint , minYear , price , maxYear , directorName);
	filteredList = filterFilmsByDatabaseAvailability(filteredList);
	return printFilmList(filteredList);
}

string FilmRepository::getPurchasedList(vector<Film*> givenList , string name  , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , string directorName){
	vector<Film*> filteredList = searchFilmWithFactorsInAList(givenList , name , minPoint , minYear , price , maxYear , directorName);
	return printFilmList(filteredList);
}

string FilmRepository::getPublihsedList(vector<Film*> givenList , string name  , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , string directorName){
	vector<Film*> filteredList = searchFilmWithFactorsInAList(givenList , name , minPoint , minYear , price , maxYear , directorName);
	return printPublishedFilms(filteredList);
}	

vector<Film*> FilmRepository::searchFilmWithFactorsInAList(vector<Film*> givenList , string name  , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , string directorName){
	vector<Film*> filteredList = givenList;
	filteredList = filterFilmsByName(filteredList , name);
	filteredList = filterFilmsByDirector(filteredList , directorName);
	filteredList = filterFilmsByPrice(filteredList , price);
	filteredList = filterFilmsByMinPoint(filteredList , minPoint);
	filteredList = filterFilmsMaxYear(filteredList , maxYear);
	filteredList = filterFilmsByMinYear(filteredList , minYear);
	filteredList =	sortFilmsById(filteredList);

	return filteredList;
}

vector<Film*> FilmRepository::filterFilmsByDatabaseAvailability(vector<Film*> givenFilmList){
	vector<Film*> filteredListByAvailability;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getAvailability() )
			filteredListByAvailability.push_back(givenFilmList[i]);

	return filteredListByAvailability;	
}

vector<Film*> FilmRepository::filterFilmsByMinPoint(vector<Film*> givenFilmList , unsigned int minPoint){
	if(minPoint == 0)
		return givenFilmList;

	vector<Film*> filteredListByMinPoint;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getPoint() )
			filteredListByMinPoint.push_back(givenFilmList[i]);

	return filteredListByMinPoint;	
}

vector<Film*> FilmRepository::filterFilmsByName(vector<Film*> givenFilmList , string name){
	if(name == "")
		return givenFilmList;

	vector<Film*> filteredListByName;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getName() == name)
			filteredListByName.push_back(givenFilmList[i]);

	return filteredListByName;
}

vector<Film*> FilmRepository::filterFilmsByDirector(vector<Film*> givenFilmList , string directorName){
	if(directorName == "")
		return givenFilmList;

	vector<Film*> filteredListByDirectorName;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getDirectorName() == directorName)
			filteredListByDirectorName.push_back(givenFilmList[i]);

	return filteredListByDirectorName;
}

vector<Film*> FilmRepository::filterFilmsByMinYear(vector<Film*> givenFilmList , unsigned int minYear){
	if(minYear == 0)
		return givenFilmList;

	vector<Film*> filteredListByMinYear;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getYear() >= minYear)
			filteredListByMinYear.push_back(givenFilmList[i]);

	return filteredListByMinYear;
}

vector<Film*> FilmRepository::filterFilmsByPrice(vector<Film*> givenFilmList , unsigned int price){
	if(price == 0)
		return givenFilmList;

	vector<Film*> filteredListByPrice;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getPrice() == price )
			filteredListByPrice.push_back(givenFilmList[i]);

	return filteredListByPrice;
}

vector<Film*> FilmRepository::filterFilmsMaxYear(vector<Film*> givenFilmList , unsigned int maxYear){
	if(maxYear == 0)
		return givenFilmList;

	vector<Film*> filteredListByMaxYear;
	for(unsigned int i = 0 ; i < givenFilmList.size() ; i++)
		if(givenFilmList[i]->getYear() <= maxYear)
			filteredListByMaxYear.push_back(givenFilmList[i]);

	return filteredListByMaxYear;
}

string FilmRepository::printPublishedFilms(vector<Film*> desiredList){
	string filmsDatas;
	filmsDatas += "<h2> -> Name | Duration | Price | Rate | Year | Director </h2> <br>";
	for(unsigned int i = 0 ; i < desiredList.size() ; i++){
		filmsDatas += to_string(i + 1) + ". ";
		filmsDatas += desiredList[i]->printYourself();
		filmsDatas += makeDeleteButtonForFilm(desiredList[i]->getId() );
		filmsDatas += "<br>";
	}
	return filmsDatas;
}

string FilmRepository::makeDeleteButtonForFilm(unsigned int id){
	string deleteButton;	
	deleteButton += "<form action='/deleteFilm' method='post' >";
	deleteButton += ("<input type='hidden' name='film_id' value='" + to_string(id) + "'/>" );
	deleteButton += "<button type='submit'> Delete </button> ";
	deleteButton += "</form>";
	return deleteButton;
}

string FilmRepository::printFilmList(vector<Film*> desiredList){
	string filmsDatas;
	filmsDatas += "<h2> -> Name | Duration | Price | Rate | Year | Director </h2> <br>";
	for(unsigned int i = 0 ; i < desiredList.size() ; i++){
		filmsDatas += to_string(i + 1) + ". ";
		filmsDatas += desiredList[i]->printYourself();
		filmsDatas += "<br>";
	}
	return filmsDatas;
}


bool filmIdComparator(const Film* film1 , const Film* film2){
	return (film1->getId() <  film2->getId() );
}

vector<Film*> FilmRepository::sortFilmsById(vector<Film*> unsortedList){
	vector<Film*> sortedList = unsortedList;
	sort(sortedList.begin() , sortedList.end() , filmIdComparator);
	return sortedList;
}

vector<Film*> FilmRepository::getFilmsWithoutRecommendedCustomerPurchases(vector<Film*> fullList , vector<Film*> dislikedList){
	vector<Film*> desiredList;
	for(unsigned int i = 0 ; i < fullList.size() ; i++)
		if(find(dislikedList.begin() , dislikedList.end() , fullList[i]) == dislikedList.end() )
			desiredList.push_back(fullList[i]);

	return desiredList;	
}

void FilmRepository::giveRecommendation(Customer* recommendedCustomer , Film* recommendedOnFilm){
	vector<Film*> recommendedGraphFilms = graphOfFilms->getRecommendedFilms(recommendedOnFilm);
	vector<Film*> dislikedList = recommendedCustomer->getPurchasedFilms();
	dislikedList.push_back(recommendedOnFilm);
	vector<Film*> filteredList = getFilmsWithoutRecommendedCustomerPurchases(recommendedGraphFilms , dislikedList);

	printRecommendedList(filteredList);
}

void FilmRepository::printRecommendedList(vector<Film*> recommendedList){
	cout << "Recommendation Film" << endl;
	cout << "#. Film Id | Film Name | Film Length | Film Director" << endl;
	for(unsigned int i = 0 ; i < recommendedList.size() ; i++){
		if(i == NUMBER_OF_ELEMENTS_GIVEN_AS_RECOMMENDATION_LIST )
			break;
		cout << i + 1 << ". ";
		recommendedList[i]->printRecommendedEdition();
		cout << endl;
	}
}
