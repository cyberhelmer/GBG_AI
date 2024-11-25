#include "dotenv-cpp.hpp"
#include "openai.hpp"
#include <iostream>

int main() {

 // dotenv::init("api_key.env");
  std::cout << "Hello, World!" << std::endl;
  openai::start();
  auto chat = openai::chat().create(R"(
    {
        "model": "gpt-3.5-turbo",
        "messages":[{"role":"user", "content":"Hej hur mår du?"}],
        "max_tokens": 7,
        "temperature": 0
    }
    )"_json);
  std::cout << "Response is:\n" << chat.dump(2) << '\n';
  return 0;
}
