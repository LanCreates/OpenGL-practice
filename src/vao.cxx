#include "vao.h"

VAO::VAO() { }

void VAO::set_attrib_pointer(
    unsigned int start,
    unsigned int attrib_count,
    unsigned int gap,
    Buffer *buffer)
{
    attrib_ptr_spec.stride = gap;
    attrib_ptr_spec.start_index = start;
    attrib_ptr_spec.attribute_count = attrib_count;

    glVertexAttribPointer( 
        VAO_spec.buffer_bound, 
        attrib_ptr_spec.attribute_count,
        buffer->get_data_type(), 
        buffer->is_normalized(),
        attrib_ptr_spec.stride * sizeof(buffer->get_data_type()),
        (void*)(attrib_ptr_spec.start_index * sizeof(buffer->get_data_type()))
    );

    glEnableVertexAttribArray(VAO_spec.buffer_bound);
    VAO_spec.buffer_bound++;
}

unsigned int VAO::get_ID() { return VAO_spec.VAO_ID; }
void VAO::init() { glGenVertexArrays(1, &VAO_spec.VAO_ID); }
void VAO::bind() { glBindVertexArray(VAO_spec.VAO_ID); }
