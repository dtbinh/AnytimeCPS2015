#include "dynamics.h"
#include "util.h"
#include "interval.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef DYNAMICS_PENDULUM_NONLINEAR

// an inverted pendulum nonlinear model, dynamics from Taylor
//x' == v

//v' == -(omega^2*sin(theta) - (5401*v)/1900 + cos(theta)*((3*omega)/2500
//       + (147*sin(theta))/5))/(3*cos(theta)^2 - 29)

//theta' == omega

//omega' == ((87*omega)/2500 + (4263*sin(theta))/5 - cos(theta)*(- 3*sin(theta)*omega^2
//          + (16203*v)/1900))/(3*cos(theta)^2 - 29)


double get_derivative_bounds(HyperRectangle* rect, int faceIndex)
{
	int dim = faceIndex / 2;
	bool isMin = (faceIndex % 2) == 0;
    Interval rv = new_interval_v(0);

//    Interval x = rect->dims[0];
    Interval v = rect->dims[1];
    Interval theta = rect->dims[2];
    Interval omega = rect->dims[3];

    // evaluate the corresponding derivative in interval arithmetic
    if (dim == 0)
    {
        // x' == v
        rv = v;
    }
    else if (dim == 1)
    {
        //v' == -(omega^2*sin(theta) - (5401*v)/1900 + cos(theta)*((3*omega)/2500 + (147*sin(theta))/5))
        //                       / (3*cos(theta)^2 - 29)

        //v' == (omega^2 * sin(theta) + (-5401/1900)*v + cos(theta)*(3/2500*omega + 147/5*sin(theta)))
        //                      /   (-3*cos(theta)^2 + 29)

        //v' == A + B + C / D

        Interval A = mul_interval(pow_interval(omega,2), sin_interval(theta));
        Interval B = mul_interval(v, new_interval_v(-5401.0/1900.0));
        Interval C = mul_interval(cos_interval(theta),
                                  add_interval(mul_interval(new_interval_v(3.0/2500.0),omega),
                                               mul_interval(new_interval_v(147.0/5.0),sin_interval(theta))
                                      ));
        Interval D = add_interval(mul_interval(new_interval_v(-3.0),pow_interval(cos_interval(theta),2)),
                                  new_interval_v(29.0));

        rv = div_interval(add_interval(add_interval(A,B),C), D);
    }
    else if (dim == 2)
    {
        //theta' == omega
        rv = omega;
    }
    else
    {
        if (dim != 3)
            printf("dim should be 3 in dynamics!\n");
        else
        {
            //omega' == ((87*omega)/2500 + (4263*sin(theta))/5 - cos(theta)*(- 3*sin(theta)*omega^2
            //          + (16203*v)/1900))/(3*cos(theta)^2 - 29)

            Interval A = mul_interval(new_interval_v(87.0/2500.0),omega);
            Interval B = mul_interval(new_interval_v(4263.0/5.0), sin_interval(theta));
            Interval C = cos_interval(theta);
            Interval D = mul_interval(new_interval_v(-3.0),
                                      mul_interval(sin_interval(theta),
                                                   pow_interval(omega,2)));
            Interval E = mul_interval(new_interval_v(16203.0/1900.0), v);
            Interval F = sub_interval(mul_interval(new_interval_v(3), pow_interval(cos_interval(theta),2)),
                                      new_interval_v(29));

            rv = div_interval(sub_interval(add_interval(A,B),mul_interval(C,add_interval(D,E))), F);
        }
    }




	return isMin ? rv.min : rv.max;
}



#endif
