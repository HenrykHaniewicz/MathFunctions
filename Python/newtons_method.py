# Newton's method functions

# Imports
import math
import decimal as deci
from decimal import Decimal as D

def roundSig( x, sig = 2 ):
    return round( x, sig - int( math.floor( math.log10( abs( x ) ) ) ) - 1 )

def definiteDerivative( func, x0, dx = 1e-25, float_prec = 56, rounding = True ):

    """
    Calculates the derivative of a function at point x0

    Parameters
    ----------
    func           : callable
        1D (at least) locally differentiatiable method
    x0             : int, float, decimal.Decimal
        Constant to calculate derivative of `func` at
    dx             : int, float, decimal.Decimal
        Step width
    float_prec     : int
        Float precision
    rounding       : bool
        Choose to account for float point error (False will give FPE)

    Returns
    -------
    f_prime        : decimal.Decimal
    """

    con = deci.getcontext()
    con.prec = float_prec

    # Decimalize everything
    dx = D( dx )
    exp = int( -math.log10( dx ) )
    x0 = D( x0 )
    x1 = D( x0 + dx )

    # Basically take the limit
    diff = D( func( x1 ) ) - D( func( x0 ) )
    f_prime = diff / dx

    # Disable rounding errors handler
    if rounding:
        f_prime = D( roundSig( f_prime, exp ) )

    return f_prime


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
