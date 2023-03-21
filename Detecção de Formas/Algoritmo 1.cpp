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
    return gerarAleatorio(6);
}

void exagono(Mat image, float posicoesX[], float posicoesY[], int i) {
    Point pontos[1][6];
    pontos[0][0] = Point(posicoesX[i], posicoesY[i] + 43.3);
    pontos[0][1] = Point(posicoesX[i] + 25, posicoesY[i]);
    pontos[0][2] = Point(posicoesX[i] + 75, posicoesY[i]);
    pontos[0][3] = Point(posicoesX[i] + 100, posicoesY[i] + 43.3);
    pontos[0][4] = Point(posicoesX[i] + 75, posicoesY[i] + 86.6);
    pontos[0][5] = Point(posicoesX[i] + 25, posicoesY[i] + 86.6);
    const Point* ppt[1] = { pontos[0] };
    int npt[] = { 6 };
    fillPoly(image,
        ppt,
        npt,
        1,
        Scalar(cor(), cor(), cor())
    );
}

void pentagono(Mat image, float posicoesX[], float posicoesY[], int i) {
    Point pontos[1][5];
    pontos[0][0] = Point(posicoesX[i], posicoesY[i] + 35);
    pontos[0][1] = Point(posicoesX[i] + 45, posicoesY[i]);
    pontos[0][2] = Point(posicoesX[i] + 90, posicoesY[i] + 35);
    pontos[0][3] = Point(posicoesX[i] + 70, posicoesY[i] + 93.3);
    pontos[0][4] = Point(posicoesX[i] + 20, posicoesY[i] + 93.3);
    const Point* ppt[1] = { pontos[0] };
    int npt[] = { 5 };
    fillPoly(image,
        ppt,
        npt,
        1,
        Scalar(cor(), cor(), cor())
    );
}

void triangulo(Mat image, float posicoesX[], float posicoesY[], int i) {
    Point points[1][3];
    points[0][0] = Point(posicoesX[i] + 50, posicoesY[i]);
    points[0][1] = Point(posicoesX[i] + 100, posicoesY[i] + 86.6);
    points[0][2] = Point(posicoesX[i], posicoesY[i] + 86.6);
    const Point* ppt[1] = { points[0] };
    int npt[] = { 3 };
    fillPoly(image,
        ppt,
        npt,
        1,
        Scalar(cor(), cor(), cor())
    );
}


int main(int argc, char** argv)
{
    srand(time(NULL));
    Mat image;
    image = imread("fundo-preto.jpg", IMREAD_COLOR);

    float posicoesX[15] = { 35, 235, 435, 635, 835, 35, 235, 435, 635, 835, 35, 235, 435, 635, 835 };
    float posicoesY[15] = { 90, 90, 90, 90, 90, 330, 330, 330, 330, 330, 570, 570, 570, 570, 570};

    if (!image.data) {
        cout << "Erro ao abrir a imagem" << endl;
        return 1;
    }

    for (int i = 0; i < 15; i++) {
        switch (sorteia()) {
        case 0:
            rectangle(image, Point(posicoesX[i], posicoesY[i]), Point(posicoesX[i] + 100, posicoesY[i] + 100), Scalar(cor(), cor(), cor()), -1);
            break;
        case 1:
            rectangle(image, Point(posicoesX[i], posicoesY[i]), Point(posicoesX[i] + 150, posicoesY[i] + 80), Scalar(cor(), cor(), cor()), -1);
            break;
        case 2:
            circle(image, Point(posicoesX[i] + 50, posicoesY[i] + 50), 50, Scalar(cor(), cor(), cor()), -1);
            break;
        case 3:
            exagono(image, posicoesX, posicoesY, i);
            break;
        case 4:
            pentagono(image, posicoesX, posicoesY, i);
            break;
        case 5:
            triangulo(image, posicoesX, posicoesY, i);
            break;
        default:
            break;
        }
    }

    imwrite("formas.jpg", image);

    imshow("Imagem", image);
    waitKey(0);
    return 0;
}