from dataclasses import dataclass

@dataclass
class Node:
    mode: int
    mark: bool = False
    source: int = None
    g_cost: int = None
    h_cost: int = None
    f_cost: int = None

    def set_f(self):
        self.f_cost = self.g_cost + self.h_cost