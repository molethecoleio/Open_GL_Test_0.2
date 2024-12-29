//Then I heard the voice of the Lord saying "Whom shall I send? And who shall go for us?" And I said, "Here am I. send me!"
//Lord give me one more chance;

#include "Utils.hpp"

constexpr auto numVAOs = 1;
constexpr auto numVBOs = 2;

float cameraX, cameraY, cameraZ, cubeLocX, cubeLocY, cubeLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;
void setupVertices(void)
{
    float vertexPositions[108] = {
        // Front face
        -1.0f,  1.0f, -1.0f,  // Top-left
        -1.0f, -1.0f, -1.0f,  // Bottom-left
         1.0f, -1.0f, -1.0f,  // Bottom-right
        -1.0f,  1.0f, -1.0f,  // Top-left
         1.0f, -1.0f, -1.0f,  // Bottom-right
         1.0f,  1.0f, -1.0f,  // Top-right

         // Back face
         -1.0f,  1.0f,  1.0f,  // Top-left
         -1.0f, -1.0f,  1.0f,  // Bottom-left
          1.0f, -1.0f,  1.0f,  // Bottom-right
         -1.0f,  1.0f,  1.0f,  // Top-left
          1.0f, -1.0f,  1.0f,  // Bottom-right
          1.0f,  1.0f,  1.0f,  // Top-right

          // Left face
          -1.0f,  1.0f,  1.0f,  // Top-left
          -1.0f, -1.0f,  1.0f,  // Bottom-left
          -1.0f, -1.0f, -1.0f,  // Bottom-right
          -1.0f,  1.0f,  1.0f,  // Top-left
          -1.0f, -1.0f, -1.0f,  // Bottom-right
          -1.0f,  1.0f, -1.0f,  // Top-right

          // Right face
           1.0f,  1.0f,  1.0f,  // Top-left
           1.0f, -1.0f,  1.0f,  // Bottom-left
           1.0f, -1.0f, -1.0f,  // Bottom-right
           1.0f,  1.0f,  1.0f,  // Top-left
           1.0f, -1.0f, -1.0f,  // Bottom-right
           1.0f,  1.0f, -1.0f,  // Top-right

           // Top face
           -1.0f,  1.0f, -1.0f,  // Top-left
           -1.0f,  1.0f,  1.0f,  // Bottom-left
            1.0f,  1.0f,  1.0f,  // Bottom-right
           -1.0f,  1.0f, -1.0f,  // Top-left
            1.0f,  1.0f,  1.0f,  // Bottom-right
            1.0f,  1.0f, -1.0f,  // Top-right

            // Bottom face
            -1.0f, -1.0f, -1.0f,  // Top-left
            -1.0f, -1.0f,  1.0f,  // Bottom-left
             1.0f, -1.0f,  1.0f,  // Bottom-right
            -1.0f, -1.0f, -1.0f,  // Top-left
             1.0f, -1.0f,  1.0f,  // Bottom-right
             1.0f, -1.0f, -1.0f   // Top-right
    };
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

void init(GLFWwindow* window) 
{
    renderingProgram = createShaderProgram();
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
    cubeLocX = 0.0; cubeLocY = -2.0f; cubeLocZ = 0.0f;
    setupVertices();

    
}


void display(GLFWwindow* window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(renderingProgram);

    // Set polygon mode to wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
    
    //get uniform vars
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    //build perspective matrix
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f,aspect, 0.1f, 1000.0f); //1.0472 radians = 60 degrees
    //build view, model, & view-model matrix
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
    mvMat = vMat * mMat;
    //copy perspective and MV matrices to corresponding uniform vars
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
    //VBO -> vertex attribute
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    //setup OpenGL to draw the model
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main(void)
{
    if (!glfwInit()) //if the GLFWinit workie it returns true :)
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //setting GLFW to version 4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //width,height, title, isFullscreen, isResorceSharring; window is made a pointer because its much more efficent to just pass the address the the entire window object each cycle;
    GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGl Test1; Init(C01E);", NULL, NULL);
    glfwMakeContextCurrent(window); //linking GLFW to open GL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSwapInterval(1); //this is required for Vsync
    init(window);

    while (!glfwWindowShouldClose(window))
    {
        display(window, glfwGetTime());
        glfwSwapBuffers(window); //this is also required for Vsync
        glfwPollEvents(); // this handles window events like keys being pressed;
    }
    //clear the allocated memory like a good programmer do :)
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}