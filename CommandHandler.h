#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "Config.h"
#include "Exceptions.h"
#include <string>
#include <algorithm>
#include <vector>

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
	string concatenateTwoStrings(string firstString , string secondString);
	vector<string> splitString(string aString);
};


#endif