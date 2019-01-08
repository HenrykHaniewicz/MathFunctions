// Co-ordinate transformations source file - C++

// Includes
#include "co-ordinate_transformations.h"
#include <iostream>
#include <math.h>
#include <cstdarg>
#include <vector>

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
#define COMMA ,
#define LOGICAL_AND &&

template <typename T, typename... PACK>
std::tuple<float> hypersphericalToCartesian( T r, PACK... angles )
{

  float f = 1;
  /*
  Generalization of sphericalToCartesian in n-dimensional spheres

  Parameters
  ----------
  r              : int, float
      Radius of the hypersphere
  *angles        : *args list (of ints or floats)
      As many angles as necessary are supplied by the user

  Returns
  -------
  X              : list
      Cartesian coordinates of given radius and angles.
      By convention, r*cos(phi_{n-1}) is X[0] and r*sin(phi_{1})*...*sin(phi_{n-1}) is X[-1]
  */

  const auto print_line = [=](auto a) { return unpackedAngles.push_back(a) ; };

  // unary right fold, syntax: ( pack_expression binary_operator ... )
  ( print_line(angles) COMMA ... ) ;
  //      pack_expression - an expression that contains an unexpanded parameter pack => print_line(pack)
  //      binary_operator - any one of the permissible 32 binary binary_operators => COMMA ie. ,

  std::cout << '\n' ;

  // unary left fold, syntax: ( ... binary_operator pack_expression  )
  ( ... LOGICAL_AND print_line(angles)  ) ;
  //      binary_operator - any one of the permissible 32 binary binary_operators => LOGICAL_AND ie. &&
  //      pack_expression - an expression that contains an unexpanded parameter pack => print_line(pack)

  std::cout << '\n' ;

  // binary left fold, syntax: ( init_expression binary_operator ... binary_operator pack_expression  )
  ( ( std::cout << "result is: " ) COMMA ... COMMA print_line(angles) ) ;
  //      init_expression - an expression that does not contain an unexpanded parameter pack => ( std::cout << "result: " )
  //      binary_operator - any one of the permissible 32 binary binary_operators => COMMA ie ,
  //      pack_expression - an expression that contains an unexpanded parameter pack => print_line(pack)

  std::cout << '\n' ;

  // binary right fold, syntax: ( pack_expression binary_operator ... binary_operator init_expression   )
  ( print_line(angles) LOGICAL_AND ... LOGICAL_AND ( std::cout << " (all items in the pack were printed)\n" ) ) ;
  //      pack_expression - an expression that contains an unexpanded parameter pack => print_line(pack)
  //      binary_operator - any one of the permissible 32 binary binary_operators => LOGICAL_AND ie. &&
  //      init_expression - an expression that does not contain an unexpanded parameter pack => ( std::cout << " (all items in the pack were printed)\n" )

  // va_list args;
  // va_start( args, angles );
  //
  // for ( int i = 0; i < angles; ++i ) {
  //     std::cout << f << std::endl;
  //     f += va_arg( args, int );
  // }
  //
  // std::cout << f << std::endl;

  //
  // angles = list( angles )
  // a_len = len( angles )
  // X = r * np.ones( a_len + 1 )
  //
  // # If there is one angle, use polar convenience function
  // if a_len is 1:
  //     X[1], X[0] = polar_to_cartesian( r, angles[0] )
  // # Else if there are two angles, use spherical convenience function
  // elif a_len is 2:
  //     X[1], X[2], X[0] = spherical_to_cartesian( r, angles[0], angles[1] )
  // # Else use general formula
  // else:
  //     for angle in angles[0:-1]:
  //         if ( angle < 0 ) or ( angle > math.pi ):
  //             angle = angle % (math.pi)
  //     angles[-1] = angles[-1] % (2*math.pi)
  //
  //     # Build X by index
  //     for i in np.arange( 0, a_len + 1 ):
  //         X[i] *= ip.product( angles, math.sin, start = 0, end = i - 1 )
  //
  //         # Check if this is the last member of X
  //         if i == ( a_len ):
  //             X[i] *= math.sin( angles[ i-1 ] )
  //         else:
  //             X[i] *= math.cos( angles[i] )
  //
  //         # Check for float point errors
  //         if abs( X[i] ) < 1e-14:
  //             X[i] = 0.0
  //
  // return X

  // va_end( args );
  return std::make_tuple(f);
}
