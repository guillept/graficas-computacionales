#include <iostream>
#include <vector>
#include "image_writer.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#define MAXFLOAT    3.37E+38

// #include "vec3.h"
// #include "ray.h"

/* float hit_sphere(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0* dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;
	if (discriminant < 0) {
		return -1.0;
	} else {
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
	// return (discriminant > 0);
} */

vec3 color(const ray& r, hitable *world) {
	/* float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
	if (t > 0.0) {
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}*/
	/* if (hit_sphere(vec3(0, 0, -1), 0.5, r))
		return vec3(1, 0, 0); */
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec)) {
		return 0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main(){

	int nx = 200;
	int ny = 100;
	int ns = 100;
	// std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	std::vector <unsigned char> pixels; //0 - 255 

	/* vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0); */

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	camera cam;
	for (int j=ny-1; j>=0; j--){
		for (int i=0; i<nx; i++){
			vec3 col(0, 0, 0);
			for(int s=0; s < ns; s++) {
				float u = float(i + float(rand())/RAND_MAX) / float(nx);
				float v = float(j + float(rand())/RAND_MAX) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}

			col /= float(ns);
			/* float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);*/

			// vec3 col = color(r, world);
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


			// std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}

	image_writer::save_png("out.png", nx, ny, 3, pixels.data());
}
