#include "PID.h"
#include <limits>       // std::numeric_limits

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	p_error = 0;
 	i_error = 0;
	d_error = 0;
}

void PID::UpdateError(double cte) {
	d_error = (cte - p_error);
  	p_error = cte;
  	i_error += cte;

}

double PID::TotalError() {
  return p_error * Kp + i_error * Ki + d_error * Kd;
}


void PID::UpdateParameters(double tol){

	double p[] = {Kp, Ki, Kd};
   	double dp[] = {1.0, 1.0, 1.0};
   	int it = 0;
   	double best_err = std::numeric_limits<double>::max();
   	double err;
   	double sum_dp = dp[0]+dp[1]+dp[2];

   	while (sum_dp > tol){
        for(int i = 0; i < 3; i++){
            p[i] += dp[i];

			this->Kp = p[0];
			this->Ki = p[1];
			this->Kd = p[2];

            err = TotalError();
            if (err < best_err){
                best_err = err;
                dp[i] *= 1.1;
            }else{
                p[i] -= 2 * dp[i];


				this->Kp = p[0];
				this->Ki = p[1];
				this->Kd = p[2];
                err = TotalError();

                if (err < best_err){
                    best_err = err;
                    dp[i] *= 1.1;
                }else{
                    p[i] += dp[i];
                    dp[i] *= 0.9;
                }
            }
    	}
    	sum_dp = dp[0]+dp[1]+dp[2];
    }
}