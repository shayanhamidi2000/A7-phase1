#ifndef FILM_GRAPH_H
#define FILM_GRAPH_H

#include <vector>
#include <map>
#include "Film.h"

struct FilmAndVertex
{
	FilmAndVertex(Film* aFilm , unsigned int aVertex) : film(aFilm) , vertex(aVertex) {}
	unsigned int vertex;
	Film* film;	
};

class FilmGraph{
private:
	std::vector<std::vector<unsigned int> > graphMatrix;
	std::map<unsigned int , Film*> filmFinderByRow;
	std::map<Film* , unsigned int> rowFinderByFilm;
	//
	std::vector<FilmAndVertex> getLinkedFilmsAndVertexes(std::vector<unsigned int> vertexes);
	std::vector<FilmAndVertex> sortFilmsByVertexWeights(std::vector<FilmAndVertex> unsortedList);
	std::vector<Film*> getFilmsFromSortedLinks(std::vector<FilmAndVertex>  linkedFilmsAndVertexes);
public:
	~FilmGraph();
	void addFilm(Film* newFilm);
	void update(Film* boughtFilm , std::vector<Film*> commonlyBoughtFilms);
	void deleteFilm(Film* deletedFilm);	

	std::vector<Film*> getRecommendedFilms(Film* desiredFilm);
};

#endif