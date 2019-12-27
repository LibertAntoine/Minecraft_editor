#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <eigen3/Eigen/Dense>

#include "glm/glm.hpp"

class RBF 
{
  private:
    std::string m_FilePath;
    std::vector<std::tuple<Eigen::Vector3i, double, double>> m_ControlPoints;
    std::vector<glm::vec3> m_Boundaries;

  public:
    RBF(std::vector<std::pair<glm::vec3, double>> controlPoints);
    //RBF(const std::string& filepath);
    //
    double computeDistance(const Eigen::Vector3i& pointA, const Eigen::Vector3i& pointB) const;
    void findOmega();
    Eigen::MatrixXd phiMatrix();

    void solveOmegas();

    double getScalar(const glm::vec3& position, const double epsilon = 1.0) const;

    static double useless(const double d);
    static double multiQuadratic(const double d, const double epsilon = 1.0);
    static double inverseQuadratic(const double d, const double epsilon = 1.0);
    static double gaussian(const double d, const double epsilon = 1.0);
};
