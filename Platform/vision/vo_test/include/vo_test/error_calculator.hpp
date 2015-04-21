/**
 * error_calculator.cpp
 *  Copyright 2015, Gareth Cross. All Rights Reserved.
 */

#ifndef ERROR_CALCULATOR_HPP
#define ERROR_CALCULATOR_HPP

#include <vo_utils/statistics.hpp>
#include <vo_utils/pose.hpp>
#include <vo_utils/time.hpp>

namespace vo {
namespace test {

/**
 * @brief The ErrorCalculator class
 */
class ErrorCalculator {
public:

  ErrorCalculator(std::size_t windowSize = 0);

  /**
   * @brief addFrame
   * @param estimate
   * @param truth
   */
  void addFrame(const Pose& estimate, const Pose& truth,
                const Timestamp& time = vo::getTimeNs());

  const vo::Statistics<>& positionStats(const std::size_t axis) const;

  const vo::Statistics<>& rotationStats(const std::size_t axis) const;

  const scalar_t& pathLength() const;

  /**
   * @brief operator << Write all poses (est and truth) to a stream.
   */
  friend std::ostream& operator<< (std::ostream&, ErrorCalculator&);

private:

  void recalculate();

  const std::size_t windowSize_;
  std::size_t count_{0};
  std::deque<Pose> estimates_;
  std::deque<Pose> truth_;
  std::deque<Timestamp> times_;
  vo::Statistics<> pos_[3];
  vo::Statistics<> rot_[3];
  scalar_t pathLength_{0.0};
};

} //  test
} //  vo

#endif
