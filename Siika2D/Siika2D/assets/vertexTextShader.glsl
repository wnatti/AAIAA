attribute vec4 coord;
varying vec2 texcoord;
 uniform mat4 window;
void main(void) 
{
  gl_Position = window * vec4(coord.xy, 0, 1);
  texcoord = coord.zw;
}