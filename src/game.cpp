//
// Created by lybin on 2023/12/2.
//

#include "../include/game.h"
#include <boost/log/trivial.hpp>

void Game::LoadMap()
{
  for (int i = 0; i < WIDTH; i += LENGTH) {
    cv::rectangle(map_,
                  cv::Rect2i(i, 0, LENGTH, LENGTH),
                  cv::Scalar(255, 144, 24),
                  -1);
    cv::rectangle(map_,
                  cv::Rect2i(i, HEIGHT - LENGTH, LENGTH, LENGTH),
                  cv::Scalar(255, 144, 24),
                  -1);
  }

  for (int i = 0; i < HEIGHT; i += LENGTH) {
    cv::rectangle(map_,
                  cv::Rect2i(0, i, LENGTH, LENGTH),
                  cv::Scalar(255, 144, 24),
                  -1);
    cv::rectangle(map_,
                  cv::Rect2i(WIDTH - LENGTH, i, LENGTH, LENGTH),
                  cv::Scalar
                      (255, 144, 24),
                  -1);
  }
}

void Game::LoadFood(const cv::Point2i &snake_head)
{
  if (snake_head.x >= food_.x - Radius && snake_head.x <= food_.x + Radius &&
      snake_head.y >= food_.y - Radius && snake_head.y <= food_.y + Radius) {
    food_.x = rand_int_(gen_);
    food_.y = rand_int_(gen_);
  }
  cv::circle(map_,
             cv::Point(food_.x, food_.y),
             Radius,
             cv::Scalar(2, 140, 250),
             -1);
}

void Game::Start()
{
  BOOST_LOG_TRIVIAL(info) << "Game start ...";
  Refresh();
  cv::putText(map_,
              "TCP-Snake",
              cv::Point2i(WIDTH / 5 - 25, HEIGHT / 5 * 2),
              7,
              2.4, cv::Scalar(47, 84, 235), 2);
  cv::putText(map_,
              "Press 't' to start the game...",
              cv::Point2i(WIDTH / 4 - 10, HEIGHT / 3 * 2 - 40),
              5,
              0.9, cv::Scalar(255, 255, 255), 1);
  int flag = 1;
  while (flag) {
    cv::imshow("TCP-Snake", map_);
    char ch = static_cast<char>(cv::waitKey(60));
    if (ch == 't')flag = 0;
  }
}

void Game::End(std::vector<cv::Point2i> &snake)
{
  BOOST_LOG_TRIVIAL(info) << "Game end ...";
  Refresh();
  cv::putText(map_,
              "You're dead.",
              cv::Point2i(WIDTH / 5 - 25, HEIGHT / 2),
              7,
              2.4, cv::Scalar(47, 84, 235), 2);
  cv::imshow("TCP-Snake", map_);
  char key = static_cast<char>(cv::waitKey(0));
  if (key == 'r') {
    snake.clear();
    snake.shrink_to_fit();
    snake.emplace_back(324, 324);
    snake.emplace_back(324, 324 - Radius / 2);
    snake.emplace_back(324, 324 - Radius);
    food_.x = rand_int_(gen_);
    food_.y = rand_int_(gen_);
    return;
  }
}

void Game::ShowMap() const
{
  cv::imshow("TCP-Snake", map_);
  cv::waitKey(1000 / 70);
}

void Game::Refresh()
{
  map_.setTo(0);
}

void Game::LoadSnake(const std::vector<cv::Point2i> &snake, int Radius)
{
  for (int i = 0; i < snake.size(); i++) {
    if (i == 0)cv::circle(map_, snake[i], Radius, cv::Scalar{79, 77, 255}, -1);
    else cv::circle(map_, snake[i], Radius, cv::Scalar{26, 7, 168}, -1);
  }
}
