#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  // PlaceFood();
  food_future = std::async(std::launch::async, &Game::PlaceFood, this);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration,
               const std::size_t grid_width, const std::size_t grid_height) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, pausedGame);
    if(!pausedGame){
      Update();
    }
    if(snake.alive == false){
      running = false;
    }
    aStar.reset(new AStar(grid_width, grid_height));
    SDL_Point start, end;
    start.x = snake.head_x;
    start.y = snake.head_y;
    // const std::vector<SDL_Point> path = aStar->Search(start, end);
    renderer.Render(snake, food, food_red, f_red_active, food_green, f_green_active);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }

    if(running == false){
      ShowScoreBox();
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      break;
    }
  }
  if(f_red_active){
    while (true) {
      x = random_w(engine);
      y = random_h(engine);
      // Check that the location is not occupied by a snake item before placing
      // food.
      if (!snake.SnakeCell(x, y) && !(x == food.x && y == food.y)) {
        food_red.x = x;
        food_red.y = y;
        break;
      }
    }
  }
  if(f_green_active){
    while (true) {
      x = random_w(engine);
      y = random_h(engine);
      // Check that the location is not occupied by a snake item before placing
      // food.
      if (!snake.SnakeCell(x, y) && !(x == food.x && y == food.y) && !(x == food_red.x && y == food_red.y)) {
        food_green.x = x;
        food_green.y = y;
        break;
      }
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  static int normal_food_count = 0;
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    normal_food_count++;

    if(normal_food_count % 5 == 0){
      // normal_food_count = 0;
      f_green_active = true;
      f_red_active = true;
    } else {
      f_green_active = false;
      f_red_active = false;
    }

    PlaceFood();
    
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  if(f_red_active == true && food_red.x == new_x && food_red.y == new_y){
      snake.alive = false;
  }
  if(f_green_active == true && food_green.x == new_x && food_green.y == new_y){
    score += 5;
    f_green_active = false;
    f_red_active = false;
  }
}

void Game::ShowScoreBox() const {
  std::string message = "Your Score: " + std::to_string(score);
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                           "Game Over",
                           message.c_str(),
                           nullptr);
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }