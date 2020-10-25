#version 330 core
layout(location = 6) in vec3 aPos; //坐标
layout(location = 7) in vec3 aColor; //RGB
layout(location = 8) in vec2 aTexCoord; //纹理

//uniform mat4 transform; //变换矩阵
uniform mat4 modelMat; //模型矩阵
uniform mat4 viewMat; //观察矩阵
uniform mat4 projMat; //投影矩阵

out vec4 vertexColor;
out vec2 TexCoord;
void main()
{
//gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
vertexColor = vec4( aColor.x, aColor.y, aColor.z, 1.0 );
TexCoord = aTexCoord;
}