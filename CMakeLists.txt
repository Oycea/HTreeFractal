cmake_minimum_required(VERSION 3.23)
project(HTree)

add_executable(HTree
        src/main.cpp
        src/Renderer/ShaderProgram.cpp
        src/Renderer/ShaderProgram.h
        src/Renderer/Texture2D.cpp
        src/Renderer/Texture2D.h
        src/Renderer/Sprite.cpp
        src/Renderer/Sprite.h
        src/Renderer/Image.cpp
        src/Renderer/Image.h
        src/Exception/Exception.cpp
        src/Exception/Exception.h
        src/Math/HTree.h
        src/Math/HTree.cpp
        src/Math/Geometry.cpp
        src/Math/Geometry.h
        src/ResourceManager/ResourceManager.cpp
        src/ResourceManager/ResourceManager.h
        src/App/App.cpp
        src/App/App.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)

# указываем куда будем класть исполняемый файл
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# копируем папку res к исполняемому файлу
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)

# cppcheck --enable=all --suppress='*:external/*' --template="[{severity}][{id}] {message} {callstack} (On {file}:{line})" -Isrc ./src 1>/dev/null 2> err.txt
