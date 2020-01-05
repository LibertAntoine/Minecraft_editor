#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <eigen3/Eigen/Dense>
#include <random>
#include <chrono>
#include <math.h>
#include <math.h>

#include "glm/glm.hpp"

namespace RBF_CALLBACKS
{
  struct Useless
  {
    double operator()(const double d) {
      return d;
    }
  };

  struct MultiQuadratic
  {
    double m_epsilon = 1.0;

    double operator()(const double d) {
      return sqrt(1.0 + pow( m_epsilon * d, 2 ));
    }
  };

  struct InverseQuadratic
  {
    double m_epsilon = 1.0;

    double operator()(const double d) {
      return 1.0 / (1.0 + pow( m_epsilon * d, 2 ));
    }
  };

  struct Gaussian
  {
    double m_epsilon = 1.0;

    double operator()(const double d) {
      return exp(-m_epsilon * d * d);
    }
  };
};

class RBF 
{
  private:
    std::vector<std::tuple<Eigen::Vector3i, double, double>> m_ControlPoints;
    std::vector<glm::ivec3> m_Boundaries;

    RBF_CALLBACKS::InverseQuadratic m_inverseQuadratic;
    RBF_CALLBACKS::MultiQuadratic m_multiQuadratic;
    RBF_CALLBACKS::Gaussian m_gaussian;
    RBF_CALLBACKS::Useless m_useless;

    std::function<double(double)> m_rbf;

    double m_epsilon = 1.0;

		double m_minVal;
		double m_maxVal;

		bool m_useProbability = true;

  public:
    //std::string m_FilePath;
    // TODO: use getters and setters instead of sharing it everywhere
    int m_RBFFileId;
    std::vector<std::string> m_FilePaths;

    RBF();

    RBF(std::vector<std::pair<glm::vec3, double>> controlPoints);
    RBF(const std::string& filepath); /// @brief automatically parse a RBF file and load properties into class

    double computeDistance(const Eigen::Vector3i& pointA, const Eigen::Vector3i& pointB) const;
    void findOmega();
    Eigen::MatrixXd phiMatrix();

    void solveOmegas(); /// @brief Method to call in order to use the new RBF function parameters

    void addFilePath(const std::string& newFilePath);

    /// @brief switch the function pointer responsible for calculating the RBF
    void switchRBFtoInverseQuadratic();
    void switchRBFtoUseless();
    void switchRBFtoMultiQuadratic();
    void switchRBFtoGaussian();
    
    /// @brief overload with epsilon update
    void switchRBFtoInverseQuadratic(const double epsilon);
    void switchRBFtoUseless(const double epsilon);
    void switchRBFtoMultiQuadratic(const double epsilon);
    void switchRBFtoGaussian(const double epsilon);

    double getScalar(const glm::vec3& position) const; /// @brief Compute the output scalar value of the current RBF function

		/**
		 * \brief Return the first terrain generator boundary
		 */
		glm::ivec3 getBoundaryA() const;
		/**
		 * \brief Return the second terrain generator boundary
		 */
		glm::ivec3 getBoundaryB() const;

    bool isThereACubeHere(const glm::vec3& position) const; /// @brief Determine the presence of a cube at a certain location using random and RBF value

    void updateEpsilon(const double newEpsilon);

    //void applyRBF() const;
    void parseSelectedRBFFile(); /// @brief Parse RBF file specified in m_FilePaths at index m_RBFFileId

};
