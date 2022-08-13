#ifndef VAO_HANDLER_H
#define VAO_HANDLER_H

#include "glew.h"
#include "glfw3.h"
#include "buffer.h"

class VAO {
    private:
        unsigned int
            VAO_ID, 
            stride,
            start_index, 
            attribute_count,
            buffer_bound = 0;
        
        bool normalized;

    public:
        VAO();
        
        void set_attrib_pointer(
            unsigned int start,
            unsigned int attrib_count,
            unsigned int gap,
            Buffer *buffer
        );

        void set_ID(unsigned int vao_ID);
        unsigned int get_ID();
        void bind();
};

#endif
