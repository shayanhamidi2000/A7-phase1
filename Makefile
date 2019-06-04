CC = g++ -std=c++11

all:Myserver.out

Myserver.out:main.o Mininet.o Handlers.o Point.o FilmRepository.o FilmGraph.o Customer.o Message.o Comment.o Publisher.o Film.o Purchase.o Security.o Admin.o server.o response.o request.o utilities.o route.o
	${CC} main.o Mininet.o Handlers.o FilmRepository.o Customer.o Admin.o Message.o Comment.o Publisher.o Film.o Purchase.o Point.o Security.o FilmGraph.o server.o response.o request.o utilities.o route.o -o Mininet.out

main.o:main.cpp Mininet.h
	${CC} -c main.cpp -o main.o

Mininet.o:Mininet.cpp Mininet.h FilmRepository.h Customer.h Admin.h Handlers.h Publisher.h Purchase.h Film.h Security.h Exceptions.h Config.h server/server.hpp
	${CC} -c Mininet.cpp -o Mininet.o

Handlers.o: Handlers.cpp Handlers.h Config.h Mininet.h server/server.hpp
	${CC} -c Handlers.cpp -o Handlers.o

FilmRepository.o: FilmRepository.cpp FilmRepository.h Film.h Publisher.h FilmGraph.h Exceptions.h Config.h
	${CC} -c FilmRepository.cpp -o FilmRepository.o

Customer.o: Customer.cpp Customer.h Publisher.h Message.h Film.h
	${CC} -c Customer.cpp -o Customer.o

Publisher.o: Publisher.cpp Publisher.h Customer.h Film.h
	${CC} -c Publisher.cpp -o Publisher.o

Film.o: Film.cpp Film.h Comment.h Point.h Publisher.h Customer.h Exceptions.h Config.h
	${CC} -c Film.cpp -o Film.o

Comment.o: Comment.cpp Comment.h Customer.h
	${CC} -c Comment.cpp -o Comment.o

Message.o: Message.cpp Message.h
	${CC} -c Message.cpp -o Message.o

Purchase.o: Purchase.cpp Purchase.h Publisher.h Config.h
	${CC} -c Purchase.cpp -o Purchase.o

Point.o: Point.cpp Point.h Customer.h
	${CC} -c Point.cpp -o Point.o

Security.o:Security.cpp Security.h Exceptions.h
	${CC} -c Security.cpp -o Security.o

Admin.o:Admin.cpp Admin.h Customer.h Config.h
	${CC} -c Admin.cpp -o Admin.o

FilmGraph.o:FilmGraph.cpp FilmGraph.h Film.h
	${CC} -c FilmGraph.cpp -o FilmGraph.o

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) -c utils/response.cpp -o response.o

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) -c utils/request.cpp -o request.o

utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) -c utils/utilities.cpp -o utilities.o

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c server/server.cpp -o server.o

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c server/route.cpp -o route.o

.PHONY:clean
clean:
	rm *.out *.o
	
