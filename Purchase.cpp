#include "Purchase.h"
#include "Config.h"

Purchase::Purchase(unsigned int filmPrice , unsigned int filmRating){
	this->filmPrice = filmPrice;
	this->filmRating = filmRating;
}

unsigned int Purchase::calculateFilmOwnerShare(){
	float filmOwnerShare = 0;
	switch(filmRating){
		case HIGH_RATED:
			filmOwnerShare = filmPrice * FILM_OWNER_SHARE_HIGHLY_RATED;
			break;
		case AVERAGE_RATED:
			filmOwnerShare = filmPrice * FILM_OWNER_SHARE_AVERAGE_RATED;
			break;
		case LOW_RATED:
			filmOwnerShare = filmPrice * FILM_OWNER_SHARE_LOW_RATED;
			break;
	}
	return (int) filmOwnerShare; 
}

unsigned int Purchase::calculateNetShare(){
	return (filmPrice - calculateFilmOwnerShare());
}