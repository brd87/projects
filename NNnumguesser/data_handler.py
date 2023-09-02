import csv

from network import Network
from number import Number
from layer import Layer

class DataHandler:
    def __init__(self, is_WAB, filename, hidden_neuron, hidden_num):
        WAB = None
        if is_WAB:
            WAB = self.load_WAB(filename)
        self.network = Network(WAB, hidden_neuron, hidden_num)


    def train_setup(self, mini_batch, epochs, learning_rate, data_range):
        self.mini_batch = mini_batch
        self.epochs = epochs
        self.learning_rate = learning_rate
        self.data_range = data_range


    def train_read(self, filename):
        for epoch in range(self.epochs):
            with open(f"{filename}.csv", "r") as file:
                batch_examples = []
                csvr = csv.reader(file, delimiter=',')
                next(csvr)
                current_row = 0
                for current in range(self.data_range):
                    for row in csvr:
                        item = [int(val) for val in row]
                        batch_examples.append(Number(item[0], item[1:]))
                        current_row += 1
                        if current_row >= self.mini_batch:
                            break
                    self.network.load_data(batch_examples)
                    self.network.forward_propagation() # preforms forwardpropagation
                    self.network.back_propagation() # preforms backpropagation
                    self.network.update_WAB() # preforms update
                    batch_examples.clear()


    def single_read(self, filename, target):
        item = None
        with open(f"{filename}.scv", "r") as file:
            csvr = csv.reader(file, delimiter=',')
            next(csvr)
            for skip in range(target):
                next(csvr)
            item = [int(val) for val in next(csvr)]
        return Number(None, item)


    def load_WAB(self, filename):
        WAB = []
        with open(f"{filename}.txt", "r") as file:
            bias = []
            weights = []
            for line in file:
                if line == "NEW":
                    WAB.append(Layer(bias, weights))
                    bias = []
                    weights = []
                    continue

                line = line.split(";")
                item = [float(val) for val in line]
                
                if bias == []:
                    bias.append(item)
                weights.append(item)
        return WAB


    def save_WAB(self, filename):
        with open(f"{filename}.scv", "w") as file:
            pass