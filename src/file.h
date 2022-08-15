#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <fstream>
#include <string>

class File_handler {
    private:
        std::string path;
    public:
        File_handler();

        void set_path(std::string new_path);
        std::string get_path();
        std::ifstream get_stream();
};

#endif
