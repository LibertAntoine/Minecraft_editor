#include "RBF.h"

// TODO: Find available rbf files automatically
// NOTE: Windows and Linux must have specific code for directory searching
RBF::RBF()
  :m_rbf(m_useless)
{
  m_FilePaths.push_back("res/rbf1.txt");
  m_FilePaths.push_back("res/rbf2.txt");
  m_FilePaths.push_back("res/rbf3.txt");
  m_RBFFileId = 0;
}

RBF::RBF(std::vector<std::pair<glm::vec3, double>> controlPoints)
  :m_rbf(m_useless)
{
  for (auto controlPoint : controlPoints) {
    Eigen::Vector3i pointCoords(controlPoint.first.x, controlPoint.first.y, controlPoint.first.z);
    m_ControlPoints.push_back(std::tuple<Eigen::Vector3i, double, double>(pointCoords, controlPoint.second, 0.0));
  }
}

RBF::RBF(const std::string& filepath)
  :m_rbf(m_useless)
{
  std::ifstream stream(filepath);
  enum class DataType { NONE = -1, BOUNDARIES = 0, CONTROL_POINTS = 1, RBF = 2};
  DataType type = DataType::NONE;
  std::string line;

  m_Boundaries.clear();
  m_ControlPoints.clear();
  while (std::getline(stream, line)) {
    if (line.find("#boundaries") != std::string::npos) {
        type = DataType::BOUNDARIES;
    }
    else if (line.find("#controlpoints") != std::string::npos) {
        type = DataType::CONTROL_POINTS;
    }
    else if (line.find("#rbf") != std::string::npos) {
        type = DataType::RBF;
    }

    else if (type != DataType::NONE && line != ""){
      std::stringstream streamRBF(line);

      if ( type == DataType::BOUNDARIES ) {
        glm::ivec3 point;
        streamRBF >> point.x;
        streamRBF >> point.y;
        streamRBF >> point.z;

        m_Boundaries.push_back(point);
      }
      else if ( type == DataType::CONTROL_POINTS ) {
        Eigen::Vector3i point;
        double weight;
        streamRBF >> point(0);
        streamRBF >> point(1);
        streamRBF >> point(2);

        streamRBF >> weight;
				if ( m_ControlPoints.size() == 0 ) {
					m_minVal = weight;
					m_maxVal = weight;
				}
				else {
				  if ( m_minVal > weight ) {
						m_minVal = weight;
				  }
					else if ( m_maxVal < weight ) {
						m_maxVal = weight;
					}
				}
        m_ControlPoints.push_back(std::tuple<Eigen::Vector3i, double, double>(point, weight, 0.0));
      }
      else if ( type == DataType::RBF ) {
        std::string rbf;

        streamRBF >> rbf;
        if ( rbf == "gaussian" ) {
          this->switchRBFtoGaussian();
        } else if ( rbf == "multiquadratic" ) {
          this->switchRBFtoMultiQuadratic();
        } else if ( rbf == "inversquadratic" ) {
          this->switchRBFtoInverseQuadratic();
        } else {
          this->switchRBFtoUseless();
        }

        if ( streamRBF ) {
          double epsilon;
          streamRBF >> epsilon;
          this->updateEpsilon(epsilon);
        }
      }
    }
  }
}

void RBF::addFilePath(const std::string& newFilePath)
{
  m_FilePaths.push_back(newFilePath);
}

void RBF::switchRBFtoInverseQuadratic() { m_rbf = m_inverseQuadratic; }
void RBF::switchRBFtoUseless() { m_rbf = m_useless; }
void RBF::switchRBFtoMultiQuadratic() { m_rbf = m_multiQuadratic; }
void RBF::switchRBFtoGaussian() { m_rbf = m_gaussian; }

void RBF::switchRBFtoInverseQuadratic(const double epsilon)
{
  m_rbf = m_inverseQuadratic;
  this->updateEpsilon(epsilon);
}
void RBF::switchRBFtoUseless(const double epsilon)
{
  m_rbf = m_useless;
  this->updateEpsilon(epsilon);
}
void RBF::switchRBFtoMultiQuadratic(const double epsilon)
{
  m_rbf = m_multiQuadratic;
  this->updateEpsilon(epsilon);
}
void RBF::switchRBFtoGaussian(const double epsilon)
{
  m_rbf = m_gaussian;
  this->updateEpsilon(epsilon);
}

void RBF::parseSelectedRBFFile()
{
  std::ifstream stream(m_FilePaths[m_RBFFileId]);
  enum class DataType { NONE = -1, BOUNDARIES = 0, CONTROL_POINTS = 1, RBF = 2};
  DataType type = DataType::NONE;
  std::string line;
	// NOTE: Reset state to normal, do not append
  m_Boundaries.clear();
  m_ControlPoints.clear();
	m_useProbability = true;

  while (std::getline(stream, line)) {
    if (line.find("#boundaries") != std::string::npos) {
        type = DataType::BOUNDARIES;
    }
		else if ( line.find("#noproba") != std::string::npos ) {
			m_useProbability = false;
		}
    else if (line.find("#controlpoints") != std::string::npos) {
        type = DataType::CONTROL_POINTS;
    }
    else if (line.find("#rbf") != std::string::npos) {
        type = DataType::RBF;
    }

    else if (type != DataType::NONE && line != ""){
      std::stringstream streamRBF(line);

      if ( type == DataType::BOUNDARIES ) {
        glm::vec3 point;
        streamRBF >> point.x;
        streamRBF >> point.y;
        streamRBF >> point.z;

        m_Boundaries.push_back(point);
      }
      else if ( type == DataType::CONTROL_POINTS ) {
        Eigen::Vector3i point;
        double weight;
        streamRBF >> point(0);
        streamRBF >> point(1);
        streamRBF >> point(2);

        streamRBF >> weight;

				if ( m_ControlPoints.size() == 0 ) {
					m_minVal = weight;
					m_maxVal = weight;
				}
				else {
				  if ( weight < m_minVal ) {
						m_minVal = weight;
				  }
					else if ( weight > m_maxVal ) {
						m_maxVal = weight;
					}
				}
        m_ControlPoints.push_back(std::tuple<Eigen::Vector3i, double, double>(point, weight, 0.0));
      }
      else if ( type == DataType::RBF ) {
        std::string rbf;

        streamRBF >> rbf;
        if ( rbf == "gaussian" ) {
          this->switchRBFtoGaussian();
        } else if ( rbf == "multiquadratic" ) {
          this->switchRBFtoMultiQuadratic();
        } else if ( rbf == "inversquadratic" ) {
          this->switchRBFtoInverseQuadratic();
        } else {
          this->switchRBFtoUseless();
        }

        if ( streamRBF ) {
          double epsilon;
          streamRBF >> epsilon;
          this->updateEpsilon(epsilon);
        }
      }
    }
  }
}

void RBF::updateEpsilon(const double newEpsilon)
{
  m_epsilon = newEpsilon;
  m_gaussian.m_epsilon = newEpsilon;
  m_multiQuadratic.m_epsilon = newEpsilon;
  m_inverseQuadratic.m_epsilon = newEpsilon;
}

double RBF::computeDistance(const Eigen::Vector3i& pointA, const Eigen::Vector3i& pointB) const
{
	Eigen::Vector3d pointAd = pointA.cast<double>();
	Eigen::Vector3d pointBd = pointB.cast<double>();

  double distance = ( pointAd - pointBd ).norm();
  return distance;
}

Eigen::MatrixXd RBF::phiMatrix()
{
  Eigen::MatrixXd phis(m_ControlPoints.size(), m_ControlPoints.size());
  for ( size_t i = 0; i < m_ControlPoints.size() ; i++ ) {
    for ( size_t j = 0; j < m_ControlPoints.size(); j++ ) {
      phis(i, j) = m_rbf(computeDistance(std::get<0>( m_ControlPoints[i] ), std::get<0>( m_ControlPoints[j] )));
    }
  }
  return phis;
}

void RBF::solveOmegas()
{
  Eigen::MatrixXd phis = phiMatrix();
  Eigen::VectorXd omega(phis.rows());
  Eigen::VectorXd weights(phis.rows());
  for ( size_t i = 0; i < m_ControlPoints.size(); i++ ) {
    weights(i) = std::get<1>(m_ControlPoints[i]);
  }
  omega = phis.colPivHouseholderQr().solve(weights);
  for ( long int i = 0; i < weights.size(); i++ ) {
    std::get<2>(m_ControlPoints[i]) = omega(i);
  }
}

double RBF::getScalar(const glm::vec3& position) const
{
  double scalar = 0;
  Eigen::Vector3i positionVector(position.x, position.y, position.z);
  for ( size_t i = 0; i < m_ControlPoints.size(); i++ ) {
    scalar += std::get<2>(m_ControlPoints[i]) * m_rbf(computeDistance(positionVector, std::get<0>( m_ControlPoints[i] )));
  }
  return scalar;
}

bool RBF::isThereACubeHere(const glm::vec3& position) const
{
  bool cube;
  double scalar = this->getScalar(position);
	if ( m_useProbability ) {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		// Select a random generator engine
		std::default_random_engine m_Generator(seed);
		std::uniform_real_distribution<double> RealDistribution(0, 1);
		double random_value = RealDistribution(m_Generator);

		if ( scalar < 0 ) {
			double chance_ratio = scalar / m_minVal;

			if ( random_value <= abs( chance_ratio ) ) {
				cube = true;
			} 
			else {
				cube = false;
			}
		}
		else {
			double chance_ratio = scalar / m_maxVal;

			if ( random_value > abs( chance_ratio ) ) {
				cube = true;
			} 
			else {
				cube = false;
			}
		}
  } 
	// NOTE: Simple RBF interpolation
	else {
    if ( scalar > 0) {
			return true;
    }
		else {
		  return false;
		}
  }

  return cube;
}

glm::ivec3 RBF::getBoundaryA() const
{
	glm::ivec3 boundA(-10, 0, -10);
	if ( m_Boundaries.size() >= 2 ) {
		boundA = m_Boundaries[m_Boundaries.size() -2]; 
	}
	return boundA;
}

glm::ivec3 RBF::getBoundaryB() const
{
	glm::ivec3 boundB(10, 10, 10);
	if ( m_Boundaries.size() >= 2 ) {
		boundB = m_Boundaries[m_Boundaries.size() -1]; 
	}
	return boundB;
}

