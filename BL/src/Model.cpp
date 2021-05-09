#include "Model.h"
#include <string>
#include <map>
#include <iostream>
#include <memory>

#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader/tiny_obj_loader.h"

Model::Model()
{
}

Model::~Model()
{
}

bool Model::LoadObj(const char* path) {
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
    std::cout << "Loading obj " << path << std::endl;
    std::cout << "Total vertices   = " << (int)(attrib.vertices.size() / 3) << std::endl;
    std::cout << "Total colors     = " << (int)(attrib.colors.size() / 3) << std::endl;
    std::cout << "Total normals    = " << (int)(attrib.normals.size() / 3) << std::endl;
    std::cout << "Total texcoords  = " << (int)(attrib.texcoords.size() / 3) << std::endl;
    std::cout << "Shapes: " << shapes.size() << std::endl;
    for (size_t s = 0; s < shapes.size(); s++)
    {
        std::map<int, tinyobj::index_t> unique_indices;//用于判断是否重复出现
        std::map<int, tinyobj::index_t>::iterator it;
        int count = 0;
        
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
        for (size_t i = 0; i < shapes[s].mesh.indices.size(); i++)
        {
            auto index = shapes[s].mesh.indices[i];
            int vi = index.vertex_index;
            int ni = index.normal_index;
            int ti = index.texcoord_index;
            it = unique_indices.find(vi);
            if (it != unique_indices.end() &&
                it->second.texcoord_index == vi &&
                it->second.normal_index == ni)
            {
                mesh->AddIndex(count);
            }
            else
            {
                mesh->AddVertex({attrib.vertices[3 * vi + 0], 
                    attrib.vertices[3 * vi + 1],
                    attrib.vertices[3 * vi + 2]});

                if (attrib.normals.size() > 0)
                {
                    mesh->AddNormal({ attrib.normals[3 * ni + 0],
                        attrib.normals[3 * ni + 1],
                        attrib.normals[3 * ni + 2], });
                }

                if (attrib.texcoords.size() > 0) {
                    mesh->AddTexCoord({attrib.texcoords[2 * ti + 0],
                        attrib.texcoords[2 * ti + 1]
                        });
                }
                mesh->AddIndex(count);
                unique_indices[vi] = { vi,ni,ti };
                count++;
            }
        }
        m_Meshes.push_back(mesh);
    }
}