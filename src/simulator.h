#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>

#include "3rdMatrix.h"

#define ZERO (1e-7)

struct stage {
    FLOAT A ;
    FLOAT mf_rate ; 
    FLOAT ue ; 
    FLOAT mR ; 
    FLOAT m0 ; 
    FLOAT dt ; 
    FLOAT mf ; 
};

class simulator {

    public:

        simulator(std::string input_filename , std::string output_filename );

        void run(); 
        
        FLOAT total_T ; 
        FLOAT v_terminal ; 
        FLOAT max_h ; 

    private: 

        FLOAT h ;
        FLOAT v ; 
        FLOAT m ; 

        FLOAT Cd ; 
        FLOAT rho ; 
        FLOAT g ; 

        std::vector<stage> stages ;  

        std::ofstream ofs; 

        void read_parameters(std::string input_filename) ;
        
};