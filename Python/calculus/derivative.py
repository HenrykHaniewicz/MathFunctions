# Methods for derivatives

# Imports
import math
import decimal as deci
from decimal import Decimal as D

# Standard calculus

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


# Fractional calulus

def fracDerivPolynomial( x ):

    deriv = x

    return deriv
