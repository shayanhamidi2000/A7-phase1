#ifndef PURCHASE_H
#define PURCHASE_H

#include "Publisher.h"

class Purchase{
private:
	Publisher* filmOwner;
	unsigned int filmPrice;
	unsigned int filmRating;
public:
	Purchase(unsigned int filmPrice , unsigned int filmRating , Publisher* filmOwner);
	unsigned int calculateFilmOwnerShare();
};

#endif