void main()
{
  float x = floor(vertexId / 2.0);
  float y = mod(vertexId + 1.0, 2.0);
  
  float angle = x / 20.0 * radians(360.0);
  float radius = 2.0 - y;
  
  float u = radius * cos(angle);
  float v = radius * sin(angle);
  
  vec2 xy = vec2(u, v) * 0.1;
  

  gl_Position = vec4(xy, 0.0, 1.0);
  gl_PointSize = 20.0;
  v_color = vec4(0.0, 0.0, 0.0, 1.0);
}

/*
vertexId    : float     : number of the vertex 0, 1, 2
vertexCount : float     : total number of vertices
*/

float TOTAL_TRIANGULOS = 30.0;


vec2 createCircle() {
  
  //vertexId = 0, 1, 2, 3, 4, 5
  float x = floor(vertexId / 2.0); //0, 0, 1, 1, 2, 2
  float y = mod(vertexId + 1.0, 2.0); //1, 0, 1, 0
  
 
  float angle = x / TOTAL_TRIANGULOS * radians(360.0);
  float r = 2.0 - y;
  
  float u = r * cos(angle);
  float v = r * sin(angle);
  
  return vec2(u, v) * 0.1; //se puede crear vec4 con vectores 2 -> vec4(xy, 0.0, 1.0);
}


void main() 
{
  
  //fuente inspiracion = https://www.vertexshaderart.com/art/yX9SGHv6RPPqcsXvh
  float circleId = floor(vertexId / (TOTAL_TRIANGULOS * 2.0));
  float numCircles = floor(vertexCount / (TOTAL_TRIANGULOS * 2.0));
  //float numGroups = floor(numCircles / NUM_CIRCLES_PER_GROUP); 
  
  float gDown = floor(sqrt(numCircles));
  float gAcross = floor(numCircles / gDown);
  
  
  float x = mod(circleId, gAcross); //float x = mod(vertexId, width); vertexId = #vertex
  float y = floor(circleId / gAcross); //float y = floor(vertexId / width);
  
  float u = x / (gAcross - 1.0);
  float v = y / (gAcross - 1.0);
  
  
  float ux = u * 2.0 - 1.0;
  float uy = v * 2.0 - 1.0;
  
  
  /*float width = 10.0;
  float x = mod(vertexId, width); 
  float y = floor(vertexId / width);
  
  float u = x /(width - 1.0);
  float v  = y / (width - 1.0);*/
  
  vec2 circulo = createCircle();
  
 
  gl_Position = vec4(circulo, 0.0, 1.0); //position del vec4
  v_color = vec4(1.0, 0.0, 0.0, 1.0); //color
  gl_PointSize = 20.0;
  
   
 vec2 cricle = createCircle() * 0.5 + vec2(ux,uy)*0.7;
 
  gl_Position = vec4(cricle, 0.0, 1.0); //position del vec4
  v_color = vec4(1.0, 0.0, 0.0, 1.0); //color
  gl_PointSize = 20.0;
}