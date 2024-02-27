#include "Geometry.h"

namespace Math {
	Vector Vector::operator-(const Vector& rhs) const noexcept {
        return {x - rhs.x, y - rhs.y};
    }

    Vector Vector::operator+(const Vector& rhs) const noexcept {
    	return {x + rhs.x, y + rhs.y};
    }

    void Vector::scaleX(double scaleCoef) noexcept {
    	x *= scaleCoef;
    }

    void Vector::scaleY(double scaleCoef) noexcept {
    	y *= scaleCoef;
    }

    void Vector::scale(double scaleCoefX, double scaleCoefY) noexcept {
    	scaleX(scaleCoefX);
    	scaleY(scaleCoefY);
    }

    void Vector::scale(double scaleCoef) noexcept {
    	scaleX(scaleCoef);
    	scaleY(scaleCoef);
    }

    void Polygon::scaleX(double scaleCoef) noexcept {
    	a.scaleX(scaleCoef);
    	b.scaleX(scaleCoef);
    	c.scaleX(scaleCoef);
    	d.scaleX(scaleCoef);
    }

    void Polygon::scaleY(double scaleCoef) noexcept {
    	a.scaleY(scaleCoef);
    	b.scaleY(scaleCoef);
    	c.scaleY(scaleCoef);
    	d.scaleY(scaleCoef);
    }

    void Polygon::scale(double scaleCoefX, double scaleCoefY) noexcept {
    	a.scale(scaleCoefX, scaleCoefY);
    	b.scale(scaleCoefX, scaleCoefY);
    	c.scale(scaleCoefX, scaleCoefY);
    	d.scale(scaleCoefX, scaleCoefY);
    }

    void Polygon::scale(double scaleCoef) noexcept {
    	a.scale(scaleCoef);
    	b.scale(scaleCoef);
    	c.scale(scaleCoef);
    	d.scale(scaleCoef);
    }

    void Rectangle::scaleX(double scaleCoef) noexcept {
        leftBottom.scaleX(scaleCoef);
        rightTop.scaleX(scaleCoef);
    }

    void Rectangle::scaleY(double scaleCoef) noexcept {
        leftBottom.scaleY(scaleCoef);
        rightTop.scaleY(scaleCoef);
    }

    void Rectangle::scale(double scaleCoefX, double scaleCoefY) noexcept {
        leftBottom.scale(scaleCoefX, scaleCoefY);
        rightTop.scale(scaleCoefX, scaleCoefY);
    }

    void Rectangle::scale(double scaleCoef) noexcept {
        scale(scaleCoef, scaleCoef);
    }

    void Line::scaleX(double scaleCoef) noexcept {
        first.scaleX(scaleCoef);
        second.scaleX(scaleCoef);
    }

    void Line::scaleY(double scaleCoef) noexcept {
        first.scaleY(scaleCoef);
        second.scaleY(scaleCoef);
    }

    void Line::scale(double scaleCoefX, double scaleCoefY) noexcept {
        first.scale(scaleCoefX, scaleCoefY);
        second.scale(scaleCoefX, scaleCoefY);
    }

    void Line::scale(double scaleCoef) noexcept {
        scale(scaleCoef, scaleCoef);
    }

    void Line::move(const Vector& o) {
        first = first - o;
        second = second - o;
    }
}