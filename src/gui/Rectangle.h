#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
    public :
        Rectangle(int width, int height);
        int getWidth() const;
        int getHeight() const;

        ~Rectangle();
    private:
        int width, height;
};

#endif /** RECTANGLE_H */
