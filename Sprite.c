#include <GL/glut.h>
#include <stdio.h> 
#include "SOIL/SOIL.h"
#include <stdlib.h>
#include <string.h>

int w,h; 

ll 
GLuint buffer[11];
//GLuint * buffer;
GLuint * animations[8];
int animationFrameNumber[8] = {10, 12, 7, 8, 9, 11, 10, 15};
int spritePointer = 0, frameNumber = 9, velocidadeFrame = 5, nextSpriteCountDown = 0, animationPointer = 0;



void colocaImagem(GLuint texid1){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texid1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
        } 


void IncrementaApontador(){
	nextSpriteCountDown++;
	if(nextSpriteCountDown == velocidadeFrame)
	{
		nextSpriteCountDown = 0;
		spritePointer++;
		if(spritePointer == frameNumber)
			spritePointer = 0;
	}
}
void DesenhaNaTela(void)
{ 

    	colocaImagem(animations[animationPointer][spritePointer]); 
	IncrementaApontador();

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT); 

    // Reset transformations
    glLoadIdentity(); 

    gluLookAt(  0.0f, 0.0f, 5.0f,
                        0.0f, 0.0f,  0.0f,
                        0.0f, 1.0f,  0.0f); 

   

        glBegin(GL_QUADS); 
	//glColor3f(1.0f,0.0f,0.0f);
        glTexCoord3f(-1,1,0);glVertex3f(-1, 1, 0);
        glTexCoord3f(1,1,0);glVertex3f( 1, 1, 0);
        glTexCoord3f(1,-1,0); glVertex3f( 1,-1, 0);
        glTexCoord3f(-1,-1,0);  glVertex3f(-1,-1, 0); 

        glEnd(); 

   

    glutSwapBuffers();
} 



GLuint * LoadAnimation(char * Directory_name, char * Initial_Name, int sprite_number ){
	char fileName[13];
	char finalName[23];
	GLuint * sprites = malloc(sizeof(GLuint) * sprite_number);
	for(int i = 0; i< sprite_number;i++){
		char fileNumber[7];
		
		if(i<10) {fileNumber[0] = '0'; fileNumber[1] = i + '0';}
		else {fileNumber[0] = '1'; fileNumber[1] = i - 10 + '0'; }
		
		fileNumber[2] = '\0';
		strcat(fileNumber, ".png");
		fileName[0] = '\0';
		strcat(fileName, Initial_Name);
		
		strcat(fileName,fileNumber);
		
		finalName[0] = '\0';
		strcat(finalName, Directory_name);
		strcat(finalName, fileName);
		printf("%s\n", finalName);
		sprites[i] = SOIL_load_OGL_texture(finalName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	}
	return sprites;
}

void CarregaTodasAnimacoes(){
	animations[0] = LoadAnimation("textures/Idle/","bc000_", animationFrameNumber[0]);
	animations[1] = LoadAnimation("textures/Walking/","bc030_", animationFrameNumber[1]);
	animations[2] = LoadAnimation("textures/Attack1/","bc200_", animationFrameNumber[2]);
	animations[3] = LoadAnimation("textures/Attack2/","bc201_", animationFrameNumber[3]);
	animations[4] = LoadAnimation("textures/Attack3/","bc202_", animationFrameNumber[4]);
	animations[5] = LoadAnimation("textures/Attack4/","bc203_", animationFrameNumber[5]);
	animations[6] = LoadAnimation("textures/Attack5/","bc208_", animationFrameNumber[6]);
	animations[7] = LoadAnimation("textures/Attack6/","bc210_", animationFrameNumber[7]);
}

void Inicializa (void)
{
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	CarregaTodasAnimacoes();
	
} 
void SetAnimation(char key){
	int number = key - '0';
	if(number < 8 && number >= 0)
	{
		animationPointer = number;
		spritePointer = 0;
		frameNumber = animationFrameNumber[number];
	}

		
}
void Teclado(unsigned char key, int x, int y){
    
    SetAnimation((char)key);

} 







void AlteraTamanhoTela(int w, int h) { 

// Função é chamada caso a tela tenha tido alterada 

    if (h == 0)
        h = 1; 

    float proporsao =  w * 1.0 / h; 

    glMatrixMode(GL_PROJECTION); 

    glLoadIdentity(); 

    glViewport(0, 0, w, h); 

    gluPerspective(45.0f, proporsao, 0.1f, 100.0f); 

    glMatrixMode(GL_MODELVIEW);
} 

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Sprite");
        Inicializa();
    glutDisplayFunc(DesenhaNaTela);
    glutIdleFunc(DesenhaNaTela);
    glutReshapeFunc(AlteraTamanhoTela);
    glutKeyboardFunc( Teclado );
    glutMainLoop();
}
