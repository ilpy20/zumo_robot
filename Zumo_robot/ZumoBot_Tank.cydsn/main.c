/**
* @mainpage ZumoBot Project
* @brief    You can make your own ZumoBot with various sensors.
* @details  <br><br>
    <p>
    <B>General</B><br>
    You will use Pololu Zumo Shields for your robot project with CY8CKIT-059(PSoC 5LP) from Cypress semiconductor.This 
    library has basic methods of various sensors and communications so that you can make what you want with them. <br> 
    <br><br>
    </p>
    
    <p>
    <B>Sensors</B><br>
    &nbsp;Included: <br>
        &nbsp;&nbsp;&nbsp;&nbsp;LSM303D: Accelerometer & Magnetometer<br>
        &nbsp;&nbsp;&nbsp;&nbsp;L3GD20H: Gyroscope<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Reflectance sensor<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Motors
    &nbsp;Wii nunchuck<br>
    &nbsp;TSOP-2236: IR Receiver<br>
    &nbsp;HC-SR04: Ultrasonic sensor<br>
    &nbsp;APDS-9301: Ambient light sensor<br>
    &nbsp;IR LED <br><br><br>
    </p>
    
    <p>
    <B>Communication</B><br>
    I2C, UART, Serial<br>
    </p>
*/

#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "LSM303D.h"
#include "IR.h"
#include "Beep.h"
#include "mqtt_sender.h"
#include <time.h>
#include <sys/time.h>
#include "serial1.h"
#include <unistd.h>
/**
 * @file    main.c
 * @brief   
 * @details  ** Enable global interrupt since Zumo library uses interrupts. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/

#if 0
//template
void zmain(void){
    
    while(true)
    {
        BatteryLed_Write(!SW1_Read());
        vTaskDelay(100);
    }
}
#endif

#if 0
// Beep light test
void zmain(void)
{
    while(true)
    {
        if ((SW1_Read() == 0)){
            for(int i = 0; i < 3; i++){
                BatteryLed_Write(1);
                Beep(750, 30);
                vTaskDelay(500);
                BatteryLed_Write(0);
                vTaskDelay(500);
            }
            for(int i = 0; i<3; i++){
                BatteryLed_Write(1);
                Beep(750, 30);
                vTaskDelay(1000);
                BatteryLed_Write(0);
                vTaskDelay(500);
            }
            for(int i = 0; i < 3; i++){
                BatteryLed_Write(1);
                Beep(750, 30);
                vTaskDelay(500);
                BatteryLed_Write(0);
                vTaskDelay(500);
            }
        }
    }
    
    
 }   
#endif

#if 0
// Name and age
void zmain(void)
{
    TickType_t start;
    TickType_t end;
    char name[32];
    int age;
    
    
    printf("\n\n");
    
    printf("Enter your name: ");
    //fflush(stdout);
    start = xTaskGetTickCount();
    scanf("%s", name);
    printf("Enter your age: ");
    //fflush(stdout);
    scanf("%d", &age);
    end = xTaskGetTickCount();
    printf("You are [%s], age = %d\n", name, age);
    if (age <= 21){
        if(end-start < 300){
            printf("Super fast dude!");
        }
        else if((end-start >= 300)&&(end-start <=500)){
            printf("So mediocre.");
        }
        else{
            printf("My granny is faster than you!");
        }
    }
    else if((age >= 22)&&(age<=50)){
        if(end-start < 3){
            printf("Be quick or be dead");
        }
        else if((end-start >= 300)&&(end-start <=500)){
            printf("You're so average.");
        }
        else{
            printf("Have you been smoking something illegal?");
        }
    }
    else{
        if(end-start <= 300){
            printf("Still going strong");
        }
        else if((end-start >= 4)&&(end-start <=5)){
            printf("You are doing ok for your age.");
        }
        else{
            printf("Do they still allow you to drive?");
        }
    }
    while(true)
    {
        BatteryLed_Write(!SW1_Read());
        vTaskDelay(100);
    }
 }   
#endif


#if 0
//battery level//
void zmain(void)
{
	ADC_Battery_Start();   	 

	int16 adcresult =0;
	float volts = 0.0;

	printf("\nBoot\n");

	//BatteryLed_Write(1); // Switch led on
	//BatteryLed_Write(0); // Switch led off
	//uint8 button;
	//button = SW1_Read(); // read SW1 on pSoC board
	// SW1_Read() returns zero when button is pressed
	// SW1_Read() returns one when button is not pressed

	while(true)
	{
    	char msg[80];
    	ADC_Battery_StartConvert(); // start sampling
    	if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) {   // wait for ADC converted value
        	adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
        	volts=(adcresult*5/4095)*(30/20);
        	// convert value to Volts
        	// you need to implement the conversion
       	 
        	// Print both ADC results and converted value
        	printf("%d %f\r\n",adcresult, volts);
       	 
    	if (volts<4){
        	while(SW1_Read()){
            	BatteryLed_Write(1);
            	vTaskDelay(500);
            	BatteryLed_Write(0);
            	vTaskDelay(500);
        	}
    	}
    	}
    	vTaskDelay(500);
	}
 }  

   
#endif

#if 0
// button
void zmain(void)
{
    while(true) {
        printf("Press button within 5 seconds!\n");
        int i = 50;
        while(i > 0) {
            if(SW1_Read() == 0) {
                break;
            }
            vTaskDelay(100);
            --i;
        }
        if(i > 0) {
            printf("Good work\n");
            while(SW1_Read() == 0) vTaskDelay(10); // wait until button is released
        }
        else {
            printf("You didn't press the button\n");
        }
    }
}
#endif

#if 0
// button
void zmain(void)
{
    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed
    
    bool led = false;
    
    while(true)
    {
        // toggle led state when button is pressed
        if(SW1_Read() == 0) {
            led = !led;
            BatteryLed_Write(led);
            if(led) printf("Led is ON\n");
            else printf("Led is OFF\n");
            Beep(1000, 150);
            while(SW1_Read() == 0) vTaskDelay(10); // wait while button is being pressed
        }        
    }
 }   
#endif

#if 0
    void tankturn_left(uint8 speed_left, uint8 speed_right, int delay);
    
void zmain(void)
{
    Ultra_Start();
    motor_start(0,0);
    motor_forward(0,0);
    
    vTaskDelay(3000);
    
    while(true){
    int distance = Ultra_GetDistance();
    
    if(distance <= 10 && distance !=0){
        motor_backward(50,500);
        Beep(150, 200);
        motor_turn(150,150, 500);
        motor_forward(0,0);
     }
    motor_turn(200,100,50);
    }   
}
#endif

#if 0
//ultrasonic sensor//
void zmain(void)
{
    Ultra_Start();                          // Ultra Sonic Start function
    
    while(true) {
        int d = Ultra_GetDistance();
        // Print the detected distance (centimeters)
        printf("distance = %d\r\n", d);
        vTaskDelay(200);
    }
}   
#endif

#if 0
//IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    uint8_t button_;
    printf("\nStart\n");
    
    while(true){
        button_ = SW1_Read();
        if(button_==0){
            IR_Start();
            printf("\n\nIR test\n");
            struct sensors_ ref;
            struct sensors_ dig;
            bool led = false,loop = true, startline= true;
            int count =0;
            motor_start();              // enable motor controller 
            IR_flush(); // clear IR receive buffer
            printf("Buffer cleared\n");
            
            reflectance_start();
            reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
            vTaskDelay(200);
                while(startline){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    if(dig.l3 != 1 && dig.r3 != 1){
                        motor_turn(50,50,50);       // motor forward
                        Beep(60,80);
                    }
                    else{
                        motor_forward(0,0);       // Stop motors
                        startline = false;
                    }
                }
            IR_wait();  // wait for IR command
            led = !led;
            BatteryLed_Write(led);   
            
            // Toggle led when IR signal is received
            while(loop)
            {   
                if(led){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    
                    if(dig.l3 == 1 && dig.r3 == 1 ){
                        motor_turn(50,50,50);       // motor forward
                        vTaskDelay(50);
                        count++;
                        printf("count %d \n",count);
                        if(count >= 7){
                            motor_forward(0,0);       // Stop motors
                            loop = false;
                        }
                    }
                    else{
                         motor_turn(50,50,50);       // motor forward
                        Beep(100,100);
                    }
                }
                else {
                    printf("Led is OFF\n");
                    loop = false;
                }
               
            }    
        }
    }
 }   
#endif


#if 1
//IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    uint8_t button_;
    printf("\nStart\n");
    
    while(true){
        button_ = SW1_Read();
        if(button_==0){
            IR_Start();
            printf("\n\nIR test\n");
            struct sensors_ ref;
            struct sensors_ dig;
            bool led = false,loop = true, startline= true;
            int count =0;
            motor_start();              // enable motor controller 
            IR_flush(); // clear IR receive buffer
            printf("Buffer cleared\n");
            
            reflectance_start();
            reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
            vTaskDelay(200);
                while(startline){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    if(dig.l3 != 1 && dig.r3 != 1){
                        motor_turn(50,50,50);       // motor forward
                        Beep(30,30);
                    }
                    else{
                        motor_forward(0,0);       // Stop motors
                        startline = false;
                    }
                }
            IR_wait();  // wait for IR command
            led = !led;
            BatteryLed_Write(led);   
            
            // Toggle led when IR signal is received
            while(loop)
            {   
                if(led){
                    do {
                        // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    
                    if(dig.l3 == 1 && dig.r3 == 1 ){
                        
                        if(count==2){
                            motor_turn(225,10,50);       // motor turn
                            Beep(20,20);
                            vTaskDelay(5);
                            //motor_turn(50,50,50);       // motor forward
                            //Beep(50,50);
                            //vTaskDelay(5);
                            count++;
                            printf("count %d \n",count);
                        }
                        if(count<=4){
                            motor_turn(10,225,50);       // motor turn
                            Beep(20,20);
                            vTaskDelay(5);
                            //motor_turn(50,50,50);       // motor forward
                            //Beep(50,50);
                            //vTaskDelay(5);
                            count++;
                            printf("count %d \n",count);
                        }
                       // printf("count %d \n",count);
                        if(count == 5){
                            motor_forward(0,0);       // Stop motors
                            led = false;
                            BatteryLed_Write(led);
                        }
                        else{
                            motor_turn(50,50,50);       // motor forward
                            vTaskDelay(5);
                            Beep(50,50);
                            //count++;
                            printf("count %d \n",count);
                        }
                    }
                    else{
                        motor_turn(50,50,50);       // motor forward
                        vTaskDelay(5);
                        Beep(50,50);
                        //count++;
                        printf("count %d \n",count);
                        /*if(count == 36){
                            motor_forward(0,0);       // Stop motors
                            led = false;
                        }*/
                    }
                    
                
                    }while(led);
                }
                else {
                    printf("Led is OFF\n");
                    loop = false;
                }
               
            }    
        }
    }
 }  
#endif

#if 0
//IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    uint8_t button_;
    printf("\nStart\n");
    
    while(true){
        button_ = SW1_Read();
        if(button_==0){
            IR_Start();
            printf("\n\nIR test\n");
            struct sensors_ ref;
            struct sensors_ dig;
            bool led = false,loop = true, startline= true;
            int count =0;
            motor_start();              // enable motor controller 
            IR_flush(); // clear IR receive buffer
            printf("Buffer cleared\n");
            
            reflectance_start();
            reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
            vTaskDelay(200);
                while(startline){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    if(dig.l3 != 1 && dig.r3 != 1){
                        motor_turn(50,50,50);       // motor forward
                        Beep(60,80);
                    }
                    else{
                        motor_forward(0,0);       // Stop motors
                        startline = false;
                    }
                }
            IR_wait();  // wait for IR command
            led = !led;
            BatteryLed_Write(led);   
            
            // Toggle led when IR signal is received
            while(loop)
            {   
                if(led){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    
                    if(dig.l3 == 1 && dig.r3 == 1 ){
                        motor_turn(50,50,50);       // motor forward
                        vTaskDelay(50);
                        count++;
                        printf("count %d \n",count);
                        if(count >= 2){
                            motor_forward(0,0);       // Stop motors
                            loop = false;
                        }
                    }
                    else if(dig.l1 == 1 && dig.r1 == 1 ){
                        motor_turn(50,50,50);       // motor forward
                        Beep(100,100);
                    }
                    else{
                        motor_turn(0,30,0);  //eta huinya isobretena ukropami
                        Beep(100,100);       //idu buhat cherez chas
                    }
                }
               
            }    
        }
    }
 }   
#endif


#if 0
//reflectance
void zmain(void)
{
    struct sensors_ ref;
    struct sensors_ dig;

    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    

    while(true)
    {
        // read raw sensor values
        reflectance_read(&ref);
        // print out each period of reflectance sensors
        printf("%5d %5d %5d %5d %5d %5d\r\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       
        
        // read digital values that are based on threshold. 0 = white, 1 = black
        // when blackness value is over threshold the sensors reads 1, otherwise 0
        reflectance_digital(&dig); 
        //print out 0 or 1 according to results of reflectance period
        printf("%5d %5d %5d %5d %5d %5d \r\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);        
        
        vTaskDelay(200);
    }
}   
#endif


#if 0
//motor
void zmain(void)
{
    struct sensors_ ref;
    struct sensors_ dig;

    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    
    reflectance_digital(&dig);
    
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors

    vTaskDelay(3000);
    
    if(dig.l3, dig.l2, dig.l1){
        
    }
    motor_forward(100,2000);     // moving forward
    motor_turn(200,50,2000);     // turn
    motor_turn(50,200,2000);     // turn
    motor_backward(100,2000);    // moving backward
     
    motor_forward(0,0);         // stop motors

    motor_stop();               // disable motor controller
    
    while(true)
    {
        vTaskDelay(100);
    }
}
#endif

#if 0
/* Example of how to use te Accelerometer!!!*/
void zmain(void)
{
    struct accData_ data;
    
    printf("Accelerometer test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
    motor_start();              // enable motor controller
    motor_forward(0,0);
    srand(time(NULL));   // Initialization, should only be called once.
    int r=0, counter=0;
    while(true)
    {
        LSM303D_Read_Acc(&data);
       
        motor_forward(200,20);
        //vTaskDelay(200);
        if (counter == 0) r = rand() % 2;
        if (counter > 19){
            counter = 0;
            r = rand() % 2;
        }// Returns a pseudo-random integer between 0 and RAND_MAX.
            if(r == 0){
                motor_turn(200,50,5);
                vTaskDelay(0);
                //motor_forward(0,0);
            }
            else if(r == 1){
                motor_turn(50,200,5);
                vTaskDelay(0);
                //motor_forward(0,0);
            }
            else {
                motor_forward(200,20);
                vTaskDelay(0);
            }
        LSM303D_Read_Acc(&data);
        if((data.accX<-4000)){
            int r = rand() % 2;      // Returns a pseudo-random integer between 0 and RAND_MAX.
            if(r == 0){
                motor_backward(80,50);
                motor_turn(200,50,500);
                vTaskDelay(0);
                //motor_forward(0,0);
            }
            else{
                motor_backward(80,50);
                motor_turn(50,200,500);
                vTaskDelay(0);
                //motor_forward(0,0);
            }
            motor_forward(100,100);
        }
        counter++;
        printf("%8d %8d %8d\n",data.accX, data.accY, data.accZ);
        vTaskDelay(0);
    }
 }   
#endif    

#if 0
// MQTT test
void zmain(void)
{
    int ctr = 0;

    printf("\nBoot\n");
    send_mqtt("Zumo01/debug", "Boot");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 

    while(true)
    {
        printf("Ctr: %d, Button: %d\n", ctr, SW1_Read());
        print_mqtt("Zumo01/debug", "Ctr: %d, Button: %d", ctr, SW1_Read());

        vTaskDelay(1000);
        ctr++;
    }
 }   
#endif


#if 0
void zmain(void)
{    
    struct accData_ data;
    struct sensors_ ref;
    struct sensors_ dig;
    
    printf("MQTT and sensor test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Accelerometer Ok...\n");
    }
    
    int ctr = 0;
    reflectance_start();
    while(true)
    {
        LSM303D_Read_Acc(&data);
        // send data when we detect a hit and at 10 second intervals
        if(data.accX > 1500 || ++ctr > 1000) {
            printf("Acc: %8d %8d %8d\n",data.accX, data.accY, data.accZ);
            print_mqtt("Zumo01/acc", "%d,%d,%d", data.accX, data.accY, data.accZ);
            reflectance_read(&ref);
            printf("Ref: %8d %8d %8d %8d %8d %8d\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       
            print_mqtt("Zumo01/ref", "%d,%d,%d,%d,%d,%d", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);
            reflectance_digital(&dig);
            printf("Dig: %8d %8d %8d %8d %8d %8d\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);
            print_mqtt("Zumo01/dig", "%d,%d,%d,%d,%d,%d", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);
            ctr = 0;
        }
        vTaskDelay(10);
    }
 }   

#endif

#if 0
void zmain(void)
{    
    RTC_Start(); // start real time clock
    
    RTC_TIME_DATE now;

    // set current time
    now.Hour = 12;
    now.Min = 34;
    now.Sec = 56;
    now.DayOfMonth = 25;
    now.Month = 9;
    now.Year = 2018;
    RTC_WriteTime(&now); // write the time to real time clock

    while(true)
    {
        if(SW1_Read() == 0) {
            // read the current time
            RTC_DisableInt(); /* Disable Interrupt of RTC Component */
            now = *RTC_ReadTime(); /* copy the current time to a local variable */
            RTC_EnableInt(); /* Enable Interrupt of RTC Component */

            // print the current time
            printf("%2d:%02d.%02d\n", now.Hour, now.Min, now.Sec);
            
            // wait until button is released
            while(SW1_Read() == 0) vTaskDelay(50);
        }
        vTaskDelay(50);
    }
 }   
#endif

#if 0
//main project
void zmain(void){
    
}
#endif
/* [] END OF FILE */
