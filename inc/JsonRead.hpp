#ifndef JSONREAD_HPP
#define JSONREAD_HPP

#include <string>
#include <vector>
#include <cstdio>

#include <SFML/Graphics.hpp>

#include "json.hpp"
using Json = nlohmann::json;

class JsonRead
{
    static void displayWarning(Json &json, std::vector<std::string> arguments, std::string expectedType);

public:
    // solution from https://stackoverflow.com/questions/9346076/static-template-functions-in-a-class
    template <class T>
    static int toVar(Json &json, std::vector<std::string> arguments, T &num)
    {
        // printf("Info: JsonRead: reading number/boolean from json ...\n");
        Json *json_ptr = &json;
        for (const auto &s : arguments)
            json_ptr = &((*json_ptr)[s]);
        // printf("Info: JsonRead: type: %s  value: %s\n", json_ptr->type_name(), json_ptr->dump().c_str());
        if (json_ptr->is_null())
        {
            JsonRead::displayWarning(*json_ptr, arguments, "number/boolean");
            return 1;
        }
        else if (json_ptr->is_number())
        {
            num = *json_ptr;
        }
        else if (json_ptr->is_boolean())
        {
            num = *json_ptr;
        }
        else
        {
            JsonRead::displayWarning(*json_ptr, arguments, "number/boolean");
            return 1;
        }
        // printf("Info: JsonRead: readed number/boolean correctly\n");
        return 0;
    }

    template <class T>
    static int toVar(Json &json, std::vector<std::string> arguments, sf::Vector2<T> &vec)
    {
        // printf("Info: JsonRead: reading sf::Vector from json ...\n");
        Json *json_ptr = &json;
        for (const auto &s : arguments)
            json_ptr = &((*json_ptr)[s]);
        // printf("Info: JsonRead: type: %s  value: %s\n", json_ptr->type_name(), json_ptr->dump().c_str());
        if (json_ptr->contains("x") && json_ptr->contains("y"))
        {
            JsonRead::toVar((*json_ptr), {"x"}, vec.x);
            JsonRead::toVar((*json_ptr), {"y"}, vec.y);
        }
        else
        {
            JsonRead::displayWarning(*json_ptr, arguments,
                                     R"(sf::Vector: {"x": number, "y": number})");
            return 1;
        }
        // printf("Info: JsonRead: readed sf::Vector correctly\n");
        return 0;
    }

    static int toVar(Json &json, std::vector<std::string> arguments, std::string &str);
    static int toVar(Json &json, std::vector<std::string> arguments, std::vector<std::string> &vstr);
    static int toVar(Json &json, std::vector<std::string> arguments, sf::Color &color);
    static int toVar(Json &json, std::vector<std::string> arguments, sf::FloatRect &flrec);
};

#endif