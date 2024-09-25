#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "AStar.h"
#include <memory>
#include <future>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration,
           const std::size_t grid_width, const std::size_t grid_height);
  int GetScore() const;
  int GetSize() const;
  void ShowScoreBox() const;
  bool pausedGame{false};
  bool f_red_active{false};
  bool f_green_active{false}; 


 private:
  Snake snake;
  SDL_Point food;
  SDL_Point food_red;
  SDL_Point food_green;
  std::unique_ptr<AStar> aStar;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  std::future<void> food_future;

  void PlaceFood();
  void Update();
};

#endif