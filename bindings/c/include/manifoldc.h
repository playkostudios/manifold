#include <stddef.h>
#include <stdint.h>
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Polygons
ManifoldSimplePolygon *manifold_simple_polygon(void *mem, ManifoldVec2 *ps,
                                               size_t length);
ManifoldPolygons *manifold_polygons(void *mem, ManifoldSimplePolygon **ps,
                                    size_t length);

// Mesh Construction
ManifoldMeshGL *manifold_meshgl(void *mem, float *vert_props, size_t n_verts,
                                size_t n_props, uint32_t *tri_verts,
                                size_t n_tris);

ManifoldMeshGL *manifold_meshgl_w_tangents(void *mem, float *vert_props,
                                           size_t n_verts, size_t n_props,
                                           uint32_t *tri_verts, size_t n_tris,
                                           float *halfedge_tangent);
ManifoldMeshGL *manifold_get_meshgl(void *mem, ManifoldManifold *m);
ManifoldMeshGL *manifold_meshgl_copy(void *mem, ManifoldMeshGL *m);

// SDF
// By default, the execution policy (sequential or parallel) of
// manifold_level_set will be chosen automatically depending on the size of the
// job and whether Manifold has been compiled with a PAR backend. If you are
// using these bindings from a language that has a runtime lock preventing the
// parallel execution of closures, then you should use manifold_level_set_seq to
// force sequential execution.
ManifoldMeshGL *manifold_level_set(void *mem, float (*sdf)(float, float, float),
                                   ManifoldBox *bounds, float edge_length,
                                   float level);
ManifoldMeshGL *manifold_level_set_seq(void *mem,
                                       float (*sdf)(float, float, float),
                                       ManifoldBox *bounds, float edge_length,
                                       float level);

// Manifold Booleans
ManifoldManifold *manifold_union(void *mem, ManifoldManifold *a,
                                 ManifoldManifold *b);
ManifoldManifold *manifold_difference(void *mem, ManifoldManifold *a,
                                      ManifoldManifold *b);
ManifoldManifold *manifold_intersection(void *mem, ManifoldManifold *a,
                                        ManifoldManifold *b);
ManifoldManifoldPair manifold_split(void *mem_first, void *mem_second,
                                    ManifoldManifold *a, ManifoldManifold *b);
ManifoldManifoldPair manifold_split_by_plane(void *mem_first, void *mem_second,
                                             ManifoldManifold *m,
                                             float normal_x, float normal_y,
                                             float normal_z, float offset);
ManifoldManifold *manifold_trim_by_plane(void *mem, ManifoldManifold *m,
                                         float normal_x, float normal_y,
                                         float normal_z, float offset);

// Manifold Transformations
ManifoldManifold *manifold_translate(void *mem, ManifoldManifold *m, float x,
                                     float y, float z);
ManifoldManifold *manifold_rotate(void *mem, ManifoldManifold *m, float x,
                                  float y, float z);
ManifoldManifold *manifold_scale(void *mem, ManifoldManifold *m, float x,
                                 float y, float z);
ManifoldManifold *manifold_transform(void *mem, ManifoldManifold *m, float x1,
                                     float y1, float z1, float x2, float y2,
                                     float z2, float x3, float y3, float z3,
                                     float x4, float y4, float z4);
ManifoldManifold *manifold_warp(void *mem, ManifoldManifold *m,
                                ManifoldVec3 (*fun)(float, float, float));
ManifoldManifold *manifold_refine(void *mem, ManifoldManifold *m, int refine);

// Manifold Shapes / Constructors
ManifoldManifold *manifold_empty(void *mem);
ManifoldManifold *manifold_copy(void *mem, ManifoldManifold *m);
ManifoldManifold *manifold_tetrahedron(void *mem);
ManifoldManifold *manifold_cube(void *mem, float x, float y, float z,
                                int center);
ManifoldManifold *manifold_cylinder(void *mem, float height, float radius_low,
                                    float radius_high, int circular_segments,
                                    int center);
ManifoldManifold *manifold_sphere(void *mem, float radius,
                                  int circular_segments);
ManifoldManifold *manifold_of_meshgl(void *mem, ManifoldMeshGL *mesh);
ManifoldManifold *manifold_smooth(void *mem, ManifoldMeshGL *mesh,
                                  int *half_edges, float *smoothness,
                                  int n_idxs);
ManifoldManifold *manifold_extrude(void *mem, ManifoldPolygons *polygons,
                                   float height, int slices,
                                   float twist_degrees, float scale_x,
                                   float scale_y);
ManifoldManifold *manifold_revolve(void *mem, ManifoldPolygons *polygons,
                                   int circular_segments);
ManifoldManifold *manifold_compose(void *mem, ManifoldManifold **ms,
                                   size_t length);
size_t manifold_decompose_length(ManifoldManifold *m);
ManifoldComponents *manifold_get_components(void *mem, ManifoldManifold *m);
size_t manifold_components_length(ManifoldComponents *components);
ManifoldManifold **manifold_decompose(void **mem, ManifoldManifold *m,
                                      ManifoldComponents *cs);
ManifoldManifold *manifold_as_original(void *mem, ManifoldManifold *m);

// Manifold Info
int manifold_is_empty(ManifoldManifold *m);
ManifoldError manifold_status(ManifoldManifold *m);
int manifold_num_vert(ManifoldManifold *m);
int manifold_num_edge(ManifoldManifold *m);
int manifold_num_tri(ManifoldManifold *m);
ManifoldBox *manifold_bounding_box(void *mem, ManifoldManifold *m);
float manifold_precision(ManifoldManifold *m);
int manifold_genus(ManifoldManifold *m);
ManifoldProperties manifold_get_properties(ManifoldManifold *m);
ManifoldCurvature *manifold_get_curvature(void *mem, ManifoldManifold *m);
ManifoldCurvatureBounds manifold_curvature_bounds(ManifoldCurvature *curv);
size_t manifold_curvature_vert_length(ManifoldCurvature *curv);
float *manifold_curvature_vert_mean(void *mem, ManifoldCurvature *curv);
float *manifold_curvature_vert_gaussian(void *mem, ManifoldCurvature *curv);
int manifold_get_circular_segments(float radius);
int manifold_original_id(ManifoldManifold *m);

// Bounding Box
ManifoldBox *manifold_box(void *mem, float x1, float y1, float z1, float x2,
                          float y2, float z2);
ManifoldVec3 manifold_box_min(ManifoldBox *b);
ManifoldVec3 manifold_box_max(ManifoldBox *b);
ManifoldVec3 manifold_box_dimensions(ManifoldBox *b);
ManifoldVec3 manifold_box_center(ManifoldBox *b);
float manifold_box_scale(ManifoldBox *b);
int manifold_box_contains_pt(ManifoldBox *b, float x, float y, float z);
int manifold_box_contains_box(ManifoldBox *a, ManifoldBox *b);
void manifold_box_include_pt(ManifoldBox *b, float x, float y, float z);
ManifoldBox *manifold_box_union(void *mem, ManifoldBox *a, ManifoldBox *b);
ManifoldBox *manifold_box_transform(void *mem, ManifoldBox *b, float x1,
                                    float y1, float z1, float x2, float y2,
                                    float z2, float x3, float y3, float z3,
                                    float x4, float y4, float z4);
ManifoldBox *manifold_box_translate(void *mem, ManifoldBox *b, float x, float y,
                                    float z);
ManifoldBox *manifold_box_mul(void *mem, ManifoldBox *b, float x, float y,
                              float z);
int manifold_box_does_overlap_pt(ManifoldBox *b, float x, float y, float z);
int manifold_box_does_overlap_box(ManifoldBox *a, ManifoldBox *b);
int manifold_box_is_finite(ManifoldBox *b);

// Static Quality Globals
void manifold_set_min_circular_angle(float degrees);
void manifold_set_min_circular_edge_length(float length);
void manifold_set_circular_segments(int number);

// Manifold Mesh Extraction
int manifold_meshgl_num_prop(ManifoldMeshGL *m);
int manifold_meshgl_num_vert(ManifoldMeshGL *m);
int manifold_meshgl_num_tri(ManifoldMeshGL *m);
size_t manifold_meshgl_vert_properties_length(ManifoldMeshGL *m);
size_t manifold_meshgl_tri_length(ManifoldMeshGL *m);
size_t manifold_meshgl_merge_length(ManifoldMeshGL *m);
size_t manifold_meshgl_run_index_length(ManifoldMeshGL *m);
size_t manifold_meshgl_run_original_id_length(ManifoldMeshGL *m);
size_t manifold_meshgl_run_transform_length(ManifoldMeshGL *m);
size_t manifold_meshgl_face_id_length(ManifoldMeshGL *m);
size_t manifold_meshgl_tangent_length(ManifoldMeshGL *m);
float *manifold_meshgl_vert_properties(void *mem, ManifoldMeshGL *m);
uint32_t *manifold_meshgl_tri_verts(void *mem, ManifoldMeshGL *m);
uint32_t *manifold_meshgl_merge_from_vert(void *mem, ManifoldMeshGL *m);
uint32_t *manifold_meshgl_merge_to_vert(void *mem, ManifoldMeshGL *m);
uint32_t *manifold_meshgl_run_index(void *mem, ManifoldMeshGL *m);
uint32_t *manifold_meshgl_run_original_id(void *mem, ManifoldMeshGL *m);
float *manifold_meshgl_run_transform(void *mem, ManifoldMeshGL *m);
uint32_t *manifold_meshgl_face_id(void *mem, ManifoldMeshGL *m);
float *manifold_meshgl_halfedge_tangent(void *mem, ManifoldMeshGL *m);

// MeshIO / Export
ManifoldMaterial *manifold_material(void *mem);
void manifold_material_set_roughness(ManifoldMaterial *mat, float roughness);
void manifold_material_set_metalness(ManifoldMaterial *mat, float metalness);
void manifold_material_set_color(ManifoldMaterial *mat, ManifoldVec4 color);
void manifold_material_set_vert_color(ManifoldMaterial *mat,
                                      ManifoldVec4 *vert_color, size_t n_vert);
ManifoldExportOptions *manifold_export_options(void *mem);
void manifold_export_options_set_faceted(ManifoldExportOptions *options,
                                         int faceted);
void manifold_export_options_set_material(ManifoldExportOptions *options,
                                          ManifoldMaterial *mat);
void manifold_export_meshgl(const char *filename, ManifoldMeshGL *mesh,
                            ManifoldExportOptions *options);

// memory size
size_t manifold_simple_polygon_size();
size_t manifold_polygons_size();
size_t manifold_manifold_size();
size_t manifold_manifold_pair_size();
size_t manifold_meshgl_size();
size_t manifold_box_size();
size_t manifold_curvature_size();
size_t manifold_components_size();
size_t manifold_material_size();
size_t manifold_export_options_size();

// destruction
void manifold_destruct_simple_polygon(ManifoldSimplePolygon *p);
void manifold_destruct_polygons(ManifoldPolygons *p);
void manifold_destruct_manifold(ManifoldManifold *m);
void manifold_destruct_meshgl(ManifoldMeshGL *m);
void manifold_destruct_box(ManifoldBox *b);
void manifold_destruct_curvature(ManifoldCurvature *c);
void manifold_destruct_components(ManifoldComponents *c);
void manifold_destruct_material(ManifoldMaterial *m);
void manifold_destruct_export_options(ManifoldExportOptions *options);

// pointer free + destruction
void manifold_delete_simple_polygon(ManifoldSimplePolygon *p);
void manifold_delete_polygons(ManifoldPolygons *p);
void manifold_delete_manifold(ManifoldManifold *m);
void manifold_delete_meshgl(ManifoldMeshGL *m);
void manifold_delete_box(ManifoldBox *b);
void manifold_delete_curvature(ManifoldCurvature *c);
void manifold_delete_components(ManifoldComponents *c);
void manifold_delete_material(ManifoldMaterial *m);
void manifold_delete_export_options(ManifoldExportOptions *options);

#ifdef __cplusplus
}
#endif
