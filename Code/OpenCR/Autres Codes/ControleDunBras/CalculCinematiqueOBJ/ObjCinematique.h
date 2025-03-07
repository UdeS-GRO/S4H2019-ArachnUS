/*
 * Le programme ci-dessous à été réalisé par l'équipe d'ARACHNUS
 * dans la cadre d'un cours de projet en génie robotique
 * de l'université de Sherbrooke (S4-GRO).
 */

/***************************************************
  Classe utilisée pour calculer la cinématique des pattes
 ****************************************************/
#ifndef OBJ_CINEMATIQUE
#define OBJ_CINEMATIQUE

#include "matrix.h"

class ObjCinematique{
  
private:
  //Création des constantes utilisées pour l'ensemble des calculs
  const float lv = 72.5;    //Longueur du bout vert (mm)
  const float lbx = 116.1;  //Longueur du bout bleu jusqu'au poignet (mm)

  //Création des matrices utilisées pour l'ensemble des calculs
  matrix_obj *q;
  matrix_obj *Tw0;
  matrix_obj *Tw1;
  matrix_obj *Tw2;
  matrix_obj *Tw3;
  matrix_obj *Rw3;
  
  matrix_obj *fkc;
  matrix_obj *fkr;

  matrix_obj *Pgoal;
  matrix_obj *Rgoal;
  matrix_obj *Pcurr;
  matrix_obj *Pcurr_old;
  matrix_obj *Rcurr;
  matrix_obj *Err;
  matrix_obj *delta_R; 

  matrix_obj *Omega;
  matrix_obj *dX;
  matrix_obj *Ppartie;
  matrix_obj *Rpartie;
  matrix_obj *A;

  matrix_obj *J;
  matrix_obj *Jtranspose;
  matrix_obj *pseudoJ;
  matrix_obj *dTheta;

  matrix_obj *Euler;
  matrix_obj *qret;

public:
  //Constructeur
  ObjCinematique() {
    // Initialisation des matrices utilisées pour l'ensemble des calculs

    // Matrice identité
      Tw0 = matrix_construct_zero(4, 4);
      Tw0->array[0] = 1;
      Tw0->array[5] = 1;
      Tw0->array[10] = 1;
      Tw0->array[15] = 1;

    q =         matrix_construct_zero(3, 1);    //qv, qbX, "rienDutile"
    Tw1 =       matrix_construct_zero(4, 4);    //Matrice de transformation du frame 0 au frame 1
    Tw2 =       matrix_construct_zero(4, 4);    //Matrice de transformation du frame 1 au frame 2
    Tw3 =       matrix_construct_zero(4, 4);    //Matrice de transformation du frame 2 au frame 3
    Rw3 =       matrix_construct_zero(3, 3);    //Matrice de de rotation de Tw3
      
    fkc =       matrix_construct_zero(3, 1);    //Position cartésienne du poignet de la patte
    fkr =       matrix_construct_zero(3, 1);    //Position angulaire du poignet de la patte avec EulerXYZ
     
    Pgoal =     matrix_construct_zero(6, 1);    //Position cartésienne voulue du bout/poignet de la patte
    Rgoal =     matrix_construct_zero(3, 3);    //Position angulaire voulue du bout/poignet de la patte avec EulerXYZ 
    Pcurr =     matrix_construct_zero(6, 1);    //Position cartésienne courante du poignet de la patte
    Pcurr_old = matrix_construct_zero(6, 1);    //Position cartésienne précédente du poignet de la patte
    Rcurr =     matrix_construct_zero(3, 3);    //Position angulaire courante du bout de la patte avec EulerXYZ
    Err =       matrix_construct_zero(6, 1);    //Différence entre la position cartésienne à atteindre et la position cartésienne courante
    delta_R =   matrix_construct_zero(3, 3);    //Différence entre la position angulaire à atteindre et la position angulaire courante
    
    Omega =     matrix_construct_zero(3, 3);    //Matrice de rotation utilisé pour l'erreur en rotation
    dX =        matrix_construct_zero(6, 1);    //Erreur à ajuster avec l'algorythme de cinématique inverse
    Ppartie =   matrix_construct_zero(3, 1);    //Matrice "buffer" pour faire des calculs de cinématique inverse
    Rpartie =   matrix_construct_zero(3, 3);    //Matrice "buffer" pour faire des calculs de cinématique inverse
    A =         matrix_construct_zero(3, 3);    //Vecteur pour la pseudo inverse de la Jacobienne

    J =         matrix_construct_zero(6, 3);    //Jacobienne
    Jtranspose =matrix_construct_zero(3, 6);    //Transposé de la Jacobienne
    pseudoJ =   matrix_construct_zero(3, 6);    //Pseudo inverse de la Jacobienne
    dTheta =    matrix_construct_zero(3, 1);    //Réponse de la cinématique (angle à ajouter pour atteindre la commande)
    
    Euler =     matrix_construct_zero(3, 1);    //Réponse au passage d'une matrice de rotation aux angles d'EulerXYZ
    qret =      matrix_construct_zero(3, 1);    //Pour transférer qb en qbX
  }

  //Print des variables sur le port serial (utile pour faciliter le debuggage)
  void printTest(){
    Serial.println("-----------------------------------------------------------------");
    Serial.println("Test OBJ: q");
    matrix_printf(q);
    Serial.println();

    Serial.println("-----------------------------------------------------------------");
    Serial.println("Test OBJ: qret");
    matrix_printf(qret);
    Serial.println();
  }

  //Calcule la position cartésienne du bout de la patte en fonction des angles des moteurs 
  void runDISTtoANG(float angleSortie[2], float qv, float qb, float dx, float dy){
    //angleSortie -> valeur de qv et qb retourne
    //qv -> valeur courante de l'angle vert
    //qb -> valeur courante de l'angle bleu
    //dx -> position voulue en x
    //dy -> position voulue en y
    
    positionAngulairePatte(q, qret, Pgoal, Err, Pcurr_old, Jtranspose, Rcurr, delta_R, dTheta, Omega, dX, Rgoal, Ppartie, A, Rpartie, Tw0, Tw1, Tw2, Tw3, J, Pcurr, fkr, fkc, Rw3, qv, qb, dx, dy);

    angleSortie[0] = qret->array[0]; //qvOUT
    angleSortie[1] = qret->array[1]; //qbOUT
  }

  //Calcule les angles aux moteurs en fonction de la position cartésienne du bout de la patte
  void runANGtoDIST(float distanceSortie[2], float qv, float qb){
    //distanceSortie -> valeur de x et y retourne
    //qv -> valeur voulue de l'angle vert
    //qb -> valeur voulue de l'angle bleu
    
    positionCartesiennePatte(q, Tw0, Tw1, Tw2, Tw3, Pgoal, qv, qb);

    distanceSortie[0] = Pgoal->array[0]; //position OUT en x
    distanceSortie[1] = Pgoal->array[1]; //position OUT en y
  }

private:

  //Fonction qui retourne la matrice de transformation du world frame au référentiel 3 selon les angles en radians entrée
  void transMat_w2f(matrix_obj * q, matrix_obj * Tw0, matrix_obj * Tw1, matrix_obj * Tw2, matrix_obj * Tw3) {
    Tw1->array[0] = cos(q->array[0]);
    Tw1->array[1] = -sin(q->array[0]);
    Tw1->array[4] = sin(q->array[0]);
    Tw1->array[5] = cos(q->array[0]);
    Tw1->array[10] = 1;
    Tw1->array[15] = 1;
  
    Tw2->array[0] = cos(q->array[1]);
    Tw2->array[1] = -sin(q->array[1]);
    Tw2->array[3] = lv * cos(q->array[0]);
    Tw2->array[4] = sin(q->array[1]);
    Tw2->array[5] = cos(q->array[1]);
    Tw2->array[7] = lv * sin(q->array[0]);
    Tw2->array[10] = 1;
    Tw2->array[15] = 1;
  
    Tw3->array[0] = cos(q->array[1]);
    Tw3->array[1] = -sin(q->array[1]);
    Tw3->array[3] = lv * cos(q->array[0]) + lbx * cos(q->array[1]);
    Tw3->array[4] = sin(q->array[1]);
    Tw3->array[5] = cos(q->array[1]);
    Tw3->array[7] = lv * sin(q->array[0]) + lbx * sin(q->array[1]);
    Tw3->array[10] = 1;
    Tw3->array[15] = 1;
  }

  //Fonction qui convertie qb en qbX
  void bonAngle(matrix_obj * q, float qv, float qb) {
    float qbx = -1.0914 * qb + 27.979;       // Angle de bleu1 à partir de vert1
  
    if (qb <= 137.25 && qb > 122.5) {
      qbx = qbx - ( (4 * pow(10, -7)) * pow(qv, 4) + (3 * pow(10, -5)) * pow(qv, 3) + 0.0003 * pow(qv, 2) + 0.0665 * qv - 0.7918);
    } else if (qb <= 122.5 && qb > 107.5) {
      qbx = qbx - ((-7 * pow(10, -9)) * pow(qv, 5) - (3 * pow(10, -7)) * pow(qv, 4) + (2 * pow(10, -5)) * pow(qv, 3) + 0.0001 * pow(qv, 2) + 0.07 * qv - 0.5725);
    } else if (qb <= 107.5 && qb > 90) {
      qbx = qbx - ( (1 * pow(10, -5)) * pow(qv, 3) - 0.0005 * pow(qv, 2) + 0.0783 * qv - 0.7722);
    } else if (qb <= 90 && qb > 70) {
      qbx = qbx - ( (2 * pow(10, -5)) * pow(qv, 3) - 0.0015 * pow(qv, 2) + 0.1111 * qv - 0.8019 );
    } else if (qb <= 152.5 && qb > 137.5) {
      qbx = qbx - ( (6 * pow(10, -8)) * pow(qv, 5) + (5 * pow(10, -6)) * pow(qv, 4) + 0.0001 * pow(qv, 3) + 0.0005 * pow(qv, 2) + 0.0793 * qv - 0.7672);
    }
    q->array[0] = qv * (2 * 3.1416 / 360);
    q->array[1] = qbx * (2 * 3.1416 / 360);
  }

  //Fonction qui convertie qbX en qb
  void bonAngleInv(matrix_obj * qret, matrix_obj * q) {
    qret->array[0] = q->array[0] * (360 / (2*3.1416));
    float qbX = q->array[1] * (360 / (2*3.1416));
    
    float qb = -0.0002*qbX*qbX - 0.9651*qbX + 23.43;       // Angle de bleu1 à partir de vert1

    qret->array[1] = qb;
  }
  
  //Fonction qui calcule la position du bout par rapport à la position du poignet
  void pointFinal(matrix_obj * T3x1, int op) {
    T3x1->array[1] = T3x1->array[1] + op * 12; // op = 1 ou -1
  }

  //Fonction qui sort la position d'une matrice de transformation
  void findPoint(matrix_obj * At, matrix_obj * T) {
    At->array[0] = T->array[3];
    At->array[1] = T->array[7];
    At->array[2] = T->array[11];
  }

  //Fonction qui retourne la matrice de rotation à partir d'un set d'angles d'Euler XYZ
  void EulerXYZtoRot(matrix_obj * Q, matrix_obj * Euler) {
    float c1 = cos(Euler->array[0]);
    float s1 = sin(Euler->array[0]);
    float c2 = cos(Euler->array[1]);
    float s2 = sin(Euler->array[1]);
    float c3 = cos(Euler->array[2]);
    float s3 = sin(Euler->array[2]);
    
    Q->array[0] = c2 * c3;
    Q->array[3] = c1 * s3 + c3 * s1 * s2;
    Q->array[6] = s1 * s3 - c1 * c3 * s2;
    Q->array[1] = -c2 * s3;
    Q->array[4] = c1 * c3 - s1 * s2 * s3;
    Q->array[7] = c3 * s1 + c1 * s2 * s3;
    Q->array[2] = s2;
    Q->array[5] = -c2 * s1;
    Q->array[8] = c1 * c2;
  }

  //Fonction qui calcul la matrice Jacobienne à partir des matrices de transformations et des angles des moteurs de la patte
  void Jacobien(matrix_obj * J, matrix_obj * Tw0, matrix_obj * Tw1, matrix_obj * Tw2, matrix_obj * Tw3) {
    //Jacobcol1
    J->array[0] = Tw0->array[6] * Tw3->array[11] - Tw0->array[10] * Tw3->array[7]; //obj->array[0] = src1->array[1]*src2->array[2] - src1->array[2]*src2->array[1];
    J->array[3] = Tw0->array[10] * Tw3->array[3] - Tw0->array[2] * Tw3->array[11]; //obj->array[1] = src1->array[2]*src2->array[0] - src1->array[0]*src2->array[2];
    J->array[6] = Tw0->array[2] * Tw3->array[7] - Tw0->array[6] * Tw3->array[3]; //obj->array[2] = src1->array[0]*src2->array[1] - src1->array[1]*src2->array[0];
    J->array[9] = Tw0->array[2];
    J->array[12] = Tw0->array[6];
    J->array[15] = Tw0->array[10];
  
    //Jacobcol2
    J->array[1] = Tw2->array[6] * (Tw3->array[11] - Tw2->array[11]) - Tw2->array[10] * (Tw3->array[7] - Tw2->array[7]);
    J->array[4] = Tw2->array[10] * (Tw3->array[3] - Tw2->array[3]) - Tw2->array[2] * (Tw3->array[11] - Tw2->array[11]);
    J->array[7] = Tw2->array[2] * (Tw3->array[7] - Tw2->array[7]) - Tw2->array[6] * (Tw3->array[3] - Tw2->array[3]);
    J->array[10] = Tw2->array[2];
    J->array[13] = Tw2->array[6];
    J->array[16] = Tw2->array[10];
  
    //Jacobcol3
    J->array[2] = Tw3->array[6] * (Tw3->array[11] - Tw3->array[11]) - Tw3->array[10] * (Tw3->array[7] - Tw3->array[7]);
    J->array[5] = Tw3->array[10] * (Tw3->array[3] - Tw3->array[3]) - Tw3->array[2] * (Tw3->array[11] - Tw3->array[11]);
    J->array[8] = Tw3->array[2] * (Tw3->array[7] - Tw3->array[7]) - Tw3->array[6] * (Tw3->array[3] - Tw3->array[3]);
    J->array[11] = Tw3->array[2];
    J->array[14] = Tw3->array[6];
    J->array[17] = Tw3->array[10];
  }

  //Fonction qui retourne les angles d'Euler à partir d'une matrice de rotation
  void MatRotationToEuler(matrix_obj * Euler, matrix_obj * Mat) {
    float nx = Mat->array[0];
    float ny = Mat->array[3];
    float nz = Mat->array[6];
    float ox = Mat->array[1];
    float oy = Mat->array[4];
    float oz = Mat->array[7];
    float ax = Mat->array[2];
    float ay = Mat->array[5];
    float az = Mat->array[8];
  
    float A1 = atan2(-ay, az);
    float A1tt = atan2(az, -ay);
    float B1l = atan2(ax, (-1 * sin(A1) * ay + cos(A1) * az));
    float C1 = atan2(cos(A1) * ny + sin(A1) * nz, cos(A1) * oy + sin(A1) * oz);
    float A1f = 0;
    float B1f = 0;
    float C1f = 0;
  
    if (abs(ax - 1) < 0.000006) {
      A1f = atan2(ny, oy) / 2;
      B1f = 3.1416 / 2;
      C1f = atan2(ny, oy) / 2;
    } else if (abs(ax + 1) < 0.000006) {
      A1f = atan2(-ny, oy) / 2;
      B1f = -3.1416 / 2;
      C1f = -atan2(-ny, oy) / 2;
    } else {
      A1f = A1;
      C1f = C1;
      B1f = B1l;
    }
    
    Euler->array[0]  = A1f;
    Euler->array[1]  = B1f;
    Euler->array[2]  = C1f;
  
  }

  //Calcule de la cinématique directe
  void fk_4_ik(matrix_obj * fk, matrix_obj * fkc, matrix_obj * fkr, matrix_obj * Rw3, matrix_obj * q, matrix_obj * Tw0, matrix_obj * Tw1, matrix_obj * Tw2, matrix_obj * Tw3) {
    transMat_w2f(q, Tw0, Tw1, Tw2, Tw3);
    findPoint(fkc, Tw3);
  
    matrix_copie_part(Rw3, Tw3, 1, 1, 3, 3);
    MatRotationToEuler(fkr, Rw3);
  
    fk->array[0] = fkc->array[0];
    fk->array[1] = fkc->array[1];
    fk->array[2] = fkc->array[2];
    fk->array[3] = fkr->array[0];
    fk->array[4] = fkr->array[1];
    fk->array[5] = fkr->array[2];
  }

  //Calcule de la cinématique inverse
  void invCinPatte(matrix_obj * q, matrix_obj * Pgoal, matrix_obj * Err, matrix_obj * Pcurr_old, matrix_obj * Jtranspose, matrix_obj * Rcurr, matrix_obj * delta_R, matrix_obj * dTheta, matrix_obj * Omega, matrix_obj * dX, matrix_obj * Rgoal, matrix_obj * Ppartie, matrix_obj * A, matrix_obj * Rpartie, matrix_obj * Tw0, matrix_obj * Tw1, matrix_obj * Tw2, matrix_obj * Tw3, matrix_obj * J, matrix_obj * Pcurr, matrix_obj * fkr, matrix_obj * fkc, matrix_obj * Rw3) {
    fk_4_ik(Pcurr, fkc, fkr, Rw3, q, Tw0, Tw1, Tw2, Tw3);
      
    matrix_copie_part(Ppartie, Pgoal, 4, 1, 6, 1);
    EulerXYZtoRot(Rgoal, Ppartie);        //Goal rotation matrix
    matrix_sub(Err, Pgoal, Pcurr);        //Error between Pgoal and Pcurr
    int iterCount = 0;
      while ((max_matrix_abs(Err) > 0.001) && (iterCount++ < 100)){  //Beginning of the iterative method
  
        matrix_copy_matrix(Pcurr_old, Pcurr);
        matrix_copie_part(Ppartie, Pcurr, 4, 1, 6, 1);   
        EulerXYZtoRot(Rcurr, Ppartie);      //Current rotational matrix from Euler angles
        matrix_sub(delta_R, Rgoal, Rcurr);  //Difference between matrices
        matrix_inv(Rpartie, Rcurr);
        matrix_mul(Omega, delta_R, Rpartie);  //matrix differential rule: delta_R=Omega*Rcurr. So Omega = delta_R*inv(Rcurr)
                      
        dX->array[3] = (Omega->array[7]-Omega->array[5])/2; //Finding wx from W
        dX->array[4] = (Omega->array[2]-Omega->array[6])/2; //Finding wy from W
        dX->array[5] = (Omega->array[3]-Omega->array[1])/2; //Finding wz from W
  
        //positional displacement as seen in the class notes
        dX->array[0] =  Pgoal->array[0] - Pcurr->array[0];
        dX->array[1] =  Pgoal->array[1] - Pcurr->array[1];
        dX->array[2] =  Pgoal->array[2] - Pcurr->array[2];
       
        transMat_w2f(q, Tw0, Tw1, Tw2, Tw3);
        Jacobien(J, Tw0, Tw1, Tw2, Tw3);   //Determination of the Jacobian at angle q
  
        matrix_transpose(Jtranspose, J);
        matrix_mul(Rpartie, Jtranspose, J);
        matrix_inv(A, Rpartie);
        matrix_mul(pseudoJ, A, Jtranspose);
        matrix_mul(dTheta, pseudoJ, dX);  //Inverse Kinematics formula
  
        matrix_add(q, q, dTheta);       //Finding new angles
                     
        fk_4_ik(Pcurr, fkc, fkr, Rw3, q, Tw0, Tw1, Tw2, Tw3); //Determining new Pcurr from new q
        matrix_sub(Err, Pcurr_old, Pcurr);  //Determining Err from new Pcurr 
        
      }     
  }

  //Fonction qui effectue la cinématique direct du bout de la patte
  void positionCartesiennePatte(matrix_obj * q, matrix_obj * Tw0, matrix_obj * Tw1, matrix_obj * Tw2, matrix_obj * Tw3, matrix_obj * Pgoal, float qv, float qb) {
    bonAngle(q, qv, qb);
    
    transMat_w2f(q, Tw0, Tw1, Tw2, Tw3);
  
    findPoint(Pgoal, Tw3);
    
    pointFinal(Pgoal, -1);
     
  }

  //Fonction qui effectue la cinématique inverse du bout de la patte
  void positionAngulairePatte(matrix_obj * q, matrix_obj * qret, matrix_obj * Pgoal, matrix_obj * Err, matrix_obj * Pcurr_old, matrix_obj * Jtranspose, matrix_obj * Rcurr, matrix_obj * delta_R, matrix_obj * dTheta, matrix_obj * Omega, matrix_obj * dX, matrix_obj * Rgoal, matrix_obj * Ppartie, matrix_obj * A, matrix_obj * Rpartie, matrix_obj * Tw0, matrix_obj * Tw1, matrix_obj * Tw2, matrix_obj * Tw3, matrix_obj * J, matrix_obj * Pcurr, matrix_obj * fkr, matrix_obj * fkc, matrix_obj * Rw3, float qv, float qb, float dx, float dy) {
    bonAngle(q, qv, qb);
    
    fk_4_ik(Pgoal, fkc, fkr, Rw3, q, Tw0, Tw1, Tw2, Tw3);
    Pgoal->array[0] = dx;
    Pgoal->array[1] = dy;
    
    pointFinal(Pgoal, 1);
  
    invCinPatte(q, Pgoal, Err, Pcurr_old, Jtranspose, Rcurr, delta_R, dTheta, Omega, dX, Rgoal, Ppartie, A, Rpartie, Tw0, Tw1, Tw2, Tw3, J, Pcurr, fkr, fkc, Rw3);
    bonAngleInv(qret, q);
       
  }
};

#endif
