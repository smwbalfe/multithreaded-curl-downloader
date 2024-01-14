//
// Created by shriller44 on 9/2/22.
//

#ifndef DOWNLOADTEST_CURLREQUEST_H
#define DOWNLOADTEST_CURLREQUEST_H

#include <curl.h>
#include <fmt/format.h>
#include <fstream>
#include <ProgressWrapper.h>
#include <HeaderWrapper.h>
#include <sstream>

using OptionsConfig = std::vector<std::unique_ptr<curlpp::OptionBase>>;

class CurlRequest {

  enum class extension {
    PDF,
    MP3,
    HTML
  };

 public:
  explicit CurlRequest(uint32_t id, std::string filename);

  /* curl request execution*/
  int operator()();

  void setOptions(OptionsConfig options);

  [[nodiscard]] uint32_t getID () const;

  [[nodiscard]] auto& getProgress() const {
    return progress_;
  }
  [[nodiscard]] auto& getHeaders() const {
    return headers_;
  }

 private:

  void writeFile(std::ostringstream& os);

  void setFileExtension(const std::string& headers);

  std::uint32_t id_;
  std::unique_ptr<curlpp::Easy> handle_;
  ProgressWrapper progress_;
  HeaderWrapper headers_;
  extension fileExtension_;
  std::shared_ptr<std::ostringstream> os_;
  std::string fileName_;
};

#endif  // DOWNLOADTEST_CURLREQUEST_H
