#include <iostream>
#include <vector>
#include "image_writer.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"
#define MAXFLOAT    3.37E+38
#define drand48 float(rand()) / RAND_MAX

// #include "vec3.h"
// #include "ray.h"

hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = drand48;
			vec3 center(a + 0.9*drand48, 0.2, b + 0.9*drand48);
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) { //diffuse
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(drand48*drand48, drand48*drand48, drand48*drand48)));
				}
				else if (choose_mat < 0.95) { //metal
					list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1 + drand48), 0.5*(1 + drand48), 0.5*(1 + drand48)), 0.5*drand48));
				}
				else { //glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));
	return new hitable_list(list, i);
}
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

vec3 color(const ray& r, hitable *world, int depth) {
	/* float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
	if (t > 0.0) {
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}*/
	/* if (hit_sphere(vec3(0, 0, -1), 0.5, r))
		return vec3(1, 0, 0); */
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
		/* vec3 target = rec.p + rec.normal + random_in_unit_shpere();
		return 0.5*color(ray(rec.p, target - rec.p), world); */
		//return 0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main(){

	int nx = 300;
	int ny = 200;
	int ns = 200;
	// std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	std::vector <unsigned char> pixels; //0 - 255 

	/* vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0); */

	/* 
	hitable *list[4];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3 (0.8, 0.3, 0.3)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8)));
	*/

	hitable *list[5];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	hitable *world = new hitable_list(list, 5);
	world = random_scene();

	// camera cam(90, float(nx)/float(ny));
	/*vec3 lookfrom(3, 3, 2);
	vec3 lookat(0, 0, -1);
	float dist_to_focus = (lookfrom - lookat).length();
	float apertur = 2.0;
	*/

	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	float dist_to_focus = 10.0;
	float apertur = 0.1;
	camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), apertur, dist_to_focus);

	/* 
	float R = cos(3.1416 / 4);
	hitable *list[2];
	list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
	list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)));
	hitable *world = new hitable_list(list, 2); */

	for (int j=ny-1; j>=0; j--){
		for (int i=0; i<nx; i++){
			vec3 col(0, 0, 0);
			for(int s=0; s < ns; s++) {
				float u = float(i + float(rand())/RAND_MAX) / float(nx);
				float v = float(j + float(rand())/RAND_MAX) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}

			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
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
