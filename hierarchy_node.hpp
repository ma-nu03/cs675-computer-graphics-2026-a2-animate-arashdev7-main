#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "gl_framework.hpp"


namespace csX75	 { 

	// A simple class that represents a node in the hierarchy tree
	class HNode {
		//glm::vec4 * vertices;
		//glm::vec4 * colors;
		GLfloat tx,ty,tz,rx,ry,rz;
		GLfloat dtx,dty,dtz,drx,dry,drz;   // default pose, remembered so reset() can restore it
		GLfloat rmin[3], rmax[3];          // rotation limits in degrees, for rx, ry, rz

		std::size_t vertex_buffer_size;
		std::size_t color_buffer_size;

		GLuint num_vertices;
		GLuint vao,vbo;

		glm::mat4 rotation;
		glm::mat4 translation;
		
		std::vector<HNode*> children;
		HNode* parent;

		void update_matrices();

	  public:
		HNode (HNode*, GLuint, glm::vec4*,  glm::vec4*, std::size_t, std::size_t);
		//HNode (HNode* , glm::vec4*,  glm::vec4*,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);

		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		void render_tree();
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();
		void inc_tx(); void dec_tx();
		void inc_ty(); void dec_ty();
		void inc_tz(); void dec_tz();
		glm::vec3 get_translation() const;

		void save_defaults();   // "remember the current pose as the rest pose"
		void reset();           // go back to the remembered rest pose
		void set_rot_limits(GLfloat rxmin, GLfloat rxmax,
                    GLfloat rymin, GLfloat rymax,
                    GLfloat rzmin, GLfloat rzmax);
	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );
};	

#endif