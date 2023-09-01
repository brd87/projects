import csv

from network import Network

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
        batch_examples = []
        with open(f"{filename}.scv", "r") as file:
            csvreader = csv.reader(file)
            next(csvreader)
            for item in csvreader[:self.mini_batch]:
                batch_examples.append(item)
        return batch_examples


    def single_read(self, filename):
        item = None
        with open(f"{filename}.scv", "r") as file:
            pass
        return item


    def load_WAB(self, filename):
        WAB = []
        with open(f"{filename}.scv", "r") as file:
            pass
        return WAB


    def save_WAB(self, filename):
        with open(f"{filename}.scv", "w") as file:
            pass