#version 330 core

out vec4 FragColor;
in vec4 out_color;
in vec2 out_tex;
in vec4 world_position;

uniform sampler2D tex;
uniform int number_of_lights;
uniform int timer;

struct Lights
{
   vec2 position;
   vec4 color;
   float timer;
   float intensity;
   float radius;
};

uniform Lights LightArray[500];

void main()
{
   vec4 c = vec4(0.05, 0.05, 0.05, 1);

   for(int i = 0; i < number_of_lights; i++)
   {
      float dist = pow(world_position.x - LightArray[i].position.x, 2) + pow(world_position.y - LightArray[i].position.y, 2);
      c += LightArray[i].color * LightArray[i].intensity*exp(LightArray[i].radius*-sqrt(dist));
   }
   
   FragColor = texture(tex, out_tex)*vec4(c.xyz, 1)*out_color;

   if (FragColor.w == 0.0)
       discard;
}
