#ifndef __WM8978_H
#define __WM8978_H

#include <stdio.h>

#define WM8978_ADDR   0X1A	//WM8978��������ַ,�̶�Ϊ0X1A 

#define EQ1_80Hz		  0X00
#define EQ1_105Hz		  0X01
#define EQ1_135Hz		  0X02
#define EQ1_175Hz		  0X03

#define EQ2_230Hz		  0X00
#define EQ2_300Hz		  0X01
#define EQ2_385Hz		  0X02
#define EQ2_500Hz		  0X03

#define EQ3_650Hz 	  0X00
#define EQ3_850Hz		  0X01
#define EQ3_1100Hz		0X02
#define EQ3_14000Hz		0X03

#define EQ4_1800Hz		0X00
#define EQ4_2400Hz		0X01
#define EQ4_3200Hz		0X02
#define EQ4_4100Hz		0X03

#define EQ5_5300Hz		0X00
#define EQ5_6900Hz		0X01
#define EQ5_9000Hz		0X02
#define EQ5_11700Hz		0X03

class WM8978
{
  public:
    WM8978() {}
    ~WM8978() {}
    bool begin(const uint8_t sda, const uint8_t scl, const uint32_t frequency = 100000);
    void ADDA_Cfg(uint8_t dacen, uint8_t adcen);
    void Input_Cfg(uint8_t micen, uint8_t lineinen, uint8_t auxen);
    void Output_Cfg(uint8_t dacen, uint8_t bpsen);
    void MIC_Gain(uint8_t gain);
    void LINEIN_Gain(uint8_t gain);
    void AUX_Gain(uint8_t gain);
    void HPvol_Set(uint8_t voll, uint8_t volr);
    void SPKvol_Set(uint8_t volx);
    void I2S_Cfg(uint8_t fmt, uint8_t len);
    void Set_3D(uint8_t depth);
    void EQ_3D_Dir(uint8_t dir);
    void EQ1_Set(uint8_t cfreq, uint8_t gain);
    void EQ2_Set(uint8_t cfreq, uint8_t gain);
    void EQ3_Set(uint8_t cfreq, uint8_t gain);
    void EQ4_Set(uint8_t cfreq, uint8_t gain);
    void EQ5_Set(uint8_t cfreq, uint8_t gain);
    void Noise_Set(uint8_t enable, uint8_t gain);
    void ALC_Set(uint8_t enable, uint8_t maxgain, uint8_t mingain);

  private:
    uint8_t Init(void);
    uint8_t Write_Reg(uint8_t reg, uint16_t val);
    uint16_t Read_Reg(uint8_t reg);
};
#endif
