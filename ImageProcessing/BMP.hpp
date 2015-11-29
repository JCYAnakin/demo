#ifndef BMP_hpp
#define BMP_hpp

#include <iostream>
#include <math.h>
using namespace::std;
typedef struct                          //4*2+2*2+2=14
{
    //unsigned short type;
    unsigned int size;
    unsigned short reserve1;
    unsigned short reserve2;
    unsigned int offset;
}head;
typedef struct
{
    unsigned int infoSize;//信息头大小       4*9+2*2 = 40
    unsigned int col;//图像宽度
    unsigned int row;//图像高度
    unsigned short planes;//位平面数，必须为1
    unsigned short bitCount;//每像素位数
    unsigned int  compressionType; //压缩类型
    unsigned int  imageSize; //压缩图像大小字节数
    unsigned int  XPelsPerMeter; //水平分辨率
    unsigned int  YPelsPerMeter; //垂直分辨率
    unsigned int  colorNum; //位图实际用到的色彩数
    unsigned int  colorImportantNum; //本位图中重要的色彩数
}information;
typedef struct
{
    unsigned char rgbB; //该颜色的蓝色分量
    unsigned char rgbG; //该颜色的绿色分量
    unsigned char rgbR; //该颜色的红色分量
    unsigned char rgbRES; //保留值
}palette;
typedef struct
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
}data;
typedef struct
{
    int Y;
    int U;
    int V;
}yuv;

class BMP{
public:
    head thisHead;
    information thisInfo;
    palette thisPalette[256];
    //data* thisData;
    unsigned char* rList;
    unsigned char* gList;
    unsigned char* bList;
    //yuv* thisYUV;
    int* yList;
    int* uList;
    int* vList;
    unsigned char* binList;
    unsigned char* dilationList;
    unsigned char* erosionList;
    
    void getHead(FILE* fp);
    void getInfo(FILE* fp);
    void getPalette(FILE* fp);
    void getData(FILE* fp);
    void showHead();
    void showInfo();
    void showPalette();
    void showData();
    void writeData(FILE* fpw);
    void toGray(FILE* fpw);
    void toRGB(FILE* fpw);
    
    void binarization(FILE* fp);
    void binarizationALL(FILE* fp);
    void dilation(FILE* fp, unsigned char* dataIn);
    void erosion(FILE* fp, unsigned char* dataIn);
    void opening(FILE* fpwTmp, FILE* fpw);
    void closing(FILE* fpwTmp, FILE* fpw);
    void hmt(FILE* fpw);
    
    void HistogramEqualization(FILE* fpwH);
    void RGBEachHistogramEqualization(FILE* fpwH);
    void RGBHistogramEqualization(FILE* fpwH);
    void logarithmic(FILE* fpw);
    void logarithmicRGB(FILE* fpw);
    void logarithmicRGBEach(FILE* fpw);
};

#endif /* BMP_hpp */
