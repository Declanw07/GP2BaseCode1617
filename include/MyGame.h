#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"

class MyGame:public GameApplication
{
public:
	MyGame();
	~MyGame();

	void initScene();
	void destroyScene();
	void render();
	void udpate();


private:
	GLuint m_VBO;
	GLuint m_VAO;
	GLuint m_IBO;

	GLuint m_ShaderProgram;
	GLuint m_Texture;
	GLuint m_Sampler;

	//matrices
	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;
	mat4 m_ModelMatrix;

	GameObject* m_TestObject;
	GameObject* m_TeaPot;

};
#endif
