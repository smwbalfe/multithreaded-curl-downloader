//
// Created by shriller44 on 9/4/22.
//

#ifndef DOWNLOADTEST_HEADERWRAPPER_H
#define DOWNLOADTEST_HEADERWRAPPER_H

#include <cstddef>
#include <iostream>
#include <memory>

class HeaderWrapper {
 public:
  explicit HeaderWrapper(uint32_t id);

  size_t operator()(char *buffer,size_t size,size_t nitems);

  [[nodiscard]] std::string headerBuffer();

 private:
  std::shared_ptr<std::string> str_;
  uint32_t id_;
};

#endif  // DOWNLOADTEST_HEADERWRAPPER_H
