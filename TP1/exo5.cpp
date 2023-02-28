#include "tp1.h"
#include <QApplication>
#include <time.h>

void complexSquare(Point * z){

    z->x = z->x * z->x - z->y * z->y;

    z->y = 2 * z->x * z-> y;
}
int isMandelbrot(Point z, int n, Point point){
    // recursiv Mandelbrot

    // check n

    // check length of z
    // if Mandelbrot, return 1 or n (check the difference)
    // otherwise, process the square of z and recall
    // isMandebrot



    return 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MandelbrotWindow(isMandelbrot);
    w->show();

    a.exec();
}



