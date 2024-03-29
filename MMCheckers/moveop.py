from dataclasses import dataclass

@dataclass
class MoveOp:
    source: int
    target: int
    score: int
    hostile: int = None
    mutation: bool = False
    def print_mop(self):
        print(f"From ({self.source[0]+1}, {self.source[1]+1}) to ({self.target[0]+1}, {self.target[1]+1})", end="")
        if self.hostile is not None:
            print(f", while capturing piece on ({self.hostile[0]+1}, {self.hostile[1]+1})", end="")
        if self.mutation == True:
            print(" and gets Queen", end="")
        print(".")
    def registr(self):
        reg = f"({self.source[0]+1}, {self.source[1]+1}) -> ({self.target[0]+1}, {self.target[1]+1})"
        if self.hostile is not None:
            reg += f" + cap({self.hostile[0]+1}, {self.hostile[1]+1})"
        if self.mutation == True:
            reg += " + Q"
        return reg + "\n"