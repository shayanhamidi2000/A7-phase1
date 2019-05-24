#include "FilmGraph.h"
#include <algorithm>

using namespace std;

FilmGraph::~FilmGraph(){
	for(unsigned int i = 0 ; i < graphMatrix.size() ; i++)
		graphMatrix[i].clear();
	
	graphMatrix.clear();
	filmFinderByRow.clear();
	rowFinderByFilm.clear();
}

void FilmGraph::addFilm(Film* newFilm){
	filmFinderByRow.insert(pair<unsigned int , Film*>(graphMatrix.size() , newFilm) );
	rowFinderByFilm.insert(pair<Film* , unsigned int>(newFilm , graphMatrix.size()) );
	graphMatrix.push_back(vector<unsigned int> (graphMatrix.size() , 0) );
	for(unsigned int i = 0 ; i < graphMatrix.size() ; i++)
		graphMatrix[i].push_back( 0 );
}

void FilmGraph::update(Film* boughtFilm , vector<Film*> commonlyBoughtFilms){
	for(unsigned int i = 0 ; i < commonlyBoughtFilms.size() ; i++){
		graphMatrix[rowFinderByFilm[commonlyBoughtFilms[i] ] ][rowFinderByFilm[boughtFilm] ]++;
		graphMatrix[rowFinderByFilm[boughtFilm] ][rowFinderByFilm[commonlyBoughtFilms[i] ] ]++;
	}

}

void FilmGraph::deleteFilm(Film* deletedFilm){
	unsigned int deletedRow = rowFinderByFilm[deletedFilm];
	graphMatrix.erase(graphMatrix.begin() + deletedRow );
	for(unsigned int i = 0 ; i < graphMatrix.size() ; i++)
		graphMatrix[i].erase(graphMatrix[i].begin() + deletedRow );

	rowFinderByFilm.erase(deletedFilm);
	filmFinderByRow.erase(deletedRow);
}	

bool vertexWeightComparator(const FilmAndVertex &film1 , const FilmAndVertex &film2){
	if(film1.vertex > film2.vertex )
		return true;
	if(film1.vertex == film2.vertex){
		if((film1.film)->getId() < (film2.film)->getId() )
			return true;
	}
	return false;
}

vector<FilmAndVertex> FilmGraph::sortFilmsByVertexWeights(vector<FilmAndVertex> unsortedList){
	vector<FilmAndVertex> sortedList = unsortedList;
	sort(sortedList.begin() , sortedList.end() , vertexWeightComparator);
	return sortedList;
}

vector<Film*> FilmGraph::getRecommendedFilms(Film* desiredFilm){
	vector<unsigned int> oneRowVertexes = graphMatrix[rowFinderByFilm[desiredFilm] ];
	vector<FilmAndVertex> linkedFilmsAndVertexes = getLinkedFilmsAndVertexes(oneRowVertexes);
	linkedFilmsAndVertexes = sortFilmsByVertexWeights(linkedFilmsAndVertexes);
	vector<Film*> recommendedFilms = getFilmsFromSortedLinks(linkedFilmsAndVertexes);

	return recommendedFilms;
}

vector<FilmAndVertex> FilmGraph::getLinkedFilmsAndVertexes(vector<unsigned int> vertexes){
	vector<FilmAndVertex> linkedFilmsAndVertexes;
	for(unsigned int i = 0 ; i < graphMatrix.size() ; i++)
		linkedFilmsAndVertexes.push_back(FilmAndVertex(filmFinderByRow[i] , vertexes[i]) );

	return linkedFilmsAndVertexes;
}

vector<Film*> FilmGraph::getFilmsFromSortedLinks(vector<FilmAndVertex>  linkedFilmsAndVertexes){
	vector<Film*> recommendedFilms;
	for(unsigned int i = 0 ; i < linkedFilmsAndVertexes.size() ; i++)
		recommendedFilms.push_back(linkedFilmsAndVertexes[i].film);
    
    return recommendedFilms;
}