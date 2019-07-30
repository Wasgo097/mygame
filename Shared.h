#pragma once
//#include <stdint.h>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <queue>
#include <vector>
#include <list>
#include <memory>
#include <utility> 
#include "Additional Library/bitmap_image.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
enum class Weight{light,medium,heavy};
enum class Effect{bleeding,toxic,stunning,none,buff_str,buff_dex,buff_dur,buff_int};
enum class AttackType{physics,magic};
enum class DefendType { physics, magic };
enum class Quality{weak,medium,strong,rare,legendary};
enum class WeaponType{sword,bow,staff,fangs,null};
using Price = uint16_t;
using Damage = uint16_t;
using Defence = uint16_t;
using Health = int16_t;
using Stamina = int16_t;
using Feature = int16_t;
using Level = uint16_t;
using Experience = uint16_t;
using Name = std::string;
typedef std::string string;

bool ** access_load_from_file(sf::Vector2f ratio,std::string txt_map_path, const size_t & height, const size_t & width);
bool ** access_save_to_file(sf::Vector2f ratio,bitmap_image & image, const size_t & height, const size_t & width, const std::string txt_map_path);
char ** boss_load_from_file(sf::Vector2f ratio,std::string txt_map_path, const size_t & height, const size_t & width);
char ** boss_save_to_file(sf::Vector2f ratio,bitmap_image & image, const size_t & height, const size_t & width, const std::string txt_map_path);
char ** terrain_load_from_file(sf::Vector2f ratio,std::string txt_map_path, const size_t & height, const size_t & width);
char ** terrain_save_to_file(sf::Vector2f ratio,bitmap_image & image, const size_t & height, const size_t & width, const std::string txt_map_path);
void clear_map(bool ** map, const size_t & height);
void clear_map(char ** map, const size_t & height);
bool control(bool ** map_x, bool ** map_y, const size_t width, const size_t height);
bool control(char ** map_x, char ** map_y, const size_t width, const size_t height);
void wait(unsigned int x);
Quality get_rand_quality();
template<typename T2, typename T1>
bool is_type(T1 * type) {
	if (T2 * ptr = dynamic_cast<T2*>(type)) return true;
	else return false;
}
template<typename T2, typename T1>
bool is_type_id(T1 * type) {
	if (typeid(T2) == typeid(*type)) return true;
	else return false;
}
