#pragma once

class Angle {
    private:
        double radians_;
    
    public:
        Angle(double radians);

        static Angle fromDegrees(double degrees);
        static Angle fromRadians(double radians);

        // radiant & degree
        double radians() const;
        double degrees() const;

        // trigonometric functions
        double sin() const;
        double cos() const;
        double tan() const;
};