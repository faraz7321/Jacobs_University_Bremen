from craps import playOneGame, playManyGames

while True:
    playOneGame()
    answer = input("Play again? (y/n): ")
    if answer.lower() != "y":
        break

playManyGames()