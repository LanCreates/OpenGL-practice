#ifndef BUFFER_HANDLER_H
#define BUFFER_HANDLER_H

#include <array>

#include "glew.h"
#include "glfw3.h"

class Buffer {
    private:
        unsigned int 
            usage,
            buffer_ID;

        GLenum data_type, buffer_type;
        bool normalized;
        std::array<float, 21> *data;
    public:
        Buffer( 
            std::array<float, 21> *data_ptr, 
            GLenum buf_type,
            GLenum dt_type,
            unsigned int mode
        );
        
        void set_ID(unsigned int buf_ID);
        GLenum get_data_type();
        bool is_normalized();

        void bind();
        void send_data();
};

#endif
