#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "Config.h"
#include "Exceptions.h"
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <map>

class MiniNet;

class CommandHandler{
public:
	CommandHandler(MiniNet* theMiniNet);

	void getRawCommand(string rawCommandLine);
	void recognizeCommandType(string keyCommand , string restOfCommand);

	void manageSignUp(string signUpInfo);
	void manageLogin(string loginInfo);
	void manageFilmUpload(string newFilmInfo);
	void manageFilmEdit(string editedFilmInfo);
	void manageFilmDelete(string deletedFilmInfo);
	void manageFollowerListRequest();
	void manageGetMoney();
	void managePublishedFilmsList(string searchInfo);
	void manageReplyComment(string commentInfo);
	void manageDeleteComment(string commentInfo);
	void manageFollow(string followedInfo);
	void manageAddMoney(string amountOfMoneyInfo);
	void manageSearch(string searchInfo);
	void manageFilmInfoRequest(string filmInfo);
	void manageBuyFilm(string filmInfo);
	void manageFilmRating(string ratingInfo);
	void manageCommenting(string newCommentInfo);
	void managePurchasesList(string searchInfo);
	void manageUnreadNotifications();
	void manageAllNotifications(string limitInfo);

private:	
	MiniNet* miniNetAccess; 
	string deleteSpacesOfAString(string aString);
	bool isConstantNumber(string aPieceOfString);
	string concatenateTwoStrings(string firstString , string secondString);
	vector<string> splitString(string aString);
	bool checkCommandValidation(string keyCommand);
	void checkFirstPartAndSecondPartOfCommand(string keyCommand , string restOfCommand);
	bool checkSecondCommandPartValidation(string secondPart);
	bool isEven(unsigned int aNumber);
	//
	vector<string> getKeys(vector<string> keysAndValues , unsigned int minNumberOfKeys , unsigned int maxNumberOfKeys);
	map<string , string> getMappedKeysAndValues(vector<string> keysAndValues);
	// 
	void checkSignupKeys(vector<string> keys);
	void checkSignupValues(string age , string email , string isPublisher);
	bool checkEmailValidation(string email);
	bool isAcceptableSuffixForEmail(string aString);
	//
	void checkLoginKeys(vector<string> keys);
	//
};


#endif