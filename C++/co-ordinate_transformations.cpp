// Co-ordinate transformations source file - C++

// Includes
#include "co-ordinate_transformations.h"
#include "iterative_processes.h"
#include <iostream>
#include <math.h>

/*
2D
*/

// Cartesian to polar

std::tuple<int, double> cartesianToPolar( int x, int y )
{
  int r = sqrt( pow( x, 2 ) + pow( y, 2 ) );
  double theta = atan( y / x );
  theta = fmod( theta, (2 * M_PI) );

  return std::make_tuple( r, theta );
}

std::tuple<double, double> cartesianToPolar( double x, double y )
{
  double r = sqrt( pow( x, 2.0 ) + pow( y, 2.0 ) );
  double theta = atan( y / x );
  theta = fmod( theta, (2 * M_PI) );

  return std::make_tuple( r, theta );
}

std::tuple<float, float> cartesianToPolar( float x, float y )
{
  float r = sqrt( pow( x, 2.0 ) + pow( y, 2.0 ) );
  float theta = atan( y / x );
  theta = fmod( theta, (2 * M_PI) );

  return std::make_tuple( r, theta );
}

// Polar to Cartesian

std::tuple<double, double> polarToCartesian( double r, double theta )
{
  theta = fmod( theta, (2 * M_PI) );
  double x = r * cos( theta );
  double y = r * sin( theta );

  return std::make_tuple( x, y );
}

std::tuple<float, float> polarToCartesian( float r, float theta )
{
  theta = fmod( theta, (2 * M_PI) );
  float x = r * cos( theta );
  float y = r * sin( theta );

  return std::make_tuple( x, y );
}

/*
3D
*/

// Cartesian to Spherical

std::tuple<double, double, double> cartesianToSpherical( double x, double y, double z )
{
  double r = sqrt( pow( x, 2.0 ) + pow( y, 2.0 ) + pow( z, 2.0 ) );
  double phi;
  if ( x == 0 && x == y )
  {
    phi = 0;
  }
  else if ( x == 0 && x != y )
  {
    phi = M_PI / 2;
  }
  else
  {
    phi = atan( y / x );
  }
  double theta = acos( z / r );
  theta = fmod( theta, M_PI );
  phi = fmod( phi, (2 * M_PI) );

  return std::make_tuple( r, theta, phi );
}

std::tuple<float, float, float> cartesianToSpherical( float x, float y, float z )
{
  float r = sqrt( pow( x, 2.0 ) + pow( y, 2.0 ) + pow( z, 2.0 ) );
  float phi;
  if ( x == 0 && x == y )
  {
    phi = 0;
  }
  else if ( x == 0 && x != y )
  {
    phi = M_PI / 2;
  }
  else
  {
    phi = atan( y / x );
  }
  float theta = acos( z / r );
  theta = fmod( theta, M_PI );
  phi = fmod( phi, (2 * M_PI) );

  return std::make_tuple( r, theta, phi );
}

// Spherical to Cartesian

std::tuple<double, double, double> sphericalToCartesian( double r, double theta, double phi )
{
    theta = fmod( theta, M_PI );
    phi = fmod( phi, (2 * M_PI) );
    double x = r * sin( theta ) * cos( phi );
    double y = r * sin( theta ) * sin( phi );
    double z = r * cos( theta );

  return std::make_tuple( x, y, z );
}

std::tuple<float, float, float> sphericalToCartesian( float r, float theta, float phi )
{
    theta = fmod( theta, M_PI );
    phi = fmod( phi, (2 * M_PI) );
    float x = r * sin( theta ) * cos( phi );
    float y = r * sin( theta ) * sin( phi );
    float z = r * cos( theta );

  return std::make_tuple( x, y, z );
}

/*
nD
*/

// Hyperspherical to Cartesian

template <typename T>
std::vector<double> hypersphericalToCartesian( T r, const std::vector<double>& angles )
{

  /*
  Generalization of sphericalToCartesian in n-dimensional spheres

  Parameters
  ----------
  r              : custom typename T
      Radius of the hypersphere
  angles        : const std::vector<double>&
      As many angles as necessary are supplied by the user as a vector {a, b, c, ...}

  Returns
  -------
  x              : std::vector<double>
      Cartesian coordinates of given radius and angles.
      By convention, r*cos(phi_{n-1}) is X[0] and r*sin(phi_{1})*...*sin(phi_{n-1}) is X[-1]
  */

  std::vector<double> angs;
  std::vector<double> sine_angs;

  for ( auto const& value : angles )
  {
    angs.push_back( value );
  }
  for ( int i = 0; i < angles.size() - 1; i++ )
  {
    if ( angs[i] < 0 || angs[i] > M_PI )
    {
      angs[i] = fmod( angs[i], M_PI );
    }
  }
  angs.back() = fmod( angs.back(), (2 * M_PI) );

  for ( auto const& value : angs )
  {
    sine_angs.push_back( sin( value ) );
  }

  std::vector<double> x( ( angs.size() + 1 ), 1 );

  for ( int i = 0; i < x.size(); i++ )
  {
    x[i] *= r;
    x[i] *= ip::product( sine_angs, 0, i - 1 );

    if ( i == ( x.size() - 1 ) )
    {
      x[i] *= sin( angs[ i - 1 ] );
    }
    else {
      x[i] *= cos( angs[i] );
    }

  }
  return x;
}

template <typename T>
std::vector<double> cartesianToHyperspherical( const std::vector<T>& x )
{
  /*
  Generalization of cartesianToSpherical in n-dimensional Euclidean space

  Parameters
  ----------
  x              : const std::vector<T>& (T = int, float, double)
      Coordinates of the n-tuple (x_1, x_2, x_3, ...)

  Returns
  -------
  r              : std::vector<double>
      r[0] is the radius and r[1] -> r[n] are the angles
      By convention, all but the last angle are bounded as [0, pi], whereas the last angle
      is bounded as [0, 2*pi)
  */

  std::vector<double> r;
  std::vector<T> squares;
  for ( auto const& value : x )
  {
    squares.push_back( value * value );
  }

  r.push_back( sqrt( ip::sum( squares, 0, squares.size() ) ) );

  for ( int i = 1; i < x.size(); i++ )
  {
    r.push_back( acos( x[i-1] / ( sqrt( ip::sum( squares, i-1, squares.size() ) ) ) ) );
    if ( i != x.size() - 1 )
    {
      r[i] = fmod( r[i], M_PI );
    }
    if ( abs( r[i] ) < 1e-14 )
    {
      r[i] = 0;
    }
  }

  r.back() = fmod( r.back(), ( 2 * M_PI ) );

  if ( r.back() < 0 )
  {
    r.back() = ( 2 * M_PI ) - r.back();
  }

  return r;
}

// For compile testing
int main(){
  return 0;
}
