# Newton's method functions

# Imports
from . import definiteDerivative

import math
import decimal as deci
from decimal import Decimal as D

def newtonsMethod( func, guess, iterations = 10, **kwargs ):

    """
    Uses Newton's method to calculate the zeros of a 1D function

    Parameters
    ----------
    func           : callable
        1D (at least) locally differentiatiable method
    guess          : int, float, decimal.Decimal
        Initial guess (x0)
    iterations     : int
        Number of iterations of the method
    **kwargs
        kwargs passed to definiteDerivative

    Returns
    -------
    x0             : decimal.Decimal
    """

    x0 = D( guess )

    for i in range( iterations ):
        x0 = x0 - D( func( x0 ) / definiteDerivative( func, x0, **kwargs ) )

    return x0
