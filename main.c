#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    glfwSwapBuffers(window);
  }
  glfwTerminate();
  return 0;
}