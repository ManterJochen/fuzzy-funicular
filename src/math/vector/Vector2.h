#pragma once

#include "VectorN.h"

class Vector2 : public VectorN {
    public:
        Vector2(double x, double y);

        double x() const;
        double y() const;
};