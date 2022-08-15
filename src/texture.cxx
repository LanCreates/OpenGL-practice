#include "texture.h"

Texture::Texture(GLenum target) { text_spec.target_type = target; }

void Texture::set_filter(GLenum shrink_mode, GLenum expand_mode) {
    glTexParameteri(text_spec.target_type, GL_TEXTURE_MIN_FILTER, shrink_mode);
    glTexParameteri(text_spec.target_type, GL_TEXTURE_MAG_FILTER, expand_mode);
}

void Texture::set_wrap(GLenum mode) {
    switch(text_spec.target_type) {
        case GL_TEXTURE_2D:
            switch(text_spec.data_type) {
                case GL_FLOAT:
                    glTexParameterf(text_spec.target_type, GL_TEXTURE_WRAP_S, mode);
                    glTexParameterf(text_spec.target_type, GL_TEXTURE_WRAP_T, mode);
                    break;
                case GL_INT:
                    glTexParameteri(text_spec.target_type, GL_TEXTURE_WRAP_S, mode);
                    glTexParameteri(text_spec.target_type, GL_TEXTURE_WRAP_T, mode);
                    break;
            } break;
        case GL_TEXTURE_3D:
            switch(text_spec.data_type) {
                case GL_FLOAT:
                    glTexParameterf(text_spec.target_type, GL_TEXTURE_WRAP_S, mode);
                    glTexParameterf(text_spec.target_type, GL_TEXTURE_WRAP_T, mode);
                    glTexParameterf(text_spec.target_type, GL_TEXTURE_WRAP_R, mode);
                    break;
                case GL_INT:
                    glTexParameteri(text_spec.target_type, GL_TEXTURE_WRAP_S, mode);
                    glTexParameteri(text_spec.target_type, GL_TEXTURE_WRAP_T, mode);
                    glTexParameteri(text_spec.target_type, GL_TEXTURE_WRAP_R, mode);
                    break;
            } break;
        default:
            // TODO: Maybe one day...
            return;
    }
}

void Texture::set_border_color(float new_color[4]) {
    for(int i = 0; i < 4; i++) {
        text_spec.border_color[i] = new_color[i];
    }

    glTexParameterfv(
            text_spec.target_type, 
            GL_TEXTURE_BORDER_COLOR, 
            text_spec.border_color
    );
}

void Texture::set_src_path(std::string path) { source_path = path;}
