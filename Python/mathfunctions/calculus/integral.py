# Methods for integrals

# Imports
import math
import decimal as deci
from decimal import Decimal as D

# Standard calculus

def definiteIntegral( func, x0, x1, dx = 1e-25, open = True, float_prec = 56, rounding = True ):

    """
    Calculates the integral of a function between points x0 and x1

    Parameters
    ----------
    func           : callable
        1D (at least) locally differentiatiable method
    x0             : int, float, decimal.Decimal
        Lower bound of integration
    x1             : int, float, decimal.Decimal
        Upper bound of integration
    dx             : int, float, decimal.Decimal
        Step width
    open           : bool
        Use `False` if function is not defined at either x0 or x1
    float_prec     : int
        Float precision
    rounding       : bool
        Choose to account for float point error (False will give FPE)

    Returns
    -------
    int        : decimal.Decimal
    """

    con = deci.getcontext()
    con.prec = float_prec



    return int


def newton_cotes_quad():

    w = 1
    err = 1

    return w, err
