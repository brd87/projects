import math

from checkerboard import Checkerboard
from moveop import MoveOp

class Match:
    def __init__(self, player_W, player_B, diff_W, diff_B):
        self.player_W = player_W
        self.diff_W = diff_W
        self.player_B = player_B
        self.diff_B = diff_B
        self.arena = Checkerboard()

    def move(self, player_ai, diff, side):
        if player_ai == False:
            while True:
                move_list = None
                position = input("Enter board coordinates (row, collumn) seperated with \"space\": ").split(' ')
                row, col = int(position[0])-1, int(position[1])-1
                if self.arena.board[row][col] == 0:
                    print("This point is empty!")
                else:
                    if (side==-1 and self.arena.board[row][col] == 1) or (side==1 and self.arena.board[row][col] == 3):
                        move_list = self.arena.get_piece_moves(row, col)
                    elif (side==-1 and self.arena.board[row][col] == 2) or (side==1 and self.arena.board[row][col] == 4):
                        move_list = self.arena.get_queen_moves(row, col)
                    else:
                        print("This piece is not on your side!")
                        continue
                    if move_list is not None:
                        self.print_moves(move_list)
                    while True:
                        print(self.arena.board[row][col])
                        print(len(move_list))
                        move = int(input("Choose move from the list: "))
                        
                        if move_list[move] is not None:
                            self.arena.perform_move(move_list[move])
                            break
                    break
        else: 
            move = self.minmax(diff, self.arena, side)
            print("Executing: ", end="")
            move[1].print_mop()
            self.arena.perform_move(move[1])

    def minmax(self, diff, arena: Checkerboard, side):
        if diff == 0:
            return 0, None
        best_move = None
        if side == 1:
            best_score = -math.inf
        else:
            best_score = math.inf
        moves = self.get_all_moves(arena, side)
        for move in moves:
            new_board = self.simulate(arena, move)
            score = (move.score * side) + self.minmax(diff-1, new_board, -side)[0]
            if (score >= best_score and side == 1) or (score <= best_score and side == -1):
                best_score, best_move = score, move
        return best_score, best_move

    def get_all_moves(self, arena: Checkerboard, side):
        valid_moves = []
        hostile = [1, 2]  # for 3-4 (black)
        if side == -1:
            hostile = [3, 4]
        for row in range(arena.board_size):
            for col in range(arena.board_size):
                if arena.board[row][col] not in hostile and arena.board[row][col] != 0:
                    if arena.board[row][col] == 1 or arena.board[row][col] == 3:
                        for move in arena.get_piece_moves(row, col):
                            valid_moves.append(move)
                    else:
                        for move in arena.get_queen_moves(row, col):
                            valid_moves.append(move)
        return valid_moves
                    
    def simulate(self, arena: Checkerboard, move: MoveOp):
        copy_arena = Checkerboard()
        copy_arena = arena.copy_cb()
        copy_arena.perform_move(move)
        return copy_arena
    
    def print_moves(self, moves):
        i = 0
        for move in moves:
            print(f"{i}. ", end="")
            move.print_mop()
            i+=1

