#ifndef S_PERLIN_SPHERES_H
#define S_PERLIN_SPHERES_H

void s_perlin_spheres() {
  hittable_list world;

  auto marble_tex = make_shared<marble_texture>(2, 15);
  auto perlin_tex = make_shared<noise_texture>(4, 4);
  world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(marble_tex)));
  world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(perlin_tex)));

  world = hittable_list(make_shared<bvh_node>(world));

  camera cam;

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth         = 50;

  cam.vfov     = 20;
  cam.lookfrom = point3(13,2,3);
  cam.lookat   = point3(0,0,0);
  cam.vup      = vec3(0,1,0);

  cam.defocus_angle = 0;

  cam.render(world);
};

#endif
