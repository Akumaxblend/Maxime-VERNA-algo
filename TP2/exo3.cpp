#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w=nullptr;


void bubbleSort(Array& toSort){
	// bubbleSort

	int tmp = 0;

	for(int i = 0 ; i < toSort.size() - 1 ; i ++){

		for(int j = i + 1 ; j < toSort.size() ; j ++){

			if(toSort[i] > toSort[j]){

				tmp = toSort[i];
				toSort[i] = toSort[j];
				toSort[j] = tmp;
			}
		}
	}
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 100;
	w = new TestMainWindow(bubbleSort);
	w->show();

	return a.exec();
}
