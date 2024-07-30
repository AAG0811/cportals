#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

typedef struct T_Matrix4f
{
  float values[4][4] = {
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}};
};
T_Matrix4f createMat4f(float value)
{
  T_Matrix4f matrix;
  matrix.values[0][0] = 1;
  matrix.values[1][1] = 1;
  matrix.values[2][2] = 1;
  matrix.values[3][3] = 1;
  return matrix;
}
void printMat4f(T_Matrix4f *mat)
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      std::cout << mat->values[i][j];
    }
  }
}

void createShaderProg(unsigned int *shaderProg, const char *vsSource, const char *fsSource);
void checkCompileErrors(unsigned int shader, std::string type);

int main()
{
  glfwInit();
  GLFWwindow *window = glfwCreateWindow(800, 600, "cportals", NULL, NULL);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwMakeContextCurrent(window);
  // callbacks
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    return -1;
  }
  // shaders
  unsigned int flatShader;
  createShaderProg(&flatShader,
                   "../shaders/flat.vs", "../shaders/flat.fs");
  glUseProgram(flatShader);
  // objects
  float vertices[] = {
      -0.5, -0.5, 0.0, // left
      0.0, 0.5, 0.0,   // top
      0.5, -0.5, 0.0   // right
  };
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindVertexArray(VAO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  T_Matrix4f mymat = createMat4f(1.0f);
  printMat4f(&mymat);
  glUniformMatrix4fv("loc", 1, GL_FALSE, &mymat.values[0]);
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    // render
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // objects
    glUseProgram(flatShader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 9);

    glfwSwapBuffers(window);
  }
  glfwTerminate();
  return 0;
}

void createShaderProg(unsigned int *shaderProg, const char *vsSource, const char *fsSource)
{
  // 1. retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try
  {
    // open files
    vShaderFile.open(vsSource);
    fShaderFile.open(fsSource);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure &e)
  {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
  }
  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  // 2. compile shaders
  unsigned int vertex, fragment;
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");
  // shader Program
  *shaderProg = glCreateProgram();
  glAttachShader(*shaderProg, vertex);
  glAttachShader(*shaderProg, fragment);
  glLinkProgram(*shaderProg);
  checkCompileErrors(*shaderProg, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}
void checkCompileErrors(unsigned int shader, std::string type)
{
  int success;
  char infoLog[1024];
  if (type != "PROGRAM")
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
  else
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
}