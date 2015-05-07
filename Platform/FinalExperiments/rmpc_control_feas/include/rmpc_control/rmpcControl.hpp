#ifndef __SO3_CONTROL_H__
#define __SO3_CONTROL_H__

#include <Eigen/Geometry>
#include <vector>
class rmpcControl
{
 public:
  rmpcControl();

  void setMass(const float mass);
  void setGravity(const float g);
  void setPosition(const Eigen::Vector3f &position);
  void setVelocity(const Eigen::Vector3f &velocity);
  void setYaw(const float current_yaw);
  void setMaxIntegral(const float max_integral);
  void resetIntegrals(void);
  void setOptParams( std::vector<double> A,
		     std::vector<double> B,
		     std::vector<double> x_limit,
	             std::vector<double> u_limit,
		     std::vector<double> ZfA_11, 	
                     std::vector<double> Zfb_11,
                     std::vector<double> ZfA_22, 	
                     std::vector<double> Zfb_22,
                     std::vector<double> ZfA_33, 	
                     std::vector<double> Zfb_33,
                     std::vector<double> ZfA_44, 	
                     std::vector<double> Zfb_44,
                     std::vector<double> ZA_110,                              
                     std::vector<double> Zb_110,
                     std::vector<double> ZA_111,
                     std::vector<double> Zb_111,
                     std::vector<double> ZA_112,
                     std::vector<double> Zb_112,
                     std::vector<double> ZA_113,
                     std::vector<double> Zb_113,
                     std::vector<double> ZA_114,
                     std::vector<double> Zb_114,
                     std::vector<double> ZA_115,
                     std::vector<double> Zb_115,
                     std::vector<double> ZA_116,
                     std::vector<double> Zb_116,
                     std::vector<double> ZA_117,
                     std::vector<double> Zb_117,
                     std::vector<double> ZA_118,
                     std::vector<double> Zb_118,
                     std::vector<double> ZA_119,
                     std::vector<double> Zb_119,
                     std::vector<double> ZA_1110,
                     std::vector<double> Zb_1110,
                     std::vector<double> ZA_1111,
                     std::vector<double> Zb_1111,
            std::vector<double> ZA_220, 
            std::vector<double> Zb_220,
            std::vector<double> ZA_221,
            std::vector<double> Zb_221,
            std::vector<double> ZA_222,
            std::vector<double> Zb_222,
            std::vector<double> ZA_223,
            std::vector<double> Zb_223,
            std::vector<double> ZA_224,
            std::vector<double> Zb_224,
            std::vector<double> ZA_225,
            std::vector<double> Zb_225,
            std::vector<double> ZA_226,
            std::vector<double> Zb_226,
            std::vector<double> ZA_227,
            std::vector<double> Zb_227,
            std::vector<double> ZA_228,
            std::vector<double> Zb_228,
            std::vector<double> ZA_229,
            std::vector<double> Zb_229,
            std::vector<double> ZA_2210,
            std::vector<double> Zb_2210,          
            std::vector<double> ZA_2211,
            std::vector<double> Zb_2211,
             std::vector<double> ZA_330, 
             std::vector<double> Zb_330,
             std::vector<double> ZA_331,
             std::vector<double> Zb_331,
             std::vector<double> ZA_332,
             std::vector<double> Zb_332,
             std::vector<double> ZA_333,
             std::vector<double> Zb_333,
             std::vector<double> ZA_334,
             std::vector<double> Zb_334,
             std::vector<double> ZA_335,
             std::vector<double> Zb_335,
             std::vector<double> ZA_336,
             std::vector<double> Zb_336,
             std::vector<double> ZA_337,
             std::vector<double> Zb_337,
             std::vector<double> ZA_338,
             std::vector<double> Zb_338,
             std::vector<double> ZA_339,
             std::vector<double> Zb_339,
             std::vector<double> ZA_3310,
             std::vector<double> Zb_3310, 
             std::vector<double> ZA_3311,
             std::vector<double> Zb_3311,
            std::vector<double> ZA_440, 
            std::vector<double> Zb_440,
            std::vector<double> ZA_441,
            std::vector<double> Zb_441,
            std::vector<double> ZA_442,
            std::vector<double> Zb_442,
            std::vector<double> ZA_443,
            std::vector<double> Zb_443,
            std::vector<double> ZA_444,
            std::vector<double> Zb_444,
            std::vector<double> ZA_445,
            std::vector<double> Zb_445,
            std::vector<double> ZA_446,
            std::vector<double> Zb_446,
            std::vector<double> ZA_447,
            std::vector<double> Zb_447,
            std::vector<double> ZA_448,
            std::vector<double> Zb_448,
            std::vector<double> ZA_449,
            std::vector<double> Zb_449,
            std::vector<double> ZA_4410,
            std::vector<double> Zb_4410,
            std::vector<double> ZA_4411,
            std::vector<double> Zb_4411);





 void calculateControl(const Eigen::Vector3f &des_pos,
                        const Eigen::Vector3f &des_vel,
                        const Eigen::Vector3f &des_acc,
                        const float des_yaw,
                        const Eigen::Vector3f &kx,
                        const Eigen::Vector3f &kv,
                        const Eigen::Vector3f &ki,
                        const float ki_yaw);


  const Eigen::Vector4f &getControls(void);

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

 private:
  // Inputs for the controller
  float mass_;
  float g_;
  Eigen::Vector3f pos_;
  Eigen::Vector3f vel_;
  float current_yaw_;
  Eigen::Vector3f pos_int_;
  float yaw_int_;
  float max_pos_int_;

  // Outputs of the controller
  Eigen::Vector4f trpy_;
};

#endif
