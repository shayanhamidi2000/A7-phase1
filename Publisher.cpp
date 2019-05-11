#include "Publisher.h"

Publisher::Publisher(string username , string password , string email , unsigned int id , unsigned int age)
	: Customer(username , password , email , id , age) {
		isPublisher = true;
}