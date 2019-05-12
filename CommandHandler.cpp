#include "CommandHandler.h"

CommandHandler::CommandHandler(MiniNet* theMiniNet){
	miniNetAccess = theMiniNet;
}

string CommandHandler::deleteSpacesOfAString(string aString){
	string modifiedString = aString;
	modifiedString.erase(remove(modifiedString.begin(), modifiedString.end(), ' ') , modifiedString.end());
	return modifiedString;
}

string CommandHandler::concatenateTwoStrings(string firstString , string secondString){
	return (firstString + secondString);
}

vector<string> splitString(string aString){
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
	keyCommand = deleteSpacesOfAString(keyCommand);

	recognizeCommandType(keyCommand , restOfCommand);
}

bool CommandHandler::checkCommandValidation(string keyCommand) {
	string commandSecondPart = deleteSpacesOfAString( splitString(keyCommand)[1] );
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

void CommandHandler::recognizeCommandType(string keyCommand , string restOfCommand){
	if(!checkCommandValidation(keyCommand))
		throw NotFoundException();

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
		manageGetMoney();

	}else if(concatenateTwoStrings(GET_KW , GET_PUBLISHED_FILMS_COMMAND) == keyCommand){
		managePublishedFilmsList(restOfCommand);

	}else if(concatenateTwoStrings(POST_KW , REPLY_COMMAND) == keyCommand){
		manageReplyComment(restOfCommand);

	}else if(concatenateTwoStrings(DL_KW , COMMENTS_COMMAND) == keyCommand){
		manageDeleteComment(restOfCommand);

	}else if(concatenateTwoStrings(POST_KW , FOLLOWERS_COMMAND) == keyCommand){
		manageFollow(restOfCommand);

	}else if(concatenateTwoStrings(POST_KW , GET_MONEY_COMMAND) == keyCommand){
		manageAddMoney(restOfCommand);

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
