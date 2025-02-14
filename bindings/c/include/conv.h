#pragma once
#include <manifold.h>
#include <meshIO.h>
#include <public.h>
#include <sdf.h>
#include <types.h>

ManifoldManifold *to_c(manifold::Manifold *m);
ManifoldSimplePolygon *to_c(manifold::SimplePolygon *p);
ManifoldPolygons *to_c(manifold::Polygons *ps);
ManifoldMesh *to_c(manifold::Mesh *m);
ManifoldMeshGL *to_c(manifold::MeshGL *m);
ManifoldBox *to_c(manifold::Box *m);
ManifoldCurvature *to_c(manifold::Curvature *m);
ManifoldComponents *to_c(manifold::Components *components);
ManifoldError to_c(manifold::Manifold::Error error);
ManifoldMaterial *to_c(manifold::Material *m);
ManifoldExportOptions *to_c(manifold::ExportOptions *m);
ManifoldVec3 to_c(glm::vec3 v);
ManifoldIVec3 to_c(glm::ivec3 v);
ManifoldProperties to_c(manifold::Properties p);

const manifold::Manifold *from_c(ManifoldManifold *m);
const manifold::SimplePolygon *from_c(ManifoldSimplePolygon *m);
const manifold::Polygons *from_c(ManifoldPolygons *m);
const manifold::Mesh *from_c(ManifoldMesh *m);
const manifold::MeshGL *from_c(ManifoldMeshGL *m);
const manifold::Box *from_c(ManifoldBox *m);
const manifold::Curvature *from_c(ManifoldCurvature *m);
const manifold::Components *from_c(ManifoldComponents *components);
manifold::Material *from_c(ManifoldMaterial *mat);
manifold::ExportOptions *from_c(ManifoldExportOptions *options);
glm::vec3 from_c(ManifoldVec3 v);
glm::ivec3 from_c(ManifoldIVec3 v);
glm::vec4 from_c(ManifoldVec4 v);

std::vector<glm::vec3> vector_of_vec_array(ManifoldVec3 *vs, size_t length);
std::vector<glm::ivec3> vector_of_vec_array(ManifoldIVec3 *vs, size_t length);
std::vector<glm::vec4> vector_of_vec_array(ManifoldVec4 *vs, size_t length);

template <typename T>
std::vector<T> vector_of_array(T *ts, size_t length) {
  auto vec = std::vector<T>();
  for (int i = 0; i < length; ++i) {
    vec.push_back(ts[i]);
  }
  return vec;
}

template <typename T>
T *copy_data(void *mem, std::vector<T> v) {
  T *ts = reinterpret_cast<T *>(mem);
  memcpy(ts, v.data(), sizeof(T) * v.size());
  return ts;
}
