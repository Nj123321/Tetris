#include <fstream>
#include <ostream>
#include <string>
#include <iostream>

class ModFileInputStream
{
    std::ifstream inputFile;
    float modWidth = 0;
public:
    ModFileInputStream(std::string fileName);
    ~ModFileInputStream() = default;

    bool isOpen();
    float getModWidth();
};

ModFileInputStream::ModFileInputStream(std::string fileName)
{
    std::string tmp;
    inputFile.open(fileName);
    try
    {
        if (!inputFile)
        {
            std::cerr << "Mod file could not be found. Throwing Exception" << std::endl;
            throw std::runtime_error("Cannot open file.");
        }

        while (inputFile >> tmp)
        {
            modWidth = std::stof(tmp);
        }

        std::cout << "ModFile read in successfully: modWidth: " << modWidth << std::endl;
    }
    catch (const std::invalid_argument &)
    {
        std::cout << "Error: The string '" << tmp << "' is not float." << std::endl;
    }
    catch (...)
    {
    }
}

bool ModFileInputStream::isOpen() {
    return inputFile.is_open();
}
