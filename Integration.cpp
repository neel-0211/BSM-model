#include <cmath>
#include "Integration.h"

using namespace std;

Integration::Integration(double temp_x_min, double temp_x_max)
        :  x_min{temp_x_min}, x_max{temp_x_max} {
}

inline double Integration::func(double x){
        return (1/pow((2*M_PI), 0.5))* pow(M_E, ((-x*x)/2));
}

double Integration::integral(int width) {        
            double step = static_cast<double>((x_max - x_min) / width);  // width of each small rectangle
            double area = 0.0;  
            for (int i = 0; i < width; i ++) {
                area += func(x_min + (i + 0.5) * step) * step; // sum up each small rectangle
            }
            return area;
}
