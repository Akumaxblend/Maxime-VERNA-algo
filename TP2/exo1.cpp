#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w = nullptr;

void selectionSort(Array& toSort){
	// selectionSort

    for(int i = 0 ; i < toSort.size() ; i++){

        for(int j = 0 ; j < toSort.size() ; j++){

            if (toSort[i] < toSort[j]){

                int tmp = toSort[i];
                toSort[i] = toSort[j];

                toSort[j] = tmp;
            }

        }

    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(selectionSort); // window which display the behavior of the sort algorithm
    w->show();

	return a.exec();
}
