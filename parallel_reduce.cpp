// https://chryswoods.com/parallel_c++/parallel_reduce.html

auto result = tbb::parallel_reduce( range, identity_value, kernel, reduction_function );

/*
range has the same meaning as tbb::parallel_for, and is the range of values over which to iterate,
identity_value is the identity value for the reduction, i.e. the starting empty value. This should normally be 0.0 for addition type reductions, or 1.0 for multiplication type reductions,
reduction_function is the standard reduction function, i.e. here we use std::plus<double>() as we are reducing double precision numbers using addition,
and kernel is the lambda function that performs a subset of iterations of the reduction.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>

int main(int argc, char **argv)
{
    auto values = std::vector<double>(10000);
    
    tbb::parallel_for( tbb::blocked_range<int>(0,values.size()),
                       [&](tbb::blocked_range<int> r)
    {
        for (int i=r.begin(); i<r.end(); ++i)
        {
            values[i] = std::sin(i * 0.001);
        }
    });

    auto total = tbb::parallel_reduce( 
                    tbb::blocked_range<int>(0,values.size()),
                    0.0,
                    [&](tbb::blocked_range<int> r, double running_total)
                    {
                        for (int i=r.begin(); i<r.end(); ++i)
                        {
                            running_total += values[i];
                        }

                        return running_total;
                    }, std::plus<double>() );

    std::cout << total << std::endl;

    return 0;
}
