#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>

using namespace std; //why do so many people avoid this one line of code and write std 100 times in there project?


void printShaderLog(GLuint shader);

void printProgramLog(int prog);

bool checkOpenGLError();

string readShaderSource(const char* filePath);

GLuint createShaderProgram();

