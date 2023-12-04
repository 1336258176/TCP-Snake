//
// Created by lybin on 2023/12/2.
//

#include "../include/snake.h"

void Snake::Move()
{
  GetMove();
  for (int i = body_.size() - 1; i > 0; i--)
    body_[i] = body_[i - 1];
  switch (head_) {
    case Orientations::UP:body_[0].y -= step_;
      break;
    case Orientations::Down:body_[0].y += step_;
      break;
    case Orientations::Right:body_[0].x += step_;
      break;
    case Orientations::Left:body_[0].x -= step_;
      break;
  }
}

void Snake::Add()
{
  int len = static_cast<int>(body_.size());
  body_.emplace_back(body_[len - 1].x,
                     body_[len - 1].y + radius_ * 2);
}

bool Snake::Empty() const
{ return body_.empty(); }

bool Snake::Die(const cv::Rect2i &frontier) const
{
  cv::Rect2i t
      (frontier.x + 3, frontier.y + 3, frontier.width - 6, frontier.height - 6);
  if (body_[0].x > t.x && body_[0].y > t.y && body_[0].x < (t.x + t.width)
      && body_[0].y < (t.y + t.height))
    return false;
  return true;
}

bool Snake::Eat(const cv::Point2i &food) const
{
  if (body_[0].x >= food.x - radius_ && body_[0].x <= food.x + radius_ &&
      body_[0].y >= food.y - radius_ && body_[0].y <= food.y + radius_)
    return true;
  return false;
}

void Snake::GetMove()
{
  char move_ = static_cast<char>(cv::waitKey(30));
  switch (move_) {
    case 'w':head_ = Orientations::UP;
      break;
    case 's':head_ = Orientations::Down;
      break;
    case 'a':head_ = Orientations::Left;
      break;
    case 'd':head_ = Orientations::Right;
      break;
    default:break;
  }
}

//void Snake::SendMsg(const std::vector<cv::Point2i> &snake_body)
//{
//  nlohmann::json json_vec = nlohmann::json::array();
//  for (const auto &point : snake_body) {
//    json_vec.push_back({{"x", point.x}, {"y", point.y}});
//  }
//  std::string jsonString = json_vec.dump();
//  write(GetServ2CliSocket(),
//        jsonString.data(),
//        sizeof(char) * jsonString.size());
//}
//
//std::vector<cv::Point2i> Snake::Receive()
//{
//  char buffer[10000];
//  read(GetCliSocket(), buffer, sizeof(buffer));
//  std::string jsonString(buffer);
//  nlohmann::json jsonPoints = nlohmann::json::parse(jsonString);
//  std::vector<cv::Point2i> snake_body;
//  for (const auto &point : jsonPoints) {
//    snake_body.emplace_back(point["x"], point["y"]);
//  }
//  return snake_body;
//}
