// variables globales
int initDone = 0;
typedef enum{
  arret,
  initial,
  manuel
}etat;
etat etat_voulu = arret;
typedef struct message{
  long etat=0;
  long moteur0=1;
  long moteur1=2;
/*  long moteur2;
  long moteur3;
  long moteur4;
  long moteur5;
  long moteur6;
  long moteur7;*/
};
message MSG;

int long_msg = sizeof(MSG);
int state = 0;
void setup() {
Serial.begin(9600);
}

void loop() {
  while(Serial.available() > 0){
   state = Serial.parseInt();
    /*if (etat == "arret"){
      etat_switch = 0;
    }
    else if (etat == "init"){
      etat_switch = 1;
    }
    else if (etat == "manuel"){
      etat_switch = 2;
    }*/
  }
  switch(state){
    case 0:
      //etat arret fait rien
      break;
    case 1:
      //etat à venir
      initDone = 1;
      break;
    case 2:
      //etat à venir
      if (initDone == 0){
        state = 0;
        break;
        //init n'a pas été fait donc on ne peut entrer en mode manuel
      }
      else{
        //opération demandée
        break;        
      }

/*    case 3:
      //etat à venir

      break;
    case 4:
      //etat à venir

      break;
    case 5:
      //etat à venir

      break;*/
  } 
//  Serial.println("Debut de l'envoi par Arduino");
  long_msg = sizeof(MSG);
//  Serial.write("S");
  Serial.write((uint8_t*)&MSG, long_msg);
//  Serial.write("E");
//  Serial.println(state);
//  Serial.println(long_msg);
/*  Serial.print("etat_switch : ");
  Serial.println(etat_switch);*/
//envoie commande moteur pour debug et confirmation

  delay(2000);
}
