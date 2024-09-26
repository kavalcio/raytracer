#ifndef S_REFLECTION_H
#define S_REFLECTION_H

void s_reflection() {
  hittable_list world;

  auto checker = make_shared<checker_texture>(0.03, color(.9, .1, .1), color(.9, .9, .9));
  auto checker_material = make_shared<lambertian>(checker);

  auto solid_material = make_shared<lambertian>(color(0.8, 0.6, 0.5));
  auto transparent_material = make_shared<dielectric>(1.5, 0.1, color(0.95, 0.85, 1.0));
  auto light_material = make_shared<diffuse_light>(color(4, 4, 4));
  auto solid_material_2 = make_shared<lambertian>(color(0.2, 0.3, 0.8));
  auto solid_material_3 = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

  // world.add(make_shared<sphere>(point3(-2, 4, 0), 0.6, light_material));
  // world.add(make_shared<quad>(point3(3.5,2,4), vec3(2,0,-1), vec3(0,2,0), light_material));

  auto top_sphere = make_shared<sphere>(point3(0, 2, 0), 2, transparent_material);
  world.add(top_sphere);
  auto bottom_sphere = make_shared<sphere>(point3(0, -10, 0), 10, checker_material);
  world.add(bottom_sphere);

  auto reflect_sphere_1 = make_shared<sphere>(point3(-8, 16, 2), 10, checker_material);
  world.add(reflect_sphere_1);
  auto reflect_sphere_2 = make_shared<sphere>(point3(15, 3, 18), 9, solid_material_2);
  world.add(reflect_sphere_2);
  auto reflect_sphere_3 = make_shared<sphere>(point3(0, 9, 20), 6, solid_material_3);
  world.add(reflect_sphere_3);
  
  world = hittable_list(make_shared<bvh_node>(world));

  camera cam;

  // cam.ground_color = color(0, 0, 0);
  // cam.sky_color = color(0.1, 0.1, 0.1);

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 600;
  cam.samples_per_pixel = 200;
  cam.max_depth         = 50;

  cam.vfov     = 30;
  cam.lookfrom = point3(0,8,13);
  cam.lookat   = point3(0,2,0);
  cam.vup      = vec3(0,1,0);

  cam.defocus_angle = 0.6;
  cam.focus_dist    = 10.0;

  cam.render(world);
}

#endif
