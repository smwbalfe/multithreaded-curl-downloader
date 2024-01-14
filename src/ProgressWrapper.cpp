//
// Created by shriller44 on 9/3/22.
//

#include <ProgressWrapper.h>

ProgressWrapper::ProgressWrapper(uint32_t id): id_ {id} {}

double ProgressWrapper::operator()(double dltotal , double dlnow, [[maybe_unused]] double ultotal , [[maybe_unused]] double ulnow) const{
  if (dlnow != 0 && dltotal != 0) {
    auto percentage = std::ceil((dlnow / dltotal) * 100);
    auto pos = std::ceil(barWidth_ * (percentage / 100));
    std::cout << "[ ";
    for (int i = 0; i < barWidth_; ++i){
      if (i < pos) std::cout << '=';
      else if (i == pos) std::cout << '>';
      else std::cout << ' ';
    }
    std::cout << fmt::format(" ] {}%\n", percentage);
    std::cout.flush();
  }
  return 0;
}