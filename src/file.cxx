#include "file.h"

File_handler::File_handler() { }

void File_handler::set_path(std::string new_path) { 
    path = new_path; 
}

std::string File_handler::get_path() {
    return path;
}

std::ifstream File_handler::get_stream() {
    std::ifstream stream(path);
    return stream; 
}
