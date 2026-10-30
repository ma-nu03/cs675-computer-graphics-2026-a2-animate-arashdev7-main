CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN= a2-animate-minifig
SRCS= a2_animate_minifig.cpp gl_framework.cpp shader_util.cpp hierarchy_node.cpp primitives.cpp ihateumore.cpp texture_util.cpp
INCLUDES=gl_framework.hpp shader_util.hpp a2_animate_minifig.hpp hierarchy_node.hpp primitives.hpp ihateumore.hpp texture_util.hpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
