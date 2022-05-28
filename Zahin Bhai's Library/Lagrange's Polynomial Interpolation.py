import sys
import math

val = [0, 1, 2, 3, 4, 5, 6]
out = [1, 1, 2, 4, 8, 16, 31]

def lagrange(n):
	res = 0
	for i in range(len(val)):
		x = out[i]
		y = 1
		for j in range(len(val)):
			if (i != j):
				x *= (n - val[j])
				y *= (val[i] - val[j])

		res += (x // y)
	return res

def main():
	print (lagrange(20))

if __name__ == '__main__':
    main()
