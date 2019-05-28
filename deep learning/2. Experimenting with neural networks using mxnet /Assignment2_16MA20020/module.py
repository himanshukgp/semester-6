import numpy as np
import mxnet as mx
from mxnet import nd, autograd, gluon
import mxnet.ndarray as F
from gluon import nn

class NN1(gluon.Block):
    def __init__(self, **kwargs):
        super(NN1, self).__init__(**kwargs)
        with self.name_scope():
            # layers created in name_scope will inherit name space
            # from parent layer.
            self.fc1 = nn.Dense(512)
            self.fc2 = nn.Dense(128)
            self.fc3 = nn.Dense(64)
            self.fc4 = nn.Dense(32)
            self.fc5 = nn.Dense(16)
            self.fc6 = nn.Dense(10)


    def forward(self):
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = F.relu(self.fc3(x))
        x = F.relu(self.fc4(x))
        x = F.relu(self.fc5(x))
        x = F.softmax(self.fc6(x))

        return x


class NN2(object):
    def __init__(self, **kwargs):
        super(Net, self).__init__(**kwargs)
        with self.name_scope():
            # layers created in name_scope will inherit name space
            # from parent layer.
            self.fc1 = nn.Dense(1024)
            self.fc2 = nn.Dense(512)
            self.fc3 = nn.Dense(256)
            self.fc4 = nn.Dense(10)


    def forward(self):
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = F.relu(self.fc3(x))
        x = F.softmax(self.fc4(x))

        return x
