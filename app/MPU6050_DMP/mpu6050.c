#include "mpu6050.h"

void MPU6050_Test(void)
{
		MPU6050_Init();  //初始化陀螺仪
 
		while(1)
		{ 
				MPU6050_Data();
		}
}

u8 mpu6050_write(u8 addr, u8 reg, u8 len, u8* buf)//返回值 0：读成功  -1：读失败
{ 
		 unsigned char i;
     addr=addr<<1;                     //注意dma库地址不包含最后一位，需要移位
		 MPU6050_IIC_Start();              //启动总线
		 MPU6050_IIC_Send_Byte(addr);      //发送器件地址           
		 MPU6050_IIC_Send_Byte(reg);       //发送器件子地址

		 for(i=0;i<len;i++)            
			 MPU6050_IIC_Send_Byte(*buf++);  //发送数据
		 MPU6050_IIC_Stop();               //结束总线

		 return 0;
}

u8 mpu6050_read(u8 addr, u8 reg, u8 len, u8 *buf)//返回值 0：读成功  -1：读失败
{
		 unsigned char i;
     addr=addr<<1;                     //注意dma库地址不包含最后一位，需要移位
		 MPU6050_IIC_Start();              //启动总线           
		 MPU6050_IIC_Send_Byte(addr);      //发送器件地址            
		 MPU6050_IIC_Send_Byte(reg);       //发送器件子地址

		 MPU6050_IIC_Start();              //重新启动总线
		 MPU6050_IIC_Send_Byte(addr+1);
		 for(i=0;i<len-1;i++)  
			 *buf++=MPU6050_IIC_Read_Byte(0);//发送数据
		 *buf=MPU6050_IIC_Read_Byte(1);
		 MPU6050_IIC_Stop();               //结束总线
	
		 return 0;
}

void mpu6050_write_reg(u8 reg, u8 dat)
{
   mpu6050_write(SlaveAddress,reg,1,&dat);
}

u8   mpu6050_read_reg (u8 reg)
{
	 u8 dat;
   mpu6050_read(SlaveAddress,reg,1,&dat);
	 return dat;
}

void MPU6050_Init(void)
{
    MPU6050_IIC_IO_Init(); 
 
    printf("MPU6050_ID=%x\r\n",mpu6050_read_reg(WHO_AM_I));
	
    mpu6050_write_reg(PWR_MGMT_1,  0x00);	//解除休眠状态
    mpu6050_write_reg(SMPLRT_DIV,  0x07); //陀螺仪采样率125Hz
    mpu6050_write_reg(CONFIG,      0x06); //低通滤波频率5Hz
	  mpu6050_write_reg(GYRO_CONFIG, 0x18); //陀螺仪自检及测量范围:不自检，2000deg/s
	  mpu6050_write_reg(ACCEL_CONFIG,0x01); //加速计自检、测量范围及高通滤波频率:不自检，2G，5Hz
}
 
void MPU6050_Data(void)
{
	u8 i;
	s16 ax,ay,az,gx,gy,gz;
	s8 data[14] ;
	for(i=0;i<14;i++) 
	{
	    data[i]=mpu6050_read_reg(0x3B+i);
	}
	ax=(data[ 0]<<8)+data[ 1];
	ay=(data[ 2]<<8)+data[ 3];
  az=(data[ 4]<<8)+data[ 5];
  gx=(data[ 8]<<8)+data[ 9];
  gy=(data[10]<<8)+data[11];
  gz=(data[12]<<8)+data[13];
    
  printf("%6d,%6d,%6d,%6d,%6d,%6d\r\n",ax,ay,az,gx,gy,gz);
}