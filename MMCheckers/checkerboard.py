import numpy as np

from moveop import MoveOp
# todo: mapping///////////////////////////////////////////////////////////////
# todo: cords
# todo: chcek queen cords
# todo: remake score

class Checkerboard:
    def __init__(self):
        self.white = 0
        self.black = 0
        self.turn = 1
        self.turn_limit = 60
        self.board_size = 8
        self.board = np.zeros((self.board_size, self.board_size), dtype=int)
        for row in range(self.board_size):
            for col in range(self.board_size):
                if (row + col) % 2 == 1 and row < 3:
                    self.board[row][col] = 1
                    self.white += 1
                elif (row + col) % 2 == 1 and row > 4:
                    self.board[row][col] = 3
                    self.black += 1

    def victory_condition(self):
        if self.white == 0 or (self.turn == self.turn_limit and self.black > self.white):
            print("Black is victorius!")
            return True
        if self.black == 0 or (self.turn == self.turn_limit and self.white > self.black):
            print("White is victorius!")
            return True
        return False

    def perform_move(self, move: MoveOp):
        self.board[move.source[0]][move.source[1]], self.board[move.target[0]][move.target[1]] = 0, self.board[move.source[0]][move.source[1]]
        if move.mutation == True and (self.board[move.target[0]][move.target[1]] == 1 or self.board[move.target[0]][move.target[1]] == 3):
            self.board[move.target[0]][move.target[1]] += 1
        if move.hostile is not None:
            self.board[move.hostile[0]][move.hostile[1]] = 0

    def get_piece_moves(self, row, col):
        valid_moves = []
        hostile = [3,4] # for 1-2 (white)
        side = 1 # for 1-2 (white)
        if (self.board[row, col] == 3):
            side = -1
            hostile = [1,2]
        move_directions = [(1*side, -1), (1*side, 1)]

        for dr, dc in move_directions:
            new_row, new_col = row + dr, col + dc
            move = None
            if 0 <= new_row < self.board_size and 0 <= new_col < self.board_size:
                if self.board[new_row][new_col] == 0: # empty
                    move = MoveOp([row, col], [new_row, new_col], 1)
                elif self.board[new_row][new_col] in hostile and 0 <= (new_row + dr) < self.board_size and 0 <= (new_col + dc) < self.board_size and self.board[new_row + dr][new_col + dc] == 0:
                    if self.board[new_row][new_col] == hostile[0]: # piece cap
                        move = MoveOp([row, col], [new_row + dr, new_col + dc], 4, [new_row, new_col])
                    else: # queen cap
                        move = MoveOp([row, col], [new_row + dr, new_col + dc], 12, [new_row, new_col])
                
            if move is not None:
                if move.target[1] == 0 or move.target[1] == (self.board_size-1):
                    move.score += 2 # sides
                elif (side == 1 and move.target[0] == 0) or (side == -1 and move.target[0] == (self.board_size-1)): # get queen
                    move.score += 10 
                    move.mutation = True
                valid_moves.append(move)
        
        return valid_moves
    
    def get_queen_moves(self, row, col):
        valid_moves = []
        hostile = [3,4] # for 1-2 (white)
        side = 1 # for 1-2 (white)
        if self.board[row, col] == 4:
            side = -1
            hostile = [1,2]

        move_directions = [(1 * side, -1), (1 * side, 1), (-1 * side, -1), (-1 * side, 1)]

        for dr, dc in move_directions:
            current_row, current_col = row, col
            while True:
                new_row, new_col = current_row + dr, current_col + dc
                move = None
                if 0 <= new_row < self.board_size and 0 <= new_col < self.board_size:
                    if self.board[new_row][new_col] == 0: # empty
                        move = MoveOp([row, col], [new_row, new_col], 1)
                    elif self.board[new_row][new_col] in hostile and 0 <= (new_row + dr) < self.board_size and 0 <= (new_col + dc) < self.board_size and self.board[new_row + dr][new_col + dc] == 0:
                        if self.board[new_row][new_col] == hostile[0]:  # piece cap
                            move = MoveOp([row, col], [new_row + dr, new_col + dc], 3, [new_row, new_col])
                        else: # queen cap
                            move = MoveOp([row, col], [new_row + dr, new_col + dc], 10, [new_row, new_col])
                        #break
                else:
                    break

                current_row, current_col = new_row, new_col
                if move is not None:
                    if move.target[1] == 0 or move.target[1] == (self.board_size-1) or move.target[0] == 0 or move.target[0] == (self.board_size-1): move.score += 3 # borders
                    valid_moves.append(move)

        return valid_moves

    def copy_cb(self):
        new_board = Checkerboard()
        new_board.black, new_board.white = self.black, self.white
        new_board.board_size = self.board_size
        new_board.board = np.copy(self.board)
        return new_board

    def print_board(self):
        print(f"White: {self.white}")
        print(f"Black: {self.black}", end="")
        for row in self.board:
            print()
            for cell in row:
                print(cell, end=" ")
        print()

#check=Checkerboard()
#check.print_board()