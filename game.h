#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(const int &width, const int &height) {
    game_screen.Initialize(width, height);
  }

  void CreateOpponents() {
    Opponent panda;
    opponent_obj.push_back(panda);
  }

  void CreateOpponentProjectiles() {
    OpponentProjectile opponent_proj;
    opponent_proj_.push_back(opponent_proj);
  }

  void CreatePlayerProjectiles() {
    PlayerProjectile player_proj;
    player_proj_.push_back(player_proj);
  }

  void Init() {
    game_screen.AddMouseEventListener(*this);
    game_screen.AddAnimationEventListener(*this);

    CreateOpponents();
    CreateOpponentProjectiles();
    CreatePlayerProjectiles();
    player_.SetX(300);
    player_.SetY(400);
  }

  void Start();

  Player &GetPlayer() { return player_; }
  graphics::Image &GetGameScreen() { return game_screen; }
  std::vector<Opponent> &GetOpponents() { return opponent_obj; }
  std::vector<OpponentProjectile> &GetOpponentProjectiles() {
    return opponent_proj_;
  }
  std::vector<PlayerProjectile> &GetPlayerProjectiles() { return player_proj_; }

  void MoveGameElements() {
    for (int k = 0; k < opponent_obj.size(); k++) {
      if (opponent_obj[k].GetIsActive()) {
        opponent_obj[k].Move(game_screen);
      }
    }
    for (int k = 0; k < opponent_proj_.size(); k++) {
      if (opponent_proj_[k].GetIsActive()) {
        opponent_proj_[k].Move(game_screen);
      }
    }
    for (int k = 0; k < player_proj_.size(); k++) {
      if (player_proj_[k].GetIsActive()) {
        player_proj_[k].Move(game_screen);
      }
    }
  }

  void FilterIntersections() {
    for (int k = 0; k < opponent_obj.size(); k++) {
      if (opponent_obj[k].IntersectsWith(player_)) {
        opponent_obj[k].SetIsActive(false);
        player_.SetIsActive(false);
      }
    }
    for (int k = 0; k < opponent_proj_.size(); k++) {
      if (opponent_proj_[k].IntersectsWith(player_)) {
        opponent_proj_[k].SetIsActive(false);
        player_.SetIsActive(false);
      }
    }
    for (int k = 0; k < player_proj_.size(); k++) {
      for (int n = 0; n < opponent_obj.size(); n++) {
        if (player_proj_[k].IntersectsWith(opponent_obj[n])) {
          player_proj_[k].SetIsActive(false);
          opponent_obj[n].SetIsActive(false);
        }
      }
    }
  }

  void UpdateScreen() {
    game_screen.DrawRectangle(0, 0, game_screen.GetWidth(),
                              game_screen.GetHeight(), 255, 255, 255);

    for (int k = 0; k < opponent_obj.size(); k++) {
      if (opponent_obj[k].GetIsActive()) {
        opponent_obj[k].Draw(game_screen);
      }
    }
    for (int k = 0; k < opponent_proj_.size(); k++) {
      if (opponent_proj_[k].GetIsActive()) {
        opponent_proj_[k].Draw(game_screen);
      }
    }
    for (int k = 0; k < player_proj_.size(); k++) {
      if (player_proj_[k].GetIsActive()) {
        player_proj_[k].Draw(game_screen);
      }
    }
    if (player_.GetIsActive()) {
      player_.Draw(game_screen);
    }
  }
  void OnAnimationStep() override {
    MoveGameElements();
    FilterIntersections();
    UpdateScreen();
    game_screen.Flush();
  }

  void OnMouseEvent(const graphics::MouseEvent &event) override {
    if (event.GetX() > 0 && event.GetX() < game_screen.GetWidth() &&
        event.GetY() > 0 && event.GetY() < game_screen.GetHeight()) {
      player_.SetX(event.GetX() - (player_.GetWidth() * 0.5));
      player_.SetY(event.GetY() - (player_.GetHeight() * 0.5));
    }
  }

 private:
  Player player_;
  graphics::Image game_screen;
  std::vector<Opponent> opponent_obj;
  std::vector<OpponentProjectile> opponent_proj_;
  std::vector<PlayerProjectile> player_proj_;
};

#endif
