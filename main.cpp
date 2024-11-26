#include "dotenv-cpp.hpp"
#include "openai.hpp"
#include <iostream>
#include "systemPromt.h"

int main() {
  try {
    // Load environment variables from .env file
    dotenv::init("api_key.env");

    // Get API key from environment
    const std::string api_key = dotenv::getenv("APIKEY", "");
    if (api_key.empty()) {
      throw std::runtime_error("API Key not found in .env file.");
    }

    // Initialize OpenAI
    openai::start(api_key);

    // Welcome message
    std::cout << "Hello! I am an expert in Shell scripts, Graphics cards, "
                 "and Cisco routers.\nPRESS Q to exit.\n"
                 "Enter your question: ";

    std::string question{};
    std::getline(std::cin, question);

    while (question != "Q") {
      // Build the JSON request dynamically
      nlohmann::json chat_request = {
          {"model", "gpt-3.5-turbo"},
          {"messages",
           {{{"role", "system"},
             {"content", "You are an assistant that only answers questions "
                         "with one word."}},
            {{"role", "user"}, {"content", question}}}},
          {"max_tokens", 200},
          {"temperature", 0}};

      // Call the OpenAI chat API
      auto chat = openai::chat().create(chat_request);

      // Print the assistant's response
      std::cout << chat["choices"][0]["message"]["content"].get<std::string>()
                << '\n';

      // Prompt for the next question
      std::cout << "Enter your question: ";
      std::getline(std::cin, question);
    }

  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
  }

  return 0;
}
