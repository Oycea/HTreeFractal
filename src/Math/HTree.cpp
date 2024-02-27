#include "HTree.h"

#include <iostream>

#include "../Renderer/Image.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/Texture2D.h"
#include "../ResourceManager/ResourceManager.h"

#define IMAGE_SIZE 600

namespace Math {
	using namespace Renderer;

	HTree::HTree(unsigned int amountSteps, double lengthRatio, double divisionRatio)
	: _viewPort({{-1, -1}, {1, 1}})
	, _amountSteps(amountSteps)
	, _lengthRatio(lengthRatio > 1. ? lengthRatio : 2.)
	, _divisionRatio(divisionRatio)
	, _img(std::make_shared<Image>(IMAGE_SIZE, IMAGE_SIZE, 1))
	, _sprite(nullptr) {
		makeFractal();
	}

	void HTree::render() {
        if (_sprite) {
            _sprite->render();
        }
    }

    void HTree::setWH(const unsigned int newWidth, const unsigned int newHeight) noexcept {
        _sprite->setSize(glm::vec2(newWidth, newHeight));
    }

    void HTree::setLengthRatio(double newLengthRatio) {
        _lengthRatio = newLengthRatio > 1. ? newLengthRatio : 2.;
        _img->clear(1);
        makeFractal();
    }

    void HTree::setDivisionRatio(double newDivisionRatio) {
        _divisionRatio = newDivisionRatio > 0. ? newDivisionRatio : 1.;
        _img->clear(1);
        makeFractal();
    }

    void HTree::setAmountStep(unsigned int newAmountStep) {
        _amountSteps = newAmountStep;
        _img->clear(1);
        makeFractal();   
    }

    void HTree::setViewPort(const Renderer::ViewPort& viewPort) {
        _viewPort = viewPort;
        _img->clear(1);
        makeFractal();
    }

	void HTree::initSprite() {
        std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(_img->width(),
                                                                         _img->height(),
                                                                         _img->data());
        const ResourceManager& res = ResourceManager::instance();
        _sprite = std::make_shared<Sprite>(texture, res.getShaderProgram("SpriteShader"),
                                           glm::vec2{0.f},
                                           (_sprite ? _sprite->size() : glm::vec2(IMAGE_SIZE)));
    }

    void HTree::makeFractal() {
    	double width = static_cast<double>(_img->width());
        double height = static_cast<double>(_img->height());
    	Line startLine {{-0.5, 0}, {0.5, 0}};
        startLine.scale(width, height);
        genFractal(startLine, _amountSteps);
		initSprite();
    }

    void HTree::genFractal(Line o, unsigned int currStep) {
        drawLine(o, 3, Color::BLACK);
        if (currStep == 0) {
            return;
        }
        if (o.first.y == o.second.y) {
            double length = std::abs(o.first.x - o.second.x);
            length /= _lengthRatio;
            Line l1 = {{o.first.x, o.first.y + length / 2},
                       {o.first.x, o.first.y - length / 2}};
            Vector diff = divingLineInGivenRatio(l1, _divisionRatio) -
                          divingLineInGivenRatio(l1, 1);
            l1.move(diff);

            Line l2 = {{o.second.x, o.second.y + length / 2},
                       {o.second.x, o.second.y - length / 2}};
            diff = divingLineInGivenRatio(l2, _divisionRatio) - divingLineInGivenRatio(l2, 1);
            l2.move(diff);
            genFractal(l1, currStep - 1);
            genFractal(l2, currStep - 1);
        } else {
            double length = std::abs(o.first.y - o.second.y);
            length /= _lengthRatio;
            Line l1 = {{o.first.x - length / 2, o.first.y},
                       {o.first.x + length / 2, o.first.y}};
            Line l2 = {{o.second.x - length / 2, o.second.y},
                       {o.second.x + length / 2, o.second.y}};
            genFractal(l1, currStep - 1);
            genFractal(l2, currStep - 1);
        }
    }

    void HTree::drawLine(const Line& o, unsigned int thickness, Renderer::Color color) {
        Rectangle rectangle = genRectangle(o, thickness);
        fillRectangle(rectangle, color);
    }

    Rectangle HTree::genRectangle(Line o, unsigned int thickness) {
        Rectangle result;
        if (thickness % 2 == 0) {
            thickness++;
        }
        if (o.first.y == o.second.y) {
            if (o.first.x > o.second.x) {
            std::swap(o.first, o.second);        
            }
            result = {{o.first.x, o.first.y - thickness / 2},
                      {o.second.x, o.first.y + thickness / 2}};
        } else {
            if (o.first.y < o.second.y) {
                std::swap(o.first, o.second);
            }
            result = {{o.second.x - thickness / 2, o.second.y},
                      {o.second.x + thickness / 2, o.first.y}};
        }
        return result;
    }

    void HTree::fillRectangle(Rectangle o, Color color) {
    	scaleRectangle(o);
    	int minX = ceil(std::min(o.leftBottom.x, o.rightTop.x));
    	int minY = ceil(std::min(o.leftBottom.y, o.rightTop.y));
    	int maxX = ceil(std::max(o.leftBottom.x, o.rightTop.x));
    	int maxY = ceil(std::max(o.leftBottom.y, o.rightTop.y));
    	for (unsigned int x = minX; x <= maxX && x < _img->width(); x++) {
    		for (unsigned int y = minY; y <= maxY && y < _img->height(); y++) {
    			_img->setColor(x, y, color);
    		}
    	}
    }

    void HTree::scaleRectangle(Rectangle& o) const noexcept {
    	auto crop = [](Vector&& o) -> Vector {
            o.x = o.x < 0 ? 0 : o.x;
            o.y = o.y < 0 ? 0 : o.y;
            return o;
        };
        auto temp = _viewPort.leftBottom;
        temp.scale(_img->width(), _img->height());
        o.leftBottom = crop(o.leftBottom - temp);
        o.rightTop = crop(o.rightTop - temp);
        auto diff = _viewPort.rightTop - _viewPort.leftBottom;
        double scaleCoefX = diff.x > 0 ? 1. / diff.x : 0.;
        double scaleCoefY = diff.y > 0 ? 1. / diff.y : 0.;
        o.scale(scaleCoefX, scaleCoefY);
    }

    Vector HTree::divingLineInGivenRatio(const Line& o, double ratio) const noexcept {
        Vector result;
        result.x = (o.first.x + ratio * o.second.x) / (1 + ratio);
        result.y = (o.first.y + ratio * o.second.y) / (1 + ratio);
        return result;
    }
}