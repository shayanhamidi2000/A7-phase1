#include "Handlers.h"
#include "Mininet.h"
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include "Config.h"

using namespace std;

/*void CommandHandler::manageSignUp(string signUpInfo){
	string username,password,email;
	unsigned int age;
	bool isPublisher = false;

	vector<string> keywordsAndValues  = splitString(signUpInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_SIGNUP , MAX_KEYS_AND_VALUES_FOR_SIGNUP);
	checkSignupKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	mappedKeysAndValues.insert(pair<string , string> (PUBLISHER_KEY , IS_NOT_PUBLISHER) );
	checkSignupValues( mappedKeysAndValues[AGE_KEY] , mappedKeysAndValues[EMAIL_KEY] , mappedKeysAndValues[PUBLISHER_KEY]);
	age = stoi(mappedKeysAndValues[AGE_KEY] );
	username = mappedKeysAndValues[USERNAME_KEY];
	password = mappedKeysAndValues[PASSWORD_KEY];
	email = mappedKeysAndValues[EMAIL_KEY];
	if(mappedKeysAndValues[PUBLISHER_KEY] == IS_PUBLISHER)
		isPublisher = true;

	miniNetAccess->registerUser(email , username , password , age , isPublisher);
}

void CommandHandler::manageLogin(string loginInfo){
	string username;
	string password;

	vector<string> keywordsAndValues = splitString(loginInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_LOGIN , MAX_KEYS_AND_VALUES_FOR_LOGIN);
	checkLoginKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	username = mappedKeysAndValues[USERNAME_KEY];
	password = mappedKeysAndValues[PASSWORD_KEY];

	miniNetAccess->loginUser(username , password);
}

void CommandHandler::manageFilmUpload(string newFilmInfo){
	string name , director , summary;
	unsigned int price , length , year;

	vector<string> keywordsAndValues = splitString(newFilmInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_FILM_UPLOAD , MAX_KEYS_AND_VALUES_FOR_FILM_UPLOAD);
	checkFilmUploadKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	checkFilmValues( mappedKeysAndValues[FILM_YEAR_KEY] , mappedKeysAndValues[FILM_LENGTH_KEY] , mappedKeysAndValues[FILM_PRICE_KEY] );
	name = mappedKeysAndValues[FILM_NAME_KEY];
	director = mappedKeysAndValues[FILM_DIRECTOR_KEY];
	summary = mappedKeysAndValues[FILM_SUMMARY_KEY];
	price = stoi(mappedKeysAndValues[FILM_PRICE_KEY] );
	length = stoi(mappedKeysAndValues[FILM_LENGTH_KEY] );
	year = stoi(mappedKeysAndValues[FILM_YEAR_KEY] );

	miniNetAccess->addFilmOnNet(name , year , director , summary , price , length);
}

void CommandHandler::manageFilmDelete(string deletedFilmInfo){
	unsigned int id;

	vector<string> keywordsAndValues = splitString(deletedFilmInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_FILM_DELETE , MAX_KEYS_AND_VALUES_FOR_FILM_DELETE);
	checkFilmKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	checkIdString( mappedKeysAndValues[FILM_ID_KEY] );

	id = stoi(mappedKeysAndValues[FILM_ID_KEY]);

	miniNetAccess->deleteAFilm(id);

}

void CommandHandler::managePublishedFilmsList(string searchInfo){
	unsigned int minPoint , maxYear , minYear , price;
	string name , directorName;
	minPoint = 0; maxYear = 0; minYear = 0; price = 0;

	vector<string> keywordsAndValues = splitString(searchInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_FILM_SEARCH , MAX_KEYS_AND_VALUES_FOR_FILM_SEARCH);
	checkFilmSearchKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	mappedKeysAndValues = initializeEmptySearchFilmKeys(mappedKeysAndValues);
	checkSearchValues(mappedKeysAndValues[FILM_MINIMUM_RATE_KEY] , mappedKeysAndValues[FILM_MINIMUM_YEAR_KEY]
	 , mappedKeysAndValues[FILM_MAXIMUM_YEAR_KEY] , mappedKeysAndValues[FILM_PRICE_KEY]);

	if(mappedKeysAndValues[FILM_MINIMUM_RATE_KEY] != "")
		minPoint = stoi(mappedKeysAndValues[FILM_MINIMUM_RATE_KEY]);
	if(mappedKeysAndValues[FILM_MAXIMUM_YEAR_KEY] != "")
		maxYear = stoi(mappedKeysAndValues[FILM_MAXIMUM_YEAR_KEY]);
	if(mappedKeysAndValues[FILM_MINIMUM_YEAR_KEY] != "")
		minYear = stoi(mappedKeysAndValues[FILM_MINIMUM_YEAR_KEY]);
	if(mappedKeysAndValues[FILM_PRICE_KEY] != "")
		price = stoi(mappedKeysAndValues[FILM_PRICE_KEY]);
	name = mappedKeysAndValues[FILM_NAME_KEY];
	directorName = mappedKeysAndValues[FILM_DIRECTOR_KEY];

	miniNetAccess->getPublishedList(name , minPoint , minYear , price , maxYear , directorName);
	
}

void CommandHandler::manageAddMoney(string amountOfMoneyInfo){
	unsigned int amount;

	vector<string> keywordsAndValues = splitString(amountOfMoneyInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_ADD_CREDIT , MAX_KEYS_AND_VALUES_FOR_ADD_CREDIT);
	checkAddMoneyKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	checkAddMoneyValues( mappedKeysAndValues[MONEY_AMOUNT_KEY] );
	amount = stoi(mappedKeysAndValues[MONEY_AMOUNT_KEY]);

	miniNetAccess->addMoney(amount);
}

void CommandHandler::checkFilmSearchOrFurtherInfo(string keysAndValues){
	vector<string> keywordsAndValues = splitString(keysAndValues);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_FILM_SEARCH , MAX_KEYS_AND_VALUES_FOR_FILM_SEARCH);

	int numberOfFilmIds = count(keys.begin() , keys.end() , FILM_ID_KEY);
	
	if(numberOfFilmIds == 0){
		manageSearch(keysAndValues);
	}else{
		if(numberOfFilmIds > 1)
			throw BadRequestException();
		else
			manageFilmInfoRequest(keysAndValues);
	}
}

void CommandHandler::manageSearch(string searchInfo){
	unsigned int minPoint , maxYear , minYear , price;
	string name , directorName;
	minPoint = 0; maxYear = 0; minYear = 0; price = 0;

	vector<string> keywordsAndValues = splitString(searchInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_FILM_SEARCH , MAX_KEYS_AND_VALUES_FOR_FILM_SEARCH);
	checkFilmSearchKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	mappedKeysAndValues = initializeEmptySearchFilmKeys(mappedKeysAndValues);
	checkSearchValues(mappedKeysAndValues[FILM_MINIMUM_RATE_KEY] , mappedKeysAndValues[FILM_MINIMUM_YEAR_KEY]
	 , mappedKeysAndValues[FILM_MAXIMUM_YEAR_KEY] , mappedKeysAndValues[FILM_PRICE_KEY]);

	if(mappedKeysAndValues[FILM_MINIMUM_RATE_KEY] != "")
		minPoint = stoi(mappedKeysAndValues[FILM_MINIMUM_RATE_KEY]);
	if(mappedKeysAndValues[FILM_MAXIMUM_YEAR_KEY] != "")
		maxYear = stoi(mappedKeysAndValues[FILM_MAXIMUM_YEAR_KEY]);
	if(mappedKeysAndValues[FILM_MINIMUM_YEAR_KEY] != "")
		minYear = stoi(mappedKeysAndValues[FILM_MINIMUM_YEAR_KEY]);
	if(mappedKeysAndValues[FILM_PRICE_KEY] != "")
		price = stoi(mappedKeysAndValues[FILM_PRICE_KEY]);
	name = mappedKeysAndValues[FILM_NAME_KEY];
	directorName = mappedKeysAndValues[FILM_DIRECTOR_KEY];

	miniNetAccess->searchFilmsInDatabase(name , minPoint , minYear , price , maxYear , directorName);
}

void CommandHandler::manageFilmInfoRequest(string filmIdInfo){
	unsigned int filmId;

	vector<string> keywordsAndValues = splitString(filmIdInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_FILM_FURTHER_INFO , MAX_KEYS_AND_VALUES_FOR_FILM_FURTHER_INFO);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	checkIdString(mappedKeysAndValues[FILM_ID_KEY] );
	filmId = stoi(mappedKeysAndValues[FILM_ID_KEY] );

	miniNetAccess->showFurtherInfo(filmId);
}

void CommandHandler::manageBuyFilm(string filmInfo){
	unsigned int id;

	vector<string> keywordsAndValues = splitString(filmInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_BUY_FILM , MAX_KEYS_AND_VALUES_FOR_BUY_FILM);
	checkFilmKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	checkIdString(mappedKeysAndValues[FILM_ID_KEY]);
	id = stoi(mappedKeysAndValues[FILM_ID_KEY]);

	miniNetAccess->buyFilm(id);
}

void CommandHandler::manageFilmRating(string ratingInfo){
	unsigned int score , id;
	vector<string> keywordsAndValues = splitString(ratingInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_RATE , MAX_KEYS_AND_VALUES_FOR_RATE);
	checkFilmRateKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	checkFilmRateValues(mappedKeysAndValues[FILM_ID_KEY] , mappedKeysAndValues[SCORE_GIVEN_KEY] );
	
	score = stoi(mappedKeysAndValues[SCORE_GIVEN_KEY] );
	id = stoi(mappedKeysAndValues[FILM_ID_KEY] );

	miniNetAccess->rateFilm(id , score);
}

void CommandHandler::manageCommenting(string newCommentInfo){
	unsigned int filmId;
	string content;

	vector<string> keywordsAndValues = splitString(newCommentInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_COMMENT , MAX_KEYS_AND_VALUES_FOR_COMMENT);
	checkCommentingKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	checkIdString(mappedKeysAndValues[FILM_ID_KEY]);

	content = mappedKeysAndValues[COMMENT_OR_REPLY_CONTENT_KEY];
	filmId = stoi(mappedKeysAndValues[FILM_ID_KEY] );

	miniNetAccess->comment(filmId , content);
}

void CommandHandler::managePurchasesList(string searchInfo){
	unsigned int maxYear , minYear , price;
	string name , directorName;
	maxYear = 0; minYear = 0; price = 0;

	vector<string> keywordsAndValues = splitString(searchInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_PURCHASED_LIST , MAX_KEYS_AND_VALUES_FOR_PURCHASED_LIST);
	checkFilmSearchKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	mappedKeysAndValues = initializeEmptySearchFilmKeys(mappedKeysAndValues);
	checkSearchValues("" , mappedKeysAndValues[FILM_MINIMUM_YEAR_KEY] , mappedKeysAndValues[FILM_MAXIMUM_YEAR_KEY] , mappedKeysAndValues[FILM_PRICE_KEY]);

	if(mappedKeysAndValues[FILM_MINIMUM_RATE_KEY] != "")
		throw BadRequestException();
	if(mappedKeysAndValues[FILM_MAXIMUM_YEAR_KEY] != "")
		maxYear = stoi(mappedKeysAndValues[FILM_MAXIMUM_YEAR_KEY]);
	if(mappedKeysAndValues[FILM_MINIMUM_YEAR_KEY] != "")
		minYear = stoi(mappedKeysAndValues[FILM_MINIMUM_YEAR_KEY]);
	if(mappedKeysAndValues[FILM_PRICE_KEY] != "")
		price = stoi(mappedKeysAndValues[FILM_PRICE_KEY]);

	name = mappedKeysAndValues[FILM_NAME_KEY];
	directorName = mappedKeysAndValues[FILM_DIRECTOR_KEY];

	miniNetAccess->getPurchasedList(name , minYear , price , maxYear , directorName);
}

void CommandHandler::manageLogout(){
	miniNetAccess->logout();
}

void CommandHandler::manageCreditShow(){
	miniNetAccess->showCredit();
}*/

