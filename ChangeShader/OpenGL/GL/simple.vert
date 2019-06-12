#version 400

in vec4 coord3d;
in vec3 v_color;

out vec3 f_color;

void main(void)
{  
   gl_Position =  coord3d;  
   f_color = v_color;  
}
