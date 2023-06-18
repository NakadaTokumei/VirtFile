#include <iostream>

#include "VirtFile.hpp"

int main(int argc, char** argv)
{
    VirtFile<4096> file;

    file.Open("testfile.txt");
    std::cout << file[0] << std::endl;
    file.Close();
}