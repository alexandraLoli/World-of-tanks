#include <iostream>
#include "core/gpu/mesh.h";
#include "utils/glm_utils.h"
using namespace std;
using namespace glm;

namespace utils {
	
	bool collisions(vec3 tank1, vec3 tank2, float raza) {
		float distance = sqrt(pow(tank1.x - tank2.x, 2) + pow(tank1.z - tank2.z, 2));
		if (distance < 2 * raza)
			return true;
		else
			return false;
	}
}