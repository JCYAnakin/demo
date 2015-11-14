#include <iostream>
#include "BMP.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    BMP bmp;
    short ch;
    FILE *fp = fopen("/Users/jason/Xcode/BMPDemo/Demo/test4.bmp", "rb");
    FILE *fpw = fopen("/Users/jason/Xcode/BMPDemo/Demo/grewOut.bmp", "wb");
    FILE *fpw2 = fopen("/Users/jason/Xcode/BMPDemo/Demo/OriginalOut.bmp", "wb");
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
    bmp.allocateData();
    //bmp.showData();
    bmp.getData(fp);
    //bmp.showData();
    //to grew
    bmp.toGrew(fpw);
    //bmp.writeData(fpw);
    //get back to the original graph..
    bmp.toRGB(fpw2);
    
    //#####binarization
    BMP bmp2;
    FILE *fp2 = fopen("/Users/jason/Xcode/BMPDemo/Demo/grewOut.bmp", "rb");
    FILE *fpw3 = fopen("/Users/jason/Xcode/BMPDemo/Demo/binOut.bmp", "wb");
    fread(&ch, 1, sizeof(short), fp2);
    cout<<ch<<endl;
    if(ch != 0x4d42){
        cout<<"the file is not a bmp file!"<<endl;
        return 0;
    }
    bmp2.getHead(fp2);
    bmp2.getInfo(fp2);
    bmp2.allocateData();
    bmp2.getData(fp2);
    bmp2.binarization(fpw3);
    
}