const char* ssid = "CedilleNetwork";
const char* password = "Club@CED1LLE:)";

// Permet de laisser le temps à une commande de s'executer
// i est le nombre de 100ms qu'on lui donne
void readwrite(int i) 
{
  int c = 0;
    while (c < i) 
    {
      while (Serial.available()) 
      {
        Serial3.write(Serial.read());
      }
    
      while (Serial3.available()) 
      {
        Serial.write(Serial3.read());
      }
    c++;
    delay(100);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial3.begin(115200);
  delay(1000);

  Serial.println("Utilisez 'Both NL & CR' pour les retours de ligne.");

  // println == write("/r/n")
  Serial3.println("AT");
  readwrite(10);
  
  Serial3.println("AT+CWJAP=\"CedilleNetwork\",\"Club@CED1LLE:)\"");
  readwrite(60);
  
  Serial3.println("AT+CIPMUX=1");
  readwrite(20);

  Serial3.println("AT+CIPSERVER=1,8080");
  readwrite(20);

  Serial3.println("AT+CIPSTO=300");
  readwrite(20);

  Serial3.println("AT+CIFSR");
  readwrite(50);

  Serial.println("\r\n");
  Serial.println("Pret!");
  readwrite(10);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(200); // Si le code roule trop vite, ca marchera juste pas. 

  Serial3.println("AT+CIPSEND=0,4");
  delay(10);
  Serial3.println("Test");
  delay(10);
  Serial3.println("AT+CIPCLOSE=0");
}

