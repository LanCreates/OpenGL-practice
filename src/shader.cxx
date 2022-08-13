#include "shader.h"

unsigned int Shader::get_program() { return program; }

unsigned int Shader::compile_shader(unsigned int type, const char* source) { 
    unsigned int shaderID = glCreateShader(type);

    glShaderSource(shaderID, 1, &source, NULL);
    glCompileShader(shaderID);

    int is_success;
    char log[1024]; 
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &is_success);
    if(is_success == GL_FALSE) {
        glGetShaderInfoLog(shaderID, 1024, NULL, log);
        std::cout << "Failed to compile "
                    << (type == GL_VERTEX_SHADER? "vertex": "fragment")
                    << " shader\n" << log << std::endl;
        return 0;
    }
    return shaderID;
}

unsigned int Shader::get_shader(std::string path) { 
    file.set_path(path);
    std::ifstream stream = file.get_stream();
    std::string line;

    getline(stream, line);
    switch(line[3]) {
        case 'V': mode = shaderType::VERTEX; break;
        case 'F': mode = shaderType::FRAGMENT; break;
    }
    
    // Provide a buffer for each type of shader
    std::stringstream ss[file.get_stream_number()];
    while(getline(stream, line)) { 
        ss[(int)mode] << (line[0] == '/'? "": line + "\n"); 
    }
    
    unsigned int shader = (int)shaderType::NONE;
    switch(mode) {
        case shaderType::VERTEX:
            shader = compile_shader(GL_VERTEX_SHADER, 
                    ss[(int)shaderType::VERTEX].str().c_str());
            break;
        case shaderType::FRAGMENT:
            shader = compile_shader(GL_FRAGMENT_SHADER, 
                    ss[(int)shaderType::FRAGMENT].str().c_str());
            break;
        default:
            (void)0;
    }
    
    if(shader != (int)shaderType::NONE) {
        shader_ID[shader] = shader;
    }

    return shader;
}

void Shader::make_shader() { 
    unsigned int vertex_shader = get_shader("../resources/shaders/vertex.glsl");
    unsigned int fragment_shader = get_shader("../resources/shaders/fragment.glsl");
    unsigned int shader_program = glCreateProgram();
    
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    
    int is_success_link, is_success_validation;
    char message[1024];

    glLinkProgram(shader_program);
    glValidateProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &is_success_link);
    glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &is_success_validation);

    if(is_success_link == GL_FALSE || is_success_validation == GL_FALSE) {
        glGetProgramInfoLog(shader_program, sizeof(message), NULL, message);
        std::cout << "Failed to make shader program\n" 
                << message << std::endl;
        program = 0;
    } else {
        program = shader_program;
    }
}

void Shader::send_floats(std::string target, float data[4], int data_count) {
    switch(data_count) {
        case 1:
            glUniform1f(
                glGetUniformLocation(program, target.c_str()), 
                data[0]);
            break;
        case 2:
            glUniform2f(
                glGetUniformLocation(program, target.c_str()), 
                data[0], data[1]);
            break;
        case 3:
            glUniform3f(
                glGetUniformLocation(program, target.c_str()), 
                data[0], data[1], data[2]);
            break;
        case 4: 
            glUniform4f(
                glGetUniformLocation(program, target.c_str()), 
                data[0], data[1], data[2], data[3]);
            break;
        default:
            void(0);
    }
}
