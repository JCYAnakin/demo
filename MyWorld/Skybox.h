//
//  Skybox.h
//  TankSim
//
//  Created by Matthew Tesfaldet on 2014-11-23.
//  Copyright (c) 2014 Matthew Tesfaldet. All rights reserved.
//

#ifndef Skybox_h
#define Skybox_h
class Skybox {
private:
    //material
    GLfloat matAmbient[4]={0.0,0.0,0.0,1.0};
    GLfloat matSpecular[4] = {1.0,1.0,1.0,1.0};
    GLfloat matDiffuse[4] = {1.0,1.0,1.0,1.0};
    GLfloat matShininess[1] = {0.0};

    int textureNum[6] = {1,2,3,4,5,6};
    RGBpixmap skyPixelStore[6];
    char skyboxFileName[6][100] ={"/Users/jason/Xcode/MyWorld/textures/back.bmp", "/Users/jason/Xcode/MyWorld/textures/left.bmp","/Users/jason/Xcode/MyWorld/textures/front.bmp","/Users/jason/Xcode/MyWorld/textures/right.bmp","/Users/jason/Xcode/MyWorld/textures/top.bmp","/Users/jason/Xcode/MyWorld/textures/bottom.bmp"};
  
    
public:
    void setTextures() {
        for(int i = 0; i < 6; i++)
        {
            //readBMPFile(skyPixelStore[i], skyboxFileName[i]);
            readBMPFile(&skyPixelStore[i], skyboxFileName[i]);
            setTexture(&skyPixelStore[i], textureNum[i]);
        }
  }
    
  void DrawSkybox(float lookFromx, float lookFromy, float lookFromz, float upx, float upy, float upz, bool flag) {
    glPushMatrix();
    glLoadIdentity();
    if(flag)
        gluLookAt(0,0,0, lookFromx, -lookFromy, lookFromz, upx, upy, upz);
    
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);
    
    // Just in case we set all vertices to white.
    glColor4f(1,1,1,1);
    
    // Render the front quad
    glBindTexture(GL_TEXTURE_2D, textureNum[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(  20.0f, -20.0f, -20.0f );
    glTexCoord2f(1, 0);
    glVertex3f( -20.0f, -20.0f, -20.0f );
    glTexCoord2f(1, 1);
    glVertex3f( -20.0f,  20.0f, -20.0f );
    glTexCoord2f(0, 1);
    glVertex3f(  20.0f,  20.0f, -20.0f );
    glEnd();
    
    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, textureNum[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(  20.0f, -20.0f,  20.0f );
    glTexCoord2f(1, 0);
    glVertex3f(  20.0f, -20.0f, -20.0f );
    glTexCoord2f(1, 1);
    glVertex3f(  20.0f,  20.0f, -20.0f );
    glTexCoord2f(0, 1);
    glVertex3f(  20.0f,  20.0f,  20.0f );
    glEnd();
    
    // Render the back quad
    glBindTexture(GL_TEXTURE_2D, textureNum[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f( -20.0f, -20.0f,  20.0f );
    glTexCoord2f(1, 0);
    glVertex3f(  20.0f, -20.0f,  20.0f );
    glTexCoord2f(1, 1);
    glVertex3f(  20.0f,  20.0f,  20.0f );
    glTexCoord2f(0, 1);
    glVertex3f( -20.0f,  20.0f,  20.0f );
    glEnd();
    
    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, textureNum[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f( -20.0f, -20.0f, -20.0f );
    glTexCoord2f(1, 0);
    glVertex3f( -20.0f, -20.0f,  20.0f );
    glTexCoord2f(1, 1);
    glVertex3f( -20.0f,  20.0f,  20.0f );
    glTexCoord2f(0, 1);
    glVertex3f( -20.0f,  20.0f, -20.0f );
    glEnd();
    
    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, textureNum[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f( -20.0f,  20.0f, -20.0f );
    glTexCoord2f(0, 0);
    glVertex3f( -20.0f,  20.0f,  20.0f );
    glTexCoord2f(1, 0);
    glVertex3f(  20.0f,  20.0f,  20.0f );
    glTexCoord2f(1, 1);
    glVertex3f(  20.0f,  20.0f, -20.0f );
    glEnd();
    
    // Render the bottom quad
    glBindTexture(GL_TEXTURE_2D, textureNum[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f( -20.0f, -20.0f, -20.0f );
    glTexCoord2f(0, 1);
    glVertex3f( -20.0f, -20.0f,  20.0f );
    glTexCoord2f(1, 1);
    glVertex3f(  20.0f, -20.0f,  20.0f );
    glTexCoord2f(1, 0);
    glVertex3f(  20.0f, -20.0f, -20.0f );
    glEnd();
    
    // Restore enable bits and matrix
    glPopAttrib();
    glPopMatrix();
  };
  
  void setTextureID(int ID[6]) {
      textureNum[0] = ID[0];
      textureNum[1] = ID[1];
      textureNum[2] = ID[2];
      textureNum[3] = ID[3];
      textureNum[4] = ID[4];
      textureNum[5] = ID[5];
  };
  
  void setFileName(const char** fileName) {
    strncpy(skyboxFileName[0], fileName[0], 100);
    skyboxFileName[0][99] = '\0';
    strncpy(skyboxFileName[1], fileName[1], 100);
    skyboxFileName[1][99] = '\0';
    strncpy(skyboxFileName[2], fileName[2], 100);
    skyboxFileName[2][99] = '\0';
    strncpy(skyboxFileName[3], fileName[3], 100);
    skyboxFileName[3][99] = '\0';
    strncpy(skyboxFileName[4], fileName[4], 100);
    skyboxFileName[4][99] = '\0';
    strncpy(skyboxFileName[5], fileName[5], 100);
    skyboxFileName[5][99] = '\0';
  }
};

#endif
