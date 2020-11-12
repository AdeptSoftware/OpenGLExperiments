#pragma once

GLfloat points[] = {
    0.0f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

const char* vertex_shader =
"#version 460 core\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";

GLuint CompileShader(GLenum type, GLsizei count, const char* string) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, count, &string, nullptr);
    glCompileShader(shader);
    return shader;
}

// Вызвать после glClearColor()
GLuint CreateShaderProgram() {
    GLuint vs = CompileShader(GL_VERTEX_SHADER, 1, vertex_shader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, 1, fragment_shader);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return shader_program;
}

GLuint CreateVBO(GLsizei n, GLfloat* data, GLsizeiptr size, GLenum usage) {
    GLuint vbo = 0;
    glGenBuffers(n, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    return vbo;
}

// stride - шаг смещения
// pointer - смещение от начала массива
void BindVBO(GLuint index, GLenum target, GLuint vbo, GLuint size, GLenum type, GLboolean normalized = GL_FALSE, GLsizei stride = 0, const void* pointer = nullptr) {
    glEnableVertexAttribArray(index);
    glBindBuffer(target, vbo);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

GLuint CreateVAO() {
    GLuint points_vbo = CreateVBO(1, points, sizeof(points), GL_STATIC_DRAW);
    GLuint colors_vbo = CreateVBO(1, colors, sizeof(colors), GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    BindVBO(0, GL_ARRAY_BUFFER, points_vbo, 3, GL_FLOAT, GL_FALSE);
    BindVBO(1, GL_ARRAY_BUFFER, colors_vbo, 3, GL_FLOAT, GL_FALSE);
    return vao;
}

/*  ...
    // Перед glClearColor:
    GLuint shader_program = CreateShaderProgram();
    GLuint vao = CreateVAO();
    // В цикле перед glClear:
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // До glfwSwapBuffers
    ...*/