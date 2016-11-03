#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"

class GameObject {

public:

	GameObject();
	~GameObject();

	void OnRender(mat4& view, mat4& projection);
	void OnUpdate();
	void OnInit();
	void OnDestroy();
	void LoadTexture(const string& filename);
	void LoadShaders(const string& vsFilename, const string& fsFilename);
	void CopyVertexData(Vertex* pVertex, unsigned int* Indices, int numberOfVertices, int numberOfIndices);

private:

	GLuint m_ShaderProgram;
	GLuint m_Texture;
	GLuint m_Sampler;
	mat4 m_ModelMatrix;

	GLuint m_VBO;
	GLuint m_VAO;
	GLuint m_IBO;

	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;

	mat4 m_TranslationMatrix;
	mat4 m_RotationMatrix;
	mat4 m_ScaleMatrix;

	int m_NumberOfVerts;
	int m_NumberOfIndices;


protected:

	

};





#endif