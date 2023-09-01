import csv

from network import Network
from number import Number

class DataHandler:
    def __init__(self):
        self.network = Network()


    def train_setup(self, mini_batch, epochs, learning_rate, is_WAB, data_range):
        self.mini_batch = mini_batch
        self.epochs = epochs
        self.learning_rate = learning_rate
        self.is_WAB = is_WAB
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
        with open(f"{filename}.scv", "r") as file:
            pass
        return WAB


    def save_WAB(self, filename):
        with open(f"{filename}.scv", "w") as file:
            pass