#pragma once
#include <GLTFSDK/GLTF.h>
#include <GLTFSDK/BufferBuilder.h>
#include <GLTFSDK/GLTFResourceWriter.h>
#include <GLTFSDK/GLBResourceWriter.h>
#include <GLTFSDK/IStreamWriter.h>
#include <GLTFSDK/Serialize.h>


#include <fstream>
#include <sstream>
#include <iostream>

#include <cassert>
#include <cstdlib>

using namespace Microsoft::glTF;

// The glTF SDK is decoupled from all file I/O by the IStreamWriter (and IStreamReader)
// interface(s) and the C++ stream-based I/O library. This allows the glTF SDK to be used in
// sandboxed environments, such as WebAssembly modules and UWP apps, where any file I/O code
// must be platform or use-case specific.
class StreamWriter : public IStreamWriter
{
public:
    StreamWriter(fs::path pathBase) : m_pathBase(std::move(pathBase))
    {
        assert(m_pathBase.has_root_path());
    }

    // Resolves the relative URIs of any external resources declared in the glTF manifest
    std::shared_ptr<std::ostream> GetOutputStream(const std::string& filename) const override
    {
        // In order to construct a valid stream:
        // 1. The filename argument will be encoded as UTF-8 so use filesystem::u8path to
        //    correctly construct a path instance.
        // 2. Generate an absolute path by concatenating m_pathBase with the specified filename
        //    path. The filesystem::operator/ uses the platform's preferred directory separator
        //    if appropriate.
        // 3. Always open the file stream in binary mode. The glTF SDK will handle any text
        //    encoding issues for us.
        auto streamPath = m_pathBase / fs::u8path(filename);
        auto stream = std::make_shared<std::ofstream>(streamPath, std::ios_base::binary);

        // Check if the stream has no errors and is ready for I/O operations
        if (!stream || !(*stream))
        {
            throw std::runtime_error("Unable to create a valid output stream for uri: " + filename);
        }

        return stream;
    }

private:
    fs::path m_pathBase;
};



class MrGltfExporter
{

public:
	fs::path m_outputPath;

    Document m_gltfDocument;

    BufferBuilder* m_pBufferBuilder;

public:
    MrGltfExporter(fs::path outputPath)
	{
		m_outputPath = outputPath;
	}

	~MrGltfExporter()
	{
		
	}

	//Property
	fs::path OutputPath()
	{
		return m_outputPath;
	}
	
	void SetOutputPath(const fs::path p)
	{
		m_outputPath = p;
	}



	//Serialize
	bool SerializeModel();

    void CreateTriangleResources(std::string& accessorIdIndices, std::string& accessorIdPositions);

    void CreateTriangleResources(std::string& accessorIdIndices, std::string& accessorIdPositions, const Adesk::UInt32 nbVertex, const AcGePoint3d* pVertexList, const Adesk::UInt32 faceListSize, const Adesk::Int32* pFaceList, const AcGiEdgeData* pEdgeData, const AcGiFaceData* pFaceData, const AcGiVertexData* pVertexData, const resbuf* pResBuf, const bool bAutoGenerateNormals);

    void CreateTriangleEntities(const std::string& accessorIdIndices, const std::string& accessorIdPositions);

};

