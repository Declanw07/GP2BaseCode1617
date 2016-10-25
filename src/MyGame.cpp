#include "MyGame.h"


//struct Vertex {
//
//	vec3 position;
//	vec4 color;
//	vec2 texCoord;
//
//};

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";

MyGame::MyGame(){

	m_TestObject = nullptr;

}

MyGame::~MyGame(){


}

void MyGame::initScene(){

	Vertex verts[] = {
		{vec3(-0.5f, -0.5f, 0.0f), vec4(0.8f, 0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},
		{vec3(-0.5f, 0.5f, 0.0f), vec4(0.0f, 0.8f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
		{vec3(0.5f, -0.5f, 0.0f), vec4(0.0f, 0.0f, 0.8f, 1.0f), vec2(1.0f, 1.0f)},
		{vec3(0.5f, 0.5f, 0.0f), vec4(0.0f, 0.8f, 0.8f, 1.0f), vec2(1.0f, 0.0f)}
	};


	m_TestObject = new GameObject;

	

	std::string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";

	std::string fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";

	m_TestObject->loadShaders(vsPath, fsPath);

	string texturePath = ASSET_PATH + TEXTURE_PATH +
		"/texture.png";
	m_TestObject->loadTexture(texturePath);

	m_TestObject->CopyVertexData(verts, 4);

}

void MyGame::destroyScene(){

	if (m_TestObject) {

		m_TestObject->OnDestroy();
		delete(m_TestObject);
		m_TestObject = nullptr;

	}

}

void MyGame::render() {

	GameApplication::render();

	m_TestObject->OnRender(m_ViewMatrix, m_ProjMatrix);

}

void MyGame::udpate(){

	m_ProjMatrix = perspective(radians(45.0f),
		(float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
	m_ViewMatrix = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f));
	m_ModelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, -1.0f));

	m_TestObject()->OnUpdate();

}
