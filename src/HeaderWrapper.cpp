//
// Created by shriller44 on 9/4/22.
//

#include <HeaderWrapper.h>

HeaderWrapper::HeaderWrapper(uint32_t id): id_ {id}, str_{std::make_shared<std::string>("")} {}

size_t HeaderWrapper::operator()(char* buffer, size_t size, size_t nitems) {
  std::cout << str_ << std::endl;
  str_->append(buffer);
  return size * nitems;
}

std::string HeaderWrapper::headerBuffer() {
  return *str_;
}
