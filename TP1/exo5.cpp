#include "tp1.h"
#include <QApplication>
#include <time.h>

Point complexSquare(Point z){

    Point tmp;
    tmp.x = z.x * z.x - z.y * z.y;
    tmp.y = 2 * z.x * z. y;
    return tmp;
}
int isMandelbrot(Point z, int n, Point point){
    // recursiv Mandelbrot

    // check n

    // check length of z
    // if Mandelbrot, return 1 or n (check the difference)
    // otherwise, process the square of z and recall
    // isMandebrot

    if(z.length() > 2 || n == 0){

        return n;
    }

    z = complexSquare(z);
    z.x += point.x;
    z.y += point.y;
    return isMandelbrot(z, n - 1, point);

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MandelbrotWindow(isMandelbrot);
    w->show();

    a.exec();
}



