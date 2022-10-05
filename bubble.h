#include <simplecpp>

/* Bubble Vars */
const int BUBBLE_START_X = 250;
const int BUBBLE_START_Y = 50;
const int BUBBLE_DEFAULT_RADIUS = 10;
const int BUBBLE_RADIUS_THRESHOLD = 10;
const int BUBBLE_DEFAULT_VX = 100;
const int BUBBLE_DEFAULT_VY = 0;
const int BUBBLE_DEFAULT_ACCELERATION_AY = 20;//acceleration along Y direction to simulate gravity.
class Bubble
{
private:
    Circle circle;  // the circle representing the bubble
    double vx, vy, ay;  // velocity in x and y direction
    Color color;    // color of the bubble

public:
    Bubble(double cx, double cy, double r, double vx_=BUBBLE_DEFAULT_VX, double vy_=BUBBLE_DEFAULT_VY, Color color_=COLOR(0, 0, 255), double ay_=BUBBLE_DEFAULT_ACCELERATION_AY)
    {
        // Bubble constructor
        color = color_;
        circle = Circle(cx, cy, r);
        circle.setColor(color);
        circle.setFill(true);

        vx = vx_;
        vy = vy_;
        ay = ay_;
    }

    void nextStep(double t)
    {
        // move the bubble
        double new_x = circle.getX() + vx*t;
        double new_y = circle.getY() + vy*t + (ay*t*t/2); //displacement: S=U*T +1/2*A*T^2
        vy += ay*t;  //change in velocity V=U + A*T.

        if ((vx < 0 && new_x < (0 + circle.getRadius())) // bounce along X direction at left border
            ||
            (vx > 0 && new_x > (WINDOW_X - circle.getRadius()))) // bounce along X direction at right border
        {

            vx = -vx;  // change in velocity direction.
            new_x = circle.getX() + vx*t; // new X position after change in velocity

        }

        if ((new_y < (0 + circle.getRadius())) // bounce along Y direction at top margin
            ||
            (new_y > (450 - circle.getRadius()))) // bounce along Y direction at Blue line
        {

            vy=-vy;   // change in velocity direction.
            new_y = circle.getY() + vy*t + (ay*t*t/2);// new Y position after change in velocity



        }
        circle.moveTo(new_x, new_y); // move bubble to next positon after STEP_TIME.
    }

    double get_radius()
    {
        // return the radius of the bubble
        return circle.getRadius();
    }

    double get_center_x()
    {
        // return the x coordinate of the center of the bubble
        return circle.getX();
    }

    double get_center_y()
    {
        // return the y coordinate of the center of the bubble
        return circle.getY();
    }

    double get_vx()
    {
        // return the x velocity of the bubble
        return vx;
    }
    double get_vy()
    {
        // return the y velocity of the bubble
        return vy;
    }

    Color get_color()
    {
        // return the color of the bubble
        return color;
    }
};
