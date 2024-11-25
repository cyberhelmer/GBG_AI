#include "dotenv-cpp.hpp"
#include "openai.hpp"
#include <iostream>

int main() {
  dotenv::init("api_key.env");
  std::cout << "Hello, World!" << std::endl;
  std::cout << "nu ska vi testa detta " << dotenv::getenv("JOHNSTEST", "hejhej") << std::endl;
  return 0;
}
