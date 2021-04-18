#version 330 core
layout(location = 6) in vec3 aPos; //坐标
layout(location = 9) in vec3 aNormal;

//uniform mat4 transform; //变换矩阵
uniform mat4 modelMat; //模型矩阵
uniform mat4 viewMat; //观察矩阵
uniform mat4 projMat; //投影矩阵

//out vec4 vertexColor;
//out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

void main()
{
gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
FragPos = (modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0)).xyz;
Normal = mat3(transpose(inverse(modelMat))) * aNormal;
}