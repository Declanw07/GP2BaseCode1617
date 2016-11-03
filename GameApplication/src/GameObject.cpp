#include "GameObject.h"

GameObject::GameObject()
{

	m_VBO = 0;
	m_VAO = 0;
	m_IBO = 0;

	m_ShaderProgram = 0;

	m_ModelMatrix = mat4(1.0f);

	m_Sampler = 0;
	m_Texture = 0;

	m_Position = vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = vec3(0.0f, 0.0f, 0.0f);
	m_Scale = vec3(1.0f, 1.0f, 1.0f);

	m_TranslationMatrix = mat4(1.0f);
	m_RotationMatrix = mat4(1.0f);
	m_ScaleMatrix = mat4(1.0f);

	m_NumberOfVerts = 0;
	m_NumberOfIndices = 0;

}

GameObject::~GameObject()
{


}

void GameObject::OnRender(mat4 & view, mat4 & projection)
{

	glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VAO);

	GLint MVPLocation = glGetUniformLocation(m_ShaderProgram,
		"MVP");

	if (MVPLocation != -1) {

		mat4 MVP = projection*view*m_ModelMatrix;
		glUniformMatrix4fv(MVPLocation, 1,
			GL_FALSE, glm::value_ptr(MVP));

	}

	glBindSampler(0, m_Sampler);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	GLint textureLocation = glGetUniformLocation(m_ShaderProgram, "diffuseSampler");

	if (textureLocation != -1) {

		glUniform1i(textureLocation, 0);

	}
	
	glDrawElements(GL_TRIANGLES, m_NumberOfIndices, GL_UNSIGNED_INT, 0);

	/*glDrawArrays(GL_TRIANGLES, 0, m_NumberOfVerts);*/

}

void GameObject::OnUpdate()
{

	m_RotationMatrix = eulerAngleXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_TranslationMatrix = translate(m_Position);
	m_ScaleMatrix = scale(m_Scale);


	m_ModelMatrix = m_TranslationMatrix*m_RotationMatrix*m_ScaleMatrix;

}

void GameObject::OnInit()
{


}

void GameObject::OnDestroy()
{

	glDeleteProgram(m_ShaderProgram);

	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);

	glDeleteTextures(1, &m_Texture);
	glDeleteSamplers(1, &m_Sampler);

}

void GameObject::LoadTexture(const string & filename)
{

	m_Texture = loadTextureFromFile(filename);

	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenSamplers(1, &m_Sampler);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_S,
		GL_CLAMP);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_T,
		GL_CLAMP);

}

void GameObject::LoadShaders(const string & vsFilename, const string & fsFilename)
{

	GLuint vertexShaderProgram = 0;
	vertexShaderProgram = loadShaderFromFile(vsFilename,
		VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
	fragmentShaderProgram = loadShaderFromFile(fsFilename,
		FRAGMENT_SHADER);


	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);

	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	logShaderInfo(m_ShaderProgram);

}

void GameObject::CopyVertexData(Vertex * pVerts, unsigned int* Indices, int numberOfVertices, int numberOfIndices)
{

	m_NumberOfIndices = numberOfIndices;
	m_NumberOfIndices = numberOfVertices;

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(unsigned int), Indices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(Vertex), pVerts, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, color));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, texCoord));

}
