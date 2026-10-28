#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include "ihateumore.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern csX75::HNode* curr_node;
extern bool solid;
extern Minifig joker, batman;
extern Minifig* hater;
namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(1.0f, 0.8f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
      hater = (hater == &joker) ? &batman : &joker;
    else if (key == GLFW_KEY_1 && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node = hater->root;
    else if (key == GLFW_KEY_2 && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node = hater->neck;
    else if (key == GLFW_KEY_3 && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node = hater->lArm;
    else if (key == GLFW_KEY_4 && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node = hater->rArm;
    else if (key == GLFW_KEY_5 && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node = hater->lThigh;
    else if (key == GLFW_KEY_6 && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node = hater->rThigh;
    else if (key == GLFW_KEY_7 && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node = hater->lShin;
    else if (key == GLFW_KEY_8 && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node = hater->rShin;
    else if (key == GLFW_KEY_9 && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node = hater->lHand;
    else if (key == GLFW_KEY_0 && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node = hater->rHand;
    else if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node->dec_ry();
    else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node->inc_ry();
    else if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node->dec_rx();
    else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node->inc_rx();
    else if (key == GLFW_KEY_COMMA && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node->dec_rz();
    else if (key == GLFW_KEY_PERIOD && (action == GLFW_PRESS || action == GLFW_REPEAT))
      curr_node->inc_rz();
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;
    else if (key == GLFW_KEY_F && action == GLFW_PRESS) {
      solid = !solid;
      glPolygonMode(GL_FRONT_AND_BACK, solid ? GL_FILL : GL_LINE);
    }
    else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
      c_xrot += 1.0;
    else if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
      c_zrot += 1.0;
    else if (key == GLFW_KEY_I && (action == GLFW_PRESS || action == GLFW_REPEAT)) curr_node->inc_ty();
    else if (key == GLFW_KEY_K && (action == GLFW_PRESS || action == GLFW_REPEAT)) curr_node->dec_ty();
    else if (key == GLFW_KEY_J && (action == GLFW_PRESS || action == GLFW_REPEAT)) curr_node->dec_tx();
    else if (key == GLFW_KEY_L && (action == GLFW_PRESS || action == GLFW_REPEAT)) curr_node->inc_tx();
    else if (key == GLFW_KEY_U && (action == GLFW_PRESS || action == GLFW_REPEAT)) curr_node->dec_tz();
    else if (key == GLFW_KEY_O && (action == GLFW_PRESS || action == GLFW_REPEAT)) curr_node->inc_tz();
    else if (key == GLFW_KEY_R && action == GLFW_PRESS) curr_node->reset();

  }
};  
  


