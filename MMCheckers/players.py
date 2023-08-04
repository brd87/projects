from checkerboard import Checkerboard

class Match:
    def __init__(self, player_W, player_B, diff_W, diff_B):
        self.player_W = player_W
        self.diff_W = diff_W
        self.player_B = player_B
        self.diff_B = diff_B
        self.arena = Checkerboard()


    def move(self, player_ai, diff):
        if self.player_ai == False:
            while True:
                position = input("Enter board coordinates (row, collumn) seperated with \"space\": ").split(' ')
                row, col = int(position[0]), int(position[1])
                if self.arena.board[row][col] == 0:
                    pass
                elif self.arena.board[row][col] == 1 or self.arena.board[row][col] == 3:
                    self.arena.get_piece_moves(row, col)
                    # thing
                    move=0 # thing
                    self.arena.perform_move(row,col,move)
                    break
                else:
                    self.arena.get_queen_moves(row, col)
                    # thing
                    move=0 # thing
                    self.arena.perform_move(row,col,move)
                    break
        else: 
            self.minmax(diff)
            # thing
            move=0 # thing
            self.arena.perform_move(row,col,move)

    def minmax(self, diff):
        pass