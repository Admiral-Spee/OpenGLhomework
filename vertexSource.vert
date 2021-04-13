#version 330 core
layout(location = 6) in vec3 aPos; //����
layout(location = 7) in vec3 aColor; //RGB
layout(location = 8) in vec2 aTexCoord; //����

//uniform mat4 transform; //�任����
uniform mat4 modelMat; //ģ�;���
uniform mat4 viewMat; //�۲����
uniform mat4 projMat; //ͶӰ����

out vec4 vertexColor;
out vec2 TexCoord;
void main()
{
//gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
vertexColor = vec4( aColor.x, aColor.y, aColor.z, 1.0 );
TexCoord = aTexCoord;
}