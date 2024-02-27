#pragma once

#include <memory>

#include "Geometry.h"

namespace Renderer {
	class Image;
	class Sprite;
	enum class Color;

	struct ViewPort {
        Math::Vector leftBottom;
        Math::Vector rightTop;
    };
}


namespace Math {
	class HTree {
	public:
		HTree(const HTree&) = delete;
		HTree& operator=(const HTree&) = delete;
		HTree& operator=(HTree&&) = delete;

	public:
		explicit HTree(unsigned int amountSteps, double lengthRatio = 2.,
					   double divisionRatio = 1.);
		HTree(HTree&&) = default;

	public:
		void render();

		void setWH(unsigned int newWidth, unsigned int newHeight) noexcept;

		void setLengthRatio(double newLengthRatio);

		void setDivisionRatio(double newDivisionRatio);

		void setAmountStep(unsigned int newAmountStep);

		void setViewPort(const Renderer::ViewPort& viewPort);

	private:
		void initSprite();

		void makeFractal();

		void genFractal(Line o, unsigned int currStep);

		void drawLine(const Line&, unsigned int thickness, Renderer::Color color);

		Rectangle genRectangle(Line o, unsigned int thickness);

		void fillRectangle(Rectangle o, Renderer::Color color);

		void scaleRectangle(Rectangle& o) const noexcept;

		Vector divingLineInGivenRatio(const Line& o, double ratio) const noexcept;

	private:
		Renderer::ViewPort _viewPort;
		unsigned int _amountSteps;
		double _lengthRatio;
		double _divisionRatio;
		std::shared_ptr<Renderer::Image> _img;
		std::shared_ptr<Renderer::Sprite> _sprite;
	};
}