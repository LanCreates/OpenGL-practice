#include "file.h"

File_handler::File_handler(int stream_num) { 
    stream_number = stream_num; 
}

void File_handler::set_path(std::string new_path) { 
    path = new_path; 
}

int File_handler::get_stream_number() {
    return stream_number; 
}

std::ifstream File_handler::get_stream() {
    std::ifstream stream(path);
    return stream; 
}
