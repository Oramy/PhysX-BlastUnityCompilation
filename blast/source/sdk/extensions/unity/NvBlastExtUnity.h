#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "windows.h"

#include "NvBlast.h"
#include "NvBlastAssert.h"
#include "NvBlastGlobals.h"
//#include "NvBlastExtExporter.h"
//#include "NvBlastPxCallbacks.h"
//#include "NvBlastTkAsset.h"
//#include "NvBlastExtLlSerialization.h"
//#include "NvBlastExtTkSerialization.h"
//#include "NvBlastExtPxSerialization.h"
#include "NvBlastExtAuthoring.h"
#include "NvBlastExtAuthoringMesh.h"
#include "NvBlastExtAuthoringBondGenerator.h"
#include "NvBlastExtAuthoringCollisionBuilderImpl.h"
#include "NvBlastExtAuthoringCutout.h"
#include "NvBlastExtAuthoringFractureTool.h"
//#include "BlastDataExporter.h"
#include "NvBlastExtAuthoringMeshCleaner.h"
#include "NvBlastTkFramework.h"

//#include "Px.h"
#include "PxPhysicsAPI.h"
#include "PxFoundation.h"

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace Nv::Blast;
using namespace std;

// Configuration des macros d'exportation pour Windows / MSVC
# define NVBLAST_API __declspec(dllexport)

// Raccourcis de types pour correspondre au fichier .cpp
using Nv::Blast::Edge;
using Nv::Blast::Facet;
using Nv::Blast::FractureTool;
using Nv::Blast::Mesh;
using Nv::Blast::MeshCleaner;
using Nv::Blast::SlicingConfiguration;
using Nv::Blast::Triangle;
using Nv::Blast::Vertex;
using Nv::Blast::VoronoiSitesGenerator;

// Obligatoire pour l'interopérabilité avec le C# de Unity
extern "C"
{

    NVBLAST_API void Version();
    NVBLAST_API void setSeed(int seed);

#pragma region MESH_FUNCTIONS
    NVBLAST_API void _Mesh_Release(Mesh* mesh);
    NVBLAST_API void _Mesh_getVertices(Mesh* mesh, void* arr);
    NVBLAST_API void _Mesh_getNormals(Mesh* mesh, void* arr);
    NVBLAST_API void _Mesh_getIndexes(Mesh* mesh, void* arr);
    NVBLAST_API void _Mesh_getUVs(Mesh* mesh, void* arr);
    NVBLAST_API void _Mesh_getUVsFromChannel(Mesh* mesh, void* arr, int channel);
    NVBLAST_API uint32_t _Mesh_getVerticesCount(Mesh* mesh);
    NVBLAST_API uint32_t _Mesh_getIndexesCount(Mesh* mesh);
#pragma endregion

#pragma region MESHCLEANER_FUNCTIONS
    NVBLAST_API void _Cleaner_Release(MeshCleaner* cleaner);
    NVBLAST_API Mesh* _Cleaner_cleanMesh(MeshCleaner* cleaner, Mesh* mesh);
#pragma endregion

#pragma region FRACTURETOOL_FUNCTIONS
    NVBLAST_API void _FractureTool_Release(FractureTool* tool);
    NVBLAST_API void _FractureTool_setRemoveIslands(FractureTool* tool, bool remove);
    NVBLAST_API void _FractureTool_setSourceMesh(FractureTool* tool, Mesh* mesh);
    NVBLAST_API bool _FractureTool_voronoiFracturing(FractureTool* tool, uint32_t chunkId, VoronoiSitesGenerator* vsg);
    NVBLAST_API bool _FractureTool_slicing(FractureTool* tool, int chunkId, SlicingConfiguration* conf, bool replaceChunk);
    NVBLAST_API void _FractureTool_finalizeFracturing(FractureTool* tool);
    NVBLAST_API uint32_t _FractureTool_getChunkCount(FractureTool* tool);
    NVBLAST_API Mesh* _FractureTool_getChunkMesh(FractureTool* tool, int chunkId, bool inside);
#pragma endregion

#pragma region VORONOISITES_FUNCTIONS
    NVBLAST_API void _NvVoronoiSitesGenerator_Release(VoronoiSitesGenerator* tool);
    NVBLAST_API VoronoiSitesGenerator* _VoronoiSitesGenerator_Create(Mesh* mesh);
    NVBLAST_API void _NvVoronoiSitesGenerator_uniformlyGenerateSitesInMesh(VoronoiSitesGenerator* tool, int count);
    NVBLAST_API void _NvVoronoiSitesGenerator_clusteredSitesGeneration(VoronoiSitesGenerator* tool,
                                                                       uint32_t numberOfClusters,
                                                                       uint32_t sitesPerCluster,
                                                                       float clusterRadius);
#pragma endregion
}
