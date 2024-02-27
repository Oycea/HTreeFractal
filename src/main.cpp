#include <iostream>
#include <memory>

#include "Exception/Exception.h"
#include "Math/HTree.h"
#include "Math/Geometry.h"
#include "App/App.h"

std::shared_ptr<App> app;

void keyCallback(GLFWwindow *pWindow, int key, int scancode, int action, int mode);

int main(int argc, char** argv) {
    try {
        app = std::make_shared<App>("MainWindow", 600, 600, argv[0]);
        auto fractal = std::make_shared<Math::HTree>(1, 1.5);
        fractal->setWH(app->getWidth(), app->getHeight());
        app->setFractal(fractal);
        app->setKeyCallback(keyCallback);
        app->start();
    } catch (Exception::Exception& ex) {
        std::cout << ex.what() << std::endl;
    } catch (std::runtime_error& ex) {
        std::cout << ex.what() << std::endl;
    }
    glfwTerminate();
    return 0;
}


unsigned int inputUInt() {
    std::string str;
    std::cin >> str;
    while (true) {
        try {
            return std::stoi(str);
        } catch (const std::invalid_argument& ex) {
            std::cout << "Try again: ";
            std::cin >> str;
        }
    }
}

double inputDouble() {
    std::string str;
    std::cin >> str;
    while (true) {
        try {
            return std::stod(str);
        } catch (const std::invalid_argument& ex) {
            std::cout << "Try again: ";
            std::cin >> str;
        }
    }
}

void changeStep() {
    unsigned int new_step;
    std::cout << "Change amount step\n";
    std::cout << "Input amount step: ";
    new_step = inputUInt();
    app->getFractal()->setAmountStep(new_step);
    app->render();
}

void changeLengthRatio() {
    double newRatio;
    std::cout << "Change length ratio\n";
    std::cout << "Input length ratio: ";
    newRatio = inputDouble();
    app->getFractal()->setLengthRatio(newRatio);
    app->render();
}

void changeDivisionRatio() {
    double newRatio;
    std::cout << "Change division ratio\n";
    std::cout << "Input division ratio: ";
    newRatio = inputDouble();
    app->getFractal()->setDivisionRatio(newRatio);
    app->render();
}

std::pair<double, double> inputTwoDouble() {
    while (true) {
        try {
            std::string str1, str2;
            std::cin >> str1 >> str2;
            return {std::stod(str1), std::stod(str2)};
        } catch (const std::invalid_argument& ex) {
            std::cout << "Try again: ";
        }
    }
}

void changeLocation() {
    double left;
    double right;
    double bottom;
    double top;
    std::cout << "Change location\n";
    std::cout << "Input left and right: ";
    auto tmp = inputTwoDouble();
    left = tmp.first;
    right = tmp.second;
    std::cout << "Input bottom and top: ";
    tmp = inputTwoDouble();
    bottom = tmp.first;
    top = tmp.second;
    app->getFractal()->setViewPort({{left, bottom}, {right, top}});
    app->render();
}

std::string inputImageName() {
    std::string name;
    std::cout << "Save image\n";
    std::cout << "Input file name: ";
    std::cin >> name;
    size_t found = name.find_last_of('.');
    if (found == std::string::npos || name.substr(found) != ".jpg") {
        name += ".jpg";
    }
    return name;
}

void save() {
    std::string name = inputImageName();
    app->saveImage(name);
}

void keyCallback(GLFWwindow *pWindow, int key, int scancode, int action, int mode) {
    if (       key == GLFW_KEY_I && action == GLFW_PRESS) {
        changeStep();
    } else if (key == GLFW_KEY_L && action == GLFW_PRESS) {
        changeLengthRatio();
    } else if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        changeLocation();
    } else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        save();
    } else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        changeDivisionRatio();
    } else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}