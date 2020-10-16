#pragma once
#include "string"

class Shader
{
public:
	const char* vertexSource;
	const char* fragmentSource;
	Shader(const char* vertexPath, const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	unsigned int ID;  //Shader Program ID
	void use();

private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

