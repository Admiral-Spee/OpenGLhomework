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




GLfloat vertices[] = {
	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
};

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};


void processInput(GLFWwindow* window);

int main() //����������
{
	
	glfwInit();  //��ʼ��GLFW��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "My OpenGL", NULL, NULL);  //����һ��800*600�Ĵ���
	if (window == NULL)  //���ڴ���ʧ�ܵķ���ֵ
	{
		std::cout << "Open Window Failed." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	glewExperimental = true;  //��ʼ��GLEW��
	if (glewInit() != GLEW_OK)  //��ʼ��ʧ�ܷ���ֵ
	{
		std::cout << "Init GLEW Failed." << std::endl;
		glfwTerminate();
		return -1;
	}


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);  //��֪OpenGL��Ⱦ���ڴ�С
	//glEnable(GL_CULL_FACE);  //�޳�����
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //�߿���Ⱦ

	Shader* testShader = new Shader("vertexSource.adm", "fragmentSource.adm");

	unsigned int VAO;  //����һ��VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);  //��

	unsigned int VBO;  //����VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);  //��
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//λ������
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);
	//��ɫ����
	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)) );
	glEnableVertexAttribArray(7);
	//��ͼ����
	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(8);

	//��������A
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);
	int image_width, image_height, image_nrChannel;
	stbi_set_flip_vertically_on_load(true); //�ߵ�ͼ��
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

	//��������B
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

	//����任
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(-1.0f, 0, 0)); //λ��
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0, 0, 1.0f)); //��ת
	//trans = glm::scale(trans, glm::vec3(1.5f, 1.5f, 2.0f)); //����

	while (!glfwWindowShouldClose(window))  //��Ⱦ(��)ѭ�� ����Ƿ���ָʾ�ر�GLFW
	{
		glm::mat4 trans;
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0, 0, 0.5f)); //��ʱ����ת

		processInput(window);  //�������
		
		glClearColor(1.0f, 1.0f, 0, 1.0f);  //���ñ�����ɫ��R��G��B��Alpha��
		glClear(GL_COLOR_BUFFER_BIT);  //���������Ϊָ����ɫ

		glActiveTexture(GL_TEXTURE0); //��������Ԫ
		glBindTexture(GL_TEXTURE_2D, TexBufferA); //������
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		testShader->use(); //������ɫ��
		glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(testShader->ID, "ourFace"), 3);
		glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		
		

		glfwSwapBuffers(window);  //��������Ⱦ���������Ļ
		glfwPollEvents();  //����Ƿ񴥷����¼�
		
	}

	glfwTerminate();  //����GLFW��Դ
	return 0;
}

void processInput(GLFWwindow* window)  //���������
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //����Ƿ���esc�����簴���򷵻�trueֵ�ر�GLFW
	{
		glfwSetWindowShouldClose(window, true);
	}
}
