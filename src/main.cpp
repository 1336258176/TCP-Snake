#include "../include/game.h"
#include "../include/snake.h"

int main()
{
  Game game = Game();
  Snake player1 = Snake();
  game.Start();
  int flag = 1;
  while (flag) {
    char ch = static_cast<char>(cv::waitKey(10));
    if (ch == 'q')flag = 0;

    if (player1.Die(game.GetFrontier()))
      game.End(player1.GetBodyDebug());

    game.LoadMap();
    game.LoadFood(player1.GetHead());

    player1.Move();
    if (player1.Eat(game.GetFood()))
      player1.Add();

    game.LoadSnake(player1.GetBody(), player1.GetRadius());
    game.ShowMap();
    game.Refresh();
  }
  return 0;
}
