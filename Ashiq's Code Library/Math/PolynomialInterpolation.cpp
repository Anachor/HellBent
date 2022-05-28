/*given n points (x0, y0), (x1, y1) ... (xn, yn) find f(x):
  f(x) = a0 + a1(x-x0)(x-x1) + a2(x-x0)(x-x1)(x-x2) + ....
         an(x-x0)(x-x1)(x-x2)...(x-x{n-1})
  now define p[xk] = yk;
  p[x{k-1},xk] = (p[xk] - p[x{k-1}])/(xk-x{k-1})
  p[x{k-2},x{k-1},xk ] = (p[x{k-1}, xk]-p[x{k-2}, x{k-2}])/
                          (xk - x{k-2})
  so f(x) = p[x0] + p[x0,x1](x-x0)(x-x1) + p[x0,x1,x2]*
            (x-x0)(x-x1)(x-x2)+..+p[x0,x1....xn]*(...)     */


