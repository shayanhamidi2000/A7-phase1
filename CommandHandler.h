#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string>
#include <vector>
#include <map>

class MiniNet;

class CommandHandler{
public:
	CommandHandler(MiniNet* theMiniNet);

	void getRawCommand(std::string rawCommandLine);
	void recognizeCommandType(std::string keyCommand , std::string restOfCommand , bool hasCommandEndSign);

	void manageSignUp(std::string signUpInfo);
	void manageLogin(std::string loginInfo);
	void manageFilmUpload(std::string newFilmInfo);
	void manageFilmEdit(std::string editedFilmInfo);
	void manageFilmDelete(std::string deletedFilmInfo);
	void manageFollowerListRequest();
	void manageGetMoney();
	void managePublishedFilmsList(std::string searchInfo);
	void manageReplyComment(std::string commentInfo);
	void manageDeleteComment(std::string commentInfo);
	void manageFollow(std::string followedInfo);
	void manageAddMoney(std::string amountOfMoneyInfo);
	void manageSearch(std::string searchInfo);
	void manageFilmInfoRequest(std::string filmInfo);
	void manageBuyFilm(std::string filmInfo);
	void manageFilmRating(std::string ratingInfo);
	void manageCommenting(std::string newCommentInfo);
	void managePurchasesList(std::string searchInfo);
	void manageUnreadNotifications();
	void manageAllNotifications(std::string limitInfo);

private:	
	MiniNet* miniNetAccess; 
	//
	std::string deleteSpacesOfAString(std::string aString);
	bool isConstantNumber(std::string aPieceOfString);
	std::string concatenateTwoStrings(std::string firstString , std::string secondString);
	std::vector<std::string> splitString(std::string aString);
	bool checkCommandValidation(std::string keyCommand);
	void checkFirstPartAndSecondPartOfCommand(std::string keyCommand , std::string restOfCommand);
	bool checkSecondCommandPartValidation(std::string secondPart);
	bool isEven(unsigned int aNumber);
	void checkIdString(std::string idString);
	//
	std::vector<std::string> getKeys(std::vector<std::string> keysAndValues , unsigned int minNumberOfKeys , unsigned int maxNumberOfKeys);
	std::map<std::string , std::string> getMappedKeysAndValues(std::vector<std::string> keysAndValues);
	// 
	void checkSignupKeys(std::vector<std::string> keys);
	void checkSignupValues(std::string age , std::string email , std::string isPublisher);
	bool checkEmailValidation(std::string email);
	//
	void checkLoginKeys(std::vector<std::string> keys);
	//
	void checkFilmUploadKeys(std::vector<std::string> keys);
	void checkFilmValues(std::string year , std::string lenght , std::string price);
	void checkFilmEditKeys(std::vector<std::string> keys);
	std::map<std::string , std::string> initializeEmptyFilmEditKeys(std::map<std::string , std::string> givenMap);
	//
	void checkFilmKeys(std::vector<std::string> keys);
	//
	void checkFilmSearchKeys(std::vector<std::string> keys);
	void checkSearchValues(std::string minPoint , std::string minYear , std::string maxYear , std::string price);
	std::map<std::string , std::string> initializeEmptySearchFilmKeys(std::map<std::string , std::string> givenMap);
	//
	void checkFollowKeys(std::vector<std::string> keys);
	//
	void checkAddMoneyKeys(std::vector<std::string> keys);
	void checkAddMoneyValues(std::string amount);
};


#endif