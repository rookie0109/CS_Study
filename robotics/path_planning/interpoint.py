import numpy as np

def quadratic_interpolation(x0, f0, df0, x1, f1):
    """
    Find the minimum of a quadratic function using interpolation.

    Args:
    - x0: First point.
    - f0: Function value at x0.
    - df0: Derivative value at x0.
    - x1: Second point.
    - f1: Function value at x1.

    Returns:
    - x_min: The x-coordinate of the minimum point of the quadratic function.
    """
    a = x1 - x0
    b = (f1 - f0 - df0 * a) / (a * a)
    x_min = x0 - df0 / (2 * b)
    return x_min

# Test the quadratic interpolation
x0, f0, df0 = 0, 1, -2
x1, f1 = 1, 0.5
x_min = quadratic_interpolation(x0, f0, df0, x1, f1)
print(f"Quadratic interpolation minimum at x = {x_min}")


def cubic_interpolation(x0, f0, df0, x1, f1, df1):
    """
    Find the minimum of a cubic function using interpolation.

    Args:
    - x0: First point.
    - f0: Function value at x0.
    - df0: Derivative value at x0.
    - x1: Second point.
    - f1: Function value at x1.
    - df1: Derivative value at x1.

    Returns:
    - x_min: The x-coordinate of the minimum point of the cubic function.
    """
    d = x1 - x0
    theta = (f0 - f1) * 3 / d + df0 + df1
    s = max(abs(theta), abs(df0), abs(df1))
    a = theta / s
    gamma = s * np.sqrt(a * a - (df0 / s) * (df1 / s))
    if x1 < x0:
        gamma = -gamma
    p = gamma - df0 + theta
    q = gamma - df0 + gamma + df1
    r = p / q
    x_min = x0 + r * d
    return x_min

# Test the cubic interpolation
x0, f0, df0 = 0, 1, -2
x1, f1, df1 = 1, 0.5, -1
x_min = cubic_interpolation(x0, f0, df0, x1, f1, df1)
print(f"Cubic interpolation minimum at x = {x_min}")


import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

# 二次插值验证
x_points = np.array([x0, x1])
y_points = np.array([f0, f1])

quadratic_interp = interp1d(x_points, y_points, kind='quadratic', fill_value="extrapolate")
x_vals = np.linspace(-0.5, 1.5, 100)
y_vals = quadratic_interp(x_vals)

plt.plot(x_vals, y_vals, label='Quadratic Interpolation')
plt.scatter(x_points, y_points, color='red')
plt.axvline(x=x_min, color='green', linestyle='--', label=f'Minimum at x = {x_min:.2f}')
plt.legend()
plt.title("Quadratic Interpolation")
plt.show()

# 三次插值验证
cubic_interp = interp1d(x_points, y_points, kind='cubic', fill_value="extrapolate")
y_vals_cubic = cubic_interp(x_vals)

plt.plot(x_vals, y_vals_cubic, label='Cubic Interpolation')
plt.scatter(x_points, y_points, color='red')
plt.axvline(x=x_min, color='green', linestyle='--', label=f'Minimum at x = {x_min:.2f}')
plt.legend()
plt.title("Cubic Interpolation")
plt.show()
