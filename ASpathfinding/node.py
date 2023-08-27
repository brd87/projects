from dataclasses import dataclass

@dataclass
class Node:
    mode: int # 0-wall, 1-space, 2-start, 3-target
    color: int = None
    done: bool = False
    source: int = None
    g_cost: int = 0
    h_cost: int = None
    f_cost: int = None

    def get_g(self, columb):
        self.g_cost = columb+1

    def find_h(self, position, target):
        self.h_cost = abs(position[0] - target[0]) + abs(position[1] - target[1])

    def find_f(self):
        self.f_cost = self.g_cost + self.h_cost