import numpy as np
import data_loader
from zipfile import ZipFile
import numpy as np
import mxnet as mx
from mxnet import nd, autograd, gluon
import mxnet.ndarray as F
import random
import matplotlib.pyplot as plt
import argparse


def NN1():
	net = gluon.nn.Sequential()
	with net.name_scope():
		net.add(gluon.nn.Dense(1024, activation="relu"))
		net.add(gluon.nn.Dense(512, activation="relu"))
		net.add(gluon.nn.Dense(256, activation="relu"))
		net.add(gluon.nn.Dense(10))
	return net


def NN2():
	net = gluon.nn.Sequential()
	with net.name_scope():
		net.add(gluon.nn.Dense(1024, activation="relu"))
		net.add(gluon.nn.BatchNorm())
		net.add(gluon.nn.Dense(512, activation="relu"))
		net.add(gluon.nn.BatchNorm())
		net.add(gluon.nn.Dense(256, activation="relu"))
		net.add(gluon.nn.BatchNorm())
		net.add(gluon.nn.Dense(10))
	return net

def NN3():
	net = gluon.nn.Sequential()
	with net.name_scope():
		net.add(gluon.nn.Dense(1024, activation="relu"))
		net.add(gluon.nn.Dropout(.1))
		net.add(gluon.nn.Dense(512, activation="relu"))
		net.add(gluon.nn.Dropout(.4))
		net.add(gluon.nn.Dense(256, activation="relu"))
		net.add(gluon.nn.BatchNorm())
		net.add(gluon.nn.Dropout(.6))
	return net




def evaluate_accuracy(data_iterator, net):
	data_ctx = mx.cpu()
	model_ctx = mx.cpu()
	acc = mx.metric.Accuracy()
	for i, (data, label) in enumerate(data_iterator):
		data = data.as_in_context(model_ctx).reshape((-1, 784))
		label = label.as_in_context(model_ctx)
		output = net(data)
		predictions = nd.argmax(output, axis=1)
		acc.update(preds=predictions, labels=label)
	return acc.get()[1]

def main():
	

	data_ctx = mx.cpu()
	model_ctx = mx.cpu()

	epochs = 10
	batch_size = 32
	lr = 0.0001

	# Seed
	mx.random.seed(1)
	random.seed(1)


	# Data
	data_obj = data_loader.DataLoader()
	X_train, y_train = data_obj.load_data(mode='train')
	X_test, y_test = data_obj.load_data(mode='test')

	X_train = X_train.astype('float32')
	X_test = X_test.astype('float32')

	train_data = gluon.data.DataLoader(
		gluon.data.dataset.ArrayDataset(X_train, y_train), batch_size=batch_size, shuffle=True)

	test_data = gluon.data.DataLoader(
		gluon.data.dataset.ArrayDataset(X_test, y_test), batch_size=batch_size, shuffle=True)

	

	# Model
	num_inputs = 784
	num_outputs = 10
	num_examples = X_train.shape[0]

	def fn(norm_=1, drop_out=0, optimizer_=1):

		if norm_== 1 and drop_out==0 :
			net = NN1()
		elif norm_==1 and drop_out==1 and optimizer_==1:
			net = NN3()
		elif norm_==0 and dropuout==0 and optimizer_==1:
			net = NN2()


		net.collect_params().initialize(mx.initializer.Normal(0.01), ctx=model_ctx)
		square_loss = gluon.loss.SoftmaxCrossEntropyLoss()


		if optimizer_==1:
		 	trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate': lr})
		elif optimizer_==2: 
			trainer = gluon.Trainer(net.collect_params(), 'nag', {'learning_rate': lr})
		elif optimizer_==3:
			trainer = gluon.Trainer(net.collect_params(), 'AdaDelta', {'learning_rate': lr})
		elif optimizer_==4: 
			trainer = gluon.Trainer(net.collect_params(), 'AdaGrad', {'learning_rate': lr})
		elif optimizer_==5: 
			trainer = gluon.Trainer(net.collect_params(), 'RMSProp', {'learning_rate': lr})
		elif optimizer_==6: 
			trainer = gluon.Trainer(net.collect_params(), 'Adam', {'learning_rate': lr})

		num_batches = num_examples / batch_size

		def train_loop():
			data_ctx = mx.cpu()
			model_ctx = mx.cpu()

			loss_ = []
			period = 10
			for e in range(epochs):
				cumulative_loss = 0
				total_loss = []
				sum = 0
				for i, (data, label) in enumerate(train_data):
					data = data.as_in_context(model_ctx).reshape(-1,784)
					label = label.as_in_context(model_ctx)
					with autograd.record():
						output = net(data)
						loss = square_loss(output, label)
					loss.backward()
					trainer.step(batch_size)
					cumulative_loss += nd.mean(loss).asscalar()
					if i * batch_size % period == 0:
						total_loss.append(np.mean(nd.mean(loss).asnumpy()))
						sum = sum+1
				loss_.append(cumulative_loss/sum)
				test_accuracy = evaluate_accuracy(test_data, net)
				train_accuracy = evaluate_accuracy(train_data, net)
				print("Epoch %s. Loss: %s, Train_acc %s, Test_acc %s" % (e, cumulative_loss/num_examples,
																		 train_accuracy, test_accuracy))
			return loss_

		loss_ = train_loop()
		return loss_

	loss_1 = fn(1,0,1)
	loss_2 = fn(1,0,2)
	loss_3 = fn(1,0,3)
	loss_4 = fn(1,0,4)
	loss_5 = fn(1,0,5)
	loss_6 = fn(1,0,6)


	plt.plot(np.arange(epochs), loss_1, 'r-', label="sgd")
	plt.plot(np.arange(epochs), loss_2, 'g-', label="nag")
	plt.plot(np.arange(epochs), loss_3, 'b-', label="AdaDelta")
	plt.plot(np.arange(epochs), loss_4, 'y-', label="AdaGrad")
	plt.plot(np.arange(epochs), loss_5, 'c-', label="RMSProp")
	plt.plot(np.arange(epochs), loss_6, 'm-', label="Adam")
	plt.legend(loc='best')
	plt.ylabel('loss')
	plt.show()



if __name__ == '__main__':
	main()
