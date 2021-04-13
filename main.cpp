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


#pragma region Model Data
//GLfloat vertices[] = {
//	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
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

//unsigned int indices[] = {
//	0, 1, 2,
//	2, 3, 0
//};

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
#pragma endregion


float lastX, lastY;
bool firstMouse = true;

//Camera camera(glm::vec3(0,0,3.0f), glm::vec3(0,0,0), glm::vec3(0,1.0f,0));
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(-130.0f), glm::vec3(0, 1.0f, 0));
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);

unsigned int LoadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot) {
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	int image_width, image_height, image_nrChannel;
	stbi_set_flip_vertically_on_load(true); //�ߵ�ͼ��
	unsigned char* data = stbi_load(filename, &image_width, &image_height, &image_nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image_width, image_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "load image failed." << std::endl;
	}
	stbi_image_free(data);
	return TexBuffer;
}

int main() //����������
{
#pragma region Open Window
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);


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
	glEnable(GL_DEPTH_TEST);
#pragma endregion

#pragma region Init Shader Program
	Shader* testShader = new Shader("vertexSource.vert", "fragmentSource.frag");
#pragma endregion

#pragma region Init and Load Models to VAO VBO
	unsigned int VAO;  //����һ��VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);  //��

	unsigned int VBO;  //����VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);  //��
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//λ������
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);
	//��ɫ����
	//glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)) );
	//glEnableVertexAttribArray(7);
	//��ͼ����
	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(8);
#pragma endregion

#pragma region Init and Load Textures
	//��������A
	unsigned int TexBufferA;
	TexBufferA = LoadImageToGPU("container.adm", GL_RGB, GL_RGB, 0);
	
	//��������B
	unsigned int TexBufferB;
	TexBufferB = LoadImageToGPU("awesomeface.adm", GL_RGBA, GL_RGBA, 3);
#pragma endregion

#pragma region Prepare MVP matrices
	//����任����
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(-1.0f, 0, 0)); //λ��
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0, 0, 1.0f)); //��ת
	//trans = glm::scale(trans, glm::vec3(1.5f, 1.5f, 2.0f)); //����

	//����һ��ģ�;���
	glm::mat4 modelMat;
	//ģ�;����λ�ơ����ź���ת����
	//modelMat = glm::rotate(modelMat, glm::radians(-20.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	//����һ���۲����
	glm::mat4 viewMat;
	//viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
	//viewMat = camera.GetViewMatrix();
	//����һ��ͶӰ����
	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
#pragma endregion

	while (!glfwWindowShouldClose(window))  //��Ⱦ(��)ѭ�� ����Ƿ���ָʾ�ر�GLFW
	{
		processInput(window);  //�������
		
		glClearColor(1.0f, 1.0f, 0, 1.0f);  //���ñ�����ɫ��R��G��B��Alpha��
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //���������Ϊָ����ɫ

		
		viewMat = camera.GetViewMatrix();

		for (int i = 0; i < 10; i++) {
			//glm::mat4 modelMat2;
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);

			testShader->use(); //������ɫ��

			glActiveTexture(GL_TEXTURE0); //��������Ԫ0
			glBindTexture(GL_TEXTURE_2D, TexBufferA); //������A
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, TexBufferB);

			glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(testShader->ID, "ourFace"), 3);

			//��shader�ļ���ץȡ
			//glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

			//����ģ��
			glBindVertexArray(VAO);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

			//ͼ�λ���
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		
		glfwSwapBuffers(window);  //��������Ⱦ���������Ļ
		glfwPollEvents();  //����Ƿ񴥷����¼�
		camera.UpdateCameraPos();
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

	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.speedZ = 1.0f;
	}

	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.speedZ = -1.0f;
	}

	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.speedX = -1.0f;
	}

	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.speedX = 1.0f;
	}

	else
	{
		camera.speedZ = 0;
		camera.speedX = 0;
	}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse == true) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = lastY - yPos;
	
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(deltaX, deltaY);
	
}
