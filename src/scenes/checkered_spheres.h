#ifndef CHECKERED_SPHERES_H
#define CHECKERED_SPHERES_H

void checkered_spheres() {
  hittable_list world;

  auto checker = make_shared<checker_texture>(0.03, color(.8, .3, .1), color(.9, .9, .9));
  auto material = make_shared<lambertian>(checker);

  auto top_sphere = make_shared<sphere>(point3(0, -10, 0), 10, material);
  world.add(top_sphere);
  auto bottom_sphere = make_shared<sphere>(point3(0, 10, 0), 10, material);
  world.add(bottom_sphere);
  
  world = hittable_list(make_shared<bvh_node>(world));

  camera cam;

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 400;
  cam.samples_per_pixel = 50;
  cam.max_depth         = 50;

  cam.vfov     = 30;
  cam.lookfrom = point3(12,1,5);
  cam.lookat   = point3(0,0,0);
  cam.vup      = vec3(0,1,0);

  cam.defocus_angle = 0.6;
  cam.focus_dist    = 10.0;

  cam.render(world);
}

#endif
