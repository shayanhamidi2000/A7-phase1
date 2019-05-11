#ifndef PURCHASE_H
#define PURCHASE_H

class Purchase{
private:
	unsigned int filmPrice;
	unsigned int filmRating;
	unsigned int customerId;
public:
	Purchase(unsigned int filmPrice , unsigned int filmRating);
	unsigned int calculateFilmOwnerShare();
	unsigned int calculateNetShare();
};

#endif