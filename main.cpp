#include "dotenv-cpp.hpp"
#include "openai.hpp"
#include <iostream>

int main() {

  dotenv::init("api_key.env");

  std::string question{};
  std::cout << "Enter your question: ";
  std::getline(std::cin, question);
  openai::start(dotenv::getenv("APIKEY", ""));
  auto chat = openai::chat().create(R"(
    {
        "model": "gpt-3.5-turbo",
        "messages":[{"role":"user", "content":" + question "}],
        "max_tokens": 200,
        "temperature": 0
    }
    )"_json);
  std::cout << "Response is:\n"
            << chat["choices"][0]["message"]["content"] << '\n';
  return 0;
}
