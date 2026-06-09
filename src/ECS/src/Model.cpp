#include "Model.h"
#include "Mesh.h"

/* Model
 */
Model::Model() {

}

/* ~Model
 */
Model::~Model() {
    for (unsigned int i = 0; i < m_meshes.size(); i++) {
        delete m_meshes[i];
    }

    m_meshes.clear();
}

/* set_transform
 */
void Model::set_transform(Transform transform) {
    Component::set_transform(transform);

    for (int i = 0; i < m_meshes.size(); i++) {
        m_meshes[i]->set_transform(transform);
    }
}

/* load_model
 */
void Model::load_model(const std::string &file_path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    this->process_node(scene->mRootNode, scene);

    std::cout << "Loaded model successfully" << std::endl;
}

/* get_meshes
 */
void Model::get_meshes(std::vector<Mesh*> &meshes) {
    meshes = m_meshes;
}

/* process_node
 */
void Model::process_node(const aiNode *node, const aiScene *scene) {
    // Process all the node's meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(this->process_mesh(mesh, scene));
    }

    // Do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        this->process_node(node->mChildren[i], scene);
    }
}

/* process_mesh
 */
Mesh *Model::process_mesh(const aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // process vertex positions, normals and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        vertex.vertex = vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        vertex.normal = vec3(
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        );

        // TODO
        vertex.uv = vec2(
            0.0f,
            0.0f            
        );

        vertices.push_back(vertex);
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process material
    if (mesh->mMaterialIndex >= 0) {
        // [...]
    }

    return new Mesh(vertices);
}
