#include "tp4.h"
#include "mainwindow.h"

#include <QApplication>
#include <time.h>
#include <stdio.h>

MainWindow* w = nullptr;
using std::size_t;
using std::string;

int Heap::leftChildIndex(int nodeIndex)
{
    return (nodeIndex * 2) + 1;
}

int Heap::rightChildIndex(int nodeIndex)
{
    return (nodeIndex * 2) + 2;
}

void Heap::insertHeapNode(int heapSize, int value)
{
    //use (*this)[i] or this->get(i) to get a value at index i

	int tmp;

	int i = heapSize;
	(*this)[i] = value;

	while(i > 0 && this->get(i) > this->get((i-1) / 2)){

		tmp = this->get(i);

		(*this)[i] = this->get((i-1)/2);
		(*this)[(i-1)/2] = tmp;

		i = (i-1) / 2;

	}
}


void Heap::heapify(int heapSize, int nodeIndex)
{
	// use (*this)[i] or this->get(i) to get a value at index i
	int i_max = nodeIndex;

	if(leftChildIndex(nodeIndex) <heapSize){

		if((*this)[leftChildIndex(nodeIndex)] > (*this)[i_max]){

			i_max = leftChildIndex(nodeIndex);
	}
	

	}if(rightChildIndex(nodeIndex) < heapSize){

		if ((*this)[rightChildIndex(nodeIndex)] > (*this)[i_max]){

			i_max = rightChildIndex(nodeIndex);
		}
	}	

	if(i_max != nodeIndex){

		int tmp = (*this)[nodeIndex];
		(*this)[nodeIndex] = (*this)[i_max];
		(*this)[i_max] = tmp;

		heapify(heapSize, i_max);
	}
	else return;
}

void Heap::buildHeap(Array& numbers)
{

}

void Heap::heapSort()
{

}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainWindow::instruction_duration = 50;
    w = new HeapWindow();
	w->show();

	return a.exec();
}
