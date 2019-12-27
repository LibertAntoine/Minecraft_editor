#include "RBF.h"

RBF::RBF(std::vector<std::pair<glm::vec3, double>> controlPoints)
{
  for (auto controlPoint : controlPoints) {
    Eigen::Vector3i pointCoords(controlPoint.first.x, controlPoint.first.y, controlPoint.first.z);
    m_ControlPoints.push_back(std::tuple<Eigen::Vector3i, double, double>(pointCoords, controlPoint.second, 0.f));
  }
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
      phis(i, j) = multiQuadratic(computeDistance(std::get<0>( m_ControlPoints[i] ), std::get<0>( m_ControlPoints[j] )));
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

double RBF::getScalar(const glm::vec3& position, const double epsilon) const
{
  double scalar = 0;
  Eigen::Vector3i positionVector(position.x, position.y, position.z);
  for ( int i = 0; i < m_ControlPoints.size(); i++ ) {
    scalar += std::get<2>(m_ControlPoints[i]) * multiQuadratic(computeDistance(positionVector, std::get<0>( m_ControlPoints[i] )));
  }
  return scalar;
}

double RBF::useless(const double d)
{
  return d;
}

double RBF::multiQuadratic(const double d, const double epsilon)
{
  return sqrt(1.0 + pow( epsilon * d, 2 ));
}

double RBF::inverseQuadratic(const double d, const double epsilon)
{
  return 1.0 / (1.0 + pow( epsilon * d, 2 ));
}

double RBF::gaussian(const double d, const double epsilon)
{
  return exp(-epsilon * d * d);
}
