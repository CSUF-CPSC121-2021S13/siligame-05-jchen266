#include "opponent.h"

void Opponent::Draw(graphics::Image &back) {
  std::string variable = "opponent.bmp";
  Helper(back, variable, x_, y_);
}

void Opponent::Move(const graphics::Image &back) {
  if (!IsOutOfBounds(back)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    is_active = false;
  }
}

void OpponentProjectile::Draw(graphics::Image &back) {
  std::string variable = "opponentp.bmp";
  Helper(back, variable, x_, y_);
}

void OpponentProjectile::Move(const graphics::Image &back) {
  if (!IsOutOfBounds(back)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    is_active = false;
  }
}
