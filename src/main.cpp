#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "player.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  Player player;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame, kGridWidth, kGridHeight);
  std::cout << "Game has terminated successfully!\n";

  int player_score = game.GetScore();
  int high_score = player.getHighScore();

  if (player_score <= high_score)
  {
    std::cout << "current high score: " << high_score << "\n";
  }
  else
  {
    std::cout << "New High Score!! Congratulations!!" << "\n";
    player.setHighScore(player_score);
  }

  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}