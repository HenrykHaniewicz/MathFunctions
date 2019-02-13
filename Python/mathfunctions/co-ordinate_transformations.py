# Co-ordinate transformations

# Imports
import iterative_processes as ip
import math
import numpy as np

# Functions
def cartesian_to_polar( x, y ):
    r = math.sqrt( x**2 + y**2 )
    theta = math.atan( y / x )
    theta = theta % (2*math.pi)
    return r, theta

def polar_to_cartesian( r, theta ):
    theta = theta % (2*math.pi)
    x = r * math.cos( theta )
    y = r * math.sin( theta )
    return x, y

def cartesian_to_cylindrical( x, y, z ):
    r, theta = cartesian_to_polar( x, y )
    h = z
    return r, theta, h

def cylindrical_to_cartesian( r, theta, h ):
    x, y = polar_to_cartesian( r, theta )
    z = h
    return x, y, z

def cartesian_to_spherical( x, y, z ):
    r = math.sqrt( x**2 + y**2 + z**2 )
    phi = math.atan( y / x )
    theta = math.acos( z / r )
    theta = theta % (math.pi)
    phi = phi % (2*math.pi)
    return r, theta, phi

def spherical_to_cartesian( r, theta, phi ):
    theta = theta % (math.pi)
    phi = phi % (2*math.pi)
    x = r * math.sin( theta ) * math.cos( phi )
    y = r * math.sin( theta ) * math.sin( phi )
    z = r * math.cos( theta )
    return x, y, z



def hyperspherical_to_cartesian( r, *angles ):

    """
    Generalization of spherical_to_cartesian in n-dimensional spheres

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
    """

    angles = list( angles )
    a_len = len( angles )
    X = r * np.ones( a_len + 1 )

    # If there is one angle, use polar convenience function
    if a_len is 1:
        X[1], X[0] = polar_to_cartesian( r, angles[0] )
    # Else if there are two angles, use spherical convenience function
    elif a_len is 2:
        X[1], X[2], X[0] = spherical_to_cartesian( r, angles[0], angles[1] )
    # Else use general formula
    else:
        for angle in angles[0:-1]:
            if ( angle < 0 ) or ( angle > math.pi ):
                angle = angle % (math.pi)
        angles[-1] = angles[-1] % (2*math.pi)

        # Build X by index
        for i in np.arange( 0, a_len + 1 ):
            X[i] *= ip.product( sin( angles ), start = 0, end = i - 1 )

            # Check if this is the last member of X
            if i == ( a_len ):
                X[i] *= math.sin( angles[ i-1 ] )
            else:
                X[i] *= math.cos( angles[i] )

            # Check for float point errors
            if abs( X[i] ) < 1e-14:
                X[i] = 0.0

    return X


def cartesian_to_hyperspherical( x ):

    """
    Generalization of cartesian_to_spherical in n-dimensional Euclidean space

    Parameters
    ----------
    x              : np.ndarray
        Coordinates of the n-tuple (x_1, x_2, x_3, ...)

    Returns
    -------
    r              : int, float
        Radius of hypersphere
    angs           : list
        Angles of hypersphere
        By convention, all but the last angle are bounded as [0, pi], whereas the last angle
        is bounded as [0, 2*pi)
    """

    if not isinstance( x, np.ndarray ):
        x = np.array( x )
    c_len = len( x )

    angs = np.zeros( c_len - 1 )

    # If one variable, return r = x and set all angles to 0
    if c_len is 1:
        r = float(x)
        angs = 0
    # Else if two variables, call polar convenience function
    elif c_len is 2:
        r, angs[0] = cartesian_to_polar( x[0], x[1] )
    # Else if three variables, call spherical convenience function
    elif c_len is 3:
        r, angs[0], angs[1] = cartesian_to_spherical( x[0], x[1], x[2] )
    # Else use general formula
    else:

        # Find the radius
        r = math.sqrt( ip.sum( x**2, start = 0, end = c_len ) )

        # Build angs by index
        for i in np.arange( 0, c_len - 1 ):
            angs[i] = math.acos( x[i] / math.sqrt( ip.sum( x**2, start = i, end = c_len ) ) )

            # Check for float point errors
            if abs( angs[i] ) < 1e-14:
                angs[i] = 0.0

        # Correction if x_n < 0
        if x[-1] < 0:
            angs[-1] = (2*math.pi) - angs[-1]

    return r, angs
