#include "stdafx.h"
#include "tchar.h"
#include "aced.h"
#include <rxregsvc.h>

#include "UtcGiWorldDraw.h"



//#include "DemoGLTF/CreateTriangleMesh.h"



//-----------------------------------------------------------------------------
#define szRDS _RXST("UTC")
//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class GeometryDumpDataApp : public AcRxArxApp {

public:
	GeometryDumpDataApp() : AcRxArxApp() {}

	virtual AcRx::AppRetCode On_kInitAppMsg(void* pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg(pkt);

		// TODO: Add your initialization code here

		return (retCode);
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg(void* pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg(pkt);

		// TODO: Unload dependencies here

		return (retCode);
	}

	virtual void RegisterServerComponents() {
	}


	static void utcCommandGroup_DUMPDATA(void) 
	{
		acutPrintf(_T("\nBegin Dump Data...!\n"));
		//Iterator all entity in Model Space
        IterateEntities();


		//
	}

    static void IterateEntities()
    {
        AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();

        if (pDb == nullptr)
        {
            acutPrintf(_T("\nCannot access the current database."));
            return;
        }

        AcDbBlockTable* pBlockTable;
        if (acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pBlockTable, AcDb::kForRead) != Acad::eOk)
        {
            acutPrintf(_T("\nCannot access the block table."));
            return;
        }

        AcDbBlockTableRecord* pModelSpace;
        if (pBlockTable->getAt(ACDB_MODEL_SPACE, pModelSpace, AcDb::kForRead) != Acad::eOk)
        {
            acutPrintf(_T("\nCannot access the Model Space."));
            pBlockTable->close();
            return;
        }

        pBlockTable->close();

        AcDbEntity* pEntity;
        AcDbBlockTableRecordIterator* pIterator;
        if (pModelSpace->newIterator(pIterator) != Acad::eOk)
        {
            acutPrintf(_T("\nCannot create iterator."));
            pModelSpace->close();
            return;
        }

        fs::path outputPath = "D:\\ABC.glb";

        MrGltfExporter* exporter = new MrGltfExporter(outputPath);

        // Pass the absolute path, without the filename, to the stream writer
        auto streamWriter = std::make_unique<StreamWriter>(exporter->OutputPath());

        fs::path pathFile = exporter->OutputPath().filename();
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


        // Use the BufferBuilder helper class to simplify the process of
        // constructing valid glTF Buffer, BufferView and Accessor entities
        BufferBuilder  bufferBuilder = BufferBuilder(std::move(resourceWriter));
        exporter->m_pBufferBuilder = &bufferBuilder;


        UtcGiWorldDraw* wd = new UtcGiWorldDraw();





        wd->SetGltfExporter(exporter);

        for (; !pIterator->done(); pIterator->step())
        {
            if (pIterator->getEntity(pEntity, AcDb::kForRead) == Acad::eOk)
            {
                // Process the entity (pEntity) here.
                acutPrintf(_T("\nCurrent Type: "));
                acutPrintf(pEntity->isA()->name());

                ACHAR handleAsString[17];
                pEntity->objectId().handle().getIntoAsciiBuffer(handleAsString);
                acutPrintf(handleAsString);
                acutPrintf(_T("\n"));

                pEntity->worldDraw(wd);

                pEntity->close();
            }
        }


        std::string manifest;

        try
        {
            // Serialize the glTF Document into a JSON manifest
            manifest = Serialize(exporter->m_gltfDocument, SerializeFlags::Pretty);
        }
        catch (const GLTFException& ex)
        {
            std::stringstream ss;

            ss << "Microsoft::glTF::Serialize failed: ";
            ss << ex.what();

            throw std::runtime_error(ss.str());
        }

        auto& gltfResourceWriter = exporter->m_pBufferBuilder->GetResourceWriter();

        if (auto glbResourceWriter = dynamic_cast<GLBResourceWriter*>(&gltfResourceWriter))
        {
            glbResourceWriter->Flush(manifest, pathFile.u8string()); // A GLB container isn't created until the GLBResourceWriter::Flush member function is called
        }
        else
        {
            gltfResourceWriter.WriteExternal(pathFile.u8string(), manifest); // Binary resources have already been written, just need to write the manifest
        }


        delete pIterator;
        pModelSpace->close();

    }

};

//-----------------------------------------------------------------------------

IMPLEMENT_ARX_ENTRYPOINT(GeometryDumpDataApp)

ACED_ARXCOMMAND_ENTRY_AUTO(GeometryDumpDataApp, utcCommandGroup, _DUMPDATA, DUMPDATA, ACRX_CMD_TRANSPARENT, NULL)

