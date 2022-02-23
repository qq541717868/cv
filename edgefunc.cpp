#include "edgefunc.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include "opencvfunc.h"

using namespace cv;

 Mat srcImage,dstImage;
 string cutImgPath;

EdgeFunc::EdgeFunc()
{

}

// roberts算子实现
cv::Mat roberts(cv::Mat srcImage)
{
    cv::Mat dstImage = srcImage.clone();
    int nRows = dstImage.rows;
    int nCols = dstImage.cols;
    for (int i = 0; i < nRows - 1; i++)
    {
        for (int j = 0; j < nCols - 1; j++)
        {
            // 根据公式计算
            int t1 = (srcImage.at<uchar>(i, j) -
                srcImage.at<uchar>(i + 1, j + 1)) *
                (srcImage.at<uchar>(i, j) -
                srcImage.at<uchar>(i + 1, j + 1));
            int t2 = (srcImage.at<uchar>(i + 1, j) -
                srcImage.at<uchar>(i, j + 1)) *
                (srcImage.at<uchar>(i + 1, j) -
                srcImage.at<uchar>(i, j + 1));
            // 计算对角线像素差
            dstImage.at<uchar>(i, j) = (uchar)sqrt(t1 + t2);
        }
    }
    return dstImage;
}

bool EdgeFunc::Robers(string str,QImage& outImg)
{
    if(cutImgPath!=str)
    {
        cutImgPath=str;
        srcImage= imread(str,0);
    }
    if (!srcImage.data)
        return false;
    else {
        srcImage= imread(str,0);
        if (!srcImage.data)
            return false;
    }
    //imshow("原图",strImage);
    dstImage=roberts(srcImage);//调用robers算子

   outImg= OpencvFunc::cvMat2QImage(dstImage);

    //imshow("Robers算子实现",dstImage);
//    imwrite(dst,dstImage);
//    cvWaitKey(0);
    return true;
}

/*----------------------------------------【Laplace算子】------------------------------------------*/

bool EdgeFunc::Laplacian(int kenelValue, string src, QImage& outImg)
{
    if(cutImgPath!=src)
    {
        cutImgPath=src;
        srcImage= imread(src,3);
    }
    if (!srcImage.data)
        return false;
    else {
        srcImage= imread(src,3);
        if (!srcImage.data)
            return false;
    }

    Mat  grayImage, abs_dstImage,gaussImage;


    //转为灰度图
    cvtColor(srcImage,grayImage,COLOR_RGB2GRAY);

    //高斯滤波
    if(kenelValue%2 ==0)
        ++kenelValue;
    if(kenelValue<0)
        kenelValue=0;
    GaussianBlur(grayImage, gaussImage, Size(kenelValue,kenelValue), 0, 0, BORDER_DEFAULT);

    //使用Laplace算子
    cv::Laplacian(gaussImage, abs_dstImage, CV_16S, 3, 1, 0, BORDER_DEFAULT);

    //计算绝对值，并将结果转换成8位
    convertScaleAbs(abs_dstImage,dstImage );

    outImg= OpencvFunc::cvMat2QImage(dstImage);

//    //显示
//    imshow("原图：",srcImage);
//    imshow("Laplace算法：",dstImage);
//    //导出
//    imwrite(dst,dstImage);

//    waitKey(3000);
    return true;
}

/*----------------------------------------【Canny算子】------------------------------------------*/
/**Canny算子检测
 *1.原理：
 *（1）图像边缘检测必须满足两个条件：一是能有效地抑制噪声，而是必须尽量精确的确定边缘的位置。
 *（2）根据对信噪比与定位乘积进行测度，得到最优化逼近算子，即Canny算子。
 *（3）先平滑后求导
 *
 *2.Canny的目标是找到一个最优的边缘检测算法，最优的含义是：
 *（1）好的检测—算法能够尽可能多的标识出图像中的实际边缘
 *（2）好的定位—标识出的边缘要尽可能与实际图像中的实际边缘尽可能接近。
 *（3）最小响应—图像中的边缘只能标志一次，并且可能存在的图像杂讯不因该标志为边缘。
 *
 *3.Canny边缘检测步骤：
 *（1）去噪
 *任何边缘检测算法都不可能在未经处理的原始数据上很好地處理，所以第一步是对原始数据与高斯 mask 作卷积，得到的
 *图像与原始图像相比有些轻微的模糊（blurred）。这样，单独的一个像素杂讯在经过高斯平滑的图像上变得几乎没有影响。
 *(2)用一阶偏导的有限差分来计算梯度的幅值和方向。
 *(3)对梯度幅值进行非极大值抑制。
 *仅仅得到全局的梯度并不足以确定边缘，因此为确定边缘，必须保留局部梯度最大的点，而抑制非极大值。解决方法：利用梯度的方向。
 *(4)用双阈值算法检测和连接边缘。
 *减少假边缘段数量的典型方法是对N[i，j]使用一个阈值。将低于阈值的所有值赋零值。但问题是如何选取阈值？
 *解决方法：双阈值算法。双阈值算法对非极大值抑制图象作用两个阈值τ1和τ2，且2τ1≈τ2，从而可以得到两个阈值边缘图象N1［i,j］
 *和N2［i，j］。由于N2［i，j］使用高阈值得到，因而含有很少的假边缘，但有间断(不闭合)。双阈值法要在N2［i，j］中把边缘连接成轮
 *廓，当到达轮廓的端点时，该算法就在N1［i,j］的8邻点位置寻找可以连接到轮廓上的边缘，这样，算法不断地在N1［i,j］中收集边缘，
 *直到将N2［i,j］连接起来为止。
 *在连接边缘的时候，用数组模拟队列的实现。以进行8-连通域搜索。
 */

/*---------------------函数使用-------------------------*/
bool EdgeFunc::Canny(int thresholdValue1,int kenelValueCanny,string src, QImage& outImg)
{
    if(cutImgPath!=src)
    {
        cutImgPath=src;
        srcImage= imread(src,3);
    }
    if (!srcImage.data)
        return false;
    else {
        srcImage= imread(src,3);
        if (!srcImage.data)
            return false;
    }

    Mat  grayImage, denoiseImage,cannyImage;

    //创建与srcImage同类型和大小的矩阵
    dstImage.create(srcImage.size(), srcImage.type());

    //将原图像转换为灰度图像
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

    //高斯滤波降噪
    GaussianBlur(grayImage, denoiseImage, Size(kenelValueCanny * 2 + 1, kenelValueCanny * 2 + 1), 0, 0);

    //使用Canny算子
    cv::Canny(denoiseImage, cannyImage, thresholdValue1, thresholdValue1 * 2 / 3, 3);

    //将dstImage内的所有元素设置为0
    dstImage = Scalar::all(0);

    //以cannyImage作为掩码，将原图srcImage拷到目标图dstImage中
    srcImage.copyTo(dstImage, cannyImage);

    outImg= OpencvFunc::cvMat2QImage(dstImage);

//    //显示
//    imshow("原图", srcImage);
//    imshow("Canny算子边缘检测效果预览：", dstImage);
//    imwrite(dst,dstImage);
    return true;
}

bool EdgeFunc::Save(string path){
    if (!dstImage.data)
        return false;
    else
        imwrite(path,dstImage);
}

