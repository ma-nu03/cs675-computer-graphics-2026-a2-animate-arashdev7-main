#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texture_util.hpp"
#include <iostream>

GLuint loadTexture(const char* path) {
    std::cout << "  loadTexture: enter, path=" << path << std::endl;
    stbi_set_flip_vertically_on_load(1);

    int w, h, channels;
    std::cout << "  loadTexture: calling stbi_load" << std::endl;
    unsigned char* data = stbi_load(path, &w, &h, &channels, 0);
    std::cout << "  loadTexture: stbi_load returned, data=" << (void*)data << std::endl;
    if (!data) {
        std::cerr << "Failed to load texture: " << path << " reason=" << stbi_failure_reason() << std::endl;
        return 0;
    }
    std::cout << "  loadTexture: " << w << "x" << h << ", channels=" << channels << std::endl;
    GLenum format;
    if (channels == 3) format = GL_RGB;
    else if (channels == 4) format = GL_RGBA;
    else { stbi_image_free(data); return 0; }

    GLuint tex;
    glGenTextures(1, &tex);
    std::cout << "  loadTexture: glGenTextures done, tex=" << tex << std::endl;
    glBindTexture(GL_TEXTURE_2D, tex);
    std::cout << "  loadTexture: bound" << std::endl;

    // Row alignment: default is 4 bytes. RGB rows may not be multiples of 4 -> crashes.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
    std::cout << "  loadTexture: glTexImage2D done" << std::endl;
    glGenerateMipmap(GL_TEXTURE_2D);
    std::cout << "  loadTexture: mipmap done" << std::endl;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    std::cout << "  loadTexture: done, returning id=" << tex << std::endl;
    return tex;
}