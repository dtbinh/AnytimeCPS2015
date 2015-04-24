/**
 * error_calculator.cpp
 *  Copyright 2015, Gareth Cross. All Rights Reserved.
 */

#include <vo_test/error_calculator.hpp>
#include <iomanip>

namespace vo {
namespace test {

ErrorCalculator::ErrorCalculator(std::size_t windowSize) :
  windowSize_(windowSize) {
  if (windowSize == 1) {
    throw std::invalid_argument("Window size cannot be 1");
  }
}

void ErrorCalculator::addFrame(const Pose& estimate, 
                               const Pose& truth,
                               const Timestamp& time) {
  //  increment path length
  if (!truth_.empty()) {
    const vec3 diff = truth.t() - truth_.back().t();
    pathLength_ += diff.norm();
  }
  
  if (!count_) {
    //  first sample (nothing special to handle this yet)
  } else if (windowSize_ && (count_ % windowSize_) == 0) {
    //  reached window size
    estimates_.pop_front();
    truth_.pop_front();
    times_.pop_front();
  }
  
  estimates_.push_back(estimate);
  truth_.push_back(truth);
  times_.push_back(time);
  if (estimates_.size() > 1) {
    recalculate();
  }
  count_++;
}

void ErrorCalculator::recalculate() {
  Pose originEst = estimates_.front();
  Pose originTruth = truth_.front();
  //  transforms to convert to relative pose
  const Pose trans = originTruth.compose( originEst.inverse() );
  
  std::vector<scalar_t> pos[3]; //  xyz components
  std::vector<scalar_t> rot[3];
  const size_t N = estimates_.size();
  for (int j=0; j < 3; j++) {
    pos[j].reserve(N);
    rot[j].reserve(N);
  }
  
  for (std::size_t i=0; i < estimates_.size(); i++) {
    const Pose pest = trans.compose(estimates_[i]);
    const Pose ptr = truth_[i];
    //  now have two body-to-world poses taken from same origin ('truth')
    //  calculate error metrics, translation and rotation
    const vec3 posErr = ptr.t() - pest.t();
    const mat3 R1 = ptr.rot().matrix();
    const mat3 R2 = pest.rot().matrix();
    const Eigen::AngleAxis<scalar_t> aa = 
        Eigen::AngleAxis<scalar_t>(R1 * R2.transpose());
    const vec3 angErr = aa.axis() * aa.angle();
    //  take absolute value
    for (int j=0; j < 3; j++) {
      pos[j].push_back( std::abs(posErr[j]) );
      rot[j].push_back( std::abs(angErr[j]) );
    }
  }
  
  //  calculate statistics about all three axes
  for (int j=0; j < 3; j++) {
    pos_[j] = pos[j];//Statistics<>( std::move(pos[j]) );
    rot_[j] = Statistics<>( std::move(rot[j]) );
  }
}

const vo::Statistics<>& 
ErrorCalculator::positionStats(const std::size_t axis) const {
  if (axis > 2) {
    throw std::invalid_argument("Axis must be 0, 1, or 2");
  }
  return pos_[axis];
}

const vo::Statistics<>& 
ErrorCalculator::rotationStats(const std::size_t axis) const {
  if (axis > 2) {
    throw std::invalid_argument("Axis must be 0, 1, or 2");
  }
  return rot_[axis];
}

const scalar_t& ErrorCalculator::pathLength() const {
  return pathLength_;
}

std::ostream& operator<< (std::ostream& os, ErrorCalculator& calc) {
  os << std::setprecision(8);  
  for (std::size_t i=0; i < calc.estimates_.size(); i++) {
    const Timestamp& time = calc.times_[i];
    const Pose& est = calc.estimates_[i];
    const Pose& truth = calc.truth_[i];
    //  timestamp in nanoseconds
    os << time;
    //  estimated pose
    os << "," << est.rot().w() << "," << est.rot().x() 
       << "," << est.rot().y() << "," << est.rot().z();
    os << "," << est.t()[0] << "," << est.t()[1] << "," << est.t()[2];
    //  true pose
    os << "," << truth.rot().w() << "," << truth.rot().x() 
       << "," << truth.rot().y() << "," << truth.rot().z();
    os << "," << truth.t()[0] << "," << truth.t()[1] << "," << truth.t()[2];
    os << "\n";
  }
  return os;
}

} //  test
} //  vo
