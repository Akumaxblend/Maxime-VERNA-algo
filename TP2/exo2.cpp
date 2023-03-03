#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w=nullptr;

void insertionSort(Array& toSort){
	Array& sorted=w->newArray(toSort.size());
	sorted[0] = toSort[0];
	int sortedSize = 1;
	int targetIndex = -1;

	for(int i = 1; i < toSort.size() ; i++){

		for(int j = 0; j < sortedSize; j ++){

			if(toSort[i] < sorted[j]){

				targetIndex = j;
				break;
				
			}
		}

		if(targetIndex != -1){

			sorted.insert(targetIndex, toSort[i]);
			targetIndex = -1;
			sortedSize ++;
		}
		
		else{

			sorted[sortedSize] = toSort[i];
			sortedSize ++;
		}
	}

	// insertion sort from toSort to sorted
	
	toSort=sorted; // update the original array
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(insertionSort); // window which display the behavior of the sort algorithm
	w->show();

	return a.exec();
}
