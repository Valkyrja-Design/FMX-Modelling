#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

Texture :: Texture(
            const std::string& texture_image_path, GLint wrap_s /* = GL_REPEAT */, GLint wrap_t /* = GL_REPEAT */,
            GLint min_filter /* = GL_LINEAR_MIPMAP_LINEAR */, GLint mag_filter /* = GL_LINEAR */
        ){
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Set texture wrapping paramters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    // flip the y-axis because opengl has origin at the bottom and images have origin at top
    stbi_set_flip_vertically_on_load(true);

    // Load the texture image data
    int height, width, nChannels;
    unsigned char* data = stbi_load(texture_image_path.c_str(), &width, &height, &nChannels, 0);

    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else{
        std::cout << "ERROR::TEXTURE::FAILED TO LOAD TEXTURE IMAGE\n";
        exit(EXIT_FAILURE);
    }

    stbi_image_free(data);
}