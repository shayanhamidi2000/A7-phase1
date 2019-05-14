#include "CommandHandler.h"
#include "Mininet.h"
#include <iostream>

CommandHandler::CommandHandler(MiniNet* theMiniNet){
	miniNetAccess = theMiniNet;
}

string CommandHandler::deleteSpacesOfAString(string aString){
	string modifiedString = aString;
	modifiedString.erase(remove(modifiedString.begin(), modifiedString.end(), ' ') , modifiedString.end());
	return modifiedString;
}

bool CommandHandler::isAcceptableSuffixForEmail(string aString){
	for(unsigned int i = 0 ; i < aString.length() ; i++)
		if(!isalpha((char) aString[i]) || (aString[i] != '.') )
			return false;

	return true;	
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

	return keysAndValues;	
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

	if(rawCommandLine.find_first_of(COMMAND_END_SIGN) == string::npos){
		keyCommand = rawCommandLine;
		restOfCommand = "";
	}else{
		keyCommand = rawCommandLine.substr(0 , rawCommandLine.find_first_of(COMMAND_END_SIGN) - 1);
		if( (rawCommandLine.find_first_of(COMMAND_END_SIGN) + 1) == rawCommandLine.length() )
			throw BadRequestException();

		restOfCommand = rawCommandLine.substr(rawCommandLine.find_first_of(COMMAND_END_SIGN) + 1);
	}

	checkFirstPartAndSecondPartOfCommand(keyCommand , restOfCommand);
	recognizeCommandType(keyCommand , restOfCommand);
}

bool CommandHandler::checkCommandValidation(string keyCommand) {
	vector<string> splitedCommand = splitString(keyCommand);
	if(splitedCommand.size() != 2)
		return false;

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

void CommandHandler::recognizeCommandType(string keyCommand , string restOfCommand){
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
		//

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

	if(isAcceptableSuffixForEmail(email.substr(email.find_first_of('@') + 1)) )
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
	if((numberOfEmails != 1) || (numberOfUsernames != 1) || (numberOfPasswords != 1) || (numberOfAges != 1) )
		throw BadRequestException(); 

	if(keys.size() == MAX_KEYS_FOR_SIGNUP){
		if(count(keys.begin() , keys.end() , PUBLISHER_KEY) != 1)
			throw BadRequestException();
	}
}

void CommandHandler::manageSignUp(string signUpInfo){
	string username,password,email;
	unsigned int age;
	bool isPublisher = false;

	vector<string> keywordsAndValues  = splitString(signUpInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_FOR_SIGNUP , MAX_KEYS_FOR_SIGNUP);
	checkSignupKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	mappedKeysAndValues.insert(pair<string , string> (PUBLISHER_KEY , IS_NOT_PUBLISHER) );
	checkSignupValues( mappedKeysAndValues[AGE_KEY] , mappedKeysAndValues[EMAIL_KEY] , mappedKeysAndValues[PUBLISHER_KEY]);
	age = stoi(mappedKeysAndValues[AGE_KEY] );
	username = mappedKeysAndValues[USERNAME_KEY];
	password = mappedKeysAndValues[PASSWORD_KEY];
	email = mappedKeysAndValues[PASSWORD_KEY];
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
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_FOR_LOGIN , MAX_KEYS_FOR_LOGIN);
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

void CommandHandler::checkFilmUploadValues(string year , string lenght , string price){
	if(!isConstantNumber(year) || !isConstantNumber(lenght) || !isConstantNumber(price) )
		throw BadRequestException();
}

void CommandHandler::manageFilmUpload(string newFilmInfo){
	if(!miniNetAccess->isAnyOneOnline() || !miniNetAccess->isOnlineUserPublisher())
		throw PermissionDenialException();

	string name , director , summary;
	unsigned int price , length , year;

	vector<string> keywordsAndValues = splitString(newFilmInfo);
	vector<string> keys = getKeys(keywordsAndValues , MIN_KEYS_FOR_FILM_UPLOAD , MAX_KEYS_FOR_FILM_UPLOAD);
	checkFilmUploadKeys(keys);
	map<string , string> mappedKeysAndValues = getMappedKeysAndValues(keywordsAndValues);
	checkFilmUploadValues( mappedKeysAndValues[FILM_YEAR_KEY] , mappedKeysAndValues[FILM_LENGTH_KEY] , mappedKeysAndValues[FILM_PRICE_KEY] );
	name = mappedKeysAndValues[FILM_NAME_KEY];
	director = mappedKeysAndValues[FILM_DIRECTOR_KEY];
	summary = mappedKeysAndValues[FILM_SUMMARY_KEY];
	price = stoi(mappedKeysAndValues[FILM_PRICE_KEY] );
	length = stoi(mappedKeysAndValues[FILM_LENGTH_KEY] );
	year = stoi(mappedKeysAndValues[FILM_YEAR_KEY] );

	miniNetAccess->addFilmOnNet(name , year , director , summary , price , length);
}

void CommandHandler::manageFilmEdit(string editedFilmInfo){

}

void CommandHandler::manageFilmDelete(string deletedFilmInfo){

}

void CommandHandler::manageFollowerListRequest(){

}

void CommandHandler::manageGetMoney(){

}

void CommandHandler::managePublishedFilmsList(string searchInfo){

}

void CommandHandler::manageReplyComment(string commentInfo){

}

void CommandHandler::manageDeleteComment(string commentInfo){

}

void CommandHandler::manageFollow(string followedInfo){

}

void CommandHandler::manageAddMoney(string amountOfMoneyInfo){

}

void CommandHandler::manageSearch(string searchInfo){

}

void CommandHandler::manageFilmInfoRequest(string filmInfo){

}

void CommandHandler::manageBuyFilm(string filmInfo){

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
