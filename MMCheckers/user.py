import datetime

from match import Match

date = datetime.datetime.now().strftime("%Y-%m-%d-%H-%M")
param = input("Match setup (seperate with sapce; White AI, Black AI, White diff, Black diff): ").split(" ")
wai, bai, wd, bd = bool(int(param[0])), bool(int(param[1])), int(param[2]), int(param[3])

with open(f"{date}.txt", "a") as file:
    plansza = Match(wai, bai, wd, bd)
    plansza.arena.print_board()
    print("/////////////////////////////////////////")
    while True:
        print(f"Turn {plansza.arena.turn}")
        plansza.move(plansza.player_W, plansza.diff_W, -1, file)
        plansza.arena.print_board()
        print("/////////////////////////////////////////")
        plansza.move(plansza.player_B, plansza.diff_B, 1, file)
        plansza.arena.print_board()
        print("/////////////////////////////////////////")
        if plansza.arena.victory_condition(file):
            break
        plansza.arena.turn += 1
        # break