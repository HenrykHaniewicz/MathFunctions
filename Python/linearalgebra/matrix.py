# Methods for vectors and matrices

# Imports
# None

def row_multiply( arr1, arr2 ):

    """
    Multiplies the i^{th} row in the first array with the i^{th} element in the second.
    (basically does the opposite of regular array multiplication)

    Parameters
    ----------
    arr1           : np.ndarray, list
        Numpy array or list of any dimension
    arr2           : inp.ndarray, list
        Numpy array or list of one less dimension than arr1

    Returns
    -------
    out_arr        : np.ndarray, list
        Row multiplied array
    """

    if arr1.ndim != 2:
        raise ValueError( "Matrix must be 2D" )
    elif arr2.ndim != ( arr1.ndim - 1 ):
        raise ValueError( "Second array must have one less dimension than the first array" )

    out_arr = ( arr1.T * arr2 ).T
    return out_arr
