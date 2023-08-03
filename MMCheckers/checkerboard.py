import numpy as np

class Checkerboard:
    def __init__(self):
        self.white = 0
        self.black = 0
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


    def get_piece_moves(self, row, col):
        valid_moves = []
        hostile = [1,2] #for 3-4 (black)
        side = 1 #for 3-4 (black)
        if (self.board[row, col] == 1):
            side = -1
            hostile = [3,4]
        move_directions = [(1*side, -1), (1*side, 1)]

        for dr, dc in move_directions:
            new_row, new_col = row + dr, col + dc
            if 0 < new_row <= self.board_size and 0 < new_col <= self.board_size:
                if self.board[new_row, new_col] == 0:
                    if new_col == 1 or new_col == 8:
                        valid_moves.append((2,[new_row, new_col]))
                    elif side == 1 and new_row == 1:
                        valid_moves.append((10,[new_row, new_col]))
                    elif side == -1 and new_row == 8:
                        valid_moves.append((10,[new_row, new_col]))
                    else:
                        valid_moves.append((1,[new_row, new_col]))
                elif self.board[new_row, new_col] in hostile and 0 < (new_row + dr) <= self.board_size and 0 < (new_col + dc) <= self.board_size and self.board[new_row + dr, new_col + dc] == 0:
                    if self.board[new_row, new_col] == hostile[0]:
                        valid_moves.append((3,[new_row + dr, new_col + dc], [new_row, new_col]))
                    else:
                        valid_moves.append((10,[new_row + dr, new_col + dc], [new_row, new_col]))
        
        return valid_moves
    
    def get_queen_moves(self, row, col):
        valid_moves = []
        hostile = [1, 2]  # for 3-4 (black)
        side = 1  # for 3-4 (black)
        if self.board[row, col] == 1:
            side = -1
            hostile = [3, 4]
        move_directions = [(1 * side, -1), (1 * side, 1), (-1 * side, -1), (-1 * side, 1)]

        for dr, dc in move_directions:
            current_row, current_col = row, col
            while True:
                new_row, new_col = current_row + dr, current_col + dc
                if not (0 < new_row <= self.board_size and 0 < new_col <= self.board_size):
                    break
                if self.board[new_row, new_col] == 0:
                    if new_col == 1 or new_col == 8 or new_row == 1 or new_row == 8:
                        valid_moves.append((2, [new_row, new_col]))
                    else:
                        valid_moves.append((1, [new_row, new_col]))
                elif self.board[new_row, new_col] in hostile and 0 < (new_row + dr) <= self.board_size and 0 < (new_col + dc) <= self.board_size and self.board[new_row + dr, new_col + dc] == 0:
                    if self.board[new_row, new_col] == hostile[0]:
                        valid_moves.append((3, [new_row + dr, new_col + dc], [new_row, new_col]))
                    else:
                        valid_moves.append((10, [new_row + dr, new_col + dc], [new_row, new_col]))
                    break
                else:
                    break
                current_row, current_col = new_row, new_col

        return valid_moves

    def print_board(self):
        print(f"White: {self.white}")
        print(f"Black: {self.black}")
        for row in self.board:
            print(" ".join(str(cell) for cell in row))
            # for cell in row:
            #     print(cell, end =" ")
            # print()

check=Checkerboard()
check.print_board()