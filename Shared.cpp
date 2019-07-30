#include "Shared.h"
bool ** access_load_from_file(sf::Vector2f ratio,std::string txt_map_path,const size_t & height, const size_t & width)
{
	bool ** map = new bool*[height];
	for (int i = 0; i < height; ++i)
		map[i] = new bool[width];
	std::fstream file;
	file.open(txt_map_path, std::ios::in);
	char character;
	for (std::size_t y = 0; y < height; ++y){
		for (std::size_t x = 0; x < width; ++x){
			file >> character;
			if (character == '1') map[y][x] = true;
			else map[y][x] = false;
		}
	}
	file.close();
	printf("Loaded\n");
	return map;
}
bool ** access_save_to_file(sf::Vector2f ratio,bitmap_image & image, const size_t & height, const size_t & width, const std::string txt_map_path){
	bitmap_image pic(width, height);
	/*float ratio_x =(float) width / (float)image.width();
	float ratio_y= (float)height / (float)image.height();*/
	bool ** map = new bool*[height];
	for (int i = 0; i < height; ++i)
		map[i] = new bool[width];
	std::fstream file;
	file.open(txt_map_path, std::ios::out);
	for (std::size_t y = 0; y < height; ++y){
		for (std::size_t x = 0; x < width; ++x){
			rgb_t colour;
			image.get_pixel(x/ratio.x, y/ratio.y, colour);
			if (colour.blue > colour.green && colour.blue > colour.red && colour.green <150 && colour.red <150){
				map[y][x] = false;
				file << 0;
				pic.set_pixel(x, y, 255, 0, 0);
			}
			else if (x/ratio.x<=53||x/ratio.x>=1865 || y/ratio.y>=1035||y/ratio.y<= 44){
				map[y][x] = false;
				file << 0;
				pic.set_pixel(x, y, 255,0,0);
			}
			else{
				map[y][x] = true;
				file << 1;
				pic.set_pixel(x, y, 0, 255,0);
			}
		}
		file << std::endl;
	}
	file.close();
	printf("Saved\n");
	pic.save_image("Map/access.bmp");
	return map;
}
char ** boss_load_from_file(sf::Vector2f ratio,std::string txt_map_path, const size_t & height, const size_t & width){
	char ** map = new char*[height];
	for (int i = 0; i < height; ++i)
		map[i] = new char[width];
	std::fstream file;
	file.open(txt_map_path, std::ios::in);
	char character;
	for (std::size_t y = 0; y < height; ++y)
	{
		for (std::size_t x = 0; x < width; ++x)
		{
			file >> map[y][x];
		}
	}
	file.close();
	printf("Loaded\n");
	return map;
}
char ** boss_save_to_file(sf::Vector2f ratio,bitmap_image & image, const size_t & height, const size_t & width, const std::string txt_map_path){
	char ** map = new char*[height];
	bitmap_image pic(width, height);
	for (int i = 0; i < height; ++i)
		map[i] = new char[width];/*
	float ratio_x = (float)width / (float)image.width();
	float ratio_y = (float)height / (float)image.height();*/
	std::fstream file;
	file.open(txt_map_path, std::ios::out);
	for (std::size_t y = 0; y < height; ++y) {
		for (std::size_t x = 0; x < width; ++x) {
			rgb_t colour;
			image.get_pixel(x/ratio.x, y/ratio.y, colour);
			if (colour.red==255&&colour.green==0&&colour.blue==0) {
				//orc
				map[y][x] = 'o';
				file << map[y][x];
				pic.set_pixel(x, y, 255,0,0);
			}
			else if (colour.red == 255 && colour.green == 255 && colour.blue == 0) {
				//spider
				map[y][x] = 's';
				file << map[y][x];
				pic.set_pixel(x, y, 255,255,0);
			}
			else if (colour.red == 255 && colour.green == 255 && colour.blue == 255) {
				//ghost
				map[y][x] = 'g';
				file << map[y][x];
				pic.set_pixel(x, y,255,255,255);
			}
			else if(colour.red == 0 && colour.green == 255 && colour.blue == 255){
				//werefolf
				map[y][x] = 'w';
				file << map[y][x];
				pic.set_pixel(x, y,0,255,255);
			}
			else {
				//nothing
				map[y][x] = 'n';
				file << map[y][x];
				pic.set_pixel(x, y, 100,100,100);
			}
		}
		file << std::endl;
	}
	file.close();
	pic.save_image("Map/boss.bmp");
	printf("Saved\n");
	return map;
}
char ** terrain_load_from_file(sf::Vector2f ratio,std::string txt_map_path, const size_t & height, const size_t & width){
	char ** map = new char*[height];
	for (int i = 0; i < height; ++i)
		map[i] = new char[width];
	std::fstream file;
	file.open(txt_map_path, std::ios::in);
	char character;
	for (std::size_t y = 0; y < height; ++y){
		for (std::size_t x = 0; x < width; ++x){
			file >> map[y][x];
		}
	}
	file.close();
	printf("Loaded\n");
	return map;
}
char ** terrain_save_to_file(sf::Vector2f ratio,bitmap_image & image, const size_t & height, const size_t & width, const std::string txt_map_path){
	char ** map = new char*[height];
	bitmap_image pic(width,height);
	for (int i = 0; i < height; ++i)
		map[i] = new char[width];
	/*float ratio_x = (float)width / (float)image.width();
	float ratio_y = (float)height / (float)image.height();*/ 
	std::fstream file;
	file.open(txt_map_path, std::ios::out);
	for (std::size_t y = 0; y < height; ++y) {
		for (std::size_t x = 0; x < width; ++x) {
			rgb_t colour;
			image.get_pixel(x/ratio.x, y/ratio.y, colour);
			if (colour.green-40>colour.red&&colour.green-40>colour.blue) {
				//forest
				map[y][x] = 'f';
				file << map[y][x];
				pic.set_pixel(x, y, 0, 255, 0);
			}
			else if (colour.red>colour.green&&colour.red>colour.blue + 50) {
				//desert
				map[y][x] = 'd';
				file << map[y][x];
				pic.set_pixel(x, y, 255, 255, 0);
			}
			else {
				//mountain
				map[y][x] = 'm';
				file << map[y][x];
				pic.set_pixel(x, y, 255, 255, 255);
			}
		}
		file << std::endl;
	}
	file.close();
	pic.save_image("Map/terrain.bmp");
	printf("Saved\n");
	return map;
}
void clear_map(bool ** map, const size_t & height)
{
	if (map != nullptr)
	{
		for (int i = 0; i < height; ++i)
			delete[] map[i];
		delete[] map;
	}
}
void clear_map(char ** map, const size_t & height)
{
	if (map != nullptr)
	{
		for (int i = 0; i < height; ++i)
			delete[] map[i];
		delete[] map;
	}
}
bool control(bool ** map_x, bool ** map_y, const size_t width, const size_t height){
	for (std::size_t y = 0; y < height; ++y)
	{
		for (std::size_t x = 0; x < width; ++x)
		{
			if (map_x[y][x] != map_y[y][x])
			{
				return false;
			}
		}
	}
	return true;
}
bool control(char ** map_x, char ** map_y, const size_t width, const size_t height) {
	for (std::size_t y = 0; y < height; ++y)
	{
		for (std::size_t x = 0; x < width; ++x)
		{
			if (map_x[y][x] != map_y[y][x])
			{
				return false;
			}
		}
	}
	return true;
}
void wait(unsigned int x) {
	sf::Clock c1;
	sf::Time t2 = sf::milliseconds(x);
	while (c1.getElapsedTime() < t2) {}
	c1.restart();
}
Quality get_rand_quality(){
	int rand = std::rand() % 1000;
	if (rand >= 0 && rand <= 470)return Quality::weak;
	else if (rand > 470 && rand <= 900)return Quality::medium;
	else if (rand > 900 && rand <= 960)return Quality::strong;
	else if (rand > 960 && rand <= 990)return Quality::rare;
	else return Quality::legendary;
}

