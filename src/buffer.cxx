#include "buffer.h"

Buffer::Buffer(
    std::array<float, 21> *data_ptr, 
    GLenum buf_type,
    GLenum dt_type,
    unsigned int mode
    )
{
    buffer_spec.usage = mode;
    buffer_spec.data_type = dt_type;
    buffer_spec.buffer_type = buf_type;
    to_data = data_ptr;
}

GLenum Buffer::get_data_type() {return buffer_spec.data_type; }
bool Buffer::is_normalized() {return buffer_spec.normalized; }

void Buffer::init() { glGenBuffers(1, &buffer_spec.buffer_ID); }
void Buffer::bind() { glBindBuffer(buffer_spec.buffer_type, buffer_spec.buffer_ID);}

void Buffer::send_data() {
    glBufferData(buffer_spec.buffer_type, sizeof(*to_data), to_data, buffer_spec.usage);
}


