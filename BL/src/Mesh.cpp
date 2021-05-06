#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader/tiny_obj_loader.h"
#include<iostream>
Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

bool Mesh::LoadObj(const char* path) {
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./"; // Path to material files

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty()) {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();
    for (size_t s = 0; s < shapes.size(); s++)
    {
        for (size_t i = 0; i < shapes[s].mesh.indices.size(); i++)
        {
            auto index = shapes[s].mesh.indices[i];

        }
    }

    std::cout << shapes.size() << std::endl;
    std::cout << shapes[0].mesh.indices.size() << std::endl;
    std::cout << 48+shapes[0].mesh.num_face_vertices[0] << std::endl;
    int vnum = attrib.vertices.size();
    int nnum = attrib.normals.size();
    int texnum = attrib.texcoords.size();

    

    //Vertex vertex;
    //for (size_t v = 0; v < attrib.vertices.size() / 3; v++) {
    //    vertex.Postion = { attrib.vertices[3 * v + 0] ,
    //        attrib.vertices[3 * v + 1],
    //        attrib.vertices[3 * v + 2] };
    //    printf("  v[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
    //        static_cast<const double>(attrib.vertices[3 * v + 0]),
    //        static_cast<const double>(attrib.vertices[3 * v + 1]),
    //        static_cast<const double>(attrib.vertices[3 * v + 2]));
    //    
    //}

    //for (size_t v = 0; v < attrib.normals.size() / 3; v++) {
    //    printf("  n[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
    //        static_cast<const double>(attrib.normals[3 * v + 0]),
    //        static_cast<const double>(attrib.normals[3 * v + 1]),
    //        static_cast<const double>(attrib.normals[3 * v + 2]));
    //}

    //for (size_t v = 0; v < attrib.texcoords.size() / 2; v++) {
    //    printf("  uv[%ld] = (%f, %f)\n", static_cast<long>(v),
    //        static_cast<const double>(attrib.texcoords[2 * v + 0]),
    //        static_cast<const double>(attrib.texcoords[2 * v + 1]));
    //}

    //// Loop over shapes
    //for (size_t s = 0; s < shapes.size(); s++) {
    //    // Loop over faces(polygon)
    //    size_t index_offset = 0;
    //    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
    //        size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

    //        // Loop over vertices in the face.
    //        for (size_t v = 0; v < fv; v++) {
    //            // access to vertex
    //            tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
    //            tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
    //            tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
    //            tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

    //            // Check if `normal_index` is zero or positive. negative = no normal data
    //            if (idx.normal_index >= 0) {
    //                tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
    //                tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
    //                tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
    //            }

    //            // Check if `texcoord_index` is zero or positive. negative = no texcoord data
    //            if (idx.texcoord_index >= 0) {
    //                tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
    //                tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
    //            }

    //            // Optional: vertex colors
    //            // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
    //            // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
    //            // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
    //        }
    //        index_offset += fv;

    //        // per-face material
    //        shapes[s].mesh.material_ids[f];
    //    }
    //}
}