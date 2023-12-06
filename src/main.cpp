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

// ################### test TCP ###################
//  std::thread t1([]() {
//    TCP player1 = TCP();
//    player1.InitServ("127.0.0.1", 3000);
//    player1.StartServ();
//    std::string test_send = "hello!";
//    player1.SendMsg(test_send);
//  });
//  std::thread t2([]() {
//    TCP player2 = TCP();
//    player2.InitCli("127.0.0.1", 3000);
//    std::string test_res = player2.Receive();
//    std::cout << "Received msg: " << test_res << std::endl;
//  });
//  t1.join();
//  t2.join();

  return 0;
}
