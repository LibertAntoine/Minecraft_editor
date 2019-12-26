#include "Gridv2.h"

namespace form {

  // NOTE: Vertex positions are expressed w/o the z index because the ground is flat and it would be redundant
  Gridv2::Gridv2(const int &half_size, const glm::vec3 &color)
    :m_color(color),
    m_size(half_size*2)
  {
    //for ( int i = -half_size; i < half_size; i++ ) {
    //  m_datas.push_back(glm::vec2(-half_size, i));
    //  m_datas.push_back(glm::vec2(half_size, i));
    //  m_datas.push_back(glm::vec2(i, -half_size));
    //  m_datas.push_back(glm::vec2(i, half_size));
    //}
    for ( int x = -half_size; x <= half_size; x++ ) {
      for ( int y = -half_size; y <= half_size; y++ ) {
        m_datas.push_back(x);
        m_datas.push_back(y);
      }
    }

    // NOTE: Drawing order in the index buffer
    //   1,4 - - 5
    //   | . # # |
    //   | # . # |
    //   | # # . |
    //   0 - - - 2,3
    //

    for ( int x = 0; x < half_size * 2; x++ ) {
      for ( int y = 0; y < half_size * 2; y++ ) {
        // Lower left square triangle
        m_indices.push_back((x * ( half_size * 2 + 1 )) + y);
        m_indices.push_back((x * ( half_size * 2 + 1 )) + y + 1);
        m_indices.push_back((x * ( half_size * 2 + 1 )) + ( half_size * 2 + 1) + y ); // Go to next column

        // Upper right square triangle
        m_indices.push_back((x * ( half_size * 2 + 1 )) + ( half_size * 2 + 1) + y );
        m_indices.push_back((x * ( half_size * 2 + 1 )) + ( half_size * 2 + 1) + y + 1 ); 
        m_indices.push_back((x * ( half_size * 2 + 1 )) + y + 1);
      }
    }

  }
  Gridv2::~Gridv2() {}
}
