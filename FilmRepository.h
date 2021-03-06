#ifndef FILMREPOSITORY_H
#define FILMREPOSITORY_H

#include <vector>
#include "Film.h"
#include "Publisher.h"
#include "FilmGraph.h"

class Customer;

class FilmRepository{
public: 
	FilmRepository();
	~FilmRepository();
	void addNewFilm(Publisher* filmOwner , std::string name , unsigned int year , std::string director , std::string summary , unsigned int price , unsigned int length);
	void editFilm(Publisher* filmOwner , unsigned int id , std::string newName , unsigned int newYear , unsigned int newLength , std::string newSummary , std::string newDirector);
	void deleteFilm(Publisher* filmOwner , unsigned int id);
	Film* findFilmByIdInDatabase(unsigned int id);
	std::string getSearchedDatabaseList(std::string name  , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , std::string directorName);	
	std::string getPublihsedList(std::vector<Film*> givenList , std::string name  , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , std::string directorName);
	std::string getPurchasedList(std::vector<Film*> givenList , std::string name  , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , std::string directorName);
	bool checkFilmPurchased(Customer* assertedPurchaser , unsigned int id);
	void checkFilmOwnership(Publisher* assertedOwner , unsigned int id);
	void updateFilmsGraph(Film* boughtFilm , std::vector<Film*> commonlyBoughtFilms);
	std::string giveRecommendation(Customer* recommendedCustomer , Film* recommendedOnFilm);
private:
	unsigned int theIdsAssigned;
	std::vector<Film*> allFilms;
	FilmGraph* graphOfFilms;
	//
	void goToNextId();	
	unsigned int findPositionById(unsigned int id , std::vector<Film*> listOfFilms);
	std::string printFilmList(std::vector<Film*> desiredList);
	std::string printPublishedFilms(std::vector<Film*> desiredList);
	std::string printPurchasedFilms(std::vector<Film*> desiredList);
	std::string makeDeleteButtonForFilm(unsigned int id);
	std::string makeFurtherInfoButton(unsigned int id);
	std::vector<Film*> searchFilmWithFactorsInAList(std::vector<Film*> givenList , std::string name  , unsigned int minPoint , unsigned int minYear , unsigned int price , unsigned maxYear , std::string directorName);
	std::vector<Film*> filterFilmsByDatabaseAvailability(std::vector<Film*> givenFilmList);
	std::vector<Film*> filterFilmsByMinPoint(std::vector<Film*> givenFilmList , unsigned int minPoint);
	std::vector<Film*> filterFilmsByName(std::vector<Film*> givenFilmList , std::string name);
	std::vector<Film*> filterFilmsByDirector(std::vector<Film*> givenFilmList , std::string directorName);
	std::vector<Film*> filterFilmsByMinYear(std::vector<Film*> givenFilmList , unsigned int minYear);
	std::vector<Film*> filterFilmsByPrice(std::vector<Film*> givenFilmList , unsigned int price);
	std::vector<Film*> filterFilmsMaxYear(std::vector<Film*> givenFilmList , unsigned int maxYear);
	Film* findFilmById(unsigned int id , std::vector<Film*> listOfFilms);
	std::vector<Film*> sortFilmsById(std::vector<Film*> unsortedList);
	void checkFilmExistence(unsigned int id);
	std::vector<Film*> getFilmsWithoutRecommendedCustomerPurchases(std::vector<Film*> fullList , std::vector<Film*> dislikedList);
	std::string printRecommendedList(std::vector<Film*> recommendedList);
};


#endif