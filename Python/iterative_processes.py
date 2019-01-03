# Useful iterative functions

# Imports
import numpy as np


def sum( list, func = None, start = 0, end = 10 ):

    """
    Calculates the sum of a list or a function applied to a list

    Parameters
    ----------
    list           : list, np.ndarray (of ints or floats)
        List (or array) or values to sum together
    func           : callable
        Optional function to apply to the list
    start          : int
        Start index of product
    end            : int
        End index of product

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

        if func is not None:
            for element in list[ start:end+1 ]:
                sum += func( element )
        else:
            for element in list[ start:end+1 ]:
                sum += element

    if abs( sum ) < 1e-14:
        sum = 0

    return sum


def product( list, func = None, start = 0, end = 10 ):

    """
    Calculates the product of a list or a function applied to a list

    Parameters
    ----------
    list           : list, np.ndarray (of ints or floats)
        List (or array) or values to multiply
    func           : callable
        Optional function to apply to the list
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

        if func is not None:
            for element in list[ start:end+1 ]:
                product *= func( element )
        else:
            for element in list[ start:end+1 ]:
                product *= element

    if abs( product ) < 1e-14:
        product = 0

    return product
