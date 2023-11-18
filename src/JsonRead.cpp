#include "JsonRead.hpp"

void JsonRead::displayWarning(Json &json, std::vector<std::string> arguments, std::string expectedType)
{
    printf("Warning: JsonRead: given json");
    for (const auto &s : arguments)
        printf("['%s']", s.c_str());
    printf(" is <%s> but expected <%s>\n", json.dump().c_str(), expectedType.c_str());
}

int JsonRead::toVar(Json &json, std::vector<std::string> arguments, std::string &str)
{
    // printf("Info: JsonRead: reading string from json ...\n");
    Json *json_ptr = &json;
    for (const auto &s : arguments)
        json_ptr = &((*json_ptr)[s]);
    // printf("Info: JsonRead: type: %s  value: %s\n", json_ptr->type_name(), json_ptr->dump().c_str());
    if (json_ptr->is_string())
    {
        str = *json_ptr;
    }
    else
    {
        JsonRead::displayWarning(*json_ptr, arguments, "string");
        return 1;
    }
    // printf("Info: JsonRead: readed string correctly\n");
    return 0;
}
int JsonRead::toVar(Json &json, std::vector<std::string> arguments, std::vector<std::string> &vstr)
{
    // printf("Info: JsonRead: reading array of strings from json ...\n");
    Json *json_ptr = &json;
    for (const auto &s : arguments)
        json_ptr = &((*json_ptr)[s]);
    // printf("Info: JsonRead: type: %s  value: %s\n", json_ptr->type_name(), json_ptr->dump().c_str());
    if (json_ptr->is_array())
    {
        vstr = std::vector<std::string>(*json_ptr);
    }
    else
    {
        JsonRead::displayWarning(*json_ptr, arguments, "array of strings");
        return 1;
    }
    // printf("Info: JsonRead: readed array of strings correctly\n");
    return 0;
}

int JsonRead::toVar(Json &json, std::vector<std::string> arguments, sf::Color &color)
{
    // printf("Info: JsonRead: reading sf::Color from json ...\n");
    Json *json_ptr = &json;
    for (const auto &s : arguments)
        json_ptr = &((*json_ptr)[s]);
    // printf("Info: JsonRead: type: %s  value: %s\n", json_ptr->type_name(), json_ptr->dump().c_str());
    if (json_ptr->contains("r") && json_ptr->contains("g") &&
        json_ptr->contains("b") && json_ptr->contains("a"))
    {
        unsigned int r, g, b, a;
        JsonRead::toVar((*json_ptr), {"r"}, r);
        JsonRead::toVar((*json_ptr), {"g"}, g);
        JsonRead::toVar((*json_ptr), {"b"}, b);
        JsonRead::toVar((*json_ptr), {"a"}, a);
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }
    else
    {
        JsonRead::displayWarning(*json_ptr, arguments,
                                 R"(sf::Color: {"r": int, "g": int, "b": int, "a": int})");
        return 1;
    }
    // printf("Info: JsonRead: readed sf::Color correctly\n");
    return 0;
}

int JsonRead::toVar(Json &json, std::vector<std::string> arguments, sf::FloatRect &flrec)
{
    // printf("Info: JsonRead: reading sf::FloatRect from json ...\n");
    Json *json_ptr = &json;
    for (const auto &s : arguments)
        json_ptr = &((*json_ptr)[s]);
    // printf("Info: JsonRead: type: %s  value: %s\n", json_ptr->type_name(), json_ptr->dump().c_str());
    if (json_ptr->contains("left") && json_ptr->contains("top") &&
        json_ptr->contains("width") && json_ptr->contains("height"))
    {
        float left, top, width, height;
        JsonRead::toVar((*json_ptr), {"left"}, left);
        JsonRead::toVar((*json_ptr), {"top"}, top);
        JsonRead::toVar((*json_ptr), {"width"}, width);
        JsonRead::toVar((*json_ptr), {"height"}, height);
        flrec.left = left;
        flrec.top = top;
        flrec.width = width;
        flrec.height = height;
    }
    else
    {
        JsonRead::displayWarning(*json_ptr, arguments,
                                 R"(sf::FloatRect: {"left": float, "top": float, "width": float, "height": float})");
        return 1;
    }
    // printf("Info: JsonRead: readed sf::FloatRect correctly\n");
    return 0;
}