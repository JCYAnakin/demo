#include "BMP.hpp"
void BMP::getHead(FILE* fp)
{
    fread(&thisHead,1,sizeof(head),fp);
}
void BMP::showHead()
{
    cout<<"size:"<<thisHead.size<<endl;
    cout<<"reserve1:"<<thisHead.reserve1<<endl;
    cout<<"reserve2:"<<thisHead.reserve2<<endl;
    cout<<"offset:"<<thisHead.offset<<endl;
}
void BMP::getInfo(FILE* fp)
{
    fread(&thisInfo,1,sizeof(information),fp);
}
void BMP::showInfo()
{
    cout<<"size:"<<thisInfo.infoSize<<endl;
    cout<<"col:"<<thisInfo.col<<endl;
    cout<<"row:"<<thisInfo.row<<endl;
    cout<<"planes:"<<thisInfo.planes<<endl;
    cout<<"bitCounts:"<<thisInfo.bitCount<<endl;
    cout<<"compressType:"<<thisInfo.compressionType<<endl;
    cout<<"imageSize:"<<thisInfo.imageSize<<endl;
    cout<<"xPelsPerMeter:"<<thisInfo.XPelsPerMeter<<endl;
    cout<<"yPelsPerMeter:"<<thisInfo.YPelsPerMeter<<endl;
    cout<<"colorNum:"<<thisInfo.colorNum<<endl;
    cout<<"colorImportant:"<<thisInfo.colorImportantNum<<endl;
}
//void BMP::getPalette(FILE* fp)
//{
//    for(unsigned int i=0;i<thisInfo.colorNum;i++)
//    {
//        fread((char *)&(thisPalette[i].rgbB),1,sizeof(unsigned char),fp);
//        fread((char *)&(thisPalette[i].rgbG),1,sizeof(unsigned char),fp);
//        fread((char *)&(thisPalette[i].rgbR),1,sizeof(unsigned char),fp);
//        fread((char *)&(thisPalette[i].rgbRES),1,sizeof(unsigned char),fp);
//    }
//}
//void BMP::showPalette()
//{
//    //cout<<thisPalette<<endl;
//}
void BMP::getData(FILE* fp)
{
    //    thisData = (data*)malloc(thisInfo.imageSize*sizeof(data)/3);
    //    for (int i = 0; i < thisInfo.imageSize / 3; i++) {
    //        thisData[i].blue = 0;
    //        thisData[i].green = 0;
    //        thisData[i].red = 0;
    //    }
    //    fread(thisData,thisInfo.imageSize * sizeof(data)  / 3, 1,fp);
    rList = (unsigned char*)malloc(thisInfo.col*thisInfo.row*sizeof(unsigned char));
    gList = (unsigned char*)malloc(thisInfo.col*thisInfo.row*sizeof(unsigned char));
    bList = (unsigned char*)malloc(thisInfo.col*thisInfo.row*sizeof(unsigned char));
    unsigned char tmp;
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            fread(&tmp, sizeof(unsigned char), 1, fp);
            bList[i * thisInfo.col + j] = tmp;
            fread(&tmp, sizeof(unsigned char), 1, fp);
            gList[i * thisInfo.col + j] = tmp;
            fread(&tmp, sizeof(unsigned char), 1, fp);
            rList[i * thisInfo.col + j] = tmp;
        }
        for(int k = 0; k < numPadBytes ; k++)
        {
            fread(&tmp, sizeof(unsigned char), 1, fp);
        }
    }
    cout<<"get data finish!"<<endl;
}

//void BMP::showData()
//{
//    for (int i = 0; i < thisInfo.imageSize / 3; i++) {
//        cout<<"B:"<<(int)thisData[i].blue<<" "
//        <<"G:"<<(int)thisData[i].green<<" "
//        <<"R:"<<(int)thisData[i].red<<endl;
//    }
//}

//void BMP::writeData(FILE* fpw)
//{
//    unsigned short BMPIndicator= 0x4d42;
//    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
//    fwrite(&thisHead,1,sizeof(head),fpw);
//    fwrite(&thisInfo,1,sizeof(information),fpw);
//
//    int i = 0, j = 0;
//    while(true){
//        if(j >= thisInfo.imageSize)
//            break;
//
//        fwrite(&(thisData[i].blue), 1, sizeof(unsigned char), fpw);
//        ++j;
//
//        if(j >= thisInfo.imageSize)
//            break;
//        fwrite(&(thisData[i].green), 1, sizeof(unsigned char), fpw);
//        ++j;
//
//        if(j >= thisInfo.imageSize)
//            break;
//        fwrite(&(thisData[i].red), 1, sizeof(unsigned char), fpw);
//        ++j;
//
//        ++i;
//    }
//}

void BMP::toGray(FILE* fpw)
{
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    
    //    thisYUV = (yuv*)malloc(sizeof(yuv)*thisInfo.imageSize/3);
    yList = (int*)malloc(sizeof(int)*thisInfo.col*thisInfo.row);
    uList = (int*)malloc(sizeof(int)*thisInfo.col*thisInfo.row);
    vList = (int*)malloc(sizeof(int)*thisInfo.col*thisInfo.row);
    
    int i = 0, j = 0;
    
    //@@@@@@@@@@@@@@@@@test!!
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    int position = 0;//i*thisInfo.height+j;
    
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            yList[position] =(((66 * rList[position] + 129*gList[position] + 25*bList[position]+128)>>8)+16);
            uList[position] = ((-38 * rList[position] -74*gList[position] + 112*bList[position]+128)>>8)+128;
            vList[position] = ((112 * rList[position] -94*gList[position] -18*bList[position]+128)>>8)+128;
            if (yList[position] <= 0) {
                yList[position] = 0;
            }
            else if(yList[position]>255)
            {
                yList[position] = 255;
            }
            fwrite(&(yList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(yList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(yList[position]), 1, sizeof(unsigned char), fpw);
            position++;
        }
        
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"to Gray finish!"<<endl;
}

void BMP::toRGB(FILE* fpw)
{
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    int position = 0;
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            int C = yList[position] - 16;
            int D = uList[position] - 128;
            int E = vList[position] - 128;
            int tmpR, tmpG, tmpB;
            
            tmpR = ( 298 * C + 409 * E + 128) >> 8;
            tmpG = ( 298 * C - 100 * D - 208 * E + 128) >> 8;
            tmpB = ( 298 * C + 516 * D + 128) >> 8;
            
            if(tmpR <= 0)
                tmpR = 0;
            if (tmpR >= 255)
                tmpR =255;
            if(tmpG <= 0)
                tmpG = 0;
            if (tmpG >= 255)
                tmpG =255;
            if(tmpB <= 0)
                tmpB = 0;
            if (tmpB >= 255)
                tmpB =255;
            
            fwrite(&(tmpB), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpG), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpR), 1, sizeof(unsigned char), fpw);
            position++;
        }
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"to RGB finish!"<<endl;
}
void BMP::binarizationALL(FILE *fpw)
{
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    binList = (unsigned char*)malloc(sizeof(unsigned char)*thisInfo.row*thisInfo.col);
    int startPosRow = 0, startPosCol = 0, endPosRow = 100, endPosCol = 100, step = 5, windowSize = 100;
    
    int value = 0;
    int max = -1, min = 3000;
    double totalPixelNum = 0;
    double avgOfFront = 0;
    double avgOfBack = 0;
    double variance = -1;
    double varianceMax = variance;
    int position = 0;
    for(int i = startPosRow; i < thisInfo.row; i++)
    {
        for(int j = startPosCol; j < thisInfo.col; j++)
        {
            value = yList[position];
            if(value < min)
                min = value;
            else if(value > max)
                max = value;
            position++;
        }
    }
    //cout<<"here";
    int threshold = min+1;
    int thresholdFinal = threshold;
    while (threshold<max) {
        double pixelNumFront = 0;
        double pixelNumBack = 0;
        double sumOfFront = 0;
        double sumOfBack = 0;
        position = 0;
        for(int i = 0; i < thisInfo.row; i++)
        {
            for(int j = 0; j < thisInfo.col; j++)
            {
                value = yList[position];
                if(value >= threshold)
                {
                    pixelNumFront++;
                    sumOfFront+=value;
                }
                else{
                    pixelNumBack++;
                    sumOfBack+=value;
                }
                position++;
            }
        }
        totalPixelNum = pixelNumFront + pixelNumBack;
        avgOfFront = sumOfFront / pixelNumFront;
        avgOfBack = sumOfBack / pixelNumBack;
        variance = ((pixelNumFront*pixelNumBack)*((avgOfFront-avgOfBack)*(avgOfFront-avgOfBack)))/(totalPixelNum*totalPixelNum);
        if(variance > varianceMax)
        {
            varianceMax = variance;
            thresholdFinal = threshold;
        }
        ++threshold;
    }
    //cout<<"haha";
    
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    position = 0;//i*thisInfo.height+j;
    
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            unsigned char tmp;
            int haha = yList[position];
            if (yList[position] <= thresholdFinal) {
                tmp = 0;
                binList[position] = tmp;
            }
            else if(yList[position] > thresholdFinal)
            {
                tmp = 255;
                binList[position] = tmp;
            }
            fwrite(&tmp, 1, sizeof(unsigned char), fpw);
            fwrite(&tmp, 1, sizeof(unsigned char), fpw);
            fwrite(&tmp, 1, sizeof(unsigned char), fpw);
            position+=1;
        }
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"binarization finish!"<<endl;
}
void BMP::binarization(FILE *fpw)
{
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    int startPosRow = 0, startPosCol = 0, windowSize = 500, endPosRow = windowSize, endPosCol = windowSize, step = 5;
    unsigned char* dataOut;
    dataOut = (unsigned char*)malloc(sizeof(unsigned char)*thisInfo.row*thisInfo.col);
    
    while(true){
        if(endPosRow > thisInfo.row)
            endPosRow = thisInfo.row;
        if(endPosCol > thisInfo.col)
            endPosCol = thisInfo.col;
        int value = 0;
        int max = -1, min = 3000;
        double totalPixelNum = 0;
        double avgOfFront = 0;
        double avgOfBack = 0;
        double variance = -1;
        double varianceMax = variance;
        //get the max and min value
        int position = startPosRow * thisInfo.col + startPosCol;
        for(int i = startPosRow; i < endPosRow; i++)
        {
            for(int j = startPosCol; j < endPosCol; j++)
            {
                value = yList[position];
                if(value < min)
                    min = value;
                else if(value > max)
                    max = value;
                position++;
            }
        }
        //cout<<"here";
        //get the threshold
        int threshold = min+1;
        int thresholdFinal = threshold;
        while (threshold<max) {
            double pixelNumFront = 0;
            double pixelNumBack = 0;
            double sumOfFront = 0;
            double sumOfBack = 0;
            position = startPosRow * thisInfo.col + startPosCol;
            for(int i = startPosRow; i < endPosRow; i++)
            {
                for(int j = startPosCol; j < endPosCol; j++)
                {
                    value = yList[position];
                    if(value >= threshold)
                    {
                        pixelNumFront++;
                        sumOfFront+=value;
                    }
                    else{
                        pixelNumBack++;
                        sumOfBack+=value;
                    }
                    position++;
                }
            }
            totalPixelNum = pixelNumFront + pixelNumBack;
            avgOfFront = sumOfFront / pixelNumFront;
            avgOfBack = sumOfBack / pixelNumBack;
            variance = ((pixelNumFront*pixelNumBack)*((avgOfFront-avgOfBack)*(avgOfFront-avgOfBack)))/(totalPixelNum*totalPixelNum);
            if(variance > varianceMax)
            {
                varianceMax = variance;
                thresholdFinal = threshold;
            }
            ++threshold;
        }
        //cout<<"haha";
        position = startPosRow * thisInfo.col + startPosCol;
        for(int i = startPosRow; i < endPosRow; i++)
        {
            for(int j = startPosCol; j < endPosCol; j++)
            {
                if(yList[position] > thresholdFinal)
                    dataOut[position] = 255;
                else
                    dataOut[position] = 0;
                position++;
            }
        }
        if(endPosRow == thisInfo.row && endPosCol == thisInfo.col)
            break;
        if(endPosCol == thisInfo.col)
        {
            startPosRow += step;
            endPosRow += step;
            startPosCol = 0;
            endPosCol = windowSize;
        }
        startPosCol+=step;
        endPosCol += step;
        //cout<<"hehe";
        
        //    startPosRow += step;
        //    startPosCol += step;
        //    endPosRow += windowSize;
        //    endPosCol += windowSize;
    }
    
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    int position = 0;//i*thisInfo.height+j;
    
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            //            unsigned char tmp;
            //            int haha = yList[position];
            //            if (yList[position] <= thresholdFinal) {
            //                tmp = 0;
            //            }
            //            else if(yList[position] > thresholdFinal)
            //            {
            //                tmp = 255;
            //            }
            fwrite(&dataOut[position], 1, sizeof(unsigned char), fpw);
            fwrite(&dataOut[position], 1, sizeof(unsigned char), fpw);
            fwrite(&dataOut[position], 1, sizeof(unsigned char), fpw);
            position+=1;
        }
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    
    cout<<"binarization finish!"<<endl;
}
void BMP::dilation(FILE *fpw, unsigned char* dataIn)
{
    //    int structure[5][5] = {0,  0,  0,  0,  0,
    //                           0,  0,  0,  0,  0,
    //                           0,     0,   0,   0,    0,
    //                           0,  0,  0,  0,  0,
    //                           0,  0,  0,  0,  0
    //    };
    //    int coordinateX[5][5] = {-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2};
    //    int coordinateY[5][5] = {-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2};
    
    int structure[13][13];
    int coordinateX[13][13] = {-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,
        -5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,
        -4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,
        -3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,
        -2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,
        2,2,2,2,2,2,2,2,2,2,2,2,2,
        3,3,3,3,3,3,3,3,3,3,3,3,3,
        4,4,4,4,4,4,4,4,4,4,4,4,4,
        5,5,5,5,5,5,5,5,5,5,5,5,5,
        6,6,6,6,6,6,6,6,6,6,6,6,6};
    int coordinateY[13][13] = {-6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6};
    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            structure[i][j] = 0;
        }
    }
    //unsigned char* dataOut;
    dilationList = (unsigned char*)malloc(sizeof(unsigned char)*thisInfo.row*thisInfo.col);
    bool breakable = false;
    for(int i = 0; i < thisInfo.row*thisInfo.col; i++)
    {
        dilationList[i] = dataIn[i];
    }
    for(int i = 6; i < thisInfo.row-6; i++)
    {
        for(int j = 6; j < thisInfo.col-6; j++)
        {
            breakable = false;
            for(int k = 0; k < 13; k++)
            {
                for(int l = 0; l < 13; l++)
                {
                    unsigned char value = dataIn[(i+coordinateX[k][l])*thisInfo.col+j+coordinateY[k][l]];
                    //has a pixel that is 255
                    if(structure[k][l] == 0 && value == 255)
                    {
                        dilationList[i*thisInfo.col+j] = 255;
                        breakable = true;
                        break;
                    }
                }
                if(breakable)
                    break;
            }
        }
    }
    //write file
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    int position = 0;//i*thisInfo.height+j;
    
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            fwrite(&dilationList[position], 1, sizeof(unsigned char), fpw);
            fwrite(&dilationList[position], 1, sizeof(unsigned char), fpw);
            fwrite(&dilationList[position], 1, sizeof(unsigned char), fpw);
            position+=1;
        }
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"dilation finish!"<<endl;
}
void BMP::erosion(FILE *fpw, unsigned char* dataIn)
{
    //    int structure[3][3] = {255,  0,   255,
    //        0,   0,   0,
    //        255,  0,   255};
    //    int coordinateX[3][3] = {-1,-1,-1,0,0,0,1,1,1};
    //    int coordinateY[3][3] = {-1,0,1,-1,0,1,-1,0,1};
    //    int structure[5][5] = {0,  0,  0,  0,  0,
    //        0,  0,  0,  0,  0,
    //        0,     0,   0,   0,    0,
    //        0,  0,  0,  0,  0,
    //        0,  0,  0,  0,  0
    //    };
    //    int coordinateX[5][5] = {-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2};
    //    int coordinateY[5][5] = {-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2};
    
    int structure[13][13];
    int coordinateX[13][13] = {-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,
        -5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,
        -4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,
        -3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,
        -2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,
        2,2,2,2,2,2,2,2,2,2,2,2,2,
        3,3,3,3,3,3,3,3,3,3,3,3,3,
        4,4,4,4,4,4,4,4,4,4,4,4,4,
        5,5,5,5,5,5,5,5,5,5,5,5,5,
        6,6,6,6,6,6,6,6,6,6,6,6,6};
    int coordinateY[13][13] = {-6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6,
        -6,-5,-4,-3,-2,-1, 0, 1, 2,3,4,5,6};
    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            structure[i][j] = 0;
        }
    }
    
    //unsigned char* erosionList;
    erosionList = (unsigned char*)malloc(sizeof(unsigned char)*thisInfo.row*thisInfo.col);
    bool breakable = false;
    for(int i = 0; i < thisInfo.row*thisInfo.col; i++)
    {
        erosionList[i] = dataIn[i];
    }
    for(int i = 6; i < thisInfo.row-6; i++)
    {
        for(int j = 6; j < thisInfo.col-6; j++)
        {
            breakable = false;
            for(int k = 0; k < 13; k++)
            {
                for(int l = 0; l < 13; l++)
                {
                    unsigned char value = dataIn[(i+coordinateX[k][l])*thisInfo.col+j+coordinateY[k][l]];
                    //has a pixel that is not 255
                    if(structure[k][l] == 0 && value != 255)
                    {
                        //erosionList[i*thisInfo.col+j] = 255;
                        breakable = true;
                        break;
                    }
                }
                if(breakable)
                    break;
            }
            if(breakable)//has a pixel not 255
            {
                erosionList[i*thisInfo.col+j] = 0;
            }
            else{
                erosionList[i*thisInfo.col+j] = 255;
            }
        }
    }
    //write file
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    int position = 0;//i*thisInfo.height+j;
    
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            fwrite(&erosionList[position], 1, sizeof(unsigned char), fpw);
            fwrite(&erosionList[position], 1, sizeof(unsigned char), fpw);
            fwrite(&erosionList[position], 1, sizeof(unsigned char), fpw);
            position+=1;
        }
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"erosion finish!"<<endl;
}
void BMP::opening(FILE *fpwTmp, FILE* fpw)
{
    erosion(fpwTmp, binList);
    dilation(fpw, erosionList);
    int count = 0;
    
    cout<<"opening finish!"<<endl;
}
void BMP::closing(FILE *fpwTmp, FILE* fpw)
{
    dilation(fpwTmp, binList);
    erosion(fpw, dilationList);
    cout<<"closinging finish!"<<endl;
}
void BMP::hmt(FILE *fpw)
{
    int structure[5][5] = {0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,
        0,     0,   0,   0,    0,
        0,  0,  0,  0,  0,
        0,  0,  0,  0,  0
    };
    int structureN[5][5];
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(structure[i][j] == 0)
                structureN[i][j] = 255;
            else
                structureN[i][j] = 0;
        }
    }
    int coordinateX[5][5] = {-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2};
    int coordinateY[5][5] = {-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2};
    
    unsigned char* erosionListForHmt;
    unsigned char* erosionListForHmtN;
    unsigned char* result;
    unsigned char* binListN;
    erosionListForHmt = (unsigned char*)malloc(sizeof(unsigned char)*thisInfo.row*thisInfo.col);
    erosionListForHmtN = (unsigned char*)malloc(sizeof(unsigned char)*thisInfo.row*thisInfo.col);
    binListN = (unsigned char*)malloc(sizeof(unsigned char)*thisInfo.row*thisInfo.col);
    result = (unsigned char*)malloc(sizeof(unsigned char)*thisInfo.row*thisInfo.col);
    for(int i = 0; i < thisInfo.row*thisInfo.col; i++)
    {
        erosionListForHmt[i] = binList[i];
    }
    for(int i = 0; i < thisInfo.row*thisInfo.col; i++)
    {
        if(binList[i] == 0)
        {
            binListN[i] = 255;
            erosionListForHmtN[i] = 255;
        }
        else
        {
            binListN[i] = 0;
            erosionListForHmtN[i] = 0;
        }
    }
    
    bool breakable = false;
    for(int i = 2; i < thisInfo.row-2; i++)
    {
        for(int j = 2; j < thisInfo.col-2; j++)
        {
            breakable = false;
            for(int k = 0; k < 5; k++)
            {
                for(int l = 0; l < 5; l++)
                {
                    unsigned char value = binList[(i+coordinateX[k][l])*thisInfo.col+j+coordinateY[k][l]];
                    //has a pixel that is not 255
                    if(structure[k][l] == 0 && value != 255)
                    {
                        //erosionListForHmt[i*thisInfo.col+j] = 255;
                        breakable = true;
                        break;
                    }
                }
                if(breakable)
                    break;
            }
            if(breakable)//has a pixel not 255
            {
                erosionListForHmt[i*thisInfo.col+j] = 0;
            }
            else{
                erosionListForHmt[i*thisInfo.col+j] = 255;
            }
        }
    }
    
    for(int i = 2; i < thisInfo.row-2; i++)
    {
        for(int j = 2; j < thisInfo.col-2; j++)
        {
            breakable = false;
            for(int k = 0; k < 5; k++)
            {
                for(int l = 0; l < 5; l++)
                {
                    unsigned char value = binListN[(i+coordinateX[k][l])*thisInfo.col+j+coordinateY[k][l]];
                    //has a pixel that is not 255
                    if(structure[k][l] == 0 && value != 255)
                    {
                        //erosionListForHmt[i*thisInfo.col+j] = 255;
                        breakable = true;
                        break;
                    }
                }
                if(breakable)
                    break;
            }
            if(breakable)//has a pixel not 255
            {
                erosionListForHmtN[i*thisInfo.col+j] =255;
            }
            else{
                erosionListForHmtN[i*thisInfo.col+j] = 0;
            }
        }
    }
    
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            result[i*thisInfo.col+j] = erosionListForHmt[i*thisInfo.col+j]&erosionListForHmtN[i*thisInfo.col+j];
            //if(result[i*thisInfo.col+j] == 255)
            //cout<<"here";
        }
    }
    
    //write file
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    int position = 0;//i*thisInfo.height+j;
    
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            fwrite(&result[position], 1, sizeof(unsigned char), fpw);
            fwrite(&result[position], 1, sizeof(unsigned char), fpw);
            fwrite(&result[position], 1, sizeof(unsigned char), fpw);
            position+=1;
        }
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"hmt finish!"<<endl;
}
void BMP::HistogramEqualization(FILE* fpw)
{
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);

    int luminate[256];
    double p[256];
    double s[256];
    int res[256];
    int totalPixel = thisInfo.row * thisInfo.col;
    double remainder;
    for(int i = 0; i < 256; i++)
    {
        luminate[i] = 0;
        p[i] = 0;
        s[i] = 0;
        res[i] = 0;
    }
    for(int i = 0; i < thisInfo.row*thisInfo.col; i++)
    {
        luminate[yList[i]]++;
    }
    for(int i = 0; i < 256; i++)
    {
        p[i] = (double)luminate[i]/totalPixel;
    }
    for(int i = 1; i < 256; i++)
    {
        s[i]=s[i-1]+p[i];
    }
    for(int i = 0; i < 256; i++)
    {
        remainder = s[i] * 255 - (int)(s[i] * 255);
        if(remainder >= 0.5)
            res[i] = (int)(s[i]*255)+1;
        else
            res[i] = (int)(s[i]*255);
    }
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    int position = 0;//i*thisInfo.height+j;
    int tmp = 0;
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            tmp = res[yList[position]];
    
            fwrite(&(tmp), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmp), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmp), 1, sizeof(unsigned char), fpw);
            position++;
        }
        
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"Grayscale Histogram finish!"<<endl;
}
void BMP::RGBEachHistogramEqualization(FILE* fpw)
{
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    
    int luminateR[256];
    int luminateG[256];
    int luminateB[256];
    double pR[256];
    double pG[256];
    double pB[256];
    double sR[256];
    double sG[256];
    double sB[256];
    char resR[256];
    char resG[256];
    char resB[256];
    int totalPixel = thisInfo.row * thisInfo.col;
    double remainder;
    for(int i = 0; i < 256; i++)
    {
        luminateR[i] = 0;
        luminateG[i] = 0;
        luminateB[i] = 0;
        pR[i] = 0;
        pG[i] = 0;
        pB[i] = 0;
        sR[i] = 0;
        sG[i] = 0;
        sB[i] = 0;
        resR[i] = 0;
        resG[i] = 0;
        resB[i] = 0;
    }
    for(int i = 0; i < thisInfo.row*thisInfo.col; i++)
    {
        luminateR[rList[i]]++;
        luminateG[gList[i]]++;
        luminateB[bList[i]]++;
    }
    for(int i = 0; i < 256; i++)
    {
        pR[i] = (double)luminateR[i]/totalPixel;
        pG[i] = (double)luminateG[i]/totalPixel;
        pB[i] = (double)luminateB[i]/totalPixel;
    }
    for(int i = 1; i < 256; i++)
    {
        sR[i]=sR[i-1]+pR[i];
        sG[i]=sG[i-1]+pG[i];
        sB[i]=sB[i-1]+pB[i];
    }
    int i = 0;
    for(int i = 0; i < 256; i++)
    {
        remainder = sR[i] * 255 - (int)(sR[i] * 255);
        if(remainder >= 0.5)
            resR[i] = (int)(sR[i]*255)+1;
        else
            resR[i] = (int)(sR[i]*255);
        
        remainder = sG[i] * 255 - (int)(sG[i] * 255);
        if(remainder >= 0.5)
            resG[i] = (int)(sG[i]*255)+1;
        else
            resG[i] = (int)(sG[i]*255);
        
        remainder = sB[i] * 255 - (int)(sB[i] * 255);
        if(remainder >= 0.5)
            resB[i] = (int)(sB[i]*255)+1;
        else
            resB[i] = (int)(sB[i]*255);
    }
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    int position = 0;//i*thisInfo.height+j;
    int tmpR = 0, tmpG = 0, tmpB = 0;
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            tmpR = resR[rList[position]];
            tmpG = resG[gList[position]];
            tmpB = resB[bList[position]];
            
            fwrite(&(tmpB), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpG), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpR), 1, sizeof(unsigned char), fpw);

            position++;
        }
        
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"colorful (Each) Histogram finish!"<<endl;
}
void BMP::RGBHistogramEqualization(FILE* fpw)
{
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    
    int luminate[256];
    double p[256];
    double s[256];
    int res[256];
    int totalPixel = thisInfo.row * thisInfo.col;
    double remainder;
    for(int i = 0; i < 256; i++)
    {
        luminate[i] = 0;
        p[i] = 0;
        s[i] = 0;
        res[i] = 0;
    }
    for(int i = 0; i < thisInfo.row*thisInfo.col; i++)
    {
        luminate[yList[i]]++;
    }
    for(int i = 0; i < 256; i++)
    {
        p[i] = (double)luminate[i]/totalPixel;
    }
    for(int i = 1; i < 256; i++)
    {
        s[i]=s[i-1]+p[i];
    }
    for(int i = 0; i < 256; i++)
    {
        remainder = s[i] * 255 - (int)(s[i] * 255);
        if(remainder >= 0.5)
            res[i] = (int)(s[i]*255)+1;
        else
            res[i] = (int)(s[i]*255);
    }
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    int position = 0;//i*thisInfo.height+j;
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            int C = res[yList[position]] - 16;
            int D = uList[position] - 128;
            int E = vList[position] - 128;
            int tmpR, tmpG, tmpB;
            
            tmpR = ( 298 * C + 409 * E + 128) >> 8;
            tmpG = ( 298 * C - 100 * D - 208 * E + 128) >> 8;
            tmpB = ( 298 * C + 516 * D + 128) >> 8;
            
            if(tmpR <= 0)
                tmpR = 0;
            if (tmpR >= 255)
                tmpR =255;
            if(tmpG <= 0)
                tmpG = 0;
            if (tmpG >= 255)
                tmpG =255;
            if(tmpB <= 0)
                tmpB = 0;
            if (tmpB >= 255)
                tmpB =255;
            
            fwrite(&(tmpB), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpG), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpR), 1, sizeof(unsigned char), fpw);
            position++;

        }
        
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
        
    }
    cout<<"Colorful Histogram finish!"<<endl;
}
void BMP::logarithmic(FILE *fpw)
{
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    
    //@@@@@@@@@@@@@@@@@test!!
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    int position = 0;//i*thisInfo.height+j;
    int Lmax = 0;
    //find the max value
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            if(yList[position] > Lmax)
                Lmax = yList[position];
            position++;
        }
    }
    position = 0;
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            double v = 10;
            double factor = (log(yList[position]+255)-log(255))/(log(Lmax+255)-log(255)); //log2(1+v*yList[position])/log2(1+v);
            int tmpY = factor*255;
            fwrite(&(tmpY), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpY), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpY), 1, sizeof(unsigned char), fpw);
            position++;
        }
        
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"logarithmic finish!"<<endl;
}
void BMP::logarithmicRGB(FILE *fpw)
{
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    
    //@@@@@@@@@@@@@@@@@test!!
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    int position = 0;//i*thisInfo.height+j;
    int Lmax = 0;
    //find the max value
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            if(yList[position] > Lmax)
                Lmax = yList[position];
            position++;
        }
    }
    position = 0;
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            double v = 20;
            double factor = (log(yList[position]+255)-log(255))/(log(Lmax+255)-log(255));//log2(1+v*yList[position])/log2(1+v);
            int tmpY = factor*255;
    
            int C = tmpY - 16;
            int D = uList[position] - 128;
            int E = vList[position] - 128;
            int tmpR, tmpG, tmpB;
            
            tmpR = ( 298 * C + 409 * E + 128) >> 8;
            tmpG = ( 298 * C - 100 * D - 208 * E + 128) >> 8;
            tmpB = ( 298 * C + 516 * D + 128) >> 8;
            
            if(tmpR <= 0)
                tmpR = 0;
            if (tmpR >= 255)
                tmpR =255;
            if(tmpG <= 0)
                tmpG = 0;
            if (tmpG >= 255)
                tmpG =255;
            if(tmpB <= 0)
                tmpB = 0;
            if (tmpB >= 255)
                tmpB =255;
            
            fwrite(&(tmpB), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpG), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpR), 1, sizeof(unsigned char), fpw);
            position++;

        }
        
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"logarithmicRGB finish!"<<endl;
}
void BMP::logarithmicRGBEach(FILE *fpw)
{
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);
    
    //@@@@@@@@@@@@@@@@@test!!
    unsigned int nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * thisInfo.col; // need this many
    //i*thisInfo.height+j;
    unsigned char rmax = 0;
    unsigned char gmax = 0;
    unsigned char bmax = 0;
    //find the max value
    int position = 0;
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            if(rList[position] > rmax)
                rmax = rList[position];
            position++;
        }
    }
    position = 0;
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            if(gList[position] > gmax)
                gmax = gList[position];
            position++;
        }
    }

    position = 0;
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            if(bList[position] > bmax)
                bmax = bList[position];
            position++;
        }
    }

    position = 0;
    for(int i = 0; i < thisInfo.row; i++)
    {
        for(int j = 0; j < thisInfo.col; j++)
        {
            double v = 2000;
            double factor = (log(rList[position]+255)-log(255))/(log(rmax+255)-log(255));//log2(1+v*yList[position])/log2(1+v);//
            int tmpR = factor*255;
            factor = (log(gList[position]+255)-log(255))/(log(gmax+255)-log(255));//log2(1+v*yList[position])/log2(1+v);//
            int tmpG = factor*255;
            factor = (log(bList[position]+255)-log(255))/(log(bmax+255)-log(255));//log2(1+v*yList[position])/log2(1+v);//
            int tmpB = factor*255;
            
            
            if(tmpR <= 0)
                tmpR = 0;
            if (tmpR >= 255)
                tmpR =255;
            if(tmpG <= 0)
                tmpG = 0;
            if (tmpG >= 255)
                tmpG =255;
            if(tmpB <= 0)
                tmpB = 0;
            if (tmpB >= 255)
                tmpB =255;
            
            fwrite(&(tmpB), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpG), 1, sizeof(unsigned char), fpw);
            fwrite(&(tmpR), 1, sizeof(unsigned char), fpw);
            position++;
            
        }
        
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"logarithmicRGB finish!"<<endl;
}
void BMP::translation(FILE *fpw)
{
    int xTrans, yTrans;
    cout<<"Please input the x, y translation:"<<endl;
    cin>>xTrans;
    cin>>yTrans;
    head newHead = thisHead;
    information newInfo = thisInfo;
    newInfo.col+=abs(yTrans);
    newInfo.row+=abs(xTrans);
    int sizeIncrease = (thisInfo.col*xTrans+thisInfo.row*yTrans+yTrans*xTrans)*3;
    newInfo.imageSize += sizeIncrease;
    newHead.size += sizeIncrease;
    
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&newHead,1,sizeof(head),fpw);
    fwrite(&newInfo,1,sizeof(information),fpw);
    int position = 0;
    unsigned int nBytesInRow = ((3 * newInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * newInfo.col; // need this many
    int dark = 0;
    if(xTrans < 0)
    {
        for(int i = 0; i < -xTrans; i++)
        {
            for(int j = 0; j < thisInfo.col + abs(yTrans); j++)
            {
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
            }
            int dump = 0;
            for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
            {
                fwrite(&dump, 1, sizeof(unsigned char), fpw);
            }
            
        }
    }
    
    for(int i = 0; i < thisInfo.row; i++)
    {
        if(yTrans > 0)
        {
            for(int j = 0; j < yTrans; j++)
            {
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
            }
        }
        for(int j = 0; j < thisInfo.col; j++)
        {
//            int tmpR, tmpG, tmpB;
            fwrite(&(bList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(gList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(rList[position]), 1, sizeof(unsigned char), fpw);
            position++;
        }
        if(yTrans < 0)
        {
            for(int j = 0; j < -yTrans; j++)
            {
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
            }
        }
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    if(xTrans > 0)
    {
        for(int i = 0; i < xTrans; i++)
        {
            for(int j = 0; j < thisInfo.col + abs(yTrans); j++)
            {
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
                fwrite(&(dark), 1, sizeof(unsigned char), fpw);
            }
            int dump = 0;
            for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
            {
                fwrite(&dump, 1, sizeof(unsigned char), fpw);
            }
            
        }
    }
    cout<<"Translation finish!"<<endl;
}
void BMP::mirror(FILE *fpw)
{
    char c;
    bool isH;
    cout<<"H or V?:"<<endl;
    cin>>c;
    if(c == 'H'||c == 'h')
        isH = true;
    else if(c == 'V' || c== 'v')
        isH = false;
    else{
        cout<<"Input error! please input 'h/H' or 'v/V'!"<<endl;
    }
//    head newHead = thisHead;
//    information newInfo = thisInfo;
//    if(isH)
//        newInfo.col+=thisInfo.col;
//    else
//        newInfo.row+=thisInfo.row;
//    newInfo.imageSize += thisInfo.imageSize;
//    newHead.size += thisInfo.imageSize;
    
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
//    fwrite(&newHead,1,sizeof(head),fpw);
//    fwrite(&newInfo,1,sizeof(information),fpw);
    fwrite(&thisHead,1,sizeof(head),fpw);
    fwrite(&thisInfo,1,sizeof(information),fpw);

    int position = 0;
    unsigned int nBytesInRow, numPadBytes;
//    if(isH)
//    {
//        nBytesInRow = ((3 * newInfo.col + 3)/4) * 4;
//        numPadBytes = nBytesInRow - 3 * newInfo.col;
//    }
//    else
//    {
        nBytesInRow = ((3 * thisInfo.col + 3)/4) * 4;
        numPadBytes = nBytesInRow - 3 * thisInfo.col;
//    }
    
    if(isH)
    {
        for(int i = 0; i < thisInfo.row; i++)
        {
            position+=thisInfo.col;
//            for(int j = 0; j < thisInfo.col; j++)
//            {
//                fwrite(&(bList[position]), 1, sizeof(unsigned char), fpw);
//                fwrite(&(gList[position]), 1, sizeof(unsigned char), fpw);
//                fwrite(&(rList[position]), 1, sizeof(unsigned char), fpw);
//                position++;
//            }
            int positionSave = position;
            for(int j = 0; j < thisInfo.col; j++)
            {
                fwrite(&(bList[position]), 1, sizeof(unsigned char), fpw);
                fwrite(&(gList[position]), 1, sizeof(unsigned char), fpw);
                fwrite(&(rList[position]), 1, sizeof(unsigned char), fpw);
                position--;
            }
            position = positionSave;
            int dump = 0;
            for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
            {
                fwrite(&dump, 1, sizeof(unsigned char), fpw);
            }
        }
    }
    else{
        position = (thisInfo.row-1) * thisInfo.col;
        for(int i = 0; i < thisInfo.row; i++)
        {
            for(int j = 0; j < thisInfo.col; j++)
            {
                fwrite(&(bList[position]), 1, sizeof(unsigned char), fpw);
                fwrite(&(gList[position]), 1, sizeof(unsigned char), fpw);
                fwrite(&(rList[position]), 1, sizeof(unsigned char), fpw);
                position++;
            }
            position-=(2*thisInfo.col);
            int dump = 0;
            for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
            {
                fwrite(&dump, 1, sizeof(unsigned char), fpw);
            }
        }
//        position = 0;
//        for(int i = 0; i < thisInfo.row; i++)
//        {
//            for(int j = 0; j < thisInfo.col; j++)
//            {
//                fwrite(&(bList[position]), 1, sizeof(unsigned char), fpw);
//                fwrite(&(gList[position]), 1, sizeof(unsigned char), fpw);
//                fwrite(&(rList[position]), 1, sizeof(unsigned char), fpw);
//                position++;
//            }
//            int dump = 0;
//            for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
//            {
//                fwrite(&dump, 1, sizeof(unsigned char), fpw);
//            }
//        }
    }
        cout<<"Mirror finish!"<<endl;
}
//xSize: col!
int twoDimensionToOne(int xCoor, int yCoor, int xSize, int ySize)
{
    return yCoor*xSize+xCoor;
}
//int oneDimensionToTwo(int coorOneDimesion, int xSize, int ySize, bool isX)
//{
//    int a[2], tmp = coorOneDimesion, count = 0;
//    while(tmp >= 0)
//    {
//        tmp -= xSize;
//        count++;
//    }
//    count--;
//    //y
//    a[1] = count;
//    //x
//    a[0] = coorOneDimesion - count * xSize;
//    if(isX)
//        return a[0];
//    else
//        return a[1];
//}
void oneDimensionToTwo(int coorOneDimesion, int xSize, int ySize, int* res)
{
    int tmp = coorOneDimesion, count = 0;
    while(tmp >= 0)
    {
        tmp -= xSize;
        count++;
    }
    count--;
    //y
    res[1] = count;
    //x
    res[0] = coorOneDimesion - count * xSize;
}

void BMP::scale(FILE *fpw)
{
    double xScale, yScale;
    cout<<"Please input the x, y Scale factors:"<<endl;
    cin>>xScale;
    cin>>yScale;
    head newHead = thisHead;
    information newInfo = thisInfo;
    newInfo.col *= xScale;
    newInfo.row *= yScale;
    newInfo.imageSize *= xScale*yScale;
    newHead.size = newInfo.imageSize+54;
    
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&newHead,1,sizeof(head),fpw);
    fwrite(&newInfo,1,sizeof(information),fpw);
    
    unsigned char* newrList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    unsigned char* newgList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    unsigned char* newbList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    
    int position = 0;
    int previousPosition = 0;
    for(int i = 0; i < newInfo.row; i++)
    {
        for(int j = 0; j < newInfo.col; j++)
        {
            int coor[2];
            oneDimensionToTwo(position, newInfo.col, newInfo.row, coor);
            double xCoorPre = coor[0] / xScale;
            double yCoorPre = coor[1] / yScale;
            //interpolation
            if(xCoorPre != (int)xCoorPre || yCoorPre != (int)yCoorPre)
            {
                unsigned char fr1R, fr1G, fr1B, fr2R, fr2G, fr2B, fpR, fpG, fpB;
                int CoorPre11 = twoDimensionToOne((int)xCoorPre, (int)yCoorPre, thisInfo.col, thisInfo.row);
                int CoorPre12 = twoDimensionToOne((int)xCoorPre, (int)yCoorPre+1, thisInfo.col, thisInfo.row);
                int CoorPre21 = twoDimensionToOne((int)xCoorPre+1, (int)yCoorPre, thisInfo.col, thisInfo.row);
                int CoorPre22 = twoDimensionToOne((int)xCoorPre+1, (int)yCoorPre+1, thisInfo.col, thisInfo.row);
                double xMinusx1 = xCoorPre-(int)xCoorPre;
                double x2Minusx = 1-xMinusx1;
                double yMinusy1 = yCoorPre-(int)yCoorPre;
                double y2Minusy = 1-yMinusy1;
                
                if(xCoorPre > thisInfo.col - 1)
                {
                    fr1R = y2Minusy*rList[CoorPre21] + yMinusy1*rList[CoorPre22];
                    fr1G = y2Minusy*gList[CoorPre21] + yMinusy1*gList[CoorPre22];
                    fr1B = y2Minusy*bList[CoorPre21] + yMinusy1*bList[CoorPre22];
                    newrList[position] = fr1R;
                    newgList[position] = fr1G;
                    newbList[position] = fr1B;
                }
                if(yCoorPre > thisInfo.row - 1)
                {
                    fr1R = x2Minusx*rList[CoorPre11] + xMinusx1*rList[CoorPre21];
                    fr1G = x2Minusx*gList[CoorPre11] + xMinusx1*gList[CoorPre21];
                    fr1B = x2Minusx*bList[CoorPre11] + xMinusx1*bList[CoorPre21];
                    newrList[position] = fr1R;
                    newgList[position] = fr1G;
                    newbList[position] = fr1B;
                }
                else
                {
                    fr1R = x2Minusx*rList[CoorPre11] + xMinusx1*rList[CoorPre21];
                    fr1G = x2Minusx*gList[CoorPre11] + xMinusx1*gList[CoorPre21];
                    fr1B = x2Minusx*bList[CoorPre11] + xMinusx1*bList[CoorPre21];
                    fr2R = x2Minusx*rList[CoorPre12] + xMinusx1*rList[CoorPre22];
                    fr2G = x2Minusx*gList[CoorPre12] + xMinusx1*gList[CoorPre22];
                    fr2B = x2Minusx*bList[CoorPre12] + xMinusx1*bList[CoorPre22];
                    fpR = y2Minusy*fr1R+yMinusy1*fr2R;
                    fpG = y2Minusy*fr1G+yMinusy1*fr2G;
                    fpB = y2Minusy*fr1B+yMinusy1*fr2B;
                    
                    newrList[position] = fpR;
                    newgList[position] = fpG;
                    newbList[position] = fpB;
                }
            }
            else{
                previousPosition = twoDimensionToOne((int)xCoorPre, (int)yCoorPre, thisInfo.col, thisInfo.row);
                newrList[position] = rList[previousPosition];
                newgList[position] = gList[previousPosition];
                newbList[position] = bList[previousPosition];
            }
            position++;
        }
    }
    //write to file
    position = 0;
    unsigned int nBytesInRow = ((3 * newInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * newInfo.col; // need this many
    for(int i = 0; i < newInfo.row; i++)
    {
        for(int j = 0; j < newInfo.col; j++)
        {
            fwrite(&(newbList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(newgList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(newrList[position]), 1, sizeof(unsigned char), fpw);
            position++;
        }
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }

    cout<<"Scale finish!"<<endl;
}
void BMP::scaleWithoutIn(FILE *fpw)
{
    double xScale, yScale;
    cout<<"Please input the x, y Scale factors:"<<endl;
    cin>>xScale;
    cin>>yScale;
    head newHead = thisHead;
    information newInfo = thisInfo;
    newInfo.col *= xScale;
    newInfo.row *= yScale;
    newInfo.imageSize *= xScale*yScale;
    newHead.size = newInfo.imageSize+54;
    
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&newHead,1,sizeof(head),fpw);
    fwrite(&newInfo,1,sizeof(information),fpw);
    
    unsigned char* newrList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    unsigned char* newgList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    unsigned char* newbList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    
    int position = 0;
    int previousPosition = 0;
    for(int i = 0; i < newInfo.row; i++)
    {
        for(int j = 0; j < newInfo.col; j++)
        {
            int coor[2];
            oneDimensionToTwo(position, newInfo.col, newInfo.row, coor);
            int xCoorPre = coor[0] / xScale;
            int yCoorPre = coor[1] / yScale;
            previousPosition = twoDimensionToOne(xCoorPre, yCoorPre, thisInfo.col, thisInfo.row);
            newrList[position] = rList[previousPosition];
            newgList[position] = gList[previousPosition];
            newbList[position] = bList[previousPosition];
            position++;
        }
    }
    //write to file
    position = 0;
    unsigned int nBytesInRow = ((3 * newInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * newInfo.col; // need this many
    for(int i = 0; i < newInfo.row; i++)
    {
        for(int j = 0; j < newInfo.col; j++)
        {
            fwrite(&(newbList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(newgList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(newrList[position]), 1, sizeof(unsigned char), fpw);
            position++;
        }
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    
    cout<<"Scale finish!"<<endl;
}
#define PI 3.141592653

void BMP::rotation(FILE *fpw)
{
    //x' = xcos - ysin
    //y' = xsin + ycos
    //x = x'cos + y'sin
    //y = x'sin - y'cos
    double theta;
    cout<<"Please input theta:"<<endl;
    cin>>theta;
    theta = ((theta+180)*PI)/180;
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);
    int xmax, ymax; //xmin, ymin;
    
    int xmaxpre = thisInfo.col/2, ymaxpre = thisInfo.row/2;
    int tmpx[4], tmpy[4];
    //get the xmax, ymax, x
    tmpx[0] = xmaxpre * cosTheta - ymaxpre * sinTheta;
    tmpx[1] = (-xmaxpre * cosTheta) - ymaxpre * sinTheta;
    tmpx[2] = xmaxpre * cosTheta - (-ymaxpre * sinTheta);
    tmpx[3] = (-xmaxpre * cosTheta) - (-ymaxpre * sinTheta);
    xmax = (tmpx[0]>tmpx[1]&&tmpx[0]>tmpx[2]&&tmpx[0]>tmpx[3])?tmpx[0]:(tmpx[1]>tmpx[0]&&tmpx[1]>tmpx[2]&&tmpx[1]>tmpx[3])?tmpx[1]:(tmpx[2]>tmpx[1]&&tmpx[2]>tmpx[0]&&tmpx[2]>tmpx[3])?tmpx[2]:tmpx[3];
    tmpy[0] = xmaxpre * sinTheta + ymaxpre * cosTheta;
    tmpy[1] = (-xmaxpre * sinTheta) + ymaxpre * cosTheta;
    tmpy[2] = xmaxpre * sinTheta + (-ymaxpre * cosTheta);
    tmpy[3] = (-xmaxpre * sinTheta) + (-ymaxpre * cosTheta);
    ymax = (tmpy[0]>tmpy[1]&&tmpy[0]>tmpy[2]&&tmpy[0]>tmpy[3])?tmpy[0]:(tmpy[1]>tmpy[0]&&tmpy[1]>tmpy[2]&&tmpy[1]>tmpy[3])?tmpy[1]:(tmpy[2]>tmpy[1]&&tmpy[2]>tmpy[0]&&tmpy[2]>tmpy[3])?tmpy[2]:tmpy[3];
    
    head newHead = thisHead;
    information newInfo = thisInfo;
    newInfo.col = xmax*2;
    newInfo.row = ymax*2;
    newInfo.imageSize *= (xmax*2/thisInfo.col)*(ymax*2/thisInfo.row);
    newHead.size = newInfo.imageSize+54;
    
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&newHead,1,sizeof(head),fpw);
    fwrite(&newInfo,1,sizeof(information),fpw);
    
    unsigned char* newrList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    unsigned char* newgList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    unsigned char* newbList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    
    int position = 0;
    int previousPosition = 0;
    for(int i = 0; i < newInfo.row; i++)
    {
        for(int j = 0; j < newInfo.col; j++)
        {
            //x = x'cos + y'sin
            //y = x'sin - y'cos
            int coor[2];
            oneDimensionToTwo(position, newInfo.col, newInfo.row, coor);
            coor[0]-=xmax;
            coor[1]-=ymax;
            double xCoorPre = coor[0]*cosTheta+coor[1]*sinTheta;
            double yCoorPre = coor[0]*sinTheta-coor[1]*cosTheta;
            xCoorPre+=xmaxpre;
            yCoorPre+=ymaxpre;
            if(xCoorPre<0||xCoorPre>thisInfo.col||yCoorPre<0||yCoorPre>thisInfo.row)
            {
                newrList[position] = 0;
                newgList[position] = 0;
                newbList[position] = 0;
            }
            //interpolation
            else if(xCoorPre != (int)xCoorPre || yCoorPre != (int)yCoorPre)
            {
                unsigned char fr1R, fr1G, fr1B, fr2R, fr2G, fr2B, fpR, fpG, fpB;
                int CoorPre11 = twoDimensionToOne((int)xCoorPre, (int)yCoorPre, thisInfo.col, thisInfo.row);
                int CoorPre12 = twoDimensionToOne((int)xCoorPre, (int)yCoorPre+1, thisInfo.col, thisInfo.row);
                int CoorPre21 = twoDimensionToOne((int)xCoorPre+1, (int)yCoorPre, thisInfo.col, thisInfo.row);
                int CoorPre22 = twoDimensionToOne((int)xCoorPre+1, (int)yCoorPre+1, thisInfo.col, thisInfo.row);
                double xMinusx1 = xCoorPre-(int)xCoorPre;
                double x2Minusx = 1-xMinusx1;
                double yMinusy1 = yCoorPre-(int)yCoorPre;
                double y2Minusy = 1-yMinusy1;
                
                if(xCoorPre > thisInfo.col - 1)
                {
                    fr1R = y2Minusy*rList[CoorPre21] + yMinusy1*rList[CoorPre22];
                    fr1G = y2Minusy*gList[CoorPre21] + yMinusy1*gList[CoorPre22];
                    fr1B = y2Minusy*bList[CoorPre21] + yMinusy1*bList[CoorPre22];
                    newrList[position] = fr1R;
                    newgList[position] = fr1G;
                    newbList[position] = fr1B;
                }
                if(yCoorPre > thisInfo.row - 1)
                {
                    fr1R = x2Minusx*rList[CoorPre11] + xMinusx1*rList[CoorPre21];
                    fr1G = x2Minusx*gList[CoorPre11] + xMinusx1*gList[CoorPre21];
                    fr1B = x2Minusx*bList[CoorPre11] + xMinusx1*bList[CoorPre21];
                    newrList[position] = fr1R;
                    newgList[position] = fr1G;
                    newbList[position] = fr1B;
                }
                else
                {
                    fr1R = x2Minusx*rList[CoorPre11] + xMinusx1*rList[CoorPre21];
                    fr1G = x2Minusx*gList[CoorPre11] + xMinusx1*gList[CoorPre21];
                    fr1B = x2Minusx*bList[CoorPre11] + xMinusx1*bList[CoorPre21];
                    fr2R = x2Minusx*rList[CoorPre12] + xMinusx1*rList[CoorPre22];
                    fr2G = x2Minusx*gList[CoorPre12] + xMinusx1*gList[CoorPre22];
                    fr2B = x2Minusx*bList[CoorPre12] + xMinusx1*bList[CoorPre22];
                    fpR = y2Minusy*fr1R+yMinusy1*fr2R;
                    fpG = y2Minusy*fr1G+yMinusy1*fr2G;
                    fpB = y2Minusy*fr1B+yMinusy1*fr2B;
                    
                    newrList[position] = fpR;
                    newgList[position] = fpG;
                    newbList[position] = fpB;
                }
            }
            else{
                previousPosition = twoDimensionToOne((int)xCoorPre, (int)yCoorPre, thisInfo.col, thisInfo.row);
                newrList[position] = rList[previousPosition];
                newgList[position] = gList[previousPosition];
                newbList[position] = bList[previousPosition];
            }
            position++;
        }
    }
    //write to file
    position = 0;
    unsigned int nBytesInRow = ((3 * newInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * newInfo.col; // need this many
    for(int i = 0; i < newInfo.row; i++)
    {
        for(int j = 0; j < newInfo.col; j++)
        {
            fwrite(&(newbList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(newgList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(newrList[position]), 1, sizeof(unsigned char), fpw);
            position++;
        }
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    
    cout<<"Rotate finish!"<<endl;
}
void BMP::shear(FILE *fpw)
{
    double dx, dy;
    cout<<"Please input dx, dy: "<<endl;
    cin>>dx;
    cin>>dy;
    int xmax, ymax; //xmin, ymin;
    int xmaxpre = thisInfo.col/2, ymaxpre = thisInfo.row/2;
    //get the xmax, ymax, x
    xmax = xmaxpre + dx * ymaxpre;
    ymax = ymaxpre + dy * xmaxpre;
    
    head newHead = thisHead;
    information newInfo = thisInfo;
    newInfo.col = xmax*2;
    newInfo.row = ymax*2;
    newInfo.imageSize *= (xmax*2/thisInfo.col)*(ymax*2/thisInfo.row);
    newHead.size = newInfo.imageSize+54;
    
    unsigned short BMPIndicator= 0x4d42;
    fwrite(&BMPIndicator,1,sizeof(unsigned short),fpw);
    fwrite(&newHead,1,sizeof(head),fpw);
    fwrite(&newInfo,1,sizeof(information),fpw);
    
    unsigned char* newrList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    unsigned char* newgList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    unsigned char* newbList = (unsigned char*)malloc(newInfo.col*newInfo.row*sizeof(unsigned char));
    
    int position = 0;
    int previousPosition = 0;
    for(int i = 0; i < newInfo.row; i++)
    {
        for(int j = 0; j < newInfo.col; j++)
        {
            int coor[2];
            oneDimensionToTwo(position, newInfo.col, newInfo.row, coor);
            coor[0]-=xmax;
            coor[1]-=ymax;
            double xCoorPre = (dx*coor[1]-coor[0])/(dx*dy-1);
            double yCoorPre = (dy*coor[0]-coor[1])/(dx*dy-1);
            xCoorPre+=xmaxpre;
            yCoorPre+=ymaxpre;
            if(xCoorPre<0||xCoorPre>thisInfo.col||yCoorPre<0||yCoorPre>thisInfo.row)
            {
                newrList[position] = 0;
                newgList[position] = 0;
                newbList[position] = 0;
            }
            //interpolation
            else if(xCoorPre != (int)xCoorPre || yCoorPre != (int)yCoorPre)
            {
                unsigned char fr1R, fr1G, fr1B, fr2R, fr2G, fr2B, fpR, fpG, fpB;
                int CoorPre11 = twoDimensionToOne((int)xCoorPre, (int)yCoorPre, thisInfo.col, thisInfo.row);
                int CoorPre12 = twoDimensionToOne((int)xCoorPre, (int)yCoorPre+1, thisInfo.col, thisInfo.row);
                int CoorPre21 = twoDimensionToOne((int)xCoorPre+1, (int)yCoorPre, thisInfo.col, thisInfo.row);
                int CoorPre22 = twoDimensionToOne((int)xCoorPre+1, (int)yCoorPre+1, thisInfo.col, thisInfo.row);
                double xMinusx1 = xCoorPre-(int)xCoorPre;
                double x2Minusx = 1-xMinusx1;
                double yMinusy1 = yCoorPre-(int)yCoorPre;
                double y2Minusy = 1-yMinusy1;
                
                if(xCoorPre > thisInfo.col - 1)
                {
                    fr1R = y2Minusy*rList[CoorPre21] + yMinusy1*rList[CoorPre22];
                    fr1G = y2Minusy*gList[CoorPre21] + yMinusy1*gList[CoorPre22];
                    fr1B = y2Minusy*bList[CoorPre21] + yMinusy1*bList[CoorPre22];
                    newrList[position] = fr1R;
                    newgList[position] = fr1G;
                    newbList[position] = fr1B;
                }
                if(yCoorPre > thisInfo.row - 1)
                {
                    fr1R = x2Minusx*rList[CoorPre11] + xMinusx1*rList[CoorPre21];
                    fr1G = x2Minusx*gList[CoorPre11] + xMinusx1*gList[CoorPre21];
                    fr1B = x2Minusx*bList[CoorPre11] + xMinusx1*bList[CoorPre21];
                    newrList[position] = fr1R;
                    newgList[position] = fr1G;
                    newbList[position] = fr1B;
                }
                else
                {
                    fr1R = x2Minusx*rList[CoorPre11] + xMinusx1*rList[CoorPre21];
                    fr1G = x2Minusx*gList[CoorPre11] + xMinusx1*gList[CoorPre21];
                    fr1B = x2Minusx*bList[CoorPre11] + xMinusx1*bList[CoorPre21];
                    fr2R = x2Minusx*rList[CoorPre12] + xMinusx1*rList[CoorPre22];
                    fr2G = x2Minusx*gList[CoorPre12] + xMinusx1*gList[CoorPre22];
                    fr2B = x2Minusx*bList[CoorPre12] + xMinusx1*bList[CoorPre22];
                    fpR = y2Minusy*fr1R+yMinusy1*fr2R;
                    fpG = y2Minusy*fr1G+yMinusy1*fr2G;
                    fpB = y2Minusy*fr1B+yMinusy1*fr2B;
                    
                    newrList[position] = fpR;
                    newgList[position] = fpG;
                    newbList[position] = fpB;
                }
            }
            else{
                previousPosition = twoDimensionToOne((int)xCoorPre, (int)yCoorPre, thisInfo.col, thisInfo.row);
                newrList[position] = rList[previousPosition];
                newgList[position] = gList[previousPosition];
                newbList[position] = bList[previousPosition];
            }
            position++;
        }
    }
    //write to file
    position = 0;
    unsigned int nBytesInRow = ((3 * newInfo.col + 3)/4) * 4;
    unsigned int numPadBytes = nBytesInRow - 3 * newInfo.col; // need this many
    for(int i = 0; i < newInfo.row; i++)
    {
        for(int j = 0; j < newInfo.col; j++)
        {
            fwrite(&(newbList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(newgList[position]), 1, sizeof(unsigned char), fpw);
            fwrite(&(newrList[position]), 1, sizeof(unsigned char), fpw);
            position++;
        }
        int dump = 0;
        for(int k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
        {
            fwrite(&dump, 1, sizeof(unsigned char), fpw);
        }
    }
    cout<<"Shear finish!"<<endl;
    
}






