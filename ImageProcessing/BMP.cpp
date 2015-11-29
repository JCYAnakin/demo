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







