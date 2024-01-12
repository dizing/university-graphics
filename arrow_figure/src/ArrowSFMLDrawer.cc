#include "ArrowSFMLDrawer.h"


ArrowSFMLDrawer::ArrowSFMLDrawer(sf::RenderWindow &window, my_graph_lib::RGBColor background_color) : background_color_(background_color),  SFMLDrawer(window) {}