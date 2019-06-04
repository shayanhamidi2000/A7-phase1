#include "Film.h"
#include "Config.h"
#include "Exceptions.h"
#include "Customer.h"
#include "Publisher.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

Film::Film(unsigned int id , string name , unsigned manufacturedYear , unsigned int length , 
		unsigned int price , string summary , string directorName , Publisher* filmOwner) {
	this->id = id;
	this->name = name;
	this->manufacturedYear = manufacturedYear;
	this->length = length;
	this->price = price;
	this->summary = summary;
	this->directorName = directorName;
	this->averagePoint = 0;
	this->theIdsAssignedToComments = BASIC_ID_VALUE;
	this->isAvailable = true;
	this->filmOwner = filmOwner;
}

Film::~Film(){
	comments.clear();
	points.clear();
}


void Film::goToNextId(){
	theIdsAssignedToComments++;
}

void Film::beUnavailable() {
	this->isAvailable = false;
}

bool Film::getAvailability() const {
	 return isAvailable; 
}

unsigned int Film::getId() const {
 	return id; 
}

double Film::getPoint() const { 
	return averagePoint; 
}

void Film::setName(const string& name){
 	this->name = name;
}

void Film::setYear(const unsigned int manufacturedYear) {
 	this->manufacturedYear = manufacturedYear;
}

void Film::setDuration(const unsigned int length) {
 	this->length = length;
}

unsigned int Film::getPrice() const{
 	return price; 
}

void Film::setDirectorName(const string& directorName) {
 	this->directorName = directorName;
}

void Film::setSummary(const string& summary) {
 	this->summary = summary; 
} 

string Film::printYourself() const{
	stringstream avgPointStream;
	avgPointStream << setprecision(2) << this->averagePoint;
	string avgPointString = avgPointStream.str();
	return  name + A_GAP + to_string(length) + A_GAP + to_string(price) + A_GAP + avgPointString +  A_GAP + to_string(manufacturedYear) + A_GAP + directorName;
}

string Film::printRecommendedEdition() const{
	string recommendedDetail;
	recommendedDetail += (name + A_GAP + to_string(length) + A_GAP + directorName);

 	return recommendedDetail;
 }


string Film::getName() const{
	return name;
}

string Film::getDirectorName() const{
	return directorName;
}

unsigned int Film::getYear() const{
	return manufacturedYear;
}

Publisher* Film::getOwner() const{
	return filmOwner;
}

unsigned int Film::getRatingQuality() const{
	if(averagePoint < 5)
		return LOW_RATED;
	else if(averagePoint >= 5 && averagePoint < 8)
		return AVERAGE_RATED;
	else
		return HIGH_RATED;
}

Point* Film::findPointByOwner(const Customer* owner){
	for(unsigned int i = 0 ; i < points.size() ; i++)
		if(owner->getId() == points[i]->getScoreOwner()->getId() )
			return points[i];

	return nullptr;		
}

void Film::rate(Customer* rater , const unsigned int rate){
	if(findPointByOwner(rater) == nullptr)
		points.push_back(new Point(rate , rater) );
	else
		findPointByOwner(rater)->editScore(rate);

	this->updateAveragePoint();
}

void Film::updateAveragePoint(){
	averagePoint = 0;
	for(unsigned int i = 0 ; i < points.size() ; i++)
		averagePoint += points[i]->getScore();

	averagePoint /= points.size();
}

void Film::newComment(Customer* commenter , const string& newCommentContent){
		comments.push_back(new Comment(theIdsAssignedToComments , newCommentContent , commenter) );
		this->goToNextId();
}

void Film::checkCommentExistence(const unsigned int commentId){
	if(findCommentById(commentId) == nullptr )
		throw NotFoundException();
}

Comment* Film::findCommentById(const unsigned int commentId){
	for(unsigned int i = 0 ; i < comments.size() ; i++)
		if(comments[i]->getId() == commentId)
			return comments[i];

	return nullptr;	
}

void Film::replyOneComment(const unsigned int commentId , const string& replyContent){
	checkCommentExistence(commentId);
	Comment* repliedComment = findCommentById(commentId);
	repliedComment->addReply(replyContent);
}

void Film::deleteOneComment(const unsigned int commentId){
	checkCommentExistence(commentId);
	Comment* deletedComment = findCommentById(commentId);
	comments.erase(find(comments.begin() , comments.end() , deletedComment) );
}

string Film::printDetailedVersionOfYourself() const{
	string detailedData;
	stringstream avgPointStream;
	avgPointStream << setprecision(2) << this->averagePoint;
	string avgPointString = avgPointStream.str();

	detailedData += "Director :   " + directorName + "<br>";
	detailedData += "Length :   " + to_string(length) + "<br>";
	detailedData += "Year :   " + to_string(manufacturedYear) + "<br>";
	detailedData += "Summary :   " + summary + "<br>";
	detailedData += "Rate :   " + avgPointString + "<br>";
	detailedData += "Price :   " + to_string(price) + "<br>";
	detailedData += "<br>";
	//printComments();
	return detailedData;
}

void Film::printComments() const {
	cout << "Comments" << endl;
	for(unsigned int i = 0 ; comments.size() ; i++)
		comments[i]->printYourself();	
}
