#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>

// #include "../../include/glad/glad.h"
#include <glad/glad.h>

class Texture{
    public:
        unsigned int ID;
        Texture(
            const std::string& texture_image_path, GLint wrap_s = GL_REPEAT, GLint wrap_t = GL_REPEAT,
            GLint min_filter = GL_LINEAR_MIPMAP_LINEAR, GLint mag_filter = GL_LINEAR
        );

        void bind(GLenum texture_unit) const {
            glActiveTexture(texture_unit);
            glBindTexture(GL_TEXTURE_2D, ID);
        }
};

#endif