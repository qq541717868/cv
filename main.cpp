#include "mainwindow.h"

#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    auto srcImage= imread("C:\\Users\\dly\\Pictures\\0723\\Snapshot006.jpg",0);
//    imshow("原图：",srcImage);
    return a.exec();
}
