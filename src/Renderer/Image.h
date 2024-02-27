#pragma once

#include <cctype>
#include <vector>

namespace Renderer {
    enum class Color {
        WHITE,
        BLACK,
        GREY
    };

    class Image {
    public:
        Image(const Image&) = delete;
        Image(Image&&) = delete;
        Image& operator=(const Image&) = delete;
        Image& operator=(Image&&) = delete;
    public:
        Image(unsigned int width, unsigned int height, double grayRatio = 0.5) noexcept;

    public:
        unsigned int width() const noexcept { return WIDTH; }

        unsigned int height() const noexcept { return HEIGHT; }

        void setColor(unsigned int x, unsigned int y, Color color);

        void clear(double grayRatio = 0.5) noexcept;

        [[nodiscard]]
        const unsigned char* data() const noexcept { return _data.data(); }

    private:
        const unsigned int WIDTH;
        const unsigned int HEIGHT;
        std::vector<unsigned char> _data;
    };
}