#include "Text.h"
using namespace ECS;

Utilities::Text::Text(ECS::EntityManager* eman)
{
    em = eman;

    color = {1.0f, 1.0f, 1.0f, 1.0f};
    position = {0.0f, 0.0f};
    scale = {13.0f, 13.0f};

    x_coord['a'] = 6.0f;
    y_coord['a'] = 4.0f;

    x_coord['b'] = 22.0f;
    y_coord['b'] = 4.0f;

    x_coord['c'] = 37.0f;
    y_coord['c'] = 4.0f;

    x_coord['d'] = 52.0f;
    y_coord['d'] = 4.0f;

    x_coord['e'] = 67.0f;
    y_coord['e'] = 4.0f;

    x_coord['f'] = 82.0f;
    y_coord['f'] = 4.0f;

    x_coord['g'] = 97.0f;
    y_coord['g'] = 4.0f;

    x_coord['h'] = 112.0f;
    y_coord['h'] = 4.0f;

    x_coord['i'] = 127.0f;
    y_coord['i'] = 4.0f;

    x_coord['j'] = 143.0f;
    y_coord['j'] = 4.0f;

    x_coord['k'] = 158.0f;
    y_coord['k'] = 4.0f;

    x_coord['l'] = 173.0f;
    y_coord['l'] = 4.0f;

    x_coord['m'] = 188.0f;
    y_coord['m'] = 4.0f;

    x_coord['n'] = 203.0f;
    y_coord['n'] = 4.0f;

    x_coord['o'] = 218.0f;
    y_coord['o'] = 4.0f;

    x_coord['p'] = 234.0f;
    y_coord['p'] = 4.0f;

    x_coord['q'] = 249.0f;
    y_coord['q'] = 4.0f;

    x_coord['r'] = 264.0f;
    y_coord['r'] = 4.0f;

    x_coord['s'] = 279.0f;
    y_coord['s'] = 4.0f;

    x_coord['t'] = 294.0f;
    y_coord['t'] = 4.0f;

    x_coord['u'] = 309.0f;
    y_coord['u'] = 4.0f;

    x_coord['v'] = 324.0f;
    y_coord['v'] = 4.0f;

    x_coord['w'] = 339.0f;
    y_coord['w'] = 4.0f;

    x_coord['x'] = 355.0f;
    y_coord['x'] = 4.0f;

    x_coord['y'] = 370.0f;
    y_coord['y'] = 4.0f;

    x_coord['z'] = 385.0f;
    y_coord['z'] = 4.0f;
}

void Utilities::Text::print(std::string message)
{
    int x_offset = 0;
    int y_offset = 0;

    for (int i = 0; i < message.length(); i++)
    {
        if (!std::isspace(message[i]))
        {
            if (message[i] == '/')
            {
               x_offset = -1;
               y_offset++;
            }
            else
            {
                int ID = em->create();
                em->add<Transform>(ID);
                em->add<ColorRotationPos>(ID);
                auto* tr_data = em->get<Transform>(ID);

                tr_data->scale = scale;
                tr_data->colors = color; 
                tr_data->tex_coords = {x_coord.at(message[i]), y_coord.at(message[i]), 12.0f, 13.0f};
                tr_data->position = {position.x + (x_offset*scale.x), position.y + (y_offset*scale.y), 0.0f};
            }
        }
        x_offset++;
    }
}
