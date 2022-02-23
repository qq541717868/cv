#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>

#include "slidercontrol.h"

#include "edgefunc.h"

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    //参数变化
    void valueChange();

    //功能选择发生变化
    void funSelChange(int id);

    //设置图片
    void SetImage();

    //更新图片
    void upImage();
    //更新图片
    void upImage(Mat mat);
    //更新图片
    void upImage(QString filename);
private slots:
    void on_imageBtn_triggered();

    void on_saveBtn_clicked();

    void on_saveAsBtn_clicked();

private:
    Ui::MainWindow *ui;


    SliderControl * k1;
    SliderControl * k2;
    SliderControl * k3;
    SliderControl * k4;

    int funid;
    QButtonGroup * buttonGroup;


    Mat srcImg, resultImg;
    //
    QImage* tempImg ;
    QImage* dstImg;
    //当前图片路径
    QString cutImgPath;
    QString dir;


    EdgeFunc edgeFunc;

//    QImage* IplImage2QImage(Mat *matImage);
};
#endif // MAINWINDOW_H
