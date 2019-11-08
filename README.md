# zumo_robot

censors 

#if 1
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
