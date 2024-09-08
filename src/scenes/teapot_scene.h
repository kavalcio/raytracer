#ifndef TEAPOT_SCENE_H
#define TEAPOT_SCENE_H

void teapot_scene() {
  hittable_list world;

  auto obj = triangle_mesh("src/external/teapot.obj");
  world.add(make_shared<hittable_list>(obj.mesh));

  world = hittable_list(make_shared<bvh_node>(world));

  camera cam;

  cam.aspect_ratio      = 1.0;
  cam.image_width       = 400;
  cam.samples_per_pixel = 5;
  cam.max_depth         = 50;

  cam.vfov     = 80;
  cam.lookfrom = point3(0,4,9);
  cam.lookat   = point3(0,0,0);
  cam.vup      = vec3(0,1,0);

  cam.defocus_angle = 0;

  cam.render(world);
}

#endif
