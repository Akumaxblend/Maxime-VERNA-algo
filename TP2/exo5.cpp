#include <QApplication>
#include <time.h>
#include "tp2.h"

MainWindow* w=nullptr;

void merge(Array& first, Array& second, Array& result);

void splitAndMerge(Array& origin)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)

	if(origin.size() <= 1){

		return;
	}
	// initialisation
	Array& first = w->newArray(origin.size()/2);
	Array& second = w->newArray(origin.size()-first.size());
	
	// split

	for(int i = 0 ; i < (origin.size() / 2) ; i++){

		first[i] = origin[i];
	}

	for(int i = origin.size()/2 ; i < origin.size() ; i ++){

		second[i - origin.size()/2] = origin[i];
	}

	// recursiv splitAndMerge of lowerArray and greaterArray

	splitAndMerge(first);
	splitAndMerge(second);


	// merge

	merge(first, second, origin);
}

void merge(Array& first, Array& second, Array& result) //On compare les deux premiers elems des deux tableaux, on insère le min dans le resultat et on le vire de l'autre tableau (MAJ du minimum en gros)
{

	int firstPos = 0;
	int secondPos = 0;

	while(firstPos < first.size() && secondPos < second.size()){

		if(first[firstPos] <= second[secondPos]){

			result[firstPos + secondPos] = first[firstPos];
			firstPos ++;
		}
		else {

			result[firstPos + secondPos] = second[secondPos];
			secondPos ++;
		}
	}
	while(firstPos < first.size()){

		result[firstPos + secondPos] = first[firstPos];
		firstPos ++;
	}

	while(secondPos < second.size()){

		result[firstPos + secondPos] = second[secondPos];
		secondPos ++;
	}
}

void mergeSort(Array& toSort)
{
    splitAndMerge(toSort);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(mergeSort);
	w->show();

	return a.exec();
}
