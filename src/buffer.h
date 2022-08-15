#ifndef BUFFER_HANDLER_H
#define BUFFER_HANDLER_H

#include <array>

#include "glew.h"
#include "glfw3.h"

class Buffer {
    private:
        struct {
            unsigned int buffer_ID;
            unsigned int usage;
            GLenum data_type;
            GLenum buffer_type;
            bool normalized;
        } buffer_spec;

        std::array<float, 21> *to_data;
    public:
        Buffer( 
            std::array<float, 21> *data_ptr, 
            GLenum buf_type,
            GLenum dt_type,
            unsigned int mode
        );
        
        GLenum get_data_type();
        bool is_normalized();
        
        void init();
        void bind();
        void send_data();
};

#endif
