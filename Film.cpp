#include "Film.h"
#include "Config.h"
#include "Exceptions.h"
#include "Customer.h"
#include "Publisher.h"
#include <iostream>

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

void Film::setName(string name){
 	this->name = name;
}

void Film::setYear(unsigned int manufacturedYear) {
 	this->manufacturedYear = manufacturedYear;
}

void Film::setDuration(unsigned int length) {
 	this->length = length;
}

unsigned int Film::getPrice() const{
 	return price; 
}

void Film::setDirectorName(string directorName) {
 	this->directorName = directorName;
}

void Film::setSummary(string summary) {
 	this->summary = summary; 
} 

void Film::printYourself() const{
	cout.precision(2);
	cout << id << " | " << name << " | " << length << " | " << price << " | " << fixed << averagePoint <<  " | "
	 << manufacturedYear << " | " << directorName;
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

unsigned int Film::getRatingQuality(){
	if(averagePoint < 5)
		return LOW_RATED;
	else if(averagePoint >= 5 && averagePoint < 8)
		return AVERAGE_RATED;
	else
		return HIGH_RATED;
}

Point* Film::findPointByOwner(Customer* owner){
	for(unsigned int i = 0 ; i < points.size() ; i++)
		if(owner->getId() == points[i]->getScoreOwner()->getId() )
			return points[i];

	return nullptr;		
}

void Film::rate(Customer* rater , unsigned int rate){
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

void Film::newComment(Customer* commenter , string newCommentContent){
		comments.push_back(new Comment(theIdsAssignedToComments , newCommentContent , commenter) );
		this->goToNextId();
}

void Film::checkCommentExistence(unsigned int commentId){
	if(findCommentById(commentId) == nullptr )
		throw NotFoundException();
}

Comment* Film::findCommentById(unsigned int commentId){
	for(unsigned int i = 0 ; i < comments.size() ; i++)
		if(comments[i]->getId() == commentId)
			return comments[i];

	return nullptr;	
}

void Film::replyOneComment(unsigned int commentId , std::string replyContent){
	checkCommentExistence(commentId);
	Comment* repliedComment = findCommentById(commentId);
	repliedComment->reply(replyContent);
}
