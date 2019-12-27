#include "RBF.h"
#include <iostream>
#include "glm/glm.hpp"

int main( int argc, char *argv[] )
{
  std::vector<std::pair<glm::vec3, double>> controlPoints;
  controlPoints.push_back(std::make_pair(glm::vec3(0,0,0), 12));
  controlPoints.push_back(std::make_pair(glm::vec3(1,1,1), 7));
  controlPoints.push_back(std::make_pair(glm::vec3(1,6,1), 17));

  RBF rbf(controlPoints);
  rbf.solveOmegas();

  glm::vec3 test;
  test.x = atof( argv[1] );
  test.y = atof( argv[2] );
  test.z = atof( argv[3] );

  std::cout << rbf.getScalar(test) << std::endl;
  return 0;
}
