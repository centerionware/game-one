#ifndef ITEMS_H
#define ITEMS_H

#include <string>
enum wear_locations { NotWearable, LeftArm, RightArm, Head, Chest, Legs, Feet, LeftFinger, RightFinger, Waist };
enum wield_locations { NotWieldable, LeftHand, RightHand, RoboticCompanion };
struct Item {
      std::string Name;
      unsigned int id; // unique id per instance of item?
      wear_locations wear; // 0 = not wearable.
      wield_locations wield; 
      std::string Description;
      unsigned int model_number; // 0 = no model
      unsigned int texture_number; // if model_number is 0, use a flat 2d texture to texture a quad for this item.
      Item(std::string& _name, unsigned int _id, wear_locations _wearable, wield_locations _weildable, 
	   std::string& _Desc, unsigned int _model_number, unsigned int _texture_number);
      Item(){};
      Item(const Item &o);
};

extern std::vector<Item> all_items;
struct item_on_floor {
	unsigned int all_items_index;
	vec3 position;
	item_on_floor() : all_items_index(-1), position() {}
	item_on_floor(unsigned int _all_items_index, vec3 &_pos): all_items_index(_all_items_index), position(_pos) {}
	item_on_floor(const item_on_floor &o) : all_items_index(o.all_items_index), position(o.position) {}
};
extern std::vector<item_on_floor> all_items_on_floor;

extern void item_pickup_test(inet_player *p, vec3 &pos);
#endif