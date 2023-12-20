//#pragma once

//#include <rapidjson/document.h>
#include "StdAfx.h"
#include "arx_interface.h"
#include <gemat3d.h>
#include <adscodes.h>
#include <dbents.h>
#include <dbapserv.h>
#include <acdocman.h>

#include <iostream>
#include <string>
#include <utc_Smiley.h>
//#include <curl/curl.h>

#pragma region test http request cUrl

//static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
//{
//    ((std::string*)userp)->append((char*)contents, size * nmemb);
//    return size * nmemb;
//}
//
////Function for test HTTP request
//void testAPIcURL() {
//    CURL* curl;
//    CURLcode res;
//    std::string response;
//
//    curl = curl_easy_init();
//    if (curl) {
//        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
//        curl_easy_setopt(curl, CURLOPT_URL, "https://reqres.in/api/unknown");
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
//        res = curl_easy_perform(curl);
//        curl_easy_cleanup(curl);
//
//        //Parse json return rapidjson
//        rapidjson::Document jsonDoc;
//        jsonDoc.Parse(response.c_str());
//        if (jsonDoc.HasMember("page")) {
//
//            if (jsonDoc["page"].IsNumber()) {
//                int64_t pageVal = jsonDoc["page"].GetInt64();
//                std::cout << pageVal << "\n";
//            }
//        }
//    }
//}

#pragma endregion


#pragma region C++ ARXInterface Functions

ArxInterface::ArxInterface()
{

}

ArxInterface::~ArxInterface()
{

}


void ArxInterface::PrintString(CString s)
{
    acutPrintf(s);
}


void ArxInterface::DrawCircle(double rad)
{

    //testAPIcURL();


    AcApDocument* pActiveDoc = acDocManager->mdiActiveDocument();

    AcApDocumentIterator* pIter = acDocManager->newAcApDocumentIterator();

    // lock the document
    // in default, the DocLockMode
    // is write enable.
    Acad::ErrorStatus es = acDocManager->lockDocument(pActiveDoc /* AcAp::DocLockMode = AcAp::kWrite */);

    if (es != Acad::eOk)
    {
        // fail to lock     
        return;
    }



    AcDbDatabase* pDb = pActiveDoc->database();
    // get the block table
    AcDbBlockTable* pBlockTable;
    es = pDb->getBlockTable(pBlockTable, AcDb::kForRead);

    if (es != Acad::eOk)
    {
        return;
    }

    // get model space
    AcDbBlockTableRecord* pBlockTableRec;

    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRec, AcDb::kForWrite);

    if (es != Acad::eOk)
    {
        pBlockTable->close();
        return;
    }
    pBlockTable->close();

    // create a new entity

    AcDbCircle* pCircle = new AcDbCircle(AcGePoint3d(0, 0, 0), AcGeVector3d(0, 0, 1), rad);

    // add the new entity to the model space
    AcDbObjectId objId;
    pBlockTableRec->appendAcDbEntity(objId, pCircle);
    // close the entity
    pCircle->close();
    // close the model space block
    pBlockTableRec->close();
    // unlock the document
    es = acDocManager->unlockDocument(pActiveDoc);
    if (es == Acad::eOk)
    {
        // handle one document
        // successfully        
    }

}

void ArxInterface::DrawLine()
{
    // We first need to declare a couple of points
    AcGePoint3d startPt(1.0, 1.0, 0.0);
    AcGePoint3d endPt(10.0, 10.0, 0.0);

    // Now we need to instantiate an AcDbLine pointer
    // In this case, its constructor allows me to pass the 2 points
    AcDbLine* pLine = new AcDbLine(startPt, endPt);

    // Now we need to open the appropriate container which is inside BlockTable
    AcDbBlockTable* pBlockTable = NULL;
    //acDocManager->lockDocument();
    // First, get the current database and then get the BlockTable
    AcDbDatabase* pDB = acdbHostApplicationServices()->workingDatabase();
    pDB->getSymbolTable(pBlockTable, AcDb::kForRead);


    // Inside BlockTable, open the ModelSpace
    AcDbBlockTableRecord* pBlockTableRecord = NULL;
    Acad::ErrorStatus ret = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);



    // After get ModelSpace we can close the BlockTable
    pBlockTable->close();

    // Using ModelSpace pointer we can add our brand new line
    AcDbObjectId lineId = AcDbObjectId::kNull;
    pBlockTableRecord->appendAcDbEntity(lineId, pLine);

    // To finish the process we need to close ModelSpace and the entity
    pBlockTableRecord->close();
    pLine->close();


}

void ArxInterface::PlaceSmiley()
{
    // Put your command code here
//Get Point
    ads_point pt_res;

    acedGetPoint(NULL, _T("Select point..."), pt_res);
    AcGePoint3d cenPt = asPnt3d(pt_res);

    utc_Smiley* pSmile = new utc_Smiley();
    pSmile->setCenter(cenPt);


    //Add entity to model space
    {
        //Check name exists
        AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
        if (pDb != NULL)
        {
            AcDbObjectId modelId;
            modelId = acdbSymUtil()->blockModelSpaceId(pDb);
            AcDbBlockTableRecord* pBlockTableRecordModel;

            acdbOpenAcDbObject((AcDbObject*&)pBlockTableRecordModel, modelId, AcDb::kForRead);

            if (pBlockTableRecordModel != NULL)
            {
                pBlockTableRecordModel->upgradeOpen();
                pBlockTableRecordModel->appendAcDbEntity(pSmile);
                pBlockTableRecordModel->close();
            }
        }

    }
    pSmile->close();

}


void ArxInterface::PlaceSmiley( double faceSize, double eyeSize)
{
    // Put your command code here
    //Get Point
    ads_point pt_res;

    acedGetPoint(NULL, _T("Select point..."), pt_res);
    AcGePoint3d cenPt = asPnt3d(pt_res);

    utc_Smiley* pSmile = new utc_Smiley();
    pSmile->setCenter(cenPt);
    pSmile->setRadius(faceSize);
    pSmile->setEyeSize(eyeSize);


    //Add entity to model space
    {
        //Check name exists
        AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
        if (pDb != NULL)
        {
            AcDbObjectId modelId;
            modelId = acdbSymUtil()->blockModelSpaceId(pDb);
            AcDbBlockTableRecord* pBlockTableRecordModel;

            acdbOpenAcDbObject((AcDbObject*&)pBlockTableRecordModel, modelId, AcDb::kForRead);

            if (pBlockTableRecordModel != NULL)
            {
                pBlockTableRecordModel->upgradeOpen();
                pBlockTableRecordModel->appendAcDbEntity(pSmile);
                pBlockTableRecordModel->close();
            }
        }

    }
    pSmile->close();

}

//return 1 datatype support by "mgdinterop.h"
//VD: Return 1 matrix move an object by Z (WCS).
AcGeMatrix3d ArxInterface::MoveUp(AcGeMatrix3d inputMat, double dis)
{
    AcGeMatrix3d movedMat = inputMat.setTranslation(AcGeVector3d(0, 0, dis));
    return movedMat;
}

#pragma endregion

