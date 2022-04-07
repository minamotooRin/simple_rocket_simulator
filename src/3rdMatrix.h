#include <iostream>

typedef float FLOAT; // double is alternative

class vector3d {
    public:

        vector3d() ; 
        vector3d(FLOAT a, FLOAT b, FLOAT c) ; 
        
        FLOAT data[3];

        vector3d operator + (vector3d b) ; 
        vector3d operator * (FLOAT d) ; 
        FLOAT& operator [] (unsigned long i) ; 

        void print()
        {
            std::cout << data[0] << " " << data[1] << " " << data[2] << std::endl;
        }
};

class matrix3d {
    public:

        matrix3d() ; 

        vector3d data[3];

        vector3d operator * (vector3d v) ;

        vector3d& operator [] (unsigned long i) ; 
};
