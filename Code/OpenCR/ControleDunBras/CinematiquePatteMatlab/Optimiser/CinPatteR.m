% CinPatteR - Main ex�cutant le programme de cin�matique de la patte
% ArachnUS - Projet S4 - GRO
% Cr�ation : 13 Mars 2019 - 10h
% Derni�re Modification : 13 Mars 2019 - 22h
clear all; close all;
%% Constantes et param�tres
lv = 72.5;      % mm
lbx = 116.1;    % mm

qb = 130;                 % Angle entre le support et bleu1

qbx = -1.0914*qb + 27.979 % Angle de bleu1 � partir de vert1
qbx = qbx*2*pi/360;
qv = -35*2*pi/360;             % Angle entre le support et vert1

q = [qv; qbx;0];


% Matrice de rotation entre le world frame et le frame 0
Tw0 = [1    0   0   0;
        0   1   0   0;
        0   0   1   0;
        0   0   0   1];
% Tw0 =  [cosd(20)       sind(20)       0       0;
%         -sind(20)      cosd(20)       0       0;
%         0       0       1       0;
%         0       0       0       1];
        

%% Recherce de la cin�matique directe
% D�finition des matrices de transformation entre le world frame et le
% frame i. 
TwF = transMat_w2f(q, Tw0);
Tw1 = TwF(1:4,1:4);
Tw2 = TwF(1:4, 5:8);
Tw3 = TwF(1:4, 9:12);
A = findpoint(Tw3);

% Ajustement du point du bout de la patte au lieu du point du bout du corps
% bleu3
P = pointfinal(A, 1);

%% Calcul du Jacobien
J = Jacobien(q, Tw0, Tw1, Tw2, Tw3);

%% Recherche de la cin�matique inverse
% D�finition de la position � atteindre et recherche des angles pour
% atteindre cette position cart�sienne
Pgoal = [A;MatRotationToEuler(Tw3(1:3,1:3))];
Ik = invCinPatte(Pgoal,q+0.2,Tw0)

%% Affichage graphique de la patte
coord = [   Tw1(1,4), Tw2(1,4), Tw3(1,4); 
            Tw1(2,4), Tw2(2,4), Tw3(2,4);
            Tw1(3,4), Tw2(3,4), Tw3(3,4)];
        
graphlim = lv+lbx;

figure(1)
plot(coord(1,:), coord(2,:))
xlim([-graphlim graphlim])
ylim([-graphlim graphlim])
hold on
grid on

plot(0, 0, '-r*')





