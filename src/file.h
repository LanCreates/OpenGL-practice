#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <fstream>
#include <string>

class File_handler {
    private:
        int stream_number;
        std::string path;
    public:
        File_handler(int stream_num);
        void set_path(std::string new_path);
        int get_stream_number();
        std::ifstream get_stream();
};

#endif
