// Co-ordinate transformations header file - C++
#pragma once

// Includes
#include <tuple>

std::tuple<int, double> cartesianToPolar( int x, int y );
std::tuple<double, double> cartesianToPolar( double x, double y );
std::tuple<float, float> cartesianToPolar( float x, float y );

std::tuple<double, double> polarToCartesian( double r, double theta );
std::tuple<float, float> polarToCartesian( float r, float theta );

std::tuple<double, double, double> cartesianToSpherical( double x, double y, double z );
std::tuple<float, float, float> cartesianToSpherical( float x, float y, float z );

std::tuple<double, double, double> sphericalToCartesian( double r, double theta, double phi );
std::tuple<float, float, float> sphericalToCartesian( float r, float theta, float phi );
