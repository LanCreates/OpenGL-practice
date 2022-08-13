#include "buffer.h"

Buffer::Buffer(
    std::array<float, 21> *data_ptr, 
    GLenum buf_type,
    GLenum dt_type,
    unsigned int mode
    )
{
    usage = mode;
    data = data_ptr;
    data_type = dt_type;
    buffer_type = buf_type;
}

void Buffer::set_ID(unsigned int buf_ID) { buffer_ID = buf_ID; }
GLenum Buffer::get_data_type() {return data_type; }

bool Buffer::is_normalized() {return normalized; }
void Buffer::bind() { glBindBuffer(buffer_type, buffer_ID);}

void Buffer::send_data() {
    glBufferData(buffer_type, sizeof(*data), data, usage);
}


