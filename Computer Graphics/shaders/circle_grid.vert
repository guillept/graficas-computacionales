#version 330

float TOTAL_TRIANGULOS = 30.0;

uniform float time; //atributos a todos los shaders que existen
out vec4 InterpolatedColor; //informacion a la siguiente etapa
uniform float vertexCount; //atributos a todos los shaders que existen

vec2 createCircle() {
  
  //gl_VertexID = 0, 1, 2, 3, 4, 5
  float x = floor(gl_VertexID / 2.0); //0, 0, 1, 1, 2, 2
  float y = mod(gl_VertexID + 1.0, 2.0); //1, 0, 1, 0
 
  float angle = x / TOTAL_TRIANGULOS * radians(360.0);
  float r = 2.0 - y;
  
  float u = r * cos(angle);
  float v = r * sin(angle);
  
  return vec2(u, v) * 0.1; //se puede crear vec4 con vectores 2 -> vec4(xy, 0.0, 1.0);
}

void main() 
{
  //fuente inspiracion = https://www.vertexshaderart.com/art/yX9SGHv6RPPqcsXvh
  float circleId = floor(gl_VertexID / (TOTAL_TRIANGULOS * 2.0 + 2.0)); //62 vueltas que es el circulo
  float numCircles = floor(vertexCount / (TOTAL_TRIANGULOS * 3.0)); // 30 * 3 = Total de vertices por triangulo
  
  float gDown = floor(sqrt(numCircles)); //7
  float gAcross = floor(numCircles / gDown); //8
  
  float x = floor(circleId / gAcross); //float y = floor(gl_VertexID / width);
  float y = mod(circleId, gAcross); //float x = mod(gl_VertexID, width); gl_VertexID = #vertex

  float u = x / (gAcross - 3.0); //espacio entre virulos
  float v = y / (gAcross - 3.0);
    
  //Desfamiento - desfazamiento + [x = diferente] * r
  float xOffset = cos(time + y * 0.2) * 0.1;
  float yOffset = cos(time + x * 0.3) * 0.2;
  
   //Acomodar en los cuadrantes
  float ux = u * 2.0 - 1.5 + xOffset;
  float uy = v * 2.0 - 1.3 + yOffset;
 
  vec2 cricle = createCircle() * 0.5 + vec2(ux,uy)*0.7;
  
  gl_Position = vec4(cricle, 0.0, 1.0); //position del vec4
  gl_PointSize = 20.0;
  
  InterpolatedColor = vec4(1.0, 0.0, 0.0, 1.0);

}
