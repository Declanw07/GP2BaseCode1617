#version 410


layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec4 inColor;
layout(location=2) in vec2 vertexTextureCoords;

out vec2 vertexTextureCoordsOut;
out vec4 OutputColor;

uniform mat4 MVP;

void main(){

OutputColor = inColor;
vertexTextureCoordsOut=vertexTextureCoords;
gl_Position = MVP * vec4(vertexPosition, 1.0);

}