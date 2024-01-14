//
// Created by shriller44 on 9/3/22.
//

#ifndef DOWNLOADTEST_PROGRESSWRAPPER_H
#define DOWNLOADTEST_PROGRESSWRAPPER_H

#include <string>
#include <cmath>
#include <iostream>
#include <fmt/format.h>

class ProgressWrapper {
 public:
  explicit ProgressWrapper(uint32_t id);
  double operator()(double dltotal , double dlnow, [[maybe_unused]] double ultotal , [[maybe_unused]] double ulnow) const;
 private:
  uint32_t id_;
  std::string progress_;
  int barWidth_ {100};
};

#endif  // DOWNLOADTEST_PROGRESSWRAPPER_H
