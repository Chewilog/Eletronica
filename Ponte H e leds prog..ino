//leitores
int pinChave = 1;                                           //pino em que será acoplada a chave
int pot = A0;                                               //pino ligado ao potenciometro
int chave = LOW;                                            //variavel para estocar o valor da chave
//transistores
int PHQ1 = 13;                                              //Transistor Q1 da ponte h
int PHQ2 = 12;                                              //Transistor Q2 da ponte h
int PHQ3 = 11;                                              //Transistor Q3 da ponte h
int PHQ4 = 10;                                              //Transistor Q4 da ponte h
//leds
int Led1 = 9;                                               //Pino ligado ao led 1
int Led2 = 8;                                               //Pino ligado ao led 2
int Led3 = 7;                                               //Pino ligado ao led 3
int Led4 = 6;                                               //Pino ligado ao led 4
int Led5 = 5;                                               //Pino ligado ao led 5
int Led6 = 4;                                               //Pino ligado ao led 6
int Led7 = 3;                                               //Pino ligado ao led 7
int Led8 = 2;                                               //Pino ligado ao led 8
int ledVec[] = {Led1, Led2, Led3, Led4, Led5, Led6, Led7, Led8};
int act = 0;                                                //led atual a ser utilizado(led1 = ledVec[0] por padrão)
//PWM
int pwm;                                                    //variavel que registra o valor do potenciometro

void setup()                                                //Inicialização de variáveis
{
  for (int i = 13; i >= 2; i--)                             //Inicialização dos pinos dos leds e transistores
  { 
    pinMode(i, OUTPUT);
  }
  pinMode(pinChave, INPUT);                                 //Pino da chave em modo de leitura
}
void loop() {
  pwm = map(analogRead(pot),0,1023,0,255);                  //lê-se e mapeia-se o valor do potenciometro
  chave = digitalRead(pinChave);                            //lê-se o valor da chave
  if (chave == HIGH)                                        //se o valor for HIGH gira no sentido horário
  {
    hor();                                                  //Sentido de rotaçao horaria do motor
    for(int i=255/pwm; i<pwm && chave==HIGH; i+=255/pwm)    //Este "for" configura o delay "HIGH" do pwm e a velocidade de rotaçao dos leds
    {
      led_hor();                                            //leds em rotaçao no sentido horario
      delay(255/pwm);                                       //delay de transiçao dos leds
      ledOff();                                             //apaga os leds  
      pwm = map(analogRead(pot),0,1023,0,255);              //verifica se ha alguma alteraçao no potenciometro
    }
    desliga();                                              //desliga o pwm
    for(int i=255/pwm; i<255-pwm && chave==HIGH; i+=255/pwm)//Este "for" configura o delay "LOW" e a velocidade de rotaçao dos leds
    {
      led_hor();                                            //leds em rotaçao no sentido horario
      delay(255/pwm);                                       //delay de transiçao dos leds
      ledOff();                                             //apaga os leds   
      pwm = map(analogRead(pot),0,1023,0,255);              //verifica se ha alguma alteraçao no potenciometro 
    }

  }
  else                                                      //se o valor for LOW gira no sentido anti-horário
  {
    anti_hor();                                             //Sentido de rotaçao anti-horario do motor
    for(int i=255/pwm; i<pwm && chave==LOW; i+=255/pwm)     //Este "for" configura o delay "HIGH" do pwm e a velocidade de rotaçao dos leds
    {
      led_anti();                                           //leds em rotaçao no sentido anti-horario    
      delay(255/pwm);                                       //delay de transiçao dos leds  
      ledOff();                                             //apaga os leds  
      pwm = map(analogRead(pot),0,1023,0,255);              //verifica se ha alguma alteraçao no potenciometro   
    }
    desliga();
    for(int i=255/pwm; i<255-pwm && chave==LOW; i+=255/pwm)//Este "for" configura o delay "LOW" e a velocidade de rotaçao dos leds
    {
      led_anti();                                          //leds em rotaçao no sentido anti-horario 
      delay(255/pwm);                                      //delay de transiçao dos leds   
      ledOff();                                            //apaga os leds  
      pwm = map(analogRead(pot),0,1023,0,255);             //verifica se ha alguma alteraçao no potenciometro 
    }
  }
}
void hor()//funçao que roda o motor no sentido horario
{
  digitalWrite(PHQ1, HIGH);                                //LIGA o transistor Q1
  digitalWrite(PHQ2, LOW);                                 //DESLIGA o transistor Q2
  digitalWrite(PHQ3, LOW);                                 //DESLIGA o transistor Q3
  digitalWrite(PHQ4, HIGH);                                //LIGA o transistor Q4
}
void anti_hor()//funçao que roda o motor no sentido anti-horario
{
  digitalWrite(PHQ1, LOW);                                 //LIGA o transistor Q1
  digitalWrite(PHQ2, HIGH);                                //DESLIGA o transistor Q2
  digitalWrite(PHQ3, HIGH);                                //DESLIGA o transistor Q3
  digitalWrite(PHQ4, LOW);                                 //LIGA o transistor Q4
}
void desliga()//funçao que desliga os transistores e leds
{
  digitalWrite(PHQ1, LOW);                                 //DESLIGA o transistor Q1
  digitalWrite(PHQ2, LOW);                                 //DESLIGA o transistor Q2
  digitalWrite(PHQ3, LOW);                                 //DESLIGA o transistor Q3
  digitalWrite(PHQ4, LOW);                                 //DESLIGA o transistor Q4
}
void ledOff()                                              //funçao que desliga todos os leds 
{
  for (int i = 0; i < 8; i++)                              //For para desligar todos os leds
  {
    digitalWrite(ledVec[i], LOW);
  }
}
void led_hor()                                             //funçao que faz os leds ligarem no sentido horario
{
  act++;                                                   //incrementa-se o valor do led atual   
  if (act == 8)                                            //caso o valor seja oito ele retorna ao 0 
  {
    act = 0;
  }
  digitalWrite(ledVec[act], HIGH);                         //liga-se o led atual
}
void led_anti()
{
  act--;                                                   //decrementa-se o valor do led atual 
  if (act == -1)                                           //caso o valor seja -1 ele se torna 7     
  {
    act = 7;
  }
  digitalWrite(ledVec[act], HIGH);                         //liga-se o led atual
}
