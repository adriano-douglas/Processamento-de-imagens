#include "opencv2/opencv.hpp"  
#include "iostream"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    Mat image;
    int width, height;
    VideoCapture cap;
    vector<cv::Mat> planes; //armazena cada componente da imagem separado
    Mat histR, histG, histB; //armazena os histogramas de cada cor
    int nbins = 64; //define o tamanho das faixas que armazenará os tons
    float range[] = { 0, 255 }; //define o intervalo do histograma
    const float* histrange = { range };
    bool uniform = true;
    bool acummulate = false;
    int key;

    //abre a câmera, para outras câmeras trocar o número 0 para 1,2,3...
    cap.open(0);

    //verifica se a câmera abriu corretamente
    if (!cap.isOpened()) {
        std::cout << "cameras indisponiveis";
        return -1;
    }

    //configura a largura e altura da imagem capturada
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    //obtem a largura e altura da imagem disponível na câmera
    width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    cout << "largura = " << width << std::endl;
    cout << "altura  = " << height << std::endl;

    //calcula a largura e altura das imagens que irão desenhar os histogramas
    int histw = nbins, histh = nbins / 2;

    //configura cada uma das imagens que desenharão os histogramas
    Mat histImgR(histh, histw, CV_8UC3, cv::Scalar(0, 0, 0));
    Mat histImgG(histh, histw, CV_8UC3, cv::Scalar(0, 0, 0));
    Mat histImgB(histh, histw, CV_8UC3, cv::Scalar(0, 0, 0));

    int soma1 = 0, soma2 = 0;
    int aux = 0, resultado = 0, cont = 0;

    int soma3 = 0, soma4 = 0;
    int resultado1 = 0;

    int soma5 = 0, soma6 = 0;
    int resultado2 = 0;

    //loop infinito de captura das imagens da câmera
    while (1) {
        cap >> image; //captura a imagem
        split(image, planes);//divide a imagem em planos de cores

        //calcula cada um dos histogramas de acordo com cada componentes decor
        calcHist(&planes[0], 1, 0, Mat(), histB, 1,
            &nbins, &histrange,
            uniform, acummulate);
        calcHist(&planes[1], 1, 0, Mat(), histG, 1,
            &nbins, &histrange,
            uniform, acummulate);
        calcHist(&planes[2], 1, 0, Mat(), histR, 1,
            &nbins, &histrange,
            uniform, acummulate);

        //normaliza os histogramas faixas de valores de 0 até a quantidade de linhas da imagem
        normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
        normalize(histG, histG, 0, histImgG.rows, NORM_MINMAX, -1, Mat());
        normalize(histB, histB, 0, histImgB.rows, NORM_MINMAX, -1, Mat());

        if (aux == 0) {
            for (int j = 0; j < nbins; j++) {
                soma1 += cvRound(histR.at<float>(j));
            }
            soma2 = 0;

            for (int j = 0; j < nbins; j++) {
                soma3 += cvRound(histG.at<float>(j));
            }
            soma4 = 0;

            for (int j = 0; j < nbins; j++) {
                soma5 += cvRound(histB.at<float>(j));
            }
            soma6 = 0;
            aux = 1;
        }
        else {
            for (int j = 0; j < nbins; j++) {
                soma2 += cvRound(histR.at<float>(j));
            }
            resultado = soma1 - soma2;
            if (resultado < 0) resultado *= -1;
            soma1 = 0;

            for (int j = 0; j < nbins; j++) {
                soma4 += cvRound(histG.at<float>(j));
            }
            resultado1 = soma3 - soma4;
            if (resultado1 < 0) resultado1 *= -1;
            soma3 = 0;

            for (int j = 0; j < nbins; j++) {
                soma6 += cvRound(histB.at<float>(j));
            }
            resultado2 = soma5 - soma6;
            if (resultado2 < 0) resultado2 *= -1;
            soma5 = 0;
            aux = 0;
        }

        if (resultado > 60 or resultado1 > 60 or resultado2 > 60) {
            cont++;
            cout << "Movimentou - " << cont << endl;
            //cout << "\n" << endl;
            //cout << "Resultado - " << resultado << endl;
            //cout << "resultado1 - " << resultado1 << endl;
            //cout << "resultado2 - " << resultado2 << endl;
        }

        //gera as imagens dos histogramas, inicialmente com a cor 0
        histImgR.setTo(Scalar(0));
        histImgG.setTo(Scalar(0));
        histImgB.setTo(Scalar(0));

        //desenha os histogramas utilizando várias linhas
        for (int i = 0; i < nbins; i++) {
            line(histImgR,
                Point(i, histh),
                Point(i, histh - cvRound(histR.at<float>(i))),
                Scalar(0, 0, 255), 1, 8, 0);
            line(histImgG,
                Point(i, histh),
                Point(i, histh - cvRound(histG.at<float>(i))),
                Scalar(0, 255, 0), 1, 8, 0);
            line(histImgB,
                Point(i, histh),
                Point(i, histh - cvRound(histB.at<float>(i))),
                Scalar(255, 0, 0), 1, 8, 0);
        }

        //copia a imagem de cada um dos histogramas, um abaixo do outro no canto superior esquerdo
        histImgR.copyTo(image(cv::Rect(0, 0, nbins, histh)));
        histImgG.copyTo(image(cv::Rect(0, histh, nbins, histh)));
        histImgB.copyTo(image(cv::Rect(0, 2 * histh, nbins, histh)));

        //exibe a imagem
        imshow("image", image);

        key = waitKey(30);

        //configura para finalizar a aplicação com a tecla ESC
        if (key == 27) break;
    }

    return 0;
}