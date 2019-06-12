#version 400

in vec3 f_color;
in vec2 TexCoord;

out vec4 FragColors;
uniform sampler2D chessBoardSampler;

void main()
{
   FragColors = 0.5 * texture( chessBoardSampler, TexCoord ) + 0.5 * vec4(f_color, 1.0);
}
