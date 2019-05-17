#include "CommandHandler.h"
#include "Mininet.h"
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include "Config.h"
#include "Exceptions.h"

using namespace std;

CommandHandler::CommandHandler(MiniNet* theMiniNet){
	miniNetAccess = theMiniNet;
}

void CommandHandler::checkIdString(string idString){
	if(!isConstantNumber(idString) )
		throw BadRequestException();
}

string CommandHandler::deleteSpacesOfAString(string aString){
	string modifiedString = aString;
	modifiedString.erase(remove(modifiedString.begin(), modifiedString.end(), ' ') , modifiedString.end());
	return modifiedString;
}

bool CommandHandler::isConstantNumber(string aPieceOfString)
{
	for(unsigned int i = 0 ; i < aPieceOfString.length() ; i++)
		if(!isdigit((char) aPieceOfString[i]))
			return false;

	return true;
}

bool CommandHandler::checkSecondCommandPartValidation(string secondPart){
	vector<string> keywordsAndValues  = splitString(secondPart);
	if(!isEven(keywordsAndValues.size() ) )
		return false;

	return true;
}

vector<string> CommandHandler::getKeys(vector<string> keysAndValues , unsigned int minNumberOfKeys , unsigned int maxNumberOfKeys){
	if(keysAndValues.size() > maxNumberOfKeys || keysAndValues.size() < minNumberOfKeys )
		throw BadRequestException();

	vector<string> keys;
	for(unsigned int i = 0 ; i < keysAndValues.size() ; i++)
		if(isEven(i))
			keys.push_back(keysAndValues[i]);

	return keys;	
}

map<string , string> CommandHandler::getMappedKeysAndValues(vector<string> keysAndValues) {
	map<string , string> mappedKeysAndValues;
	for(unsigned int i = 0 ; i < keysAndValues.size() ; i += 2)
		mappedKeysAndValues.insert(pair<string , string> (keysAndValues[i] , keysAndValues[i + 1]) );

	return mappedKeysAndValues;
}

string CommandHandler::concatenateTwoStrings(string firstString , string secondString){
	return (firstString + secondString);
}

bool CommandHandler::isEven(unsigned int aNumber){
	if(aNumber % 2 == 0)
		return true;
	return false;
}

vector<string> CommandHandler::splitString(string aString){
	vector<string> splitedString;
	string newSubString;
	int j;
	
	for(unsigned int i = 0 ; i < aString.length() ; i++){
		if(aString[i] == COMMAND_DELIMITER)
			continue;
		j = i;
		newSubString = "";
		while(aString[j] != COMMAND_DELIMITER){
			newSubString += aString[j];
			j++;
			if(j == aString.length())
				break;
		}
		splitedString.push_back(newSubString);
		i = j;
	}
	return splitedString;
}
//
void CommandHandler::getRawCommand(string rawCommandLine){
	string keyCommand;
	string restOfCommand;
	bool hasCommandEndSign = false;

	if(rawCommandLine.find_first_of(COMMAND_END_SIGN) == string::npos){
		keyCommand = rawCommandLine;
		restOfCommand = "";
	}else{
		keyCommand = rawCommandLine.substr(0 , rawCommandLine.find_first_of(COMMAND_END_SIGN) - 1);
		restOfCommand = rawCommandLine.substr(rawCommandLine.find_first_of(COMMAND_END_SIGN) + 1);
		hasCommandEndSign = true;
	}

	checkFirstPartAndSecondPartOfCommand(keyCommand , restOfCommand);
	recognizeCommandType(keyCommand , restOfCommand , hasCommandEndSign);
}

bool CommandHandler::checkCommandValidation(string keyCommand) {
	vector<string> splitedCommand = splitString(keyCommand);
	if(splitedCommand.size() != 2)
		return false;
	//bug notification read
	string commandSecondPart = deleteSpacesOfAString( splitedCommand[1] );
	if(commandSecondPart == REGISTER_C0MMAND)
		return true;
	if(commandSecondPart == LOGIN_COMMAND)
		return true;
	if(commandSecondPart == FILMS_COMMAND)
		return true;
	if(commandSecondPart == FOLLOWERS_COMMAND)
		return true;
	if(commandSecondPart == GET_MONEY_COMMAND)
		return true;
	if(commandSecondPart == GET_PUBLISHED_FILMS_COMMAND)
		return true;
	if(commandSecondPart == REPLY_COMMAND)
		return true;
	if(commandSecondPart == COMMENTS_COMMAND)
		return true;
	if(commandSecondPart == BUY_COMMAND)
		return true;
	if(commandSecondPart == RATE_COMMAND)
			return true;
	if(commandSecondPart == PURCHASES_COMMAND)
		return true;
	if(commandSecondPart == NOTIFICATIONS_COMMAND)
		return true;
	if(commandSecondPart == READ_NOTIFICATIONS_COMMAND)
		return true;
	
	return false;	
}

void CommandHandler::checkFirstPartAndSecondPartOfCommand(string keyCommand , string restOfCommand){
	if(!checkCommandValidation(keyCommand))
		throw NotFoundException();

	if(!checkSecondCommandPartValidation(restOfCommand))
		throw BadRequestException();
}

void CommandHandler::recognizeCommandType(string keyCommand , string restOfCommand , bool hasCommandEndSign){
	keyCommand = deleteSpacesOfAString(keyCommand);


	if(concatenateTwoStrings(POST_KW , REGISTER_C0MMAND) == keyCommand){
		manageSignUp(restOfCommand);

	}else if(concatenateTwoStrings(POST_KW , LOGIN_COMMAND) == keyCommand){
		manageLogin(restOfCommand);

	}else if(concatenateTwoStrings(POST_KW , FILMS_COMMAND) == keyCommand){
		manageFilmUpload(restOfCommand);

	}else if(concatenateTwoStrings(PUT_KW , FILMS_COMMAND) == keyCommand){
		manageFilmEdit(restOfCommand);

	}else if(concatenateTwoStrings(DL_KW , FILMS_COMMAND) == keyCommand){
		manageFilmDelete(restOfCommand);

	}else if(concatenateTwoStrings(GET_KW , FOLLOWERS_COMMAND) == keyCommand){
		manageFollowerListRequest();

	}else if(concatenateTwoStrings(POST_KW , GET_MONEY_COMMAND) == keyCommand){
		if(hasCommandEndSign){
			manageAddMoney(restOfCommand);
		}else{
			manageGetMoney();
		}	
	}else if(concatenateTwoStrings(GET_KW , GET_PUBLISHED_FILMS_COMMAND) == keyCommand){
		managePublishedFilmsList(restOfCommand);

	}else if(concatenateTwoStrings(POST_KW , REPLY_COMMAND) == keyCommand){
		manageReplyComment(restOfCommand);

	}else if(concatenateTwoStrings(DL_KW , COMMENTS_COMMAND) == keyCommand){
		manageDeleteComment(restOfCommand);

	}else if(concatenateTwoStrings(POST_KW , FOLLOWERS_COMMAND) == keyCommand){
		manageFollow(restOfCommand);

	}else if(concatenateTwoStrings(GET_KW , FILMS_COMMAND) == keyCommand){
		//

	}else if(concatenateTwoStrings(POST_KW , BUY_COMMAND) == keyCommand){
		manageBuyFilm(restOfCommand);

	}else if(concatenateTwoStrings(POST_KW , RATE_COMMAND) == keyCommand){
		manageFilmRating(restOfCommand);

	}else if(concatenateTwoStrings(POST_KW , COMMENTS_COMMAND) == keyCommand){
		manageCommenting(restOfCommand);

	}else if(concatenateTwoStrings(GET_KW , PURCHASES_COMMAND) == keyCommand){
		managePurchasesList(restOfCommand);

	}else if(concatenateTwoStrings(GET_KW , NOTIFICATIONS_COMMAND) == keyCommand){
		manageUnreadNotifications();

	}else if(concatenateTwoStrings(GET_KW , READ_NOTIFICATIONS_COMMAND) == keyCommand){
		manageAllNotifications(restOfCommand);

	}else{
		throw BadRequestException();
	}   
		
}

bool CommandHandler::checkEmailValidation(string email){
	int numberOfDots = count(email.begin() , email.end() , '.'); 
	int numberOfAsign = count(email.begin() , email.end() , '@');
	if(numberOfAsign != 1)
		return false;

	if(numberOfDots == 0)
		return false;

	if(email.find_first_of('@') > email.find_first_of('.') )
		return false;

	if(isConstantNumber(email.substr(0 , email.find_first_of('@') - 1) ) )
		return false;

	return true;
}

void CommandHandler::checkSignupValues(string age , string email , string isPublisher){
	if(!checkEmailValidation(email) ){
		throw BadRequestException();
	}
	if(!isConstantNumber(age) ){
		throw BadRequestException();
	}

	if(isPublisher != IS_NOT_PUBLISHER && isPublisher != IS_PUBLISHER)
		throw BadRequestException();
}

void CommandHandler::checkSignupKeys(vector<string> keys){
	int numberOfEmails = count(keys.begin() , keys.end() , EMAIL_KEY);
	int numberOfUsernames = count(keys.begin() , keys.end() , USERNAME_KEY);
	int numberOfPasswords = count(keys.begin() , keys.end() , PASSWORD_KEY);
	int numberOfAges = count(keys.begin() , keys.end() , AGE_KEY);
	int numberOfPublishers = count(keys.begin() , keys.end() , PUBLISHER_KEY);

	if((numberOfEmails != 1) || (numberOfUsernames != 1) || (numberOfPasswords != 1) || (numberOfAges != 1) )
		throw BadRequestException(); 

	if( (numberOfAges + numberOfPublishers + numberOfUsernames + numberOfPasswords + numberOfEmails) != keys.size() )
		throw BadRequestException();
}

void CommandHandler::manageSignUp(string signUpInfo){
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

void CommandHandler::checkLoginKeys(vector<string> keys){
	int numberOfUsernames = count(keys.begin() , keys.end() , USERNAME_KEY);
	int numberOfPasswords = count(keys.begin() , keys.end() , PASSWORD_KEY);
	if((numberOfPasswords != 1) || (numberOfUsernames != 1))
		throw BadRequestException();
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

void CommandHandler::checkFilmUploadKeys(vector<string> keys){
	int numberOfYears = count(keys.begin() , keys.end() , FILM_YEAR_KEY);
	int numberOfDirectors = count(keys.begin() , keys.end() , FILM_DIRECTOR_KEY);
	int numberOfPrices = count(keys.begin() , keys.end() , FILM_PRICE_KEY);
	int numberOfLengths = count(keys.begin() , keys.end() , FILM_LENGTH_KEY);
	int numberOfSummaries = count(keys.begin() , keys.end() , FILM_SUMMARY_KEY);
	int numberOfNames = count(keys.begin() , keys.end() , FILM_NAME_KEY);

	if( (numberOfNames != 1) || (numberOfPrices != 1) || (numberOfLengths != 1) || (numberOfSummaries != 1) || (numberOfDirectors != 1) || (numberOfYears != 1) )
		throw BadRequestException();
}

void CommandHandler::checkFilmValues(string year , string lenght , string price){
	if(!isConstantNumber(year) || !isConstantNumber(lenght) || !isConstantNumber(price) )
		throw BadRequestException();
}

map<string , string> CommandHandler::initializeEmptyFilmEditKeys(map<string , string> givenMap){
	map<string , string> modifiedMap = givenMap;

	modifiedMap.insert(pair<string , string> (FILM_YEAR_KEY , "") );
	modifiedMap.insert(pair<string , string> (FILM_NAME_KEY , "") );
	modifiedMap.insert(pair<string , string> (FILM_LENGTH_KEY , "") );
	modifiedMap.insert(pair<string , string> (FILM_SUMMARY_KEY , "") );

	return modifiedMap;
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

void CommandHandler::checkFilmEditKeys(vector<string> keys){
	int numberOfYears = count(keys.begin() , keys.end() , FILM_YEAR_KEY);
	int numberOfDirectors = count(keys.begin() , keys.end() , FILM_DIRECTOR_KEY);
	int numberOfIds = count(keys.begin() , keys.end() , FILM_ID_KEY);
	int numberOfLengths = count(keys.begin() , keys.end() , FILM_LENGTH_KEY);
	int numberOfSummaries = count(keys.begin() , keys.end() , FILM_SUMMARY_KEY);
	int numberOfNames = count(keys.begin() , keys.end() , FILM_NAME_KEY);

	if(numberOfIds != 1)
		throw BadRequestException();

	if( (numberOfYears > 1) || (numberOfNames > 1) || (numberOfSummaries > 1) || (numberOfLengths > 1) || (numberOfDirectors > 1) )
		throw BadRequestException();

	if( (numberOfDirectors + numberOfLengths + numberOfSummaries + numberOfYears + numberOfNames) != (keys.size() - 1) )
		throw BadRequestException();

}

void CommandHandler::manageFilmEdit(string editedFilmInfo){
	string modifiedName,modifiedSummary , modifiedDirector;
	unsigned int modifiedYear , modifiedLength , id;
	modifiedYear = 0; modifiedLength = 0;

	vector<string> keywordsAndValues = splitString(editedFilmInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_FILM_EDIT , MAX_KEYS_AND_VALUES_FOR_FILM_EDIT);
	checkFilmEditKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	mappedKeysAndValues = initializeEmptyFilmEditKeys(mappedKeysAndValues);
	checkFilmValues( mappedKeysAndValues[FILM_YEAR_KEY] , mappedKeysAndValues[FILM_LENGTH_KEY] , "" );
	checkIdString(mappedKeysAndValues[FILM_ID_KEY]);

	id = stoi(mappedKeysAndValues[FILM_ID_KEY]);
	modifiedName = mappedKeysAndValues[FILM_NAME_KEY];
	modifiedSummary = mappedKeysAndValues[FILM_SUMMARY_KEY];
	modifiedDirector = mappedKeysAndValues[FILM_DIRECTOR_KEY];
	if( mappedKeysAndValues[FILM_LENGTH_KEY] != "" )
		modifiedLength = stoi(mappedKeysAndValues[FILM_LENGTH_KEY]);
	if( mappedKeysAndValues[FILM_YEAR_KEY] != "" )
		modifiedYear = stoi(mappedKeysAndValues[FILM_YEAR_KEY]);
	
	miniNetAccess->editAFilm(id , modifiedName , modifiedYear , modifiedLength , modifiedSummary , modifiedDirector);
}

void CommandHandler::checkFilmKeys(vector<string> keys){
	int numberOfIds = count(keys.begin() , keys.end() , FILM_ID_KEY);

	if(numberOfIds != 1)
		throw BadRequestException();
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

void CommandHandler::checkFilmSearchKeys(vector<string> keys){
	int numberOfMaxYears = count(keys.begin() , keys.end() , FILM_MAXIMUM_YEAR_KEY);
	int numberOfMinYears = count(keys.begin() , keys.end() , FILM_MINIMUM_YEAR_KEY);
	int numberOfNames = count(keys.begin() , keys.end() , FILM_NAME_KEY);
	int numberOfPrices = count(keys.begin() , keys.end() , FILM_PRICE_KEY);
	int numberOfDirectors = count(keys.begin() , keys.end() , FILM_DIRECTOR_KEY);
	int numberOfMinRates = count(keys.begin() , keys.end() , FILM_MINIMUM_RATE_KEY);

	if( (numberOfMaxYears + numberOfDirectors + numberOfNames + numberOfPrices + numberOfMinRates + numberOfMinYears) != keys.size() )
		throw BadRequestException();
}

void CommandHandler::checkSearchValues(string minPoint , string minYear , string maxYear , string price){
	if(!isConstantNumber(minYear) || !isConstantNumber(minPoint) || !isConstantNumber(maxYear) || !isConstantNumber(price) )
		throw BadRequestException();

	if(minPoint != ""){
		if(stoi(minPoint) > MAX_POINT)
			throw BadRequestException();
	}
}

map<string , string> CommandHandler::initializeEmptySearchFilmKeys(map<string , string> givenMap){
	map<string , string> modifiedMap = givenMap;

	modifiedMap.insert(pair<string , string> (FILM_MINIMUM_RATE_KEY , "") );
	modifiedMap.insert(pair<string , string> (FILM_MINIMUM_YEAR_KEY , "") );
	modifiedMap.insert(pair<string , string> (FILM_MAXIMUM_YEAR_KEY , "") );
	modifiedMap.insert(pair<string , string> (FILM_DIRECTOR_KEY , "") );
	modifiedMap.insert(pair<string , string> (FILM_PRICE_KEY , "") );
	modifiedMap.insert(pair<string , string> (FILM_NAME_KEY , "") );
	return modifiedMap;
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

void CommandHandler::manageFollowerListRequest(){
	miniNetAccess->getFollowersList();
}

void CommandHandler::manageGetMoney(){
	miniNetAccess->getMoneyFromNet();
}

void CommandHandler::manageReplyComment(string commentInfo){

}

void CommandHandler::manageDeleteComment(string commentInfo){

}

void CommandHandler::checkFollowKeys(vector<string> keys){
	int numberOfIds = count(keys.begin() , keys.end() , USER_ID_KEY);

	if(numberOfIds != 1)
		throw BadRequestException();
}

void CommandHandler::manageFollow(string followedInfo){
	unsigned int id;

	vector<string> keywordsAndValues = splitString(followedInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_AND_VALUES_FOR_FOLLOW , MAX_KEYS_AND_VALUES_FOR_FOLLOW);
	checkFollowKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	checkIdString( mappedKeysAndValues[USER_ID_KEY] );
	id = stoi(mappedKeysAndValues[USER_ID_KEY]);

	miniNetAccess->follow(id);
}

void CommandHandler::checkAddMoneyKeys(vector<string> keys){
	int numberOfAmounts = count(keys.begin() , keys.end() , MONEY_AMOUNT_KEY);

	if(numberOfAmounts != 1)
		throw BadRequestException();
}

void CommandHandler::checkAddMoneyValues(string amount){
	if(!isConstantNumber(amount))
		throw BadRequestException();

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

void CommandHandler::manageSearch(string searchInfo){

}

void CommandHandler::manageFilmInfoRequest(string filmInfo){

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

}

void CommandHandler::manageCommenting(string newCommentInfo){

}

void CommandHandler::managePurchasesList(string searchInfo){

}

void CommandHandler::manageUnreadNotifications(){

}

void CommandHandler::manageAllNotifications(string limitInfo){

}
