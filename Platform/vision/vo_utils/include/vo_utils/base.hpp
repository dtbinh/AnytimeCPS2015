/**
 * base.hpp
 *  Copyright 2014, Gareth Cross. All Rights Reserved.
 */

#ifndef BASE_HPP
#define BASE_HPP

#include <algorithm>
#include <cmath>
#include <memory>
#include <mutex>
#include <functional>
#include <cstdint>

#include <Eigen/Core>

#ifdef VO_BUILD_ROS
# include <ros/ros.h>
#endif

namespace vo {

/**
 * @brief scalar_t is the type used for all calculations.
 */
typedef float scalar_t;

typedef Eigen::Matrix<scalar_t,2,1> vec2;
typedef Eigen::Matrix<scalar_t,3,1> vec3;
typedef Eigen::Matrix<scalar_t,4,1> vec4;
typedef Eigen::Quaternion<scalar_t> quat;

typedef Eigen::Matrix<scalar_t,2,2> mat2;
typedef Eigen::Matrix<scalar_t,3,3> mat3;
typedef Eigen::Matrix<scalar_t,4,4> mat4;
typedef Eigen::Matrix<scalar_t,6,6> mat6;

template <int Rows, int Cols>
using mat = Eigen::Matrix<scalar_t,Rows,Cols>;

typedef uint64_t Timestamp;
typedef uint64_t Id;

class Frame;
class Feature;
class Instance;
typedef std::shared_ptr<Frame> FramePtr;
typedef std::shared_ptr<Feature> FeaturePtr;
typedef std::shared_ptr<Instance> InstancePtr;

class PoseWithCovariance;

} //   namespace vo

/**
  * Logging methods
  */
#if defined(VO_BUILD_ROS)
#   define log_i(...)   ROS_INFO(__VA_ARGS__)
#   define log_w(...)   ROS_WARN(__VA_ARGS__)
#   define log_e(...)   ROS_ERROR(__VA_ARGS__)
#elif defined(VO_BUILD_ANDROID)
#   define log_i(...)   __android_log_print(ANDROID_LOG_INFO, "VO", __VA_ARGS__)
#   define log_w(...)   __android_log_print(ANDROID_LOG_WARN, "VO", __VA_ARGS__)
#   define log_e(...)   __android_log_print(ANDROID_LOG_ERROR, "VO", __VA_ARGS__)
#else
#   define log_i(...)   fprintf(stdout,__VA_ARGS__)
#   define log_w(...)   fprintf(stdout,__VA_ARGS__)
#   define log_e(...)   fprintf(stderr,__VA_ARGS__)
#endif

#if defined(VO_BUILD_DEBUG)
#include <assert.h>
#define vo_assert(x) assert(x)
#else
//  Silence unused variable errors
static inline void doNothing(const bool&) {}
#define vo_assert(x)  doNothing(x)
#endif
#endif // BASE_HPP
