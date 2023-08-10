from dataclasses import dataclass

@dataclass
class MoveOp:
    source: int
    target: int
    score: int
    hostile: int = None
    mutation: bool = False
