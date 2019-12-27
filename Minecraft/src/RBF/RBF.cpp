#include "RBF.h"

RBF::RBF(std::vector<std::pair<glm::vec3, double>> controlPoints)
  :m_rbf(m_gaussian)
{
  for (auto controlPoint : controlPoints) {
    Eigen::Vector3i pointCoords(controlPoint.first.x, controlPoint.first.y, controlPoint.first.z);
    m_ControlPoints.push_back(std::tuple<Eigen::Vector3i, double, double>(pointCoords, controlPoint.second, 0.f));
  }
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

void RBF::updateEpsilon(const double newEpsilon)
{
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
  for ( int i = 0; i < m_ControlPoints.size() ; i++ ) {
    for ( int j = 0; j < m_ControlPoints.size(); j++ ) {
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
  for ( int i = 0; i < m_ControlPoints.size(); i++ ) {
    solutions(i) = std::get<1>(m_ControlPoints[i]);
  }
  omega = phis.colPivHouseholderQr().solve(solutions);
  for ( int i = 0; i < solutions.size(); i++ ) {
    std::get<2>(m_ControlPoints[i]) = solutions(i);
  }
}

double RBF::getScalar(const glm::vec3& position) const
{
  double scalar = 0;
  Eigen::Vector3i positionVector(position.x, position.y, position.z);
  for ( int i = 0; i < m_ControlPoints.size(); i++ ) {
    scalar += std::get<2>(m_ControlPoints[i]) * m_rbf(computeDistance(positionVector, std::get<0>( m_ControlPoints[i] )));
  }
  return scalar;
}
