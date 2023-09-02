import numpy as np

from number import Number
from layer import Layer

class Network:
    def __init__(self, WAB, hidden_neuron, hidden_num):
        self.layers = []
        if WAB is None:
            self.generate_WAB(hidden_neuron, hidden_num)
        for single_layer in WAB:
                self.layers.append(single_layer)


    def load_data(self, batch_examples):
        self.batch_examples = batch_examples


    def generate_WAB(self, hidden_neuron, hidden_num):
        layer_info = [[784, 1], [hidden_neuron, hidden_num], [10, 1]]
        bias = []
        weights = []
        for part in layer_info:
            for sub_part in range(part[1]):
                layer = Layer(None, None)
                layer


    def forward_propagation(self):
        pass
    

    def back_propagation(self):
        pass
    

    def update_WAB(self):
        pass
