import numpy as np
import argparse


parser = argparse.ArgumentParser()
parser.add_argument('--x1', default=1, type=float)
parser.add_argument('--x2', default=1.4, type=float)
parser.add_argument('--y1', default=0, type=float)
parser.add_argument('--y2', default=0.0566, type=float)
parser.add_argument('--h', default=0.1, type=float)
args = parser.parse_args()
x1 = args.x1
x2 = args.x2
y1 = args.y1
y2 = args.y2
h = args.h


def thomas_(a,b,c,d):
	c_ = np.zeros(c.size)
	d_ = np.zeros(d.size)

	c_[0] = c[0]/b[0]
	d_[0] = d[0]/b[0]

	for i in range(1, c.shape[0]-1):
		c_[i] = c[i]/(b[i] - a[i]*c_[i-1])

	for i in range(1, d.shape[0]):
		d_[i] = (d[i] - a[i]*d_[i-1])/(b[i] - a[i]*c_[i-1])

	return [c_, d_]


def main():
	n = int((x2-x1)/h)+1

	a = np.zeros(n-1)
	b = np.zeros(n-1)
	c = np.zeros(n-1)
	d = np.zeros(n-1)

	for i in range(n-1):
		b[i] = -2/np.power(h,2)

	for i in range(n-1):
		a[i] = 1/np.power(h,2) - 1/(2*h*(x1+(i+1)*h))

	for i in range(n-1):
		c[i] = 1/np.power(h,2) + 1/(2*h*(x1+(i+1)*h))

	d[0] = 1/np.power(x1+h,2) - a[0]*y1
	for i in range(n-3):
		d[i+1] = 1/(np.power(x1+(i+2)*h, 2))
	d[-1] = 1/np.power(x2-2*h, 2) - c[-1]*y2

	c_, d_ = thomas_(a,b,c,d)


	res = np.zeros(n-1)

	res[-1] = d_[-1]
	for i in range(n-2):
		res[n-3-i] = d_[n-3-i] - res[n-2-i]*c_[n-3-i]

	for i in range(n-1):
		print(np.power(np.log(x1+h*(i+1)),2)/2 , end=" ")
	print()

	print(res)

if __name__=="__main__":
    main()
