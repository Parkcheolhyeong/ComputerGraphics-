#version 400

in vec4 coord3d;
in vec3 v_color;
in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 f_color;

void main(void)
{  
   gl_Position = coord3d;  
   f_color = v_color;  
   TexCoord = aTexCoord;
}
