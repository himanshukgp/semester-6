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


def thomas_(A=None, d=None):
	res = np.eye(A.shape[0]+1)
	d_new = np.zeros(d.shape[0]+1)

	res[0][1] = A[0][1]/A[0][0]
	d_new[0] = d[0]/A[0][0]

	for i in range(A.shape[0]-2):
		res[i+1][i+2] = A[i+1][i+2]/(A[i+1][i+1]+A[i+1][i]*res[i][i+1])
		d_new[i+1] = (d[i+1]-A[i+1][i]*d_new[i])/(A[i+1][i+1]-A[i+1][i]*res[i][i+1])

	d_new[-2] = (d[-2] - A[-2][-1]*d_new[-3]) / (A[-2][-2] - A[-2][-3]*res[-3][-2])
	d_new[-1] = y2


	return [res, d_new]


def main():
	n = int((x2-x1)/h)+1

	A = np.zeros((n-1,n-1))
	d = np.zeros(n-1)

	A[0][0] = -2/np.power(h,2)
	A[0][1] = (1/ np.power(h,2) + 1/(2*h*x1) )
	d[0] = 1/np.power(x1,2) - ( 1/ np.power(h,2) - 1/(2*h*x1) ) * y1

	A[n-2][n-3] = (1/np.power(h,2) - 1/(2*h*(x2-2*h)) )
	A[n-2][n-2] = -2/np.power(h,2)
	d[n-2] = 1/np.power(x2-2*h, 2) - (1/np.power(h,2) + 1/(2*h*(x2-2*h)) )*y2

	for i in range(n-3):
		A[i+1][i] = (1/ np.power(h,2) - 1/(2*h* (x1+(i+1)*h) ))
		A[i+1][i+1] = -2/np.power(h,2)
		A[i+1][i+2] = (1/ np.power(h,2) + 1/(2*h* (x1+(i+1)*h) ))
		d[i+1] = 1/(np.power(x1+(i+1)*h, 2))

	C, d_ = thomas_(A, d)

	print(C)
	print(d_)
	
	res = np.zeros(n)
	res[n-1] = d_[n-1]

	for i in range(n-1):
		res[n-2-i] = (d_[n-2-i]-res[n-1-i]*A[n-2-i][n-1-i])

	for i in range(n-1):
		print(np.power(np.log(x1+h*(i+1)),2)/2 , end=" ")
		print(res[i])



if __name__=="__main__":
    main()
