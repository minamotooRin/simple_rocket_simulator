#include "simulator.h"

simulator::simulator( std::string input_filename , std::string output_filename )
{
    read_parameters(input_filename) ; 
    
    ofs.open(output_filename) ; 
}

/*
Format:
ρ g CD v0 h0
m0 mR A m ̇f ue ∆t
m0 mR A m ̇f ue ∆t
m0 mR A m ̇f ue ∆t
...
*/
void simulator::read_parameters(std::string input_filename) 
{
    std::ifstream ifs(input_filename);
    if ( !ifs.is_open() )
    {
        std::cout << "no data!" << std::endl;
        return ; 
    }
    
    ifs >> rho ; 
    ifs >> g ; 
    ifs >> Cd ; 
    ifs >> v ; 
    ifs >> h ; 

    m = 0 ; 

    while( !ifs.eof() )
    {
        stage para; 
        ifs >> para.m0 ; 
        ifs >> para.mR ; 
        ifs >> para.A ; 
        ifs >> para.mf_rate ; 
        ifs >> para.ue ; 
        ifs >> para.dt ; 

        m       += para.m0 ; 
        para.mf =  para.m0 - para.mR ; 

        stages.push_back(para) ;         
    }

    // free fall
    
    stage &lastStage = stages.back(); 
    stage fallStage; 
    fallStage.mf        = 1;
    fallStage.m0        = lastStage.mR;
    fallStage.mR        = lastStage.mR;
    fallStage.A         = lastStage.A;
    fallStage.mf_rate   = 0;
    // fallStage.ue        = lastStage.ue; // unmeaningful
    fallStage.dt        = lastStage.dt;
    stages.push_back(fallStage) ;   
    
    return ; 
}

void simulator::run()
{
    total_T     = 0 ; 
    max_h       = h ; 
    v_terminal  = 0 ; 

    vector3d x(h , v , m) ; 
    FLOAT& h_ = x[0];
    FLOAT& v_ = x[1];
    FLOAT& m_ = x[2];

    vector3d k1 ; 
    vector3d k2 ;
    vector3d k3 ;
    vector3d k4 ;   

    /*
        generating matrix of M(x) in the eqaution
        | 0 1    0 |
        | 0 f(x) 0 |
        | 0 0    0 |  
    */
    matrix3d M ;     
    M[0][0] = 0 ;  
    M[0][1] = 1 ; 
    M[2][2] = 0 ; 

    bool isLanded = false;
    for(size_t i = 0 ; i < stages.size() ; i++)
    { 
        vector3d B(0 , -g , -stages[i].mf_rate ) ;   
        auto F = [&](vector3d x_) -> vector3d
        {
            M[1][1] = ( 2 * stages[i].mf_rate * stages[i].ue - rho * Cd * x_[1] * x_[1] * stages[i].A ) / (2 * x_[2] * fabs(x_[1]));
            return M * x_ + B;
        };
        // for(unsigned int j = 0 ; j < (stages[i].mf / stages[i].mf_rate) / stages[i].dt ; j++  )
        while(stages[i].mf > 0)
        {
            ofs << total_T << " " << h_ << " " << v_ << " " << m_ << std::endl;
            
            total_T += stages[i].dt ; 

            stages[i].mf -= stages[i].mf_rate * stages[i].dt;
            
            k1 = F(x); 
            k2 = F(x + k1 * (stages[i].dt/2) ); 
            k3 = F(x + k2 * (stages[i].dt/2) );
            k4 = F(x + k3 * stages[i].dt ); 

            x = x + (k1 + k2 * 2 + k3 * 2 + k4 ) * (stages[i].dt/6) ; 

            max_h = max_h < h_ ? h_ : max_h;

            if(h_ < ZERO)
            {   
                isLanded = true;
                break;
            }
        }
        
        if(isLanded) break;

        if( i < stages.size() - 2)
            m_ -= stages[i].mR;
    }
        
    ofs << total_T << " " << h_ << " " << v_ << " " << m_ << std::endl;    

    return ;
}
