#include "Team.h"
void Team::save_to_file() const {
	for (auto& character : team_full) {
		character.second->save_to_file();
	}
}
void Team::load_from_file(){
	for (auto& character : team_full) {
		character.second->load_from_file();
	}
}

