cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

set(PROJECTNAME OpenGLExperiments)
project(${PROJECTNAME})
add_executable(${PROJECTNAME}
src/callbacks.h
src/camera.h
src/crt_debug.h
src/loader.h
src/main.cpp
src/Resources/gl_res.h
src/Resources/object.cpp
src/Resources/object.h
src/Resources/res_manager.cpp
src/Resources/res_manager.h
src/Resources/shader_program.cpp
src/Resources/shader_program.h
src/Resources/stb_image.h
src/Resources/texture2D.cpp
src/Resources/texture2D.h
src/Resources/VertexArraysObject.cpp
src/Resources/VertexArraysObject.h
)

target_compile_features(${PROJECTNAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECTNAME} glfw)


add_subdirectory(external/glad)
target_link_libraries(${PROJECTNAME} glad)


add_subdirectory(external/glm)
target_link_libraries(${PROJECTNAME} glm)

# Обновление файлов после билда проекта (не после повторного запуска программы, без внесения изменений)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
