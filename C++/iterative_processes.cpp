// Useful iterative functions source file - C++

// Includes
#include "iterative_processes.h"
#include <math.h>

namespace ip
{
  double sum( const std::vector<double>& x, int start, int end )
  {

    /*
    Calculates the sum of a vector

    Parameters
    ----------
    x           : const std::vector<double>&
        Vector of values to sum together
    start          : int
        Start index of product
    end            : int
        End index of product

    Returns
    -------
    sum            : int, float
    */

    double sum = 0.0;
    if ( end >= start )
    {
      for ( int i = start; i < end + 1; i++ )
      {
        sum += x[i];
      }
      if ( abs( sum ) < 1e-14 )
      {
        sum = 0.0;
      }
    }
    if ( abs( sum ) < 1e-14 )
    {
      sum = 0;
    }
    return sum;
  }

  double product( const std::vector<double>& x, int start, int end )
  {

    /*
    Calculates the product of a vector

    Parameters
    ----------
    x           : const std::vector<double>&
        Vector of values to multiply
    start          : int
        Start index of product
    end            : int
        End index of product

    Returns
    -------
    prod        : double
    */

    double prod = 1.0;

    if ( end >= start )
    {
      for ( int i = start; i < ( end + 1 ); i++ )
      {
        prod *= x[i];
      }
      if ( abs( prod ) < 1e-14 )
      {
        prod = 0.0;
      }
    }
    return prod;
  }
}
