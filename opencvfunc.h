#ifndef OPENCVFUNC_H
#define OPENCVFUNC_H

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QImage>

using namespace cv;
using namespace std;
class OpencvFunc
{
public:
    OpencvFunc();

    static Mat QImage2cvMat(QImage image);

    static QImage cvMat2QImage(const cv::Mat& mat);
};

#endif // OPENCVFUNC_H
