#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Camera.h"




//GLfloat vertices[] = {
//	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};

glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f, -4.0f),
  glm::vec3( 2.0f,  0.0f, -4.0f),
  glm::vec3(-2.0f,  0.0f, -4.0f),
  glm::vec3( 0.0f,  2.0f, -4.0f),
  glm::vec3( 2.0f,  2.0f, -4.0f),
  glm::vec3(-2.0f,  2.0f, -4.0f),
  glm::vec3( 0.0f, -2.0f, -4.0f),
  glm::vec3( 2.0f, -2.0f, -4.0f),
  glm::vec3(-2.0f, -2.0f, -4.0f),
  glm::vec3( 0.0f,  4.0f, -4.0f)
};

void processInput(GLFWwindow* window);

int main() //主函数部分
{
	
	glfwInit();  //初始化GLFW库
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "My OpenGL", NULL, NULL);  //创建一个800*600的窗口
	if (window == NULL)  //窗口创建失败的返回值
	{
		std::cout << "Open Window Failed." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	glewExperimental = true;  //初始化GLEW库
	if (glewInit() != GLEW_OK)  //初始化失败返回值
	{
		std::cout << "Init GLEW Failed." << std::endl;
		glfwTerminate();
		return -1;
	}


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);  //告知OpenGL渲染窗口大小
	//glEnable(GL_CULL_FACE);  //剔除背面
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //线框渲染
	glEnable(GL_DEPTH_TEST);

	Shader* testShader = new Shader("vertexSource.adm", "fragmentSource.adm");

	unsigned int VAO;  //建立一个VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);  //绑定

	unsigned int VBO;  //建立VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //绑定
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);  //绑定
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//位置属性
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);
	//颜色属性
	//glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)) );
	//glEnableVertexAttribArray(7);
	//贴图属性
	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(8);

	//生成纹理A
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);
	int image_width, image_height, image_nrChannel;
	stbi_set_flip_vertically_on_load(true); //颠倒图像
	unsigned char* data = stbi_load("container.adm", &image_width, &image_height, &image_nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "load image failed." << std::endl;
	}
	stbi_image_free(data);

	//生成纹理B
	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);
	unsigned char* data2 = stbi_load("awesomeface.adm", &image_width, &image_height, &image_nrChannel, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "load image failed." << std::endl;
	}
	stbi_image_free(data2);

	//坐标变换矩阵
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(-1.0f, 0, 0)); //位移
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0, 0, 1.0f)); //旋转
	//trans = glm::scale(trans, glm::vec3(1.5f, 1.5f, 2.0f)); //缩放

	//
	Camera camera(glm::vec3(0,0,3.0f), glm::vec3(0,0,0), glm::vec3(0,1.0f,0));

	
	
	//创建一个模型矩阵
	glm::mat4 modelMat;
	//模型矩阵的位移、缩放和旋转操作
	modelMat = glm::rotate(modelMat, glm::radians(-20.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	//创建一个观察矩阵
	glm::mat4 viewMat;
	//viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
	viewMat = camera.GetViewMatrix();
	//创建一个投影矩阵
	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);


	while (!glfwWindowShouldClose(window))  //渲染(死)循环 检查是否已指示关闭GLFW
	{
		

		processInput(window);  //检查输入
		
		glClearColor(1.0f, 1.0f, 0, 1.0f);  //设置背景颜色（R，G，B，Alpha）
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清除缓冲区为指定颜色

		glActiveTexture(GL_TEXTURE0); //激活纹理单元
		glBindTexture(GL_TEXTURE_2D, TexBufferA); //绑定纹理
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		

		for (int i = 0; i < 10; i++) {
			glm::mat4 modelMat2;
			modelMat2 = glm::translate(modelMat2, cubePositions[i]);

			testShader->use(); //激活着色器
			glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(testShader->ID, "ourFace"), 3);

			//从shader文件中抓取
			//glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2));
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

			//图形绘制
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		

		
		

		glfwSwapBuffers(window);  //缓冲区渲染并输出到屏幕
		glfwPollEvents();  //检查是否触发了事件
		
	}

	glfwTerminate();  //清理GLFW资源
	return 0;
}

void processInput(GLFWwindow* window)  //检查输入项
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //检查是否按下esc键，如按下则返回true值关闭GLFW
	{
		glfwSetWindowShouldClose(window, true);
	}
}
