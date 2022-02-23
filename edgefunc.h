#ifndef EDGEFUNC_H
#define EDGEFUNC_H


#include<iostream>
#include <QImage>
using namespace std;

class EdgeFunc
{
public:
    EdgeFunc();


    // roberts算子实现
    bool Robers(string str, QImage& outImg);
    //Laplace算子
    bool Laplacian(int kenelValue,string src, QImage& outImg);
    //Canny算子
    bool Canny(int thresholdValue1, int kenelValueCanny, string src, QImage& outImg);

    bool Save(string path);

};

#endif // EDGEFUNC_H
