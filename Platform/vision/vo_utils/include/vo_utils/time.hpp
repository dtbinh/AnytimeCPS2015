/**
 * time.hpp
 *  Copyright 2014, Gareth Cross. All Rights Reserved.
 */

#ifndef TIME_HPP
#define TIME_HPP

#include <vo_utils/base.hpp>
#include <vo_utils/statistics.hpp>
#include <ostream>

namespace vo {

/**
 * @brief Get the monotonic time in nanoseconds.
 * @return Timestamp
 */
Timestamp getTimeNs();

/**
 * @brief Class for benchmarking code runtime.
 */
class Bench : public WindowedStatistics<double> {
public:

  Bench(const std::string& name, std::size_t window_size) :
    WindowedStatistics<double>(window_size), name_(name) {}

  virtual ~Bench() {}

  /**
   * @brief Start a sample.
   */
  void tic();

  /**
   * @brief End a sample.
   */
  void toc();

  /**
   * @brief Are we due to write to the log?
   */
  const bool& dirty() const { return dirty_; }

  /**
   * @brief Name of this bench object.
   */
  const std::string& name() const { return name_; }

private:
  const std::string name_;
  Timestamp tic_time_{0};
  bool dirty_{false};

  friend std::ostream& operator<< (std::ostream&, Bench&);
};

} //  namespace vo

#endif // TIME_HPP
