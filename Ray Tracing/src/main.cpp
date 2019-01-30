#include <iostream>
#include <vector>
#include "image_writer.h"
// #include "vec3.h"
#include "ray.h"

bool hit_sphere(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0* dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;
	return (discriminant > 0);
}

vec3 color(const ray& r) {
	if (hit_sphere(vec3(0, 0, -1), 0.5, r))
		return vec3(1, 0, 0);
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main(){

	int nx = 200;
	int ny = 100;

	std::vector <unsigned char> pixels; //0 - 255 

	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	for (int j=ny-1; j>=0; j--){
		for (int i=0; i<nx; i++){

			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			/* vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]); */

			pixels.push_back(ir);
			pixels.push_back(ig);
			pixels.push_back(ib);

			/* float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2f;
			pixels.push_back(int(255.99 * r));
			pixels.push_back(int(255.99 * g));
			pixels.push_back(int(255.99 * b)); */
		}
	}

	image_writer::save_png("out.png", nx, ny, 3, pixels.data());
}
