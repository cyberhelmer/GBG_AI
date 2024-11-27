#include "dotenv-cpp.hpp"
#include "openai.hpp"
#include "systemPromt.h"
#include <iostream>
#include <stdexcept>

nlohmann::json buildChatRequest(const std::string& systemPrompt, const std::string& userQuestion) {
    return {
        {"model", "gpt-3.5-turbo"},
        {"messages", {{{"role", "system"}, {"content", systemPrompt}}, {{"role", "user"}, {"content", userQuestion}}}},
        {"max_tokens", 200},
        {"temperature", 0.0}
    };
}

int main() {
    try {
        dotenv::init("api_key.env");
        const std::string api_key = dotenv::getenv("APIKEY", "");
        if (api_key.empty()) {
            throw std::runtime_error("API Key not found in .env file.");
        }
        openai::start(api_key);

        std::cout << "Hello! I am an expert in Shell scripts, Graphics cards, and Cisco routers.\n";
        std::cout << "Ask me a question or press 'Q' to quit.\n";

        std::string question;
        while (true) {
            std::cout << "Enter your question: ";
            std::getline(std::cin, question);

            if (question == "Q" || question == "q") {
                std::cout << "Goodbye! Thank you for using the assistant.\n";
                break;
            }

            if (question.empty()) {
                std::cout << "Please enter a valid question.\n";
                continue;
            }

            auto chatRequest = buildChatRequest(startPrompt, question);

            try {
                auto chatResponse = openai::chat().create(chatRequest);

                //Convert answer for indexing next systemPromt
                int promptChoice = std::stoi(chatResponse["choices"][0]["message"]["content"].get<std::string>());

                //Makes sure the promtChoice is valid
                if (promptChoice < 0 || promptChoice >= promptArray.size()) {
                    std::cout << "Invalid choice. Please ask a valid question.\n";
                    continue;
                }

                chatRequest = buildChatRequest(promptArray[promptChoice], question);

                std::cout << "AI Response:\n"
                          << openai::chat().create(chatRequest)["choices"][0]["message"]["content"].get<std::string>()
                          << "\n";

            } catch (const std::exception& ex) {
                std::cerr << "Error during API call: " << ex.what() << "\n";
            }
        }

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }

    return 0;
}
