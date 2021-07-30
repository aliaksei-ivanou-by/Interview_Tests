#include <iostream>
#include <string>

void DeleteSpaces(std::string& str)
{
    unsigned int iterator1 = 0;
    unsigned int iterator2 = 0;
    bool is_space = false;
    for (; iterator2 < str.size(); ++iterator2)
    {
        if (str[iterator2] != ' ')
        {
            is_space = false;
            str[iterator1++] = str[iterator2];
        }
        if (str[iterator2] == ' ' && !is_space)
        {
            is_space = true;
            str[iterator1++] = ' ';
        }
    }
    str.erase(iterator1);
}

int main()
{
  std::string str = "my      string";
  std::cout << str << '\n';
  DeleteSpaces(str);
  std::cout << str << '\n';
}
