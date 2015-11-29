#include <iostream>
#include "BMP.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    BMP bmp;
    short ch;
    FILE *fp = fopen("/Users/jason/Xcode/BMPDemo/Demo/222.bmp", "rb");
    FILE *fpw = fopen("/Users/jason/Xcode/BMPDemo/Demo/grayOut.bmp", "wb");
//    FILE *fpw2 = fopen("/Users/jason/Xcode/BMPDemo/Demo/OriginalOut.bmp", "wb");
//    FILE *fpw3 = fopen("/Users/jason/Xcode/BMPDemo/Demo/binOut.bmp", "wb");
//    FILE *fpw4 = fopen("/Users/jason/Xcode/BMPDemo/Demo/dilationOut.bmp", "wb");
//    FILE *fpw5 = fopen("/Users/jason/Xcode/BMPDemo/Demo/erosionOut.bmp", "wb");
//    FILE *fpw6 = fopen("/Users/jason/Xcode/BMPDemo/Demo/openingTmp.bmp", "wb");
//    FILE *fpw7 = fopen("/Users/jason/Xcode/BMPDemo/Demo/openingOut.bmp", "wb");
//    FILE *fpw8 = fopen("/Users/jason/Xcode/BMPDemo/Demo/closingTmp.bmp", "wb");
//    FILE *fpw9 = fopen("/Users/jason/Xcode/BMPDemo/Demo/closingOut.bmp", "wb");
//    FILE *fpw10 = fopen("/Users/jason/Xcode/BMPDemo/Demo/hmtOut.bmp", "wb");
    FILE* fpwH = fopen("/Users/jason/Xcode/BMPDemo/Demo/HisOut.bmp", "wb");
    FILE* fpwHRGBEach = fopen("/Users/jason/Xcode/BMPDemo/Demo/RGBHisEachOut.bmp", "wb");
    FILE* fpwHRGB = fopen("/Users/jason/Xcode/BMPDemo/Demo/RGBHisOut.bmp", "wb");
    FILE* fpwL = fopen("/Users/jason/Xcode/BMPDemo/Demo/logarithmicOut.bmp", "wb");
    FILE* fpwLRGB = fopen("/Users/jason/Xcode/BMPDemo/Demo/logarithmicRGBOut.bmp", "wb");
    fread(&ch, 1, sizeof(short), fp);
    cout<<ch<<endl;
    //0x4d42: the right start signal
    if(ch != 0x4d42){
        cout<<"the file is not a bmp file!"<<endl;
        return 0;
    }
    
    bmp.getHead(fp);
    bmp.showHead();
    bmp.getInfo(fp);
    bmp.showInfo();
    
    //bmp.getPalette(fp);
    //bmp.allocateData();
    //bmp.showData();
    bmp.getData(fp);
    //bmp.showData();
    //to gray
    bmp.toGray(fpw);
    //get back to the original graph..
    //bmp.toRGB(fpw2);
    
//    //binarization
//    bmp.binarizationALL(fpw3);
//    //bmp.binarization(fpw3);
//    bmp.dilation(fpw4, bmp.binList);
//    bmp.erosion(fpw5, bmp.binList);
//    bmp.opening(fpw6, fpw7);
//    bmp.closing(fpw8, fpw9);
//    bmp.hmt(fpw10);
    
    //histogram
    bmp.HistogramEqualization(fpwH);
    bmp.RGBEachHistogramEqualization(fpwHRGBEach);
    bmp.RGBHistogramEqualization(fpwHRGB);
    bmp.logarithmic(fpwL);
    bmp.logarithmicRGBEach(fpwLRGB);
    
}