#ifndef EARTH_H
#define EARTH_H

void earth() {
  hittable_list world;

  auto earth_texture = make_shared<image_texture>("earthmap.jpg");
  auto material = make_shared<lambertian>(earth_texture);

  world.add(make_shared<sphere>(point3(0, 0, 0), 2, material));
  
  world = hittable_list(make_shared<bvh_node>(world));

  camera cam;

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth         = 50;

  cam.vfov     = 20;
  cam.lookfrom = point3(0,0,12);
  cam.lookat   = point3(0,0,0);
  cam.vup      = vec3(0,1,0);

  cam.defocus_angle = 0;

  cam.render(world);
}

#endif
