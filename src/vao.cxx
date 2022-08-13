#include "vao.h"

VAO::VAO() {}

void VAO::set_attrib_pointer(
    unsigned int start,
    unsigned int attrib_count,
    unsigned int gap,
    Buffer *buffer)
{
    stride = gap;
    start_index = start;
    attribute_count = attrib_count;
    glVertexAttribPointer( 
        buffer_bound, 
        attribute_count,
        buffer->get_data_type(), 
        buffer->is_normalized(),
        stride * sizeof(buffer->get_data_type()),
        (void*)(start_index*sizeof(buffer->get_data_type()))
    );
    glEnableVertexAttribArray(buffer_bound);
    buffer_bound++;
}

void VAO::set_ID(unsigned int vao_ID) { VAO_ID = vao_ID; }
void VAO::bind() { glBindVertexArray(VAO_ID); }
unsigned int VAO::get_ID() { return VAO_ID; }
