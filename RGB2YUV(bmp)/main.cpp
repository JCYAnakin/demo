#include <iostream>
#include "BMP.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    BMP bmp;
    short ch;
    FILE *fp = fopen("/Users/jason/Xcode/Demo/Demo/test2.bmp", "rb");
    FILE *fpw = fopen("/Users/jason/Xcode/Demo/Demo/out.bmp", "wb");
    
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
    
    bmp.toGrew(fpw);
    //bmp.writeData(fpw);
    
    BMP bmp2;
    FILE *fp2 = fopen("/Users/jason/Xcode/Demo/Demo/out.bmp", "rb");
    FILE *fpw2 = fopen("/Users/jason/Xcode/Demo/Demo/out2.bmp", "wb");
    bmp2.getHead(fp2);
    bmp2.getInfo(fp2);
    bmp2.allocateData();
    bmp2.getData(fp2);
    bmp.toRGB(fpw2);

    
}