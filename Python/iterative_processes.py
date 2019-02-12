# Useful iterative functions

# Imports
import numpy as np


def sum( list, start = 0, end = 10 ):

    """
    Calculates the sum of the elements in a list

    Parameters
    ----------
    list           : list, np.ndarray (of ints or floats)
        List (or array) or values to sum together
    start          : int
        Start index of sum
    end            : int
        End index of sum

    Returns
    -------
    sum            : int, float
    """

    # Make sure start and end points are some type of integer
    if not isinstance( start, int ) and not isinstance( start, np.integer ):
        raise TypeError( "Start point must be an integer or NumPy integer. Current type is: {}".format( type(start) ) )
    if not isinstance( end, int ) and not isinstance( end, np.integer ):
        raise TypeError( "End point must be an integer or NumPy integer. Current type is: {}".format( type(end) ) )

    sum = 0.0

    if end >= start:
        for element in list[ start:end+1 ]:
            sum += element

        if abs( sum ) < 1e-14:
            sum = 0

    return sum


def product( list, start = 0, end = 10 ):

    """
    Calculates the product of the elements in a list

    Parameters
    ----------
    list           : list, np.ndarray (of ints or floats)
        List (or array) or values to multiply
    start          : int
        Start index of product
    end            : int
        End index of product

    Returns
    -------
    product        : int, float
    """

    # Make sure start and end points are some type of integer
    if not isinstance( start, int ) and not isinstance( start, np.integer ):
        raise TypeError( "Start point must be an integer or NumPy integer. Current type is: {}".format( type(start) ) )
    if not isinstance( end, int ) and not isinstance( end, np.integer ):
        raise TypeError( "End point must be an integer or NumPy integer. Current type is: {}".format( type(end) ) )

    product = 1.0

    if end >= start:
        for element in list[ start:end+1 ]:
            product *= element

        if abs( product ) < 1e-14:
            product = 0

    return product
