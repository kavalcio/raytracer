#ifndef TEAPOT_SCENE_H
#define TEAPOT_SCENE_H

void teapot_scene() {
  hittable_list world;

  auto teapot_material = make_shared<lambertian>(color(.9, .2, .3));
  auto obj = triangle_mesh("src/external/teapot.obj", vec3(0, 0.5, 0), teapot_material);
  world.add(make_shared<hittable_list>(obj.mesh));

  auto ground_material = make_shared<lambertian>(color(.9, .9, .9));
  world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

  // auto material1 = make_shared<dielectric>(1.5);
  // world.add(make_shared<sphere>(point3(0, 1, 4), 1.0, material1));

  auto material2 = make_shared<lambertian>(color(0.4, 0.8, 0.1));
  world.add(make_shared<sphere>(point3(4, 1, -3), 2.0, material2));

  auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
  world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material3));


  world = hittable_list(make_shared<bvh_node>(world));

  camera cam;

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 400;
  cam.samples_per_pixel = 20;
  cam.max_depth         = 50;

  cam.vfov     = 25;
  cam.lookfrom = point3(5,3,12);
  cam.lookat   = point3(0,1,0);
  cam.vup      = vec3(0,1,0);

  cam.defocus_angle = 0.6;
  cam.focus_dist    = 10.0;

  cam.render(world);
}

#endif
