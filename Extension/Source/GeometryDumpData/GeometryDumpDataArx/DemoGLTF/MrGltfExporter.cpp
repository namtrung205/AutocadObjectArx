#include "stdafx.h"
#include "MrGltfExporter.h"

bool MrGltfExporter::SerializeModel()
{
    // Pass the absolute path, without the filename, to the stream writer
    auto streamWriter = std::make_unique<StreamWriter>(m_outputPath.parent_path());

    fs::path pathFile = m_outputPath.filename();
    fs::path pathFileExt = pathFile.extension();

    auto MakePathExt = [](const std::string& ext)
    {
        return "." + ext;
    };

    std::unique_ptr<ResourceWriter> resourceWriter;

    // If the file has a '.gltf' extension then create a GLTFResourceWriter
    if (pathFileExt == MakePathExt(GLTF_EXTENSION))
    {
        resourceWriter = std::make_unique<GLTFResourceWriter>(std::move(streamWriter));
    }

    // If the file has a '.glb' extension then create a GLBResourceWriter. This class derives
    // from GLTFResourceWriter and adds support for writing manifests to a GLB container's
    // JSON chunk and resource data to the binary chunk.
    if (pathFileExt == MakePathExt(GLB_EXTENSION))
    {
        resourceWriter = std::make_unique<GLBResourceWriter>(std::move(streamWriter));
    }

    if (!resourceWriter)
    {
        throw std::runtime_error("Command line argument path filename extension must be .gltf or .glb");
    }

    // The Document instance represents the glTF JSON manifest

    std::string accessorIdIndices;
    std::string accessorIdPositions;


    //CreateTriangleResources(accessorIdIndices, accessorIdPositions);
    //CreateTriangleEntities(accessorIdIndices, accessorIdPositions);

    std::string manifest;

    try
    {
        // Serialize the glTF Document into a JSON manifest
        manifest = Serialize(m_gltfDocument, SerializeFlags::Pretty);
    }
    catch (const GLTFException& ex)
    {
        std::stringstream ss;

        ss << "Microsoft::glTF::Serialize failed: ";
        ss << ex.what();

        throw std::runtime_error(ss.str());
    }

    auto& gltfResourceWriter = m_pBufferBuilder->GetResourceWriter();

    if (auto glbResourceWriter = dynamic_cast<GLBResourceWriter*>(&gltfResourceWriter))
    {
        glbResourceWriter->Flush(manifest, pathFile.u8string()); // A GLB container isn't created until the GLBResourceWriter::Flush member function is called
    }
    else
    {
        gltfResourceWriter.WriteExternal(pathFile.u8string(), manifest); // Binary resources have already been written, just need to write the manifest
    }



	return false;
}

void MrGltfExporter::CreateTriangleResources(std::string& accessorIdIndices, std::string& accessorIdPositions)
{
    // Create all the resource data (e.g. triangle indices and
    // vertex positions) that will be written to the binary buffer
    const char* bufferId = nullptr;

    // Specify the 'special' GLB buffer ID. This informs the GLBResourceWriter that it should use
    // the GLB container's binary chunk (usually the desired buffer location when creating GLBs)
    if (dynamic_cast<const GLBResourceWriter*>(&(* m_pBufferBuilder).GetResourceWriter()))
    {
        bufferId = GLB_BUFFER_ID;
    }

    // Create a Buffer - it will be the 'current' Buffer that all the BufferViews
    // created by this BufferBuilder will automatically reference
    (* m_pBufferBuilder).AddBuffer(bufferId);

    // Create a BufferView with a target of ELEMENT_ARRAY_BUFFER (as it will reference index
    // data) - it will be the 'current' BufferView that all the Accessors created by this
    // BufferBuilder will automatically reference
    (*m_pBufferBuilder).AddBufferView(BufferViewTarget::ELEMENT_ARRAY_BUFFER);

    // Add an Accessor for the indices
    std::vector<uint16_t> indices = {
        0U, 1U, 2U
    };

    // Copy the Accessor's id - subsequent calls to AddAccessor may invalidate the returned reference
    accessorIdIndices = (*m_pBufferBuilder).AddAccessor(indices, { TYPE_SCALAR, COMPONENT_UNSIGNED_SHORT }).id;

    // Create a BufferView with target ARRAY_BUFFER (as it will reference vertex attribute data)
    (*m_pBufferBuilder).AddBufferView(BufferViewTarget::ARRAY_BUFFER);

    // Add an Accessor for the positions
    std::vector<float> positions = {
        0.0f, 0.0f, 0.0f, // Vertex 0
        1.0f, 0.0f, 0.0f, // Vertex 1
        0.0f, 1.0f, 0.0f  // Vertex 2
    };

    std::vector<float> minValues(3U, std::numeric_limits<float>::max());
    std::vector<float> maxValues(3U, std::numeric_limits<float>::lowest());

    const size_t positionCount = positions.size();

    // Accessor min/max properties must be set for vertex position data so calculate them here
    for (size_t i = 0U, j = 0U; i < positionCount; ++i, j = (i % 3U))
    {
        minValues[j] = std::min(positions[i], minValues[j]);
        maxValues[j] = std::max(positions[i], maxValues[j]);
    }

    accessorIdPositions = (*m_pBufferBuilder).AddAccessor(positions, { TYPE_VEC3, COMPONENT_FLOAT, false, std::move(minValues), std::move(maxValues) }).id;

    // Add all of the Buffers, BufferViews and Accessors that were created using BufferBuilder to
    // the Document. Note that after this point, no further calls should be made to BufferBuilder
    (*m_pBufferBuilder).Output(m_gltfDocument);
}


void MrGltfExporter::CreateTriangleResources(std::string& accessorIdIndices, std::string& accessorIdPositions, const Adesk::UInt32 nbVertex, const AcGePoint3d* pVertexList, const Adesk::UInt32 faceListSize, const Adesk::Int32* pFaceList, const AcGiEdgeData* pEdgeData = NULL, const AcGiFaceData* pFaceData = NULL, const AcGiVertexData* pVertexData = NULL, const resbuf* pResBuf = NULL, const bool bAutoGenerateNormals = true)
{

    if(nbVertex > 2)
    {
    
        // Create all the resource data (e.g. triangle indices and
        // vertex positions) that will be written to the binary buffer
        const char* bufferId = nullptr;

        // Specify the 'special' GLB buffer ID. This informs the GLBResourceWriter that it should use
        // the GLB container's binary chunk (usually the desired buffer location when creating GLBs)
        if (dynamic_cast<const GLBResourceWriter*>(&(*m_pBufferBuilder).GetResourceWriter()))
        {
            bufferId = GLB_BUFFER_ID;
        }

        // Create a Buffer - it will be the 'current' Buffer that all the BufferViews
        // created by this BufferBuilder will automatically reference
        (*m_pBufferBuilder).AddBuffer(bufferId);

        // Create a BufferView with a target of ELEMENT_ARRAY_BUFFER (as it will reference index
        // data) - it will be the 'current' BufferView that all the Accessors created by this
        // BufferBuilder will automatically reference
        (*m_pBufferBuilder).AddBufferView(BufferViewTarget::ELEMENT_ARRAY_BUFFER);

        // Add an Accessor for the indices
        std::vector<uint16_t> indices = {
            0U, 1U, 2U
        };

        // Copy the Accessor's id - subsequent calls to AddAccessor may invalidate the returned reference
        accessorIdIndices = (*m_pBufferBuilder).AddAccessor(indices, { TYPE_SCALAR, COMPONENT_UNSIGNED_SHORT }).id;

        // Create a BufferView with target ARRAY_BUFFER (as it will reference vertex attribute data)
        (*m_pBufferBuilder).AddBufferView(BufferViewTarget::ARRAY_BUFFER);


        std::vector<float> positions = {};

        for (size_t i = 0; i < 3; i++)
        {
            positions.push_back((float)pVertexList[i].x);
            positions.push_back((float)pVertexList[i].y);
            positions.push_back((float)pVertexList[i].z);
        }


        std::vector<float> minValues(3U, std::numeric_limits<float>::max());
        std::vector<float> maxValues(3U, std::numeric_limits<float>::lowest());

        const size_t positionCount = positions.size();

        // Accessor min/max properties must be set for vertex position data so calculate them here
        for (size_t i = 0U, j = 0U; i < positionCount; ++i, j = (i % 3U))
        {
            minValues[j] = std::min(positions[i], minValues[j]);
            maxValues[j] = std::max(positions[i], maxValues[j]);
        }

        accessorIdPositions = (*m_pBufferBuilder).AddAccessor(positions, { TYPE_VEC3, COMPONENT_FLOAT, false, std::move(minValues), std::move(maxValues) }).id;

        // Add all of the Buffers, BufferViews and Accessors that were created using BufferBuilder to
        // the Document. Note that after this point, no further calls should be made to BufferBuilder
        (*m_pBufferBuilder).Output(m_gltfDocument);

    }
}


void MrGltfExporter::CreateTriangleEntities(const std::string& accessorIdIndices, const std::string& accessorIdPositions)
{
    // Create a very simple glTF Document with the following hierarchy:
    //  Scene
    //     Node
    //       Mesh (Triangle)
    //         MeshPrimitive
    //           Material (Blue)
    // 
    // A Document can be constructed top-down or bottom up. However, if constructed top-down
    // then the IDs of child entities must be known in advance, which prevents using the glTF
    // SDK's automatic ID generation functionality.

    // Construct a Material
    Material material;
    material.metallicRoughness.baseColorFactor = Color4(0.0f, 0.0f, 1.0f, 1.0f);
    material.metallicRoughness.metallicFactor = 0.2f;
    material.metallicRoughness.roughnessFactor = 0.4f;
    material.doubleSided = true;

    // Add it to the Document and store the generated ID
    auto materialId = m_gltfDocument.materials.Append(std::move(material), AppendIdPolicy::GenerateOnEmpty).id;

    // Construct a MeshPrimitive. Unlike most types in glTF, MeshPrimitives are direct children
    // of their parent Mesh entity rather than being children of the Document. This is why they
    // don't have an ID member.
    MeshPrimitive meshPrimitive;
    meshPrimitive.materialId = materialId;
    meshPrimitive.indicesAccessorId = accessorIdIndices;
    meshPrimitive.attributes[ACCESSOR_POSITION] = accessorIdPositions;

    // Construct a Mesh and add the MeshPrimitive as a child
    Mesh mesh;
    mesh.primitives.push_back(std::move(meshPrimitive));
    // Add it to the Document and store the generated ID
    auto meshId = m_gltfDocument.meshes.Append(std::move(mesh), AppendIdPolicy::GenerateOnEmpty).id;

    // Construct a Node adding a reference to the Mesh
    Node node;
    node.meshId = meshId;
    // Add it to the Document and store the generated ID
    auto nodeId = m_gltfDocument.nodes.Append(std::move(node), AppendIdPolicy::GenerateOnEmpty).id;

    // Construct a Scene
    Scene scene;
    scene.nodes.push_back(nodeId);
    // Add it to the Document, using a utility method that also sets the Scene as the Document's default
    m_gltfDocument.SetDefaultScene(std::move(scene), AppendIdPolicy::GenerateOnEmpty);
}
