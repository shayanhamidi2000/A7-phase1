CC = g++ -std=c++11

all:Mininet.out

Mininet.out:main.o Mininet.o CommandHandler.o FilmRepository.o Customer.o Message.o Comment.o Publisher.o Film.o Purchase.o
	${CC} main.o Mininet.o CommandHandler.o FilmRepository.o Customer.o Message.o Comment.o Publisher.o Film.o Purchase.o -o Mininet.out

main.o:main.cpp Mininet.h
	${CC} -c main.cpp -o main.o

Mininet.o:Mininet.cpp Mininet.h FilmRepository.h CommandHandler.h Publisher.h Purchase.h
	${CC} -c Mininet.cpp -o Mininet.o

CommandHandler.o: CommandHandler.cpp CommandHandler.h Exceptions.h Config.h
	${CC} -c CommandHandler.cpp -o CommandHandler.o

FilmRepository.o: FilmRepository.cpp FilmRepository.h Film.h Publisher.h Exceptions.h Config.h
	${CC} -c FilmRepository.cpp -o FilmRepository.o

Customer.o: Customer.cpp Customer.h Message.h Film.h
	${CC} -c Customer.cpp -o Customer.o

Publisher.o: Publisher.cpp Publisher.h Customer.h Film.h
	${CC} -c Publisher.cpp -o Publisher.o

Film.o: Film.cpp Film.h Comment.h
	${CC} -c Film.cpp -o Film.o

Comment.o: Comment.cpp Comment.h
	${CC} -c Comment.cpp -o Comment.o

Message.o: Message.cpp Message.h
	${CC} -c Message.cpp -o Message.o

Purchase.o: Purchase.cpp Purchase.h Config.h
	${CC} -c Purchase.cpp -o Purchase.o

.PHONY:clean
clean:
	rm *.out *.o
	
