#include "pid.h"
#include "usart1.h"
#include "pwm.h"

int OUTPUT,OUTPUT1;					// OUTPUT 是控制舵机的PWM输出值; OUTPUT1 是控制小车速度的PWM输出值
int PID_value=0;					//舵机PID控制器的PWM输出值
int PID_jc=0;						//小车基础速度PID控制器的PWM输出值
int PID_sd=0;						//小车速度变化PID控制器的PWM输出值

extern int error;					//引用main.c定义的error，才能在本文件内使用error该变量  //作为舵机PID控制器和差速PID控制器的传参输入值

extern int a;						//引用main.c定义的a，才能在本文件内使用a该变量  //作为基础速度PID控制器的传参输入值

//void TIM2_IRQHandler(void)   		//TIM3中断服务函数
//{
//	if(TIM2->SR&0X0001)				//定时器每10ms定时中断一次
//	{   
//		  TIM2->SR&=~(1<<0);		//清除定时器三的计时标志，执行完TIM3中断服务函数里的操作后定时器会重新计时
//   		  PID_value=Position_PD (error,0);	//将舵机PID控制器输出的PWM值赋值给PID_value  //将error和0传入
//		  PID_jc=Position_P (a,0);				//将基础速度PID控制器输出的PWM值赋值给PID_jc         //将a和0传入
//		  Xianfu_PID();							//限幅函数
//		  Su();									//PWM输出函数
//		}
//}


void pid_control(void){
		  PID_value=Position_PD (error,0);		//将舵机PID控制器输出的PWM值赋值给PID_value  //将error和0传入
		  PID_jc=Position_P (a,0);				//将基础速度PID控制器输出的PWM值赋值给PID_jc         //将a和0传入
		  Xianfu_PID();							//限幅函数
		  Su();									//PWM输出函数
}
	
/*PID控制全部都属于位置式PID*/

int Position_P (int Encoder,int Target)   		//基础速度PID控制器//这里Encoder=a，Target=0;
{  
	 float Position_KP=800,Position_KD=0; 		//参数整定，需要调到适合自己小车的数值大小  //因为没有用到KI(积分)，所以这里去除了和KI相关的式子
	 static float Bias,Pwm,Last_Bias;
	 Bias=Encoder-Target; 						//偏差=实际值-目标值
	 Pwm=7000-Position_KP*Bias+Position_KD*(Bias-Last_Bias);//位置式PID控制器//这里7000是小车电机PWM的最大值，也就是主函数TIM2的传参传入的数，当error为零时，表示小车处于黑线的中央，没有偏移，所以这时a=0，使得最后返回的PWM值为7200，使电机达到最大速度
	 Last_Bias=Bias;                                       	//保存上一次偏差 
	 return Pwm;                                           	//返回PWM值
}


int Position_PD (int Encoder,int Target)   		//舵机PID控制器//这里Encoder=error，Target=0;
{ 	
	 float Position_KP=10,Position_KD=0.1;
	 static float Bias,Pwm,Last_Bias;
	 Bias=Encoder-Target;                       //计算偏差
												//求出偏差的积分
	 Pwm=Position_KP*Bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       	  //保存上一次偏差 
	 return Pwm;                                              //返回PWM值
}
//int Position_PID (int Encoder,int Target)   //差速PID控制器//这里Encoder=error，Target=0;
//{ 	
//	 float Position_KP=240,Position_KI=0.5,Position_KD=4500;
//	 static float Bias,Pwm,Integral_bias,Last_Bias;
//	 Bias=Encoder-Target;                                  //计算偏差
//	 Integral_bias+=Bias;	                                 //求出偏差的积分
//	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
//	 Last_Bias=Bias;                                       //保存上一次偏差 
//	 return Pwm;                                           //返回PWM值
//}
void Su(void)//将OUTPUT，OUTPUT1，OUTPUT2输出出去，使舵机和小车电机受到相应控制
{
		  
			TIM_SetCompare1(TIM4,OUTPUT); //舵机控制
			TIM_SetCompare2(TIM3,OUTPUT1);//电机控制

}	

void Xianfu_PID(void)//限幅
{
	OUTPUT=1450+PID_value;//725时，舵机的连接杆和黑线重合，也就是处于中央位置
	OUTPUT1=PID_jc;//基础速度+速度偏差量 //基础速度也可以恒定为某个值，这样调差速和舵机就比较好调
	
	
	
//		 /*控制舵机的PWM有效值范围为500-2500*/
//    if(OUTPUT>1000) {OUTPUT=1000;}
//    if(OUTPUT<450) {OUTPUT=450;}
	   /*控制小车电机的PWM有效值范围为0-7200*/
	if(OUTPUT1>6000) OUTPUT1=6000;
    if(OUTPUT1<0) OUTPUT1=0;

		
}



