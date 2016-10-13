#include "MyGame.h"


struct Vertex {

	float x, y, z;
	float r, g, b, a;

};

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";

MyGame::MyGame(){


}

MyGame::~MyGame(){


}

void MyGame::initScene(){

	Vertex verts[] = {
		{-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f},
		{-0.5f, 0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.8f, 1.0f},
		{0.5f, 0.5f, 0.0f, 0.0f, 0.8f, 0.8f, 1.0f}
	};

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), verts, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(3 * sizeof(float)));

	GLuint vertexShaderProgram = 0;
	std::string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath,
		VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath,
		FRAGMENT_SHADER);

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);
	logShaderInfo(m_ShaderProgram);

	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

}

void MyGame::destroyScene(){

	glDeleteProgram(m_ShaderProgram);

	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);

}

void MyGame::render(){

	glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VAO);

	GLint MVPLocation = glGetUniformLocation(m_ShaderProgram,
		"MVP");

	if (MVPLocation != -1) {

		mat4 MVP = m_ProjMatrix* m_ViewMatrix* m_ModelMatrix;
		glUniformMatrix4fv(MVPLocation, 1,
			GL_FALSE, glm::value_ptr(MVP));

	}
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}

void MyGame::udpate(){

	m_ProjMatrix = perspective(radians(45.0f),
		(float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
	m_ViewMatrix = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f));
	m_ModelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, -1.0f));

}
