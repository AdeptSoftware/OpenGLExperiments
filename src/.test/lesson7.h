#pragma once // 7

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

GLfloat texpts[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};


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
    // GLuint colors_vbo = CreateVBO(1, colors, sizeof(colors), GL_STATIC_DRAW);
    GLuint texpts_vbo = CreateVBO(1, texpts, sizeof(colors), GL_STATIC_DRAW);


    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    BindVBO(0, GL_ARRAY_BUFFER, points_vbo, 3, GL_FLOAT, GL_FALSE);
    // BindVBO(1, GL_ARRAY_BUFFER, colors_vbo, 3, GL_FLOAT, GL_FALSE);
    BindVBO(1, GL_ARRAY_BUFFER, texpts_vbo, 2, GL_FLOAT, GL_FALSE);
    return vao;
}