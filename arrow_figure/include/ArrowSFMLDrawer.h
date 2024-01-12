#pragma once

#include "SFMLDrawer.h"

class tArrowFigure;
class ArrowSFMLDrawer : public SFMLDrawer
{
public:
    ArrowSFMLDrawer(sf::RenderWindow &window, my_graph_lib::RGBColor background_color);

    
    
private:
    my_graph_lib::RGBColor background_color_;
};