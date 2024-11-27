#include "dotenv-cpp.hpp"
#include "openai.hpp"
#include "systemPromt.h"
#include <iostream>

int main() {
  try {
    // Load environment variables from .env file
    dotenv::init("api_key.env");

    // Get API key from environment
    const std::string api_key = dotenv::getenv("APIKEY", "");
    if (api_key.empty()) {
      throw std::runtime_error(
          "API Key not found in .env file. You need to create an env file named \n api_key.env and add your OpenAI API key to it.");
    }
    // Initialize OpenAI
    openai::start(api_key);
    // Welcome message
    std::cout << "Hello! I am an expert in Shell scripts, Graphics cards, "
                 "and Cisco routers.\nPRESS Q to exit.\n"
                 "Enter your question: ";

    std::string question{};

    while (question != "Q") {
      // Prompt for the next question
      std::cout << "Enter your question: ";
      std::getline(std::cin, question);
      // Build the JSON request dynamically
      nlohmann::json chat_request = {
          {"model", "gpt-3.5-turbo"},
          {"messages", {{{"role", "system"}, {"content", startPrompt}}, {{"role", "user"}, {"content", question}}}},
          {"max_tokens", 200},
          {"temperature", 0}};

      // Call the OpenAI chat API
      auto chat = openai::chat().create(chat_request);

      // Convert the respons to an int for indexing the promptArray
      int promtChoice = std::stoi(chat["choices"][0]["message"]["content"].get<std::string>());

      // TO-DO Add error handling here
      if (promtChoice < 0) {
        std::cout << "Invalid question. I can only answer questions about Shell scripts, Graphics cards, "
                     "and Cisco routers \n Please try again.\n";
      } else {
        chat_request = {
            {"model", "gpt-3.5-turbo"},
            {"messages",
             {{{"role", "system"}, {"content", promptArray[promtChoice]}}, {{"role", "user"}, {"content", question}}}},
            {"max_tokens", 200},
            {"temperature", 0}};

        std::cout << openai::chat().create(chat_request)["choices"][0]["message"]["content"].get<std::string>()
                  << std::endl;
      }
    }

  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
  }
  return 0;
}