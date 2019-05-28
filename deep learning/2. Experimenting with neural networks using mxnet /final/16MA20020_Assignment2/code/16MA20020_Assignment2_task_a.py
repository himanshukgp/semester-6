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
		net.add(gluon.nn.Dense(512, activation="relu"))
		net.add(gluon.nn.Dense(128, activation="relu"))
		net.add(gluon.nn.Dense(64, activation="relu"))
		net.add(gluon.nn.Dense(32, activation="relu"))
		net.add(gluon.nn.Dense(16, activation="relu"))
		net.add(gluon.nn.Dense(10))
	return net

def NN2():
	net = gluon.nn.Sequential()
	with net.name_scope():
		net.add(gluon.nn.Dense(1024, activation="relu"))
		net.add(gluon.nn.Dense(512, activation="relu"))
		net.add(gluon.nn.Dense(256, activation="relu"))
		net.add(gluon.nn.Dense(10))
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

	parser = argparse.ArgumentParser()
	parser.add_argument('--train', action='store_true')
	parser.add_argument('--test', action='store_true')
	args = parser.parse_args()
	

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

	if args.train == True:

		# Model
		num_inputs = 784
		num_outputs = 10
		num_examples = X_train.shape[0]

		net = NN2()
		net.collect_params().initialize(mx.initializer.Uniform(0.01), ctx=model_ctx)
		square_loss = gluon.loss.SoftmaxCrossEntropyLoss()
		trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate': lr})
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

		file_name = "../weights/param1b"
		net.save_parameters(file_name)

		plt.plot(np.arange(epochs), loss_, 'r-')
		plt.ylabel('some numbers')
		plt.show()


		epochs=100
		net = NN1()
		net.collect_params().initialize(mx.initializer.Uniform(0.01), ctx=model_ctx)
		square_loss = gluon.loss.SoftmaxCrossEntropyLoss()
		trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate': lr})
		num_batches = num_examples / batch_size

		loss_ = train_loop()

		file_name = "../weights/param1a"
		net.save_parameters(file_name)

		plt.plot(np.arange(epochs), loss_, 'r-')
		plt.ylabel('some numbers')
		plt.show()


	if args.test == True:
		new_net = NN2()
		file_name = "../weights/param1a"
		new_net.load_parameters(file_name)
		test_accuracy = evaluate_accuracy(test_data, new_net)
		print("Test Accuracy for the 1st architecture is ", test_accuracy)

		new_net = NN1()
		file_name = "../weights/param1b"
		new_net.load_parameters(file_name)
		test_accuracy = evaluate_accuracy(test_data, new_net)
		print("Test Accuracy for the 2nd architecture is ", test_accuracy)


if __name__ == '__main__':
	main()
