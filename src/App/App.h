#pragma once

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Math {
    class HTree;
}

class App {
public:
    App& operator=(const App&) = delete;
    App(App&&) = delete;
    App& operator=(App&&) = delete;

public:
    App(const std::string& windowName, int width, int height, const std::string& path);
    App(const App&) = default;

public:
    std::shared_ptr<Math::HTree> getFractal() const noexcept;

    void setFractal(const std::shared_ptr<Math::HTree>& fractal) noexcept;

    void start() noexcept;

    void render() const noexcept;

    void saveImage(const std::string& filePath) const noexcept;

    void setKeyCallback(void(*func)(GLFWwindow*, int, int, int, int));

    [[nodiscard]]
    int getWidth() const noexcept { return WIDTH; }
    [[nodiscard]]
    int getHeight() const noexcept { return HEIGHT; }
private:
    void init(const std::string& windowName);

    GLFWwindow* _window;
    const int WIDTH;
    const int HEIGHT;
    std::shared_ptr<Math::HTree> _fractal;
};
