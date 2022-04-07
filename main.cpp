#include "simulator.h"

int main()
{
    std::string input_file("parameters.txt");
    std::string output_file("output.txt");

    simulator handle(input_file, output_file);
    handle.run() ; 
    
    return 0;
}