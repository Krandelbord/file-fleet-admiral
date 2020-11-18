#include "Rectangle.h"

Rectangle::Rectangle(int aWidth, int aHeight) {
    this->width = aWidth;
    this->height = aHeight;
}

Rectangle::~Rectangle() {
}

int Rectangle::getWidth() const {
    return width;
}

int Rectangle::getHeight() const {
    return height;
}
