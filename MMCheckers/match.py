from checkerboard import Checkerboard

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
                move = None
                position = input("Enter board coordinates (row, collumn) seperated with \"space\": ").split(' ')
                row, col = int(position[0]), int(position[1])
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
                    while True:
                        move = input("Choose move from the list: ")
                        if move in move_list: break
                    self.arena.perform_move(move)
                    break
        else: 
            move = self.minmax(diff, self.arena, side)
            self.arena.perform_move(move[1])

    def minmax(self, diff, arena: Checkerboard, side):
        if diff == 0:
            return self.scoring(arena), None # todo
        best_move = None
        best_score = 0
        moves = self.get_all_moves(arena, side) # todo
        for move in moves:
            new_board = self.simulate(arena, move) # todo
            score = self.minmax(diff-1, new_board, -side)
            if (score[0] >= best_score and side == 1) or (score[0] <= best_score and side == -1):
                best_score, best_move = score[0], move
            return best_score, best_move
    
    def scoring(arena: Checkerboard):
        pass

    def get_all_moves(arena: Checkerboard, side):
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
                    
    def simulate(arena: Checkerboard, move):
        arena.perform_move(move)