/**
 * se3.hpp
 *  Copyright 2014, Gareth Cross. All Rights Reserved.
 */

#ifndef SE3_HPP
#define SE3_HPP

#include <Eigen/Dense>
#include <boost/optional.hpp>

namespace vo {
namespace se3 {

/**
 * @brief Skew-symmetry operator. Convert from vector in R3 to skew-symmetric
 * 3x3 matrix.
 * @return 3x3 matrix
 */
template <typename Scalar>
Eigen::Matrix<Scalar,3,3> skew(const Eigen::Matrix<Scalar,3,1>& v) {
  Eigen::Matrix<Scalar,3,3> V;
  V << 0, -v[2], v[1],
       v[2], 0, -v[0],
      -v[1], v[0], 0;
  return V;
}

/**
 * @brief Compute the R, V and V-inverse matrices reqiured for the exp() and
 * log() operations.
 * 
 * @param R [Optional output] R matrix
 * @param V [Optional output] V matrix
 * @param Vinv [Optional output] V inverse matrix
 * 
 * @note These formulae are copied from:
 * 
 * "Lie Groups for 2D and 3D Transformations", Ethan Eade, last accesible from:
 * 
 *    http://ethaneade.com/lie.pdf
 * 
 * The small-angle approximations were determined by taking limits theta -> 0
 * in MATLAB.
 */
template <typename Scalar>
void computeRV(const Eigen::Matrix<Scalar,3,1>& w,
               boost::optional<Eigen::Matrix<Scalar,3,3>&> R = boost::none,
               boost::optional<Eigen::Matrix<Scalar,3,3>&> V = boost::none,
               boost::optional<Eigen::Matrix<Scalar,3,3>&> Vinv = boost::none) {
  const static auto I3(Eigen::Matrix<Scalar,3,3>::Identity());
  const auto theta = w.norm();
  const auto S = skew(w);
  
  Scalar A,B,C,coeff;
  //  check if the approximation is valid, for theta < 1deg
  if (theta < M_PI / 180) {
    A = 1;
    B = 0.5;
    C = 1 / 6.0;
    coeff = 1 / 12.0;
  } else {
    //  otherwise rodrigues formula
    A = std::sin(theta) / theta;
    B = (1 - std::cos(theta)) / (theta*theta);
    C = (1 - A) / (theta*theta);
    coeff = (1 - A/(2*B)) / (theta * theta);
  }
  if (R) {
    *R = I3 + S*A + S*S*B;
  }
  if (V) {
    *V = I3 + S*B + S*S*C;
  }
  if (Vinv) {
    *Vinv = I3 - S*0.5 + S*S*coeff;
  }
}

/**
 * @brief Compute the log() operation. Performs the conversion SE(3) -> se(3).
 * 
 * @param SE3 4x4 matrix belonging to SE(3).
 * @return 6x1 twist vector: [u,w]
 */
template <typename Scalar>
static Eigen::Matrix<Scalar,6,1> log(const Eigen::Matrix<Scalar,4,4>& SE3) {
  //  get rotation axis & angle
  const Eigen::AngleAxis<Scalar> aa(SE3.template topLeftCorner<3,3>());
  const Eigen::Matrix<Scalar,3,1> rvec = aa.axis() * aa.angle();
  //  solve for translation
  Eigen::Matrix<Scalar,3,3> Vinv;
  computeRV<Scalar>(rvec, boost::none, boost::none, Vinv);
  //  form twist vector [u,w]
  Eigen::Matrix<Scalar,6,1> twist;
  twist << Vinv * SE3.template topRightCorner<3,1>(), rvec;
  return twist;
}

/**
 * @brief Compute the exp() operation. Performs the conversion se(3) -> SE(3).
 * 
 * @param twist 6x1 twist vector: [u,w]
 * @return SE3 4x4 matrix belonging to SE(3).
 */
template <typename Scalar>
Eigen::Matrix<Scalar,4,4> exp(const Eigen::Matrix<Scalar,6,1>& twist) {
  Eigen::Matrix<Scalar,4,4> H;
  H.setZero();
  //  execute rodrigues formula
  Eigen::Matrix<Scalar,3,3> R,V;
  computeRV<Scalar>(twist.template tail<3>(), R, V);
  H.template block<3,3>(0,0) = R;
  H.template block<3,1>(0,3) = V * twist.template head<3>();
  H(3,3) = 1;
  return H;
}

} //  namespace se3
} //  namespace vo

#endif // SE3_HPP
