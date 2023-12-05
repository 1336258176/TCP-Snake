//
// Created by lybin on 2023/12/2.
//

#ifndef TCP_SNAKE__GAME_H_
#define TCP_SNAKE__GAME_H_

#include <opencv2/opencv.hpp>
#include <boost/log/trivial.hpp>
#include <random>
#include <memory>

enum class Orientations {
  UP, Down, Right, Left, None
};

class Game {
 private:
  int LENGTH;
  int HEIGHT;
  int WIDTH;
  int Radius;
  cv::Mat map_;
  cv::Point2i food_;
  cv::Rect2i frontier_;

  std::mt19937 gen_;
  std::uniform_int_distribution<> rand_int_;

 public:
  explicit Game(int radius = 4, int length = 6, int width = 648, int height =
  648)
      : Radius(radius), LENGTH(length), HEIGHT(height),
        WIDTH(width)
  {
    map_ = cv::Mat::zeros(HEIGHT, WIDTH, CV_8UC3);
    frontier_ = std::move(cv::Rect2i(LENGTH / 2, LENGTH / 2, WIDTH, HEIGHT));
    std::random_device rd;
    gen_ = std::mt19937(rd());
    rand_int_ = std::uniform_int_distribution<>(LENGTH * 3 / 2,
                                                HEIGHT - LENGTH * 3 / 2);
    food_.x = rand_int_(gen_);
    food_.y = rand_int_(gen_);

    cv::namedWindow("TCP-Snake");
  }
  ~Game()
  {
    cv::destroyAllWindows();
  };
  void Start();
  void End(std::vector<cv::Point2i> &snake);

  [[nodiscard]] const cv::Point2i &GetFood() const
  { return food_; }
  [[nodiscard]] const cv::Rect2i &GetFrontier() const
  { return frontier_; }

  void LoadMap();
  void LoadSnake(const std::vector<cv::Point2i> &snake, int Radius);
  void Refresh();
  void ShowMap() const;
  void LoadFood(const cv::Point2i &snake_head);
};

#endif //TCP_SNAKE__GAME_H_
