from match import Match

param = input("Match setup (seperate with sapce; White AI, Black AI, White diff, Black diff): ").split(" ")
wai, bai, wd, bd = bool(int(param[0])), bool(int(param[1])), int(param[2]), int(param[3])
print(wai, bai, wd, bd)
plansza = Match(wai, bai, wd, bd)
turn = 1
plansza.arena.print_board()
print("/////////////////////////////////////////")
while True:
    
    print(f"Turn {turn}")
    plansza.move(plansza.player_W, plansza.diff_W, -1)
    plansza.arena.print_board()
    print("/////////////////////////////////////////")
    if plansza.arena.victory_condition():
        break
    plansza.move(plansza.player_B, plansza.diff_B, 1)
    plansza.arena.print_board()
    print("/////////////////////////////////////////")
    if plansza.arena.victory_condition():
        break