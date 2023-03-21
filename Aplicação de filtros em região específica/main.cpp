#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{

    Mat image, imgFilter, original;

    original = imread("foto.jpg", IMREAD_COLOR);
    image = imread("foto.jpg", IMREAD_COLOR);

    blur(image(Rect(75, 180, 100, 100)), imgFilter, Size(15, 15));
    Rect WhereRec1(75, 180, imgFilter.cols, imgFilter.rows);
    imgFilter.copyTo(image(WhereRec1));

    blur(image(Rect(240, 140, 100, 100)), imgFilter, Size(15, 15));
    Rect WhereRec2(240, 140, imgFilter.cols, imgFilter.rows);
    imgFilter.copyTo(image(WhereRec2));

    blur(image(Rect(445, 125, 100, 100)), imgFilter, Size(15, 15));
    Rect WhereRec3(445, 125, imgFilter.cols, imgFilter.rows);
    imgFilter.copyTo(image(WhereRec3));

    blur(image(Rect(600, 185, 100, 100)), imgFilter, Size(15, 15));
    Rect WhereRec4(600, 185, imgFilter.cols, imgFilter.rows);
    imgFilter.copyTo(image(WhereRec4));

    blur(image(Rect(765, 140, 100, 100)), imgFilter, Size(15, 15));
    Rect WhereRec5(765, 140, imgFilter.cols, imgFilter.rows);
    imgFilter.copyTo(image(WhereRec5));

    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Filtrada", WINDOW_AUTOSIZE);

    imshow("Original", original);
    imshow("Filtrada", image);

    waitKey(0);

    return 0;
}