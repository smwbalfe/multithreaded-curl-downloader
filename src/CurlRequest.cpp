//
// Created by shriller44 on 9/2/22.
//

#include <CurlRequest.h>

#include <utility>

CurlRequest::CurlRequest(uint32_t id, std::string fileName):fileName_ {std::move(fileName)}, id_ {id}, handle_ {std::make_unique<curlpp::Easy>()}, progress_ {id}, headers_{id}{}

void CurlRequest::setOptions(OptionsConfig options){
  for (auto& opt: options){
    handle_->setOpt(std::move(opt));
  }
}


void CurlRequest::setFileExtension(const std::string& headers){
  std::istringstream os {headers};
  std::string line;
  while (std::getline(os, line)){
    if (line.contains("Content-Type: ")){
      auto pos = std::find(line.begin(), line.end(), ' ');
      line.erase(line.begin(), pos + 1);
      if (line.contains("application/pdf")){
          fileExtension_ = extension::PDF;
      }
      else if (line.contains("audio/mpeg")){
          fileExtension_ = extension::MP3;
      }
      else if (line.contains("text/html")){
        fileExtension_ = extension::HTML;
      }
    }
  }
}

void CurlRequest::writeFile(std::ostringstream& os) {
  std::ofstream outfile;
  std::string extension;
  switch (fileExtension_){
    case extension::MP3:
      extension = "mp3";
    case extension::PDF:
      extension = "pdf";
    case extension::HTML:
      extension = "html";
  }

  outfile.open(fmt::format("../../downloads/{}", fileName_, extension));
  outfile << os.str();
}

int CurlRequest::operator()() {
  std::ostringstream os;
  handle_->setOpt(new curlpp::options::WriteStream(&(os)));
  handle_->perform();
  setFileExtension(headers_.headerBuffer());
  writeFile(os);
  return 1;
}
[[nodiscard]] uint32_t CurlRequest::getID() const {
  return id_;
}
