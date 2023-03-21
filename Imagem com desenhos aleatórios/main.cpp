#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int gerarAleatorio(int max) {
    return rand() % max;
}

int cor() {
    return gerarAleatorio(255);
}

int sorteia() {
    return gerarAleatorio(3);
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    Mat image;
    image = imread("fundo.png", IMREAD_COLOR);

    if (!image.data) {
        cout << "Erro ao abrir a imagem" << endl;
        return 1;
    }

    for (int i = 0; i < 50; i++) {
        int x1 = gerarAleatorio(800), y1 = gerarAleatorio(600), x2 = gerarAleatorio(800), y2 = gerarAleatorio(600);

        switch (sorteia()) {
        case 0:
            line(image, Point(x1, y1), Point(x2, y2), Scalar(cor(), cor(), cor()), 2, 8);
            break;
        case 1:
            circle(image, Point(x1, y1), gerarAleatorio(50), Scalar(cor(), cor(), cor()), 2, 8);
            break;
        case 2:
            rectangle(image, Point(x1, y1), Point(x2, y2), Scalar(cor(), cor(), cor()), 2, 8);
            break;
        default:
            break;
        }
    }

    imwrite("imagem-colorida.png", image);

    image = imread("imagem-colorida.png", IMREAD_GRAYSCALE);

    if (!image.data) {
        cout << "Erro ao abrir a imagem" << endl;
        return 1;
    }

    imwrite("imagem-grayscale.png", image);

    imshow("Imagem", image);
    waitKey(0);
    return 0;
}