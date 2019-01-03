# Useful iterative functions

# Imports
import numpy as np

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
    product : float
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
