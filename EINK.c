//////PA0	O	IO_EN
//////PA1	O	Border
//////PA2	O	DISCHANGE
//////PA3	O	Eink_ON
//////PA4	O	led
//////PA5	A	SPI_SCLK
//////PA6	A	SPI_MISO
//////PA7	A	SPI_MOSI
//////		
//////PA9	O	SPI_CS
//////PA10	IN	BUSY
//////	
//////B1	O	Eink_RESET



#define SPI1_DR_8bit          (*(__IO uint8_t *)((uint32_t)&(SPI1->DR))) 

uint16_t Spi1_send (uint8_t data){

        while (!(SPI1->SR & SPI_SR_TXE));     
        SPI1_DR_8bit = data;                       
        while (!(SPI1->SR & SPI_SR_RXNE));     
        return (SPI1_DR_8bit); 
}










int spi_init (void){
	   RCC->APB2ENR |=RCC_APB2ENR_SPI1EN;
  SPI1->CR1 |=
       SPI_CR1_BR_0 |   
       //SPI_CR1_BR_1 |
        SPI_CR1_MSTR |
        SPI_CR1_SSI  |             
        SPI_CR1_SSM	 
	//|SPI_CR1_CPOL
	//|SPI_CR1_CPHA
	;  
   SPI1->CR2  = 0x700;//8 bit mode
   SPI1->CR2 |= SPI_CR2_FRXTH;
   SPI1->CR1 |= SPI_CR1_SPE;  
	
	SPI_RxFIFOThresholdConfig (SPI1, SPI_RxFIFOThreshold_QF);
	
}

void IO_EN (int in){if(in==1){GPIO_SetBits(GPIOA,GPIO_Pin_0);}else{ GPIO_ResetBits(GPIOA,GPIO_Pin_0);};}
void Border (int in){if(in==1){GPIO_SetBits(GPIOA,GPIO_Pin_1);}else{ GPIO_ResetBits(GPIOA,GPIO_Pin_1);};}
void Dischange (int in){if(in==1){GPIO_SetBits(GPIOA,GPIO_Pin_2);}else{ GPIO_ResetBits(GPIOA,GPIO_Pin_2);};}
void EINK_ON (int in){if(in==1){GPIO_SetBits(GPIOA,GPIO_Pin_3);}else{ GPIO_ResetBits(GPIOA,GPIO_Pin_3);};}
void CS (int in){if(in==1){GPIO_SetBits(GPIOA,GPIO_Pin_9);}else{ GPIO_ResetBits(GPIOA,GPIO_Pin_9);};}
void E_RES (int in){if(in==1){GPIO_SetBits(GPIOB,GPIO_Pin_1);}else{ GPIO_ResetBits(GPIOB,GPIO_Pin_1);};}






void CE (int in){if(in==1){GPIO_SetBits(GPIOA,GPIO_Pin_4);}else{ GPIO_ResetBits(GPIOA,GPIO_Pin_4);};}

void initAll()
{

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);//ok
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);//ok
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);//ok
	
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//ok
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);//ok
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);//ok
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);//ok

RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//ok
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);//ok
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//ok
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ok
RCC_APB2PeriphClockCmd(RCC_APB2Periph_DBGMCU, ENABLE);//ok	
	
RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);//ok
//RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);//ok
RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//ok








////////////////////PWM
TIM_OCStructInit(&timerPWM);
timerPWM.TIM_Pulse = 1;
timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
timerPWM.TIM_OutputState = TIM_OutputState_Enable;
TIM_OC1Init(TIM3,&timerPWM);	
	
//GPIOB->MODER
	
/*////////////////B1 Blink
GPIO_StructInit(&port);
port.GPIO_Mode = GPIO_Mode_AF;
port.GPIO_Pin = GPIO_Pin_1;
port.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_Init(GPIOB, &port);
*/
	
////////////// OUTPUTS
GPIO_StructInit(&port);
port.GPIO_Mode = GPIO_Mode_OUT;
port.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_9;
port.GPIO_Speed = GPIO_Speed_50MHz;
port.GPIO_OType = GPIO_OType_PP;
port.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA, &port);	

GPIO_StructInit(&port);
port.GPIO_Mode = GPIO_Mode_OUT;
port.GPIO_Pin = GPIO_Pin_1;
port.GPIO_Speed = GPIO_Speed_50MHz;
port.GPIO_OType = GPIO_OType_PP;
port.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOB, &port);	



////////////// INPUTS
GPIO_StructInit(&port);
port.GPIO_Mode = GPIO_Mode_IN;
port.GPIO_Pin = GPIO_Pin_10;
port.GPIO_Speed = GPIO_Speed_10MHz;
port.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA, &port);		




//////////////F0
GPIO_StructInit(&port);
port.GPIO_Mode = GPIO_Mode_OUT;
port.GPIO_Pin = GPIO_Pin_0;
port.GPIO_Speed = GPIO_Speed_2MHz;
port.GPIO_OType = GPIO_OType_PP;
port.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOF, &port);	

//////////////F1 
GPIO_StructInit(&port);
port.GPIO_Mode = GPIO_Mode_OUT;
port.GPIO_Pin = GPIO_Pin_1;
port.GPIO_Speed = GPIO_Speed_2MHz;
port.GPIO_OType = GPIO_OType_PP;
port.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOF, &port);	








/////////////////////SPI
      GPIO_PinAFConfig(GPIOA, GPIO_Pin_5,GPIO_AF_0);//CLK
      GPIO_PinAFConfig(GPIOA, GPIO_Pin_6,GPIO_AF_0);//IN
      GPIO_PinAFConfig(GPIOA, GPIO_Pin_7,GPIO_AF_0);//DATA

      port.GPIO_Pin =   GPIO_Pin_5  |GPIO_Pin_6  | GPIO_Pin_7;
      port.GPIO_Mode =  GPIO_Mode_AF;
      port.GPIO_Speed = GPIO_Speed_10MHz;
      port.GPIO_OType = GPIO_OType_PP;
      port.GPIO_PuPd  = GPIO_PuPd_NOPULL;
      GPIO_Init(GPIOA, &port);







////////////TMR 1 
TIM_TimeBaseStructInit(&timer);
timer.TIM_Prescaler = 72;// TMR_PRSLR 720
timer.TIM_Period = 5000;
TIM_TimeBaseInit (TIM1,&timer);

////////////TMR 3 
TIM_TimeBaseStructInit(&timer);
timer.TIM_Prescaler = 3;// TMR_PRSLR 720
timer.TIM_Period = 4100;
TIM_TimeBaseInit (TIM3,&timer);
	
////////////TMR 14 
TIM_TimeBaseStructInit(&timer);
timer.TIM_Prescaler = 72;// TMR_PRSLR 720
timer.TIM_Period = 500;
TIM_TimeBaseInit (TIM14,&timer);
	
////////////TMR 16 
TIM_TimeBaseStructInit(&timer);
timer.TIM_Prescaler = 72;// TMR_PRSLR 720
timer.TIM_Period = 5000;
TIM_TimeBaseInit (TIM16,&timer);

////////////TMR 17 
TIM_TimeBaseStructInit(&timer);
timer.TIM_Prescaler = 72;// TMR_PRSLR 720
timer.TIM_Period = 5000;
TIM_TimeBaseInit (TIM17,&timer);
	
}	

uint8_t Eink_SPI_W(uint8_t com, uint8_t data)
{
CS (1);Delay (10);	
CS (0);
Spi1_send(0x70);
Spi1_send(com);
	Delay (1);	
CS (1);	

	Delay (2);	
// delay_80ns	
CS (0);
Spi1_send(0x72);
Spi1_send(data);
	Delay (1);	
CS (1);	
	Delay (1);	
}

uint8_t Eink_SPI_Chanel()
{
CS (1);Delay (10);	
CS (0);
Spi1_send(0x70);
Spi1_send(1);
	Delay (1);	
CS (1);	

	Delay (2);	
// delay_80ns	
CS (0);
Spi1_send(0x72);
Spi1_send(0);Spi1_send(0);
Spi1_send(0);Spi1_send(0x7F);
Spi1_send(0xff);Spi1_send(0xfe);
Spi1_send(0);Spi1_send(0);
	Delay (1);	
CS (1);	
	Delay (1);	
}

void display_off()
{
	
	for(uint8_t s =0;s<176;s++)
{
CS (1);Delay (10);	
CS (0);
Spi1_send(0x70);
Spi1_send(0x0A);
	Delay (1);	
CS (1);	

	Delay (2);	
// delay_80ns	
CS (0);
//Spi1_send(0x72);
Spi1_send(0);
	
for(uint8_t i =0;i<33;i++)	Spi1_send(0x00);
for(uint8_t i =0;i<44;i++)	Spi1_send(0x00);	
for(uint8_t i =0;i<33;i++)	Spi1_send(0x00);	
	
	Delay (10);	
CS (1);	
	Delay (1);	
	Eink_SPI_W(0x02,0x07);  //Output enable to disable
}
	Delay (30);	
Border (0);
	Delay (150);	//150
Border (1);

Eink_SPI_W(0x0B,0x00);
Eink_SPI_W(0x03,0x01);
Eink_SPI_W(0x05,0x03);
Eink_SPI_W(0x05,0x01);
	Delay (330);	//330
Eink_SPI_W(0x05,0x00);
Eink_SPI_W(0x07,0x01);
	Delay (60);//60
IO_EN (1);
	Delay (10);
CS (0);
E_RES (0);
EINK_ON (0);

Dischange (1);
	Delay (150);//150
Dischange (1);
}




void display_init()
{
	int i=0;
// 3. Power On G2 COG Driver
Dischange (0);
EINK_ON (1);
IO_EN (0);
EINK_ON (1);
E_RES (1);
CS (1);	
Border (1);
Delay_ms (7);	
E_RES (0);
Delay_ms (7);	
E_RES (1);
Delay_ms (10);
	
// 4. Initialize G2 COG Driver
while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10));	
//	Check COG Driver IDSPI_RID*1 == 0x12
Eink_SPI_W(0x02,0x40);	//SystemYesDisable OE
Eink_SPI_W(0x0B,0x02);	//Power Saving Mode
Eink_SPI_Chanel();	//2.7”: SPI(0x01, (0x0000,007F,FFFE,0000))
Eink_SPI_W(0x07,0xD1);	//High Power Mode Osc Setting
Eink_SPI_W(0x08,0x02);	//Power Setting
Eink_SPI_W(0x09,0xC2);	//Set Vcom level
Eink_SPI_W(0x04,0x03);	//Power Setting
Eink_SPI_W(0x03,0x01);  //Driver latch on
Eink_SPI_W(0x03,0x00);  //Driver latch off
Delay_ms (6);
i=1;
while (i!=2)//4
{
Eink_SPI_W(0x05,0x01);  //Start chargepump positive voltage VGH & VDH on*3
	Delay_ms (160);
Eink_SPI_W(0x05,0x03);  //Start chargepump negative voltage VGL & VDL on*4
	Delay_ms (100);
Eink_SPI_W(0x05,0x0F);  //Set chargepump Vcom on
	Delay_ms (50);
	
	///////////////////!!!!!!!!!!!!
	// 4Check DC/DCSPI_R(0x0F,0x00) & 0x40 == 0x40
	///////////////////!!!!!!!!!!!!
	i++;
}
Eink_SPI_W(0x02,0x06);  //Output enable to disable
}



void display_Black_Frame()
{
// Section 5
//Write data from the Memory to the EPD

for(uint8_t s =0;s<176;s++)
{
CS (1);Delay (10);	
CS (0);
Spi1_send(0x70);
Spi1_send(0x0A);
	Delay (1);	
CS (1);	

	Delay (2);	
// delay_80ns	
CS (0);
Spi1_send(0x72);
Spi1_send(0);
	
for(uint8_t i =0;i<33;i++)	Spi1_send(0xff);
for(uint8_t i =0;i<44;i++)	Spi1_send(0xff);	
for(uint8_t i =0;i<33;i++)	Spi1_send(0xff);	
	
	Delay (10);	
CS (1);	
	Delay (1);	
	Eink_SPI_W(0x02,0x07);  //Output enable to disable
}
Border (1);
}

void display_line_Frame()
{
// Section 5
//Write data from the Memory to the EPD

for(uint8_t s =0;s<176;s++)
{
CS (1);Delay (10);	
CS (0);
Spi1_send(0x70);
Spi1_send(0x0A);
	Delay (1);	
CS (1);	

	Delay (2);	
// delay_80ns	
CS (0);
Spi1_send(0x72);
Spi1_send(0);
	
for(uint8_t i =0;i<33;i++)	Spi1_send(0xee);
for(uint8_t i =0;i<44;i++)	Spi1_send(0xff);	
for(uint8_t i =0;i<33;i++)	Spi1_send(0xbb);	
	
	Delay (10);	
CS (1);	
	Delay (1);	
	Eink_SPI_W(0x02,0x07);  //Output enable to disable
}
Border (1);
}

void display_BW_Frame()
{
// Section 5
//Write data from the Memory to the EPD

for(uint8_t s =0;s<176/2;s++)
{
	{
CS (1);Delay (10);	
CS (0);
Spi1_send(0x70);
Spi1_send(0x0A);
	Delay (1);	
CS (1);	

	Delay (2);	
// delay_80ns	
CS (0);
Spi1_send(0x72);
Spi1_send(0);
	
for(uint8_t i =0;i<33;i++)	Spi1_send(0xff);
for(uint8_t i =0;i<44;i++)	Spi1_send(0xff);	
for(uint8_t i =0;i<33;i++)	Spi1_send(0xaa);	
	
	Delay (10);	
CS (1);	
	Delay (1);	
	Eink_SPI_W(0x02,0x07);  //Output enable to disable
}
}
Border (1);
}


void display_White_Frame()
{
// Section 5
//Write data from the Memory to the EPD

for(uint8_t s =0;s<176;s++)
{
CS (1);Delay (10);	
CS (0);
Spi1_send(0x70);
Spi1_send(0x0A);
	Delay (1);	
CS (1);	

	Delay (2);	
// delay_80ns	
CS (0);
Spi1_send(0x72);
Spi1_send(0);
	
for(uint8_t i =0;i<33;i++)	Spi1_send(0xaa);
for(uint8_t i =0;i<44;i++)	Spi1_send(0xff);	
for(uint8_t i =0;i<33;i++)	Spi1_send(0xaa);	
	
	Delay (10);	
CS (1);	
	Delay (1);	
	Eink_SPI_W(0x02,0x07);  //Output enable to disable
}
Border (1);
}

void display_Frame( const uint8_t * A, uint8_t NEG)
{
uint16_t c = 0;

for(uint8_t s=0;s<176;s++)
{
CS (1);Delay (10);	
CS (0);
Spi1_send(0x70);
Spi1_send(0x0A);
	Delay (5);	
CS (1);	

	Delay (5);	
// delay_80ns	
CS (0);
Spi1_send(0x72);
Spi1_send(0);
	
/// OK!!!	
	uint8_t scan [44]={0};
scan[(s>>2)]=0x3<<((s-(s>>2)*4)*2);	

uint8_t line_2_N [33] = {0};
	uint8_t line_1_C [33] = {0};


if(NEG!=1)
{

for(uint8_t i =0;i<33;i++)	line_1_C [i] =0xAA;// i+1;	

for(uint8_t i =0;i<=33;i++)	line_2_N [i] = 0xAA;//i+101;

	for(uint8_t byte = 0;byte<66;byte+=2)
	{
		for(uint8_t bit = 0;bit<8;bit++)
		{
			if(bit==0|bit==2|bit==4|bit==6)
			{
				//if Line 1
				if (A[c]&(1<<(bit))){line_2_N[byte/2]|=3<<(bit);}//ok
			}
		else
			{
				// if Line 2
				if (A[c]&(1<<(8-bit))){line_1_C[byte/2]|=3<<(bit-1);}
			}
		}
		c++;
	}
}
else
{
	
	for(uint8_t i =0;i<33;i++)	line_1_C [i] =0xFF;// i+1;	

	for(uint8_t i =0;i<=33;i++)	line_2_N [i] = 0xFF;//i+101;
		
	for(uint8_t byte = 0;byte<66;byte+=2)
	{
		for(uint8_t bit = 0;bit<8;bit++)
		{
			if(bit==0|bit==2|bit==4|bit==6)
			{
				//if Line 1
				if (A[c]&(1<<(bit))){line_2_N[byte/2]&=~(1<<(bit));}//ok
			}
		else
			{
				// if Line 2
				if (A[c]&(1<<(8-bit))){line_1_C[byte/2]&=~(3<<(bit-1));}
			}
		}
		c++;
	}
}













for(uint8_t i =0;i<33;i++)	Spi1_send(line_1_C[32-i]);Delay (10);
for(uint8_t i =0;i<44;i++)	Spi1_send(scan[43-i]);Delay (10);	// OK!!
for(uint8_t i =0;i<33;i++)	Spi1_send(line_2_N[i]);	
	
	Delay (10);	
CS (1);	
	Delay (1);	
	Eink_SPI_W(0x02,0x07);  //Output enable to disable
}
Border (1);

}


void EINK_START ()
{
IO_EN (0);
Border (0);
Dischange (0);
EINK_ON (1);
CS (0);
E_RES (0);


display_init();
display_Black_Frame();Delay_ms (300);
display_off();

display_init();
display_White_Frame();Delay_ms (300);
display_off();

display_init();
display_Black_Frame();Delay_ms (300);
display_off();

display_init();
display_White_Frame();Delay_ms (300);
display_off();

display_init();
display_White_Frame();Delay_ms (300);
display_off();

}

void EINK_LINES_B ()
{
display_init();
display_line_Frame();Delay_ms (200);
display_off();

display_init();
display_line_Frame();Delay_ms (200);
display_off();

}

void EINK_LINES_I ()
{
display_init();
display_BW_Frame();Delay_ms (200);
display_off();

display_init();
display_BW_Frame();Delay_ms (200);
display_off();
}

void EINK_WHITE ()
{
display_init();
display_White_Frame();Delay_ms (500);
display_off();
display_init();
display_White_Frame();Delay_ms (500);
display_off();
}

void EINK_BLACK ()
{
display_init();
display_Black_Frame();Delay_ms (500);
display_off();
display_init();
display_Black_Frame();Delay_ms (500);
display_off();
}

void EINK_PRINT_PIC (const uint8_t * A)
{
display_init();
display_Frame(A, 0);
Delay_ms (200);
display_off();

display_init();
display_Frame(A, 0);
Delay_ms (200);
display_off();

display_init();
display_Frame(A, 0);
Delay_ms (200);
display_off();
}

void EINK_ERACE_PIC (const uint8_t * A)
{
display_init();
display_Frame(A, 1);
Delay_ms (200);
display_off();

EINK_WHITE ();
}


int main(){
{//init dev
	rc48mhz();
__enable_irq();	
		spi_init();
initAll();
TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//IRQ OWER CLOCK
TIM_Cmd(TIM3,ENABLE); //TIMER6_ON
NVIC_EnableIRQ(TIM1_CC_IRQn);	//IRQ_ON
}
EINK_START ();
EINK_LINES_I ();
Delay_ms (3000);
EINK_START ();
EINK_LINES_B ();
Delay_ms (3000);
EINK_PRINT_PIC(pic1);
Delay_ms (3000);
EINK_ERACE_PIC(pic1);
Delay_ms (3000);
EINK_BLACK ();
EINK_WHITE();
EINK_PRINT_PIC(pic1);

uint16_t c=0;
while(1){
CE(1);
	Delay_ms (100);
	CE(0);
	Delay_ms (100);
	if(c++>300){EINK_PRINT_PIC(pic1);c=0;}
	}
}
