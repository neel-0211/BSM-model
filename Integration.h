#pragma once

const long steps{5'000};

class Integration{
public:
        double integral(int width=steps);
        Integration(double temp_x_min, double temp_x_max);
private:
        double x_min;
        double x_max;
        double func(double x);
};