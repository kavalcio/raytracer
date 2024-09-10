#ifndef TEAPOT_SCENE_H
#define TEAPOT_SCENE_H

void teapot_scene() {
  hittable_list world;

  auto teapot_material = make_shared<lambertian>(color(.9, .2, .3));
  auto teapot = triangle_mesh("src/external/teapot.obj", vec3(0, 0, -1), teapot_material);
  world.add(make_shared<hittable_list>(teapot.mesh));

  auto ground_material = make_shared<lambertian>(color(.9, .9, .9));
  world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

  auto material2 = make_shared<lambertian>(color(0.4, 0.8, 0.1));
  world.add(make_shared<sphere>(point3(4, 1, -3), 2.0, material2));

  auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
  world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material3));

  auto light = make_shared<diffuse_light>(color(4, 4, 4));
  world.add(make_shared<sphere>(point3(-2, 4, 0), 0.6, light));

  world.add(make_shared<quad>(point3(3.5,2,4), vec3(2,0,-1), vec3(0,2,0), light));

  world = hittable_list(make_shared<bvh_node>(world));

  camera cam;

  cam.ground_color = color(0, 0, 0);
  cam.sky_color = color(0.05, 0, 0);

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 800;
  cam.samples_per_pixel = 200;
  cam.max_depth         = 50;

  cam.vfov     = 35;
  cam.lookfrom = point3(0,3,12);
  cam.lookat   = point3(0,2,0);
  cam.vup      = vec3(0,1,0);

  cam.defocus_angle = 0.6;
  cam.focus_dist    = 10.0;

  cam.render(world);
}

#endif
