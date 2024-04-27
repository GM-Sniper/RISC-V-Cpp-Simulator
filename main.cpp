#include <iostream>
#include <string>


void simulate()
{
    std::cout<<"2"<<std::endl;
    std::cout<<"2"<<std::endl;
}

int main()
{
    std::string input1, input2;

    // Read the first input string
    //std::cout << "Enter first string: ";
    std::getline(std::cin, input1);

    // Read the second input string
   // std::cout << "Enter second string: ";
    std::getline(std::cin, input2);

    // Process the input strings (example: concatenate them)

    std::cout << "first string: " << input1 << std::endl;
    std::cout << "second string: " << input2 << std::endl;
    simulate();

    
    // Perform your program logic here based on the input strings

    // Return an exit code (optional)
    return 0;
}
