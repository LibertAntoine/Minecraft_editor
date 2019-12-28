#include "RBF.h"

// TODO: Find available rbf files automatically
// NOTE: Windows and Linux must have specific code for directory searching
RBF::RBF()
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
  double distance = ( pointB - pointA ).norm();
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
  Eigen::VectorXd solutions(phis.rows());
  for ( size_t i = 0; i < m_ControlPoints.size(); i++ ) {
    solutions(i) = std::get<1>(m_ControlPoints[i]);
  }
  omega = phis.colPivHouseholderQr().solve(solutions);
  for ( long int i = 0; i < solutions.size(); i++ ) {
    std::get<2>(m_ControlPoints[i]) = solutions(i);
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
  double chances = this->getScalar(position);
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  // Select a random generator engine
  std::default_random_engine generator(seed);
  // uniform real distribution
  std::uniform_real_distribution<double> uniformRealDistribution(0, abs( chances * 0.5 ));

  if ( chances < 0 ) {
    cube = false;
    if ( trunc( uniformRealDistribution(generator) ) ) {
      cube = true;
    } 
  }
  else {
    cube = true;
    if ( trunc( uniformRealDistribution(generator) ) ) {
      cube = false;
    } 
  }

  return cube;
}

