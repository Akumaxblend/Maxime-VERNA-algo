#include <QApplication>
#include <time.h>

#include "tp2.h"


MainWindow* w=nullptr;

void recursivQuickSort(Array& toSort, int size)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)
	
	if(size <= 1){

		return;

	}
	
	Array& lowerArray = w->newArray(size);
	Array& greaterArray= w->newArray(size);
	int lowerSize = 0, greaterSize = 0; // effectives sizes

	// split
	for(int i = 0; i < size; i ++){

		if(i != size / 2){

			if(toSort[i] < toSort[ size / 2]){

			lowerArray.insert(lowerSize, toSort[i]);
			lowerSize ++;
		}
		else{

			greaterArray.insert(greaterSize, toSort[i]);
			greaterSize ++;
		}

		}
		
	}
	
	// recursiv sort of lowerArray and greaterArray

	recursivQuickSort(lowerArray, lowerSize);
	recursivQuickSort(greaterArray, greaterSize);


	// merge
	int tmp = toSort[size / 2];

	for(int i = 0 ; i < lowerSize ; i ++){

		toSort[i] = lowerArray[i];
	}

	toSort[lowerSize] = tmp;

	for(int i = lowerSize + 1 ; i < size ; i ++){

		toSort[i] = greaterArray[i - lowerSize - 1];
	}
}

void quickSort(Array& toSort){
	recursivQuickSort(toSort, toSort.size());
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(quickSort);
	w->show();

	return a.exec();
}
