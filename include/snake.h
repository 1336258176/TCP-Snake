//
// Created by lybin on 2023/12/2.
//

#ifndef TCP_SNAKE__SNAKE_H_
#define TCP_SNAKE__SNAKE_H_

#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <thread>
#include "game.h"
#include "TCP.h"

class Snake {
 private:
  int radius_;
  int step_;
  std::vector<cv::Point2i> body_;
  Orientations head_ = Orientations::UP;

 public:
  explicit Snake(int radius = 4, int step = 8)
      : radius_(radius), step_(step)
  {
    body_.emplace_back(324, 324);
    body_.emplace_back(324, 324 - radius_ / 2);
    body_.emplace_back(324, 324 - radius_);
  }
  ~Snake() = default;

  void Move();
  [[nodiscard]] bool Eat(const cv::Point2i &food) const;
  void Add();

  [[nodiscard]] const cv::Point2i &GetHead() const
  { return body_[0]; }
  [[nodiscard]] const std::vector<cv::Point2i> &GetBody() const
  { return body_; }
  [[nodiscard]] int GetRadius() const
  { return radius_; }
  std::vector<cv::Point2i> &GetBodyDebug()
  { return body_; }

  [[nodiscard]] bool Die(const cv::Rect2i &frontier) const;
  [[nodiscard]] bool Empty() const;
  void GetMove();

//  void SendMsg(const std::vector<cv::Point2i> &snake_body) override;
//  std::vector<cv::Point2i> Receive() override;
};

#endif //TCP_SNAKE__SNAKE_H_
