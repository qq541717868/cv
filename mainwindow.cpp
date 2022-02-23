#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QDateTime>

#include<iostream>


#include "opencvfunc.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , k1(new SliderControl(this))
    , k2(new SliderControl(this))
    , k3(new SliderControl(this))
    , k4(new SliderControl(this))
    ,funid(1)
    ,buttonGroup(new QButtonGroup)
    ,tempImg(new QImage)
    ,dstImg(new QImage)
    ,dir("C:\\Users\\dly\\Pictures\\0723\\test\\")
{
    ui->setupUi(this);

    ui->ccLayout->addWidget(k1);
    ui->ccLayout->addWidget(k2);
    ui->ccLayout->addWidget(k3);
    ui->ccLayout->addWidget(k4);

//



    connect(buttonGroup,static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            this,&MainWindow::funSelChange);
    connect(ui->testBtn,&QPushButton::clicked,this,&MainWindow::valueChange);

    buttonGroup->addButton(ui->rBtn,1);
    buttonGroup->addButton(ui->rBtn2,2);
    buttonGroup->addButton(ui->rBtn3,3);
    buttonGroup->addButton(ui->rBtn4,4);
    buttonGroup->addButton(ui->rBtn5,5);
    buttonGroup->addButton(ui->rBtn6,6);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::valueChange()
{

    switch (funid) {
        //Robers
        case 1:
        {
            edgeFunc.Robers(cutImgPath.toStdString(),*dstImg);
        }
            break;
        //Laplacian
        case 2:
        {
            edgeFunc.Laplacian(k1->getValue(),cutImgPath.toStdString(),*dstImg);
        }
            break;
        case 3:
        {
         edgeFunc.Canny(k1->getValue(),k2->getValue(),cutImgPath.toStdString(),*dstImg);
        }
            break;
        default:
            return;
    }
    upImage();
    //upImage(dst);
//     qDebug()<<"测试"<<funid;
}



void MainWindow::funSelChange(int id)
{
//    disconnect(k1,&SliderControl::sendValueChangeMessage,this,&MainWindow::valueChange);
//    disconnect(k2,&SliderControl::sendValueChangeMessage,this,&MainWindow::valueChange);
//    disconnect(k3,&SliderControl::sendValueChangeMessage,this,&MainWindow::valueChange);
//    disconnect(k4,&SliderControl::sendValueChangeMessage,this,&MainWindow::valueChange);
    switch (funid) {
        //Robers
        case 1:
        {

        }
            break;
        //Laplacian
        case 2:
        {
            disconnect(k1,&SliderControl::sendValueChangeMessage,this,&MainWindow::valueChange);
;
        }
            break;
        case 3:
        {
            disconnect(k1,&SliderControl::sendValueChangeMessage,this,&MainWindow::valueChange);
            disconnect(k2,&SliderControl::sendValueChangeMessage,this,&MainWindow::valueChange);

        }
            break;
        default:
            return;


    }


    funid=id;
//    qDebug()<<id;
    switch (funid) {
        //Robers
        case 1:
        {
           k1->reload("无");
           k2->reload("无");
           k3->reload("无");
           k4->reload("无");
        }
            break;
        //Laplacian
        case 2:
        {
            k1->reload("内核",9,1,2);
            connect(k1,&SliderControl::sendValueChangeMessage,this,&MainWindow::valueChange);
            k2->reload("无");
            k3->reload("无");
            k4->reload("无");
        }
            break;
        case 3:
        {
            k1->reload("滞后性阈值",300,0,270);
            k2->reload("降噪内核",10,0,4);
            connect(k1,&SliderControl::sendValueChangeMessage,this,&MainWindow::valueChange);
            connect(k2,&SliderControl::sendValueChangeMessage,this,&MainWindow::valueChange);
            k3->reload("无");
            k4->reload("无");
        }
            break;
        default:
            return;
    }
}


/**
* @breaf 设置图片
* @param
* @note
*/
void MainWindow::SetImage()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("打开图片"),"C:\\Users\\dly\\Documents","Image Files (*.*)|*.*");
    if(filename.isEmpty())  // 若文件名为空，则不执行操作
    {
        return; // 不执行操作
    }
    cutImgPath=filename;

    tempImg->load(filename);


    QPixmap pix=QPixmap::fromImage(*tempImg);

    int with = ui->img->width();
    int height = ui->img->height();
    QPixmap fitpixmap = pix.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->img->setPixmap(fitpixmap);
}
//更新图片
void MainWindow::upImage()
{

    QPixmap pix=QPixmap::fromImage(*dstImg);

    int with = ui->img->width();
    int height = ui->img->height();
    QPixmap fitpixmap = pix.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->img2->setPixmap(fitpixmap);
}

//更新图片
void MainWindow::upImage(Mat mat)
{
    *dstImg=OpencvFunc::cvMat2QImage(mat);

    QPixmap pix=QPixmap::fromImage(*dstImg);

    int with = ui->img->width();
    int height = ui->img-
