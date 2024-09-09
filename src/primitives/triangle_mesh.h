#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include "triangle.h"
#include "../hittable_list.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../external/tiny_obj_loader.h"

#include <vector>
#include <fstream>

class triangle_mesh {
  // TODO: add mesh-wide rotation and scale values (or use a transformation matrix)
  public:
    hittable_list mesh;

    triangle_mesh(const char* image_filename, const point3& center, shared_ptr<material> mat) : center(center) {
      auto filename = std::string(image_filename);
      
      tinyobj::ObjReaderConfig reader_config;
      tinyobj::ObjReader reader;
      if (!reader.ParseFromFile(filename)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
      }

      if (!reader.Warning().empty()) {
        std::cerr << "TinyObjReader: " << reader.Warning();
      }

      auto& attrib = reader.GetAttrib();
      auto& shapes = reader.GetShapes();

      // Loop over shapes
      for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
          // Loop over vertices in the face.
          size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
          std::vector<vec3> face_vertices;
          for (size_t v = 0; v < fv; v++) {
            tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
            tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
            tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
            tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];
            face_vertices.push_back(vec3(vx, vy, vz) + center);
          }
          index_offset += fv;

          mesh.add(make_shared<triangle>(
            face_vertices[0],
            face_vertices[1] - face_vertices[0],
            face_vertices[2] - face_vertices[0],
            mat
          ));
        }
      }

      // Convert the list of triangles into a BVH
      mesh = hittable_list(make_shared<bvh_node>(mesh));
    }
  
  private:
    point3 center;

};

#endif
