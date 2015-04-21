/**
 * pose.hpp
 *  Copyright 2014, Gareth Cross. All Rights Reserved.
 */

#ifndef POSE_HPP
#define POSE_HPP

#include <vo_utils/base.hpp>
#include <vo_utils/se3.hpp>

#include <Eigen/Dense>

#ifdef VO_BUILD_ROS
# include <geometry_msgs/Pose.h>
# include <geometry_msgs/TransformStamped.h>
#endif

namespace vo {

/**
 * @brief Stores a rigid transformation (or pose) in R3. The translation
 * is represented by a vector in R3, while the rotation representation is
 * specified by the user with `RotationType`.
 *
 * Jacobians are determined by approximating the pose in SE(3) as a
 * mean and a perturbation:
 *
 * H' = [I4 + [w,u]^] * H
 *
 * Where `H` is the mean (a 4x4 matrix) and `[w,u]^` performs the first order
 * approximation of the exponential map from se(3) to SE(3).
 *
 * Derivatives are taken with respect to `w` (small rotation) and `u` (small
 * translation).
 *
 * @param RotationType Underlying type used to represent the rotation component
 * of the pose. Must conform to the Eigen::RotationBase interface.
 */
template <class RotationType>
class PoseT {
public:
  typedef typename RotationType::Scalar Scalar;

  using Vec3 = Eigen::Matrix<Scalar,3,1>;
  using Mat3 = Eigen::Matrix<Scalar,3,3>;
  using Mat4 = Eigen::Matrix<Scalar,4,4>;
  using Mat6 = Eigen::Matrix<Scalar,6,6>;
  using Mat3x6 = Eigen::Matrix<Scalar,3,6>;
  using Quat = Eigen::Quaternion<Scalar>;

  /**
   * @brief Construct identity pose.
   */
  PoseT() : rot_(RotationType::Identity()), t_(0,0,0) {}

  /**
   * @brief Construct a pose from a abstract rotation representation and a
   * translation vector.
   *
   * @param rot Instance of Eigen::RotationBase
   * @param t 3x1 translation vector.
   *
   * @note If the RotationType is quaternion, the input quaternion will be
   * normalized.
   */
  template <typename Derived, int _Dim>
  PoseT(const Eigen::RotationBase<Derived,_Dim>& rot, const Vec3& t) :
    rot_(rot.derived()), t_(t) {
    normalizeRotation(rot_);
  }

  /**
   * @brief Copy constructor.
   *
   * @param pose Instance of another pose.
   * @note This constructor automatically converts the `Scalar` type.
   */
  template <typename RotationType_>
  PoseT(const PoseT<RotationType_>& pose) :
    PoseT(pose.rot().template cast<Scalar>(),
          pose.t().template cast<Scalar>()) {}

  /**
   * @brief Construct a pose from a 3x3 rotation matrix and a 3x1 translation
   * vector. Resulting pose has corresponding SE(3) transformation: H = [R | t]
   *
   * @param R 3x3 rotation matrix.
   * @param t 3x1 translation vector.
   *
   * @note If the RotationType is quaternion, the input quaternion will be
   * normalized.
   */
  PoseT(const Mat3& R, const Vec3& t) : rot_(R), t_(t) {
    normalizeRotation(rot_);
  }

  /**
   * @brief Construct a pose from a 4x4 member of SE(3).
   *
   * @param H 4x4 matrix. Upper-left 3x3 corner must be member of SO(3), or the
   * resulting pose is likely undefined.
   */
  PoseT(const Mat4& H) : PoseT(H.template topLeftCorner<3,3>(),
                               H.template topRightCorner<3,1>()) {}

  /**
   * @brief Return representation of the rotation. This represents the upper-
   * left 3x3 matrix of the corresponding SE(3) transformation.
   *
   * @return RotationType
   */
  const RotationType& rot() const { return rot_; }

  /**
   * @brief Return translation vector. This is the upper-right 3x1 column of the
   * corresponding SE(3) transformation.
   *
   * @return Vec3
   */
  const Vec3& t() const { return t_; }

  /**
   * @brief Transform an R3 vector by left-multiplying the transform described
   * by this pose.
   *
   * @param x Vector to transform.
   * @param J_lha [Optional output] Jacobian w.r.t. to the pose.
   * @param J_rha [Optional output] Jacobian w.r.t. to x.
   *
   * @return Transformed vector.
   */
  Vec3 transform(const Vec3& x,
                 boost::optional<Mat3x6&> J_lha = boost::none,
                 boost::optional<Mat3&>   J_rha = boost::none) const {
    const Vec3 y = rot()*x + t();
    if (J_lha) {  //  jacobian w.r.t pose
      *J_lha << Mat3::Identity(), -se3::skew(y);
    }
    //  jacobian w.r.t point
    if (J_rha) { *J_rha = rot().matrix(); }
    return y;
  }

  /**
   * @brief Rotate an R3 vector by left-multiplying the SO(3) transform
   * contained in this pose.
   *
   * @param x Vector to rotate.
   * @param J_lha [Optional output] Jacobian w.r.t. to the rotation part of the
   * pose.
   * @param J_rha [Optional output] Jacobian w.r.t. to x.
   *
   * @return Rotated vector.
   */
  Vec3 rotate(const Vec3& x,
              boost::optional<Mat3&> J_lha = boost::none,
              boost::optional<Mat3&> J_rha = boost::none) const {
    const Vec3 y = rot()*x;
    if (J_lha) { *J_lha = -se3::skew(y); }
    if (J_rha) { *J_rha = rot().matrix(); }
    return y;
  }

  /**
   * @brief Left multiply the receiver by the argument, and return the resulting
   * pose. Equivalent to the SE(3) composition:
   *
   *  H' = H1*H0
   *
   * Where H0 is the argument and H1 is the receiver.
   *
   * @param rha Pose to right-multiply by the receiver.
   * @param J_lha [Optional output] Jacobian w.r.t. to the left argument.
   * @param J_rha [Optional output] Jacobian w.r.t. to the right argument.
   *
   * @return PoseT with the same `RotationType` as the receiver.
   */
  template <class RotationType_>
  PoseT<RotationType> compose(const PoseT<RotationType_>& rha,
                        boost::optional<Mat6&> J_lha = boost::none,
                        boost::optional<Mat6&> J_rha = boost::none) const {
    //  left multiply the receiver
    PoseT<RotationType> H(rot() * rha.rot(), rot()*rha.t() + t());
    if (J_lha) {
      *J_lha = Mat6::Identity();
    }
    if (J_rha) {
      const Mat3& R1 = rot().matrix();
      //  adjoint of se3
      *J_rha << R1, se3::skew(t())*R1,
                Mat3::Zero(), R1;
    }
    return H;
  }

  /**
   * @brief Invert this pose by inverting the underlying SE(3) transformation.
   *
   * @param J [Optional output] Jacobian w.r.t. the receiver.
   *
   * @return Inverted pose, with same RotationType as receiver.
   */
  PoseT<RotationType>
  inverse(boost::optional<Mat6&> J = boost::none) const {
    //  use appropriate inversion formula for rotation, see below
    const RotationType& rotInv = invertRotation( rot() );
    PoseT<RotationType> inv(rotInv, rotInv * -t());
    if (J) {
      //  negative adjoint of new pose
      const Mat3& R1inv = rotInv.matrix();
      *J << -R1inv, -se3::skew(inv.t()) * R1inv,
             Mat3::Zero(), -R1inv;
    }
    return inv;
  }

  /**
   * @brief Convert pose to a member of SE(3), the 4x4 homogenous matrix
   * representation.
   * @return Mat4 with an upper 3x4 block: [R | t]
   */
  Mat4 matrix() const {
    Mat4 H;
    H.template topLeftCorner<3,3>() = rot().matrix();
    H.template topRightCorner<3,1>() = t();
    H(3,0) = H(3,1) = H(3,2) = 0;
    H(3,3) = 1;
    return H;
  }

  /*
   *  Casting operators
   */

#ifdef VO_BUILD_ROS
  /**
   * @brief Construct pose from ROS message.
   * @param geo Instance of geometry_msgs::Pose.
   * @note Loss of accuracy will occur if Scalar is float32.
   */
  PoseT(const geometry_msgs::Pose &geo) :
    PoseT(Quat(geo.orientation.w, geo.orientation.x,
               geo.orientation.y, geo.orientation.z),
          Vec3(geo.position.x,geo.position.y,geo.position.z)) {}

  /**
   * @brief Explicit cast to ROS geometry_msgs::Pose.
   */
  explicit operator geometry_msgs::Pose() const {
    geometry_msgs::Pose geo;
    const Eigen::Quaternion<Scalar> q(rot());
    geo.orientation.w = q.w();
    geo.orientation.x = q.x();
    geo.orientation.y = q.y();
    geo.orientation.z = q.z();
    geo.position.x = t_[0];
    geo.position.y = t_[1];
    geo.position.z = t_[2];
    return geo;
  }

  /**
   * @brief Construct pose from TF transform.
   * @param trans Instance of geometry_msgs::TransformStamped.
   */
  PoseT(const geometry_msgs::TransformStamped &trans) :
    PoseT(Quat(trans.transform.rotation.w, trans.transform.rotation.x,
               trans.transform.rotation.y, trans.transform.rotation.z),
          Vec3(trans.transform.translation.x, trans.transform.translation.y,
               trans.transform.translation.z)) {}
#endif

#ifdef VO_BUILD_GTSAM
  /**
   * @brief Construct pose from GTSAM Pose3.
   * @param gtpose Instance of GTSAM 6DOF pose.
   */
  PoseT(const gtsam::Pose3& gtpose) :
    PoseT(gtpose.rotation().toQuaternion().cast<Scalar>(),
          gtpose.translation().vector().cast<Scalar>()) {}

  /**
   * @brief Explicit cast to GTSAM Pose3.
   */
  explicit operator gtsam::Pose3() const {
    const Eigen::Quaterniond quat(rot().template cast<double>());
    const gtsam::Rot3 R3(quat);
    return gtsam::Pose3(R3, gtsam::Point3(t().template cast<double>()));
  }
#endif

private:

  /// Invert an axis-angle
  static Eigen::AngleAxis<Scalar>
  invertRotation(const Eigen::AngleAxis<Scalar>& aa) { return aa.inverse(); }

  /// Invert a Quaternion
  static Quat invertRotation(const Quat& q) { return q.conjugate(); }

  /// Invert a 3x3 orthonormal matrix by calling transpose instead of invert.
  static Mat3 invertRotation(const Mat3& R) { return R.transpose(); }

  /// Do nothing to non-quaternions, normalize quaternions.
  template <class RotationType_>
  static void normalizeRotation(RotationType_&) {}
  static void normalizeRotation(Quat& q) { q.normalize(); }

  RotationType rot_;
  Vec3 t_;
};

/**
 * @brief Default Pose type to use in most common operations.
 */
typedef PoseT<Eigen::Quaternion<vo::scalar_t>> Pose;

} //  namespace vo

#endif // POSE_HPP
