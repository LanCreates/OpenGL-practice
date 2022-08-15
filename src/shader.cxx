#include "shader.h"

Shader::Shader(){}

void Shader::set_path(std::string path) {
    shader_spec.file.set_path(path);
}

void Shader::set_shader_type(shader_type type) {
    shader_spec.type = type;
}

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

void Shader::get_shader() { 
    std::ifstream stream = shader_spec.file.get_stream();
    std::string line;

    getline(stream, line);
    switch(line[3]) {
        case 'V': shader_spec.type = shader_type::VERTEX; break;
        case 'F': shader_spec.type = shader_type::FRAGMENT; break;
    }
    
    // Provide a buffer for each type of shader
    std::stringstream ss;
    while(getline(stream, line)) { ss << (line[0] == '/'? "": line + "\n"); }
    
    unsigned int shader = (int)shader_type::NONE;
    switch(shader_spec.type) {
        case shader_type::VERTEX:
            shader = compile_shader(GL_VERTEX_SHADER, ss.str().c_str());
            break;
        case shader_type::FRAGMENT:
            shader = compile_shader(GL_FRAGMENT_SHADER, ss.str().c_str());
            break;
        default:
            shader = 0;
    }
    shader_spec.ID = shader;
}

unsigned int Shader::get_ID() {
    return shader_spec.ID;
}

// SHADER PROGRAM CLASS DEFINITIONS ======================================
Shader_program::Shader_program() { }

void Shader_program::set_shader_source_path(char shader_t, std::string new_path) {
    switch(shader_t) {
        case 'V':
        case 'V' + 32:
            shaders[(int)shader_type::VERTEX].set_path(new_path);
            break;
        case 'F':
        case 'F' + 32:
            shaders[(int)shader_type::FRAGMENT].set_path(new_path);
            break;
        default:
            break;
    }
}

void Shader_program::send_floats(std::string target, float data[4], int data_count) {
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

void Shader_program::make_shader_program() { 
    shaders[(int)shader_type::VERTEX].set_shader_type(shader_type::VERTEX);
    shaders[(int)shader_type::VERTEX].get_shader();

    shaders[(int)shader_type::FRAGMENT].set_shader_type(shader_type::VERTEX);
    shaders[(int)shader_type::FRAGMENT].get_shader();

    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, shaders[(int)shader_type::VERTEX].get_ID());
    glAttachShader(shader_program, shaders[(int)shader_type::FRAGMENT].get_ID());
    
    int is_success_link, is_success_validation;
    char message[1024];

    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &is_success_link);
    if(is_success_link == GL_FALSE) {
        glGetProgramInfoLog(shader_program, sizeof(message), NULL, message);
        std::cout << "Failed to make shader program: LINK FAILURE\n" 
                "Details ==========\n" << message << "\n";
        program = 0;
        return;
    }

    glValidateProgram(shader_program);
    glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &is_success_validation);
    if(is_success_validation == GL_FALSE) {
        glGetProgramInfoLog(shader_program, sizeof(message), NULL, message);
        std::cout << "Failed to make shader program: VALIDATION FAILURE\n" 
                "Details ==========\n" << message << "\n";
        program = 0;
        return;
    }

    program = shader_program;
}

void Shader_program::use_program() {
    glUseProgram(program);
}

void Shader_program::list_uniforms() {

}

Shader_program::~Shader_program() {
    glDeleteProgram(program);
}
