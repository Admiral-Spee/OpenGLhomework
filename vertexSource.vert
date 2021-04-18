#version 330 core
layout(location = 6) in vec3 aPos; //����
layout(location = 9) in vec3 aNormal;

//uniform mat4 transform; //�任����
uniform mat4 modelMat; //ģ�;���
uniform mat4 viewMat; //�۲����
uniform mat4 projMat; //ͶӰ����

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