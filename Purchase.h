#ifndef PURCHASE_H
#define PURCHASE_H

class Purchase{
private:
	unsigned int filmPrice;
	unsigned int filmRating;
	unsigned int filmId;
public:
	Purchase(unsigned int filmPrice , unsigned int filmRating);
	unsigned int calculateFilmOwnerShare();
	unsigned int calculateNetShare();
};

#endif