
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

using namespace std;

namespace createObjects {

	Mesh* createTrack(glm::vec3 color, float scale, string name);
	Mesh* createBody(glm::vec3 color, float scale, string name);
	Mesh* createTurret(glm::vec3 color, float scale, string name);
	Mesh* createCannon(glm::vec3 color, float scale, string name);
	Mesh* createGround(glm::vec3 color, float scale);
	Mesh* createPPP1(glm::vec3 color, float scale, string name);
	Mesh* createPPP2(glm::vec3 color, float scale, string name);
	Mesh* createPPP3(glm::vec3 color, float scale, string name);
}
