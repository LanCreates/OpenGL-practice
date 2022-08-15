#ifndef TEXTURE_HANDLER_H
#define TEXTURE_HANDLER_H

#include <string>

#include "glew.h"
#include "glfw3.h"

class Texture {
    private:
        struct {
            GLenum data_type;
            GLenum filter_mode;
            GLenum wrap_mode;
            GLenum target_type;
            float border_color[4] {0.0f, 0.0f, 0.0f, 0.0f};
        } text_spec;

        std::string source_path;
    public:
        Texture(GLenum target);
        void set_filter(GLenum shrink_mode, GLenum expand_mode);
        void set_wrap(GLenum mode);
        void set_border_color(float new_color[4]);
        void set_src_path(std::string path);
};

#endif
