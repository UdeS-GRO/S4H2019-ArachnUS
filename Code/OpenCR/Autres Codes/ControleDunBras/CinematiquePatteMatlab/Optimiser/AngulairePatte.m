% AngulairePatte - ArachnUS - Cin�matique de Patte
% Fonction qui retourne la cin�matique directe de la patte
% Cr�ation : 20 Mars 2019 - 10h
% Derni�re Modification : 13 Mars 2019 - 10h
function Q = AngulairePatte(dx, dy, qv, qb)
%% Constantes et param�tres
lv = 72.5;      % mm
lbx = 116.1;    % mm

qi = bonAngle(qv,qb)*2*pi/360;

% Matrice de rotation entre le world frame et le frame 0
Tw0 = [1    0   0   0;
        0   1   0   0;
        0   0   1   0;
        0   0   0   1];
% Tw0 =  [cosd(20)       sind(20)       0       0;
%         -sind(20)      cosd(20)       0       0;
%         0       0       1       0;
%         0       0       0       1];

% D�finition des matrices de transformation entre le world frame et le
% frame i. 
TwF = transMat_w2f(qi, Tw0);
Tw3 = TwF(1:4, 9:12);
A = findpoint(Tw3)

% Ajustement du point du bout de la patte au lieu du point du bout du corps
% bleu3
P = pointfinal(A, 1);

%% Recherche de la cin�matique inverse
Ag = A + [dx; dy; 0]
% D�finition de la position � atteindre et recherche des angles pour
% atteindre cette position cart�sienne
Pgoal = [Ag;MatRotationToEuler(Tw3(1:3,1:3))];
Ik = invCinPatte(Pgoal,qi,Tw0);
Q = Ik;
