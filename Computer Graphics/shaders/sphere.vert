#version 330

uniform float time; //atributos a todos los shaders que existen
out vec4 InterpolatedColor; //informacion a la siguiente etapa
uniform float vertexCount; //atributos a todos los shaders que existen

const float TOTAL_PUNTOS = 256.;
const float PI = radians(180.);
float s = sin(time);
float c = cos(time);

mat4 rotZ() {   
    return mat4( 
      c,-s, 0, 0, 
      s, c, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1); 
}

mat4 rotY() {
  return mat4(
    c, 0, -s, 0,
    0, 1, 0, 0,
    s, 0, c, 0,
    0, 0, 0, 1);
}

mat4 rotX() {
  return mat4(
    1, 0, 0, 0,
    0, c, -s, 0,
    0, s, c, 0,
    0, 0, 0, 1);
}


mat4 trans(vec3 trans) {
  return mat4(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    trans, 1);
}

mat4 scale(float s) {
  return mat4(
    s, 0, 0, 0,
    0, s, 0, 0,
    0, 0, s, 0,
    0, 0, 0, 1);
}

void main() {
  
  float pointId = mod(gl_VertexID, TOTAL_PUNTOS);
  float numCircles = floor(vertexCount / TOTAL_PUNTOS);
  float circleId = floor(gl_VertexID / TOTAL_PUNTOS);
  float totalInnerCircles = floor(numCircles / 2.);
  float innerCicrcles = floor(circleId / 2.) / totalInnerCircles;
  float point = pointId / TOTAL_PUNTOS * 2.;

  float alpha = point * PI * 2.;
  float x = cos(alpha);
  float z = sin(alpha);
  
  //trasladar, aspcet
  //trans = 0, cos(beta), 0 -> aspect = sin (beta)
  float beta = innerCicrcles * PI;
  mat4 transform = trans(vec3(0, cos(beta), 0)) * scale(sin(beta));
  gl_Position =  transform * vec4(x, 0, z, 1.) * rotX()* rotZ() ;
  gl_PointSize = 2.5;
  
  InterpolatedColor = vec4(1.0, 0.0, 0.0, 1.0);
}
