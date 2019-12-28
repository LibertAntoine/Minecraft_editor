#include "RBF.h"
#include <iostream>
#include <iomanip>
#include "glm/glm.hpp"

int main( int argc, char *argv[] )
{
  //std::vector<std::pair<glm::vec3, double>> controlPoints;
  //controlPoints.push_back(std::make_pair(glm::vec3(0,0,0), 1));
  //controlPoints.push_back(std::make_pair(glm::vec3(1,1,1), 7));
  //controlPoints.push_back(std::make_pair(glm::vec3(1,6,1), 17));

  RBF rbf(argv[1]);
  //RBF rbf(controlPoints);
  rbf.solveOmegas();

  /*
  glm::vec3 test;
  test.x = atof( argv[1] );
  test.y = atof( argv[2] );
  test.z = atof( argv[3] );
  */

  /*
  while ( true ) {
    glm::vec3 point;
    std::cout << "values: ";
    std::cin >> point.x;
    std::cin >> point.y;
    std::cin >> point.z;
    std::cout << std::boolalpha << rbf.isThereACubeHere(point) << std::endl;
    std::cout << std::endl;
  }
  */


  /*
  int count = 0;
  double highest;
  double lowest = 0;
  std::vector<double> values;
  values.reserve(20 * 200 * 10);


  for ( int i = 0; i < 20; i++ ) {
    for ( int j = 0; j < 200; j++ ) {
      for ( int z = 0; z < 10; z++ ) {
        double value = rbf.getScalar(glm::vec3(i, j, z));
        values.push_back(value);
        if ( i == 0 && j == 0 && z == 0 ) {
          lowest = value;
          highest = value;
        } else {
          if ( value > highest ) {
            highest = value;
          } else if (value < lowest) {
            lowest = value;
          }
        }
        if ( value <= 0 ) {
          count++;
        }
      }
    }
  }

  double step = ( highest - lowest ) / 4;
  double range1 = 0;
  double range2 = 0;
  double range3 = 0;
  for (auto value : values) {
    if ( value <= step ) {
      range1++;
    } else if ( value <= step * 2 ) {
      range2++;
    } else if ( value <= step*3 ) {
      range3++;
    }
  }
  */

  int count = 0;
  for ( int i = 0; i < 200; i++ ) {
    for ( int j = 0; j < 200; j++ ) {
      for ( int z = 0; z < 10; z++ ) {
        bool cube = rbf.isThereACubeHere(glm::vec3(i, j, z));
        if ( cube ) {
          count++;
        }
      }
    }
  }

  //std::cout << rbf.getScalar(glm::vec3(0,0,0)) << std::endl;
  //rbf.switchRBFtoUseless();
  //rbf.solveOmegas();
  //std::cout << rbf.getScalar(test) << std::endl;
  return 0;
}
