#include <iostream>
#include <vector>
#include "cpputils/graphics/image.h"
#include "game.h"

int main() {
  std::string Player_Image_Filename, Opponent_Image_Filename,
      Player_Projectile_Image_Filename, Opponent_Projectile_Image_Filename;

  const int sizeImage = 50;
  graphics::Image player_image(sizeImage, sizeImage);
  std::cout << "Please provide player image filename: ";
  std::cin >> Player_Image_Filename;
  player_image.DrawCircle(25, 25, 15, graphics::Color(173, 216, 230));
  player_image.SaveImageBmp(Player_Image_Filename);

  const int sizeImage2 = 50;
  graphics::Image opponent_image(sizeImage2, sizeImage2);
  std::cout << "Please provide opponent image filename: ";
  std::cin >> Opponent_Image_Filename;
  opponent_image.DrawCircle(25, 25, 15, graphics::Color(255, 182, 193));
  opponent_image.SaveImageBmp(Opponent_Image_Filename);

  const int sizeImage3 = 5;
  graphics::Image projectile_image1(sizeImage3, sizeImage3);
  std::cout << "Please provide player projectile image filename: ";
  std::cin >> Player_Projectile_Image_Filename;
  projectile_image1.DrawRectangle(0, 0, 5, 5, graphics::Color(255, 0, 0));
  projectile_image1.SaveImageBmp(Player_Projectile_Image_Filename);

  const int sizeImage4 = 5;
  graphics::Image projectile_image2(sizeImage4, sizeImage4);
  std::cout << "Please provide opponent projectile image filename: ";
  std::cin >> Opponent_Projectile_Image_Filename;
  projectile_image2.DrawRectangle(0, 0, 5, 5, graphics::Color(0, 0, 255));
  projectile_image2.SaveImageBmp(Opponent_Projectile_Image_Filename);
  Game my_game;
  my_game.Init();
  my_game.UpdateScreen();
  my_game.Start();
  return 0; 
}
