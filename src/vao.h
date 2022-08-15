#ifndef VAO_HANDLER_H
#define VAO_HANDLER_H

#include "glew.h"
#include "glfw3.h"
#include "buffer.h"

class VAO {
    private:
        struct {
            unsigned int VAO_ID;
            unsigned int buffer_bound = 0;
        } VAO_spec;
        
        struct {
            unsigned int stride;
            unsigned int start_index; 
            unsigned int attribute_count;
            bool normalized;
        } attrib_ptr_spec;


    public:
        VAO();
        
        void set_attrib_pointer(
            unsigned int start,
            unsigned int attrib_count,
            unsigned int gap,
            Buffer *buffer
        );

        unsigned int get_ID();
        void init();
        void bind();
};

#endif
