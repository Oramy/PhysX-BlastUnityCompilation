#include "NvBlastExtUnity.h"

//#define CONSOLEDEBUG

class SimpleRandomGenerator : public Nv::Blast::RandomGeneratorBase
{
public:
    SimpleRandomGenerator() {
        remember = false;
    };

    virtual float getRandomValue()
    {
        float r = (float)rand();
        r = r / RAND_MAX;
        return r;
    }
    virtual void seed(int32_t seed)
    {
        srand(seed);
    }

    virtual ~SimpleRandomGenerator() {};

private:
    bool remember;
};

SimpleRandomGenerator rnd;
void Version()
{
	printf("Unity Wrapper V1.0\n");
}
void setSeed(int seed)
{
	rnd.seed(seed);
}

#pragma region MESH_FUNCTIONS

/*
Mesh Virtual Functions
*/

 void _Mesh_Release(Mesh* mesh)
{
	if (!mesh) { printf("(Warning) _Mesh_Relase: NULL mesh\n"); return; }
	mesh->release();
}

 void _Mesh_getVertices(Mesh* mesh, void* arr)
{
	if (!arr) { printf("(Warning) _Mesh_getVertices: NULL arr\n"); return; }
	if (!mesh) { printf("(Warning) _Mesh_getVertices: NULL mesh\n"); return; }
	const Vertex* verts = mesh->getVertices();

	NvcVec3* vertArr = (NvcVec3*)arr;

	for (uint32_t i = 0; i < mesh->getVerticesCount(); i++)
	{
		vertArr[i] = verts[i].p;
	}
}
 void _Mesh_getNormals(Mesh* mesh, void* arr)
{
	if (!arr) { printf("(Warning) _Mesh_getNormals: NULL arr\n"); return; }
	if (!mesh) { printf("(Warning) _Mesh_getNormals: NULL mesh\n"); return; }
	const Vertex* verts = mesh->getVertices();

	NvcVec3* vertArr = (NvcVec3*)arr;

	for (uint32_t i = 0; i < mesh->getVerticesCount(); i++)
	{
		vertArr[i] = verts[i].n;
	}
}
 void _Mesh_getIndexes(Mesh* mesh, void* arr)
{
	if (!arr) { printf("(Warning) _Mesh_getIndexes: NULL arr\n"); return; }
	if (!mesh) { printf("(Warning) _Mesh_getIndexes: NULL mesh\n"); return; }

	const Edge* edges = mesh->getEdges();
	const Facet* facet = mesh->getFacetsBuffer();

	uint32_t* vertArr = (uint32_t*)arr;

	for (uint32_t i = 0; i < mesh->getFacetCount(); i++)
	{
		vertArr[i * 3 + 0] = edges[facet[i].firstEdgeNumber + 0].s;
		vertArr[i * 3 + 1] = edges[facet[i].firstEdgeNumber + 1].s;
		vertArr[i * 3 + 2] = edges[facet[i].firstEdgeNumber + 2].s;
	}
}

void _Mesh_getUVs(Mesh* mesh, void* arr)
{
	if (!arr) { printf("(Warning) _Mesh_getUVs: NULL arr\n"); return; }
	if (!mesh) { printf("(Warning) _Mesh_getUVs: NULL mesh\n"); return; }
	const Vertex* verts = mesh->getVertices();

	NvcVec2* vertArr = (NvcVec2*)arr;

	for (uint32_t i = 0; i < mesh->getVerticesCount(); i++)
	{
		vertArr[i] = verts[i].uv[0];
	}
}

void _Mesh_getUVsFromChannel(Mesh* mesh, void* arr, int channel)
{
	if (!arr) { printf("(Warning) _Mesh_getUVs: NULL arr\n"); return; }
	if (!mesh) { printf("(Warning) _Mesh_getUVs: NULL mesh\n"); return; }
	const Vertex* verts = mesh->getVertices();

	NvcVec2* vertArr = (NvcVec2*)arr;

	for (uint32_t i = 0; i < mesh->getVerticesCount(); i++)
	{
		vertArr[i] = verts[i].uv[channel];
	}
}

 uint32_t _Mesh_getVerticesCount(Mesh* mesh)
{
	if (!mesh) { printf("(Warning) _Mesh_getVerticesCount: NULL mesh\n"); return 0; }
	return mesh->getVerticesCount();
}

 uint32_t _Mesh_getIndexesCount(Mesh* mesh)
{
	if (!mesh) { printf("(Warning) _Mesh_getIndexesCount: NULL mesh\n"); return 0; }
	return mesh->getFacetCount() * 3;
}
#pragma endregion

#pragma region MESHCLEANER_FUNCTIONS

/*
MeshCleaner Virtual Functions
*/
 void _Cleaner_Release(MeshCleaner* cleaner)
{
	if (!cleaner) { printf("(Warning) _Cleaner_Release: NULL MeshCleaner\n"); return; }
	cleaner->release();
}

 Mesh* _Cleaner_cleanMesh(MeshCleaner* cleaner, Mesh* mesh)
{
	if (!mesh) { printf("(Warning) _Cleaner_cleanMesh: NULL mesh\n"); return NULL; }
	if (!cleaner) { printf("(Warning) _Cleaner_cleanMesh: NULL MeshCleaner\n"); return NULL; }
	return cleaner->cleanMesh(mesh);
}
#pragma endregion

#pragma region FRACTURETOOL_FUNCTIONS
/*
FractureTool Virtual Functions
*/
 void _FractureTool_Release(FractureTool* tool)
{
	if (!tool) { printf("(Warning) _FractureTool_Release: NULL tool\n"); return; }
	tool->release();
}

 void _FractureTool_setRemoveIslands(FractureTool* tool, bool remove)
{
	if (!tool) { printf("(Warning) _FractureTool_setMesh: NULL tool\n"); return; }
	tool->setRemoveIslands(remove);
}

 void _FractureTool_setSourceMesh(FractureTool* tool, Mesh* mesh)
{
	if (!mesh) { printf("(Warning) _FractureTool_setMesh: NULL mesh\n"); return; }
	if (!tool) { printf("(Warning) _FractureTool_setMesh: NULL tool\n"); return; }
	tool->setSourceMeshes(&mesh, 1);
}

 bool _FractureTool_voronoiFracturing(FractureTool* tool, uint32_t chunkId, VoronoiSitesGenerator* vsg)
{
	if (!vsg) { printf("(Warning) _FractureTool_voronoiFracturing: NULL vsg\n"); return false; }
	if (!tool) { printf("(Warning) _FractureTool_voronoiFracturing: NULL tool\n"); return false; }

	const NvcVec3* sites = nullptr;
	uint32_t sitesCount = vsg->getVoronoiSites(sites);

	return tool->voronoiFracturing(chunkId, sitesCount, sites, false);
}

 bool _FractureTool_slicing(FractureTool* tool, int chunkId, SlicingConfiguration* conf, bool replaceChunk)
{
	if (!tool) { printf("(Warning) _FractureTool_slicing: NULL tool\n"); return NULL; }

	return tool->slicing(chunkId, *conf, replaceChunk, &rnd);
}

 void _FractureTool_finalizeFracturing(FractureTool* tool)
{
	if (!tool) { printf("(Warning) _FractureTool_finalizeFracturing: NULL tool\n"); return; }

	tool->finalizeFracturing();
}

// AuthoringResult* _FractureTool_finalizeWithResult(FractureTool* tool)
//{
//	if (!tool) { printf("(Warning) _FractureTool_finalizeFracturing: NULL tool\n"); return NULL; }
//
//	Nv::Blast::AuthoringResult* result = NvBlastExtAuthoringProcessFracture(*tool, *bondGenerator, *collisionBuilder, collisionParameter);
//
//	return result;
//}

 uint32_t _FractureTool_getChunkCount(FractureTool* tool)
{
	if (!tool) { printf("(Warning) _FractureTool_getChunkCount: NULL tool\n"); return 0; }

	return tool->getChunkCount();
}

 Mesh* _FractureTool_getChunkMesh(FractureTool* tool, int chunkId, bool inside)
{
	if (!tool) { printf("(Warning) _FractureTool_getChunkMesh: NULL tool\n"); return NULL; }

	//tool->getBufferedBaseMeshes()

	Triangle* tris;
	uint32_t s = tool->getBaseMesh(chunkId, tris);

	NvcVec3* pos = new NvcVec3[s * 3];
	NvcVec3* norm = new NvcVec3[s * 3];
    NvcVec2* uv = new NvcVec2[s * 3 * 4];

	//uint32_t* idx = new uint32_t[s * 3];
	vector<uint32_t> idx;

	for (uint32_t i = 0; i < s; i++)
    {
        pos[i * 3 + 0] = tris[i].a.p;
        pos[i * 3 + 1] = tris[i].b.p;
        pos[i * 3 + 2] = tris[i].c.p;

        norm[i * 3 + 0] = tris[i].a.n;
        norm[i * 3 + 1] = tris[i].b.n;
        norm[i * 3 + 2] = tris[i].c.n;

        for (uint32_t j = 0; j < 4; j++) {
            uv[j * s * 3 + i * 3 + 0] = tris[i].a.uv[j];
            uv[j * s * 3 + i * 3 + 1] = tris[i].b.uv[j];
            uv[j * s *3 + i * 3 + 2] = tris[i].c.uv[j];
        }

		if (inside && tris[i].materialId == Nv::Blast::kMaterialInteriorId)
		{
			idx.push_back(i * 3 + 0);
			idx.push_back(i * 3 + 1);
			idx.push_back(i * 3 + 2);
		}
		if (!inside && tris[i].materialId != Nv::Blast::kMaterialInteriorId)
		{
			idx.push_back(i * 3 + 0);
			idx.push_back(i * 3 + 1);
			idx.push_back(i * 3 + 2);
		}
		//idx[i * 3 + 0] = i * 3 + 0;
		//idx[i * 3 + 1] = i * 3 + 1;
		//idx[i * 3 + 2] = i * 3 + 2;
	}
	return NvBlastExtAuthoringCreateMesh(pos, norm, uv, s * 3, idx.data(), idx.size());

	//return tool->createChunkMesh(chunkId);
}

#pragma endregion

#pragma region VORONOISITES_FUNCTIONS
/*
NvVoronoiSitesGenerator Virtual Functions
*/
 void _NvVoronoiSitesGenerator_Release(VoronoiSitesGenerator* tool)
{
	if (!tool) { printf("(Warning) _NvVoronoiSitesGenerator_Release: NULL tool\n"); return; }

	tool->release();
}

 VoronoiSitesGenerator* _VoronoiSitesGenerator_Create(Mesh* mesh)
{
	return NvBlastExtAuthoringCreateVoronoiSitesGenerator(mesh, &rnd);
}

 void _NvVoronoiSitesGenerator_uniformlyGenerateSitesInMesh(VoronoiSitesGenerator* tool, int count)
{
	if (!tool) { printf("(Warning) _NvVoronoiSitesGenerator_uniformlyGenerateSitesInMesh: NULL tool\n"); return; }
	tool->uniformlyGenerateSitesInMesh(count);
}

 void _NvVoronoiSitesGenerator_clusteredSitesGeneration(VoronoiSitesGenerator* tool, uint32_t numberOfClusters, uint32_t sitesPerCluster, float clusterRadius)
{
	if (!tool) { printf("(Warning) _NvVoronoiSitesGenerator_clusteredSitesGeneration: NULL tool\n"); return; }
	tool->clusteredSitesGeneration(numberOfClusters, sitesPerCluster, clusterRadius);
}

 void _NvVoronoiSitesGenerator_addSite(VoronoiSitesGenerator* tool, NvcVec3* site)
{
	if (!tool) { printf("(Warning) _NvVoronoiSitesGenerator_addSite: NULL tool\n"); return; }
	tool->addSite(*site);
}

 uint32_t _NvVoronoiSitesGenerator_getSitesCount(VoronoiSitesGenerator* tool)
{
	if (!tool) { printf("(Warning) _NvVoronoiSitesGenerator_getSiteCount: NULL tool\n"); return 0; }

	const NvcVec3* sites;
	return tool->getVoronoiSites(sites);
}

 void _NvVoronoiSitesGenerator_getSites(VoronoiSitesGenerator* tool, void* arr)
{
	if (!tool) { printf("(Warning) _NvVoronoiSitesGenerator_getSiteCount: NULL tool\n"); return; }

	NvcVec3* vertArr = (NvcVec3*)arr;

	const NvcVec3* sites;
	uint32_t total = tool->getVoronoiSites(sites);
	for (uint32_t i = 0; i < total; i++)
	{
		vertArr[i] = sites[i];
	}
}

#pragma endregion

