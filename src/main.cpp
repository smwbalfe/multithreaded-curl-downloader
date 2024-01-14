#include <CurlRequest.h>
#include <ThreadPool.h>
#include <iostream>
#include <random>
#include <thread>
#include <utility>

std::string parseFileName(const std::string& u){
  std::string fileName;
  auto name = u.find_last_of('/');
  fileName = u.substr(name+1, u.length() - 1);
  std::replace(fileName.begin(), fileName.end(), '%', ' ');
  if(fileName.contains('.')){
    size_t findDot = fileName.find_first_of('.');
    fileName.erase(fileName.begin() + findDot, fileName.end());
  }
  return fileName;
}


int main(int argc, char* argv[]) {

    if (argc < 2){
        std::cerr << "incorrect arguments" << std::endl;
    }

    std::vector<std::string> urlvec;

    for (int i = 1; i < argc; ++i){
      urlvec.emplace_back(argv[i]);
    }

    try {

      using optionvec = std::vector<std::unique_ptr<curlpp::OptionBase>>;

      ThreadPool tp {36};

      std::vector<std::future<int>> results;

      uint32_t x = 0;

      for (const auto& u: urlvec){

        auto fileName = parseFileName(u);

        CurlRequest cr {x, fileName};
        optionvec optvec;
        optvec.emplace_back(std::make_unique<curlpp::options::Url>(u));
        optvec.emplace_back(std::make_unique<curlpp::options::NoProgress>(false));
        optvec.emplace_back(std::make_unique<curlpp::options::ProgressFunction>(cr.getProgress()));
        optvec.emplace_back(std::make_unique<curlpp::options::HeaderFunction>(cr.getHeaders()));
        cr.setOptions(std::move(optvec));
        results.emplace_back(tp.enqueue( std::move(cr)));
        ++x;
      }

    } catch (curlpp::LogicError & e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (curlpp::RuntimeError& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
