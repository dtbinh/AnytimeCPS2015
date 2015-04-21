/**
 * statistics.hpp
 *  Copyright 2014, Gareth Cross. All Rights Reserved.
 */

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vo_utils/base.hpp>

#include <ostream>
#include <deque>
#include <cmath>
#include <limits>
#include <type_traits>
#include <algorithm>

namespace vo {

template <typename Scalar = scalar_t>
class Statistics {
  static_assert(std::is_arithmetic<Scalar>::value,
                "Scalar must be an arithmetic type");
public:

  Statistics() {}

  /**
   * @brief Calculate statistics on a set of scalars.
   * @note This constructor does not copy but must be called explicitly.
   */
  explicit Statistics(std::vector<Scalar>&& data) {
    //  sort, small to large
    std::sort(data.begin(), data.end());
    const std::size_t N = data.size();
    if (N > 0) {
      //  median/iq-range
      median_ = data[N / 2];
      iq_ = data[(N*3)/4] - data[N/4];
      //  mean+variance
      var_ = 0;
      total_ = 0;
      for (const Scalar& x : data) {
        total_ += x;
        var_ += x*x;
      }
      mean_ = total_ / N;
      var_ /= N;
      rms_ = std::sqrt(var_); //  root of the mean of squares
      var_ -= mean_*mean_;
      var_ = std::max(static_cast<Scalar>(0), var_);
      std_ = std::sqrt(var_);
      //  max/minimums
      max_ = data.back();
      min_ = data.front();
      count_ = N;
    } else {
      //  otherwise leave at defaults of 0
    }
  }

  /**
   * @see Statistics::Statistics
   * @note This constructor forces a copy.
   */
  Statistics(const std::vector<Scalar>& data) :
    Statistics(std::vector<Scalar>(data)) {}

  /**
   * @brief Average of the samples.
   */
  const Scalar& mean() const { return mean_; }

  /**
   * @brief Varianace of the samples.
   */
  const Scalar& variance() const { return var_; }

  /**
   * @brief Root-mean-square of the samples.
   */
  const Scalar& rms() const { return rms_; }

  /**
   * @brief Standard deviation of the samples.
   */
  const Scalar& std() const { return std_; }

  /**
   * @brief Median of the samples.
   */
  const Scalar& median() const { return median_; }

  /**
   * @brief Inter-quartile range of the samples.
   */
  const Scalar& iqRange() const { return iq_; }

  /**
   * @brief Maximum of the sample.
   */
  const Scalar& max() const { return max_; }

  /**
   * @brief Minimum of the samples.
   */
  const Scalar& min() const { return min_; }

  /**
   * @brief Total of the samples.
   */
  const Scalar& total() const { return total_; }

  /**
   * @brief Total # of samples
   */
  const std::size_t& count() const { return count_; }

private:
  Scalar mean_{0};
  Scalar var_{0};
  Scalar std_{0};
  Scalar rms_{0};
  Scalar median_{0};
  Scalar iq_{0};
  Scalar max_{0};
  Scalar min_{0};
  Scalar total_{0};
  std::size_t count_{0};
};

/**
 * @brief Maintains a buffer of samples and calculates basic statistics of
 * the data in the window.
 */
template <typename Scalar = scalar_t>
class WindowedStatistics {
public:
  /**
   * @brief Create a new statistics object.
   * @param max_size Optional, max size of the window.
   * @note If max_size is 0, the size of the window is unlimited.
   */
  WindowedStatistics(std::size_t max_size = 0) : max_size_(max_size) {}

  /**
   * @brief ~WindowedStatistics
   */
  virtual ~WindowedStatistics() {}

  /**
   * @brief Push a new sample into the window
   * @param x Measurement to add.
   * @param and_update If true, all stats will be recalculated.
   */
  void push(const Scalar& x, bool and_update = false) {
    if (max_size_ && (size() ==  max_size_)) {
      //  need to discard a sample first
      //  lazy man's pop front
      data_.erase(data_.begin());
    }
    data_.push_back(x);
    count_++;
    needs_update_ = true;
    if (and_update) {
      update();
    }
  }

  /**
   * @brief Size of the window.
   * @return std::size_t
   */
  std::size_t size() const { return data_.size(); }

  /**
   * @brief Recalculate all the statistics.
   * @note Does nothing in the case where the window has not been modified
   * since the last calculation.
   */
  void update() {
    stats_ = Statistics<Scalar>(data_);
    max_ever_ = std::max(stats_.max(),max_ever_);
    min_ever_ = std::min(stats_.min(),min_ever_);
    needs_update_ = false;
  }

  /**
   * @brief Retrieve stats object.
   */
  const Statistics<Scalar>& stats() const { return stats_; }

  /**
   * @brief Maximum of samples ever observed.
   */
  const Scalar& maxEver() const { return max_ever_; }

  /**
   * @brief Minimum of samples ever observed.
   */
  const Scalar& minEver() const { return min_ever_; }

  /**
   * @brief Total number of samples added, which may exceed the amount
   * presently stored in the window.
   */
  const std::size_t& count() const { return count_; }

  /**
   * @brief Maximum size of the window.
   * @return std::size_t
   */
  const std::size_t& maxSize() const { return max_size_; }

protected:
  std::vector<Scalar> data_;
  const std::size_t max_size_;
  Statistics<Scalar> stats_;
  Scalar max_ever_{std::numeric_limits<Scalar>::min()};
  Scalar min_ever_{std::numeric_limits<Scalar>::max()};
  std::size_t count_{0};
  bool needs_update_{false};
};

} //  namespace vo

/**
 *  @brief Output statistics to stream.
 */
template <typename Scalar>
std::ostream&
operator<<(std::ostream& os, const vo::WindowedStatistics<Scalar>& s) {
  const vo::Statistics<Scalar> st = s.stats();
  os << "Mean/var/std: " << st.mean() << " / " << st.variance()
     << " / " << st.std() << "\n";
  os << "Median/iq-range: " << st.median() << " / " << st.iqRange() << "\n";
  os << "Max (ever): " << st.max() << " (" << s.maxEver() << ")\n";
  os << "Min (ever): " << st.min() << " (" << s.minEver() << ")\n";
  os << "Window size (allowed): " << s.size() << " (" << s.maxSize() << ")\n";
  os << "Total count: " << s.count() << "\n";
  return os;
}

#endif // STATISTICS_HPP
