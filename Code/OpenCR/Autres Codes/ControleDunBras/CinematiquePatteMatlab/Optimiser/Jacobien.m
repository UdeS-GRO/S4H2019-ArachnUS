% Jacobien - ArachnUS - Cin�matique de Patte
% Fonction qui calcul la matrice Jacobienne � partir des matrices de
% transformations et des angles des moteurs de la patte
% Cr�ation : 13 Mars 2019 - 11h
% Derni�re Modification : 13 Mars 2019 - 11h

function J = Jacobien(Tw0, Tw1, Tw2, Tw3)

    % G�n�ration des colonnes du Jacobien avec l'�quation d'une colone
    Jacobcol1=[cross([Tw0(1,3); Tw0(2,3); Tw0(3,3)], [Tw3(1,4); Tw3(2,4); Tw3(3,4)]); Tw0(1,3); Tw0(2,3); Tw0(3,3)];
    Jacobcol2=[cross([Tw2(1,3); Tw2(2,3); Tw2(3,3)], [Tw3(1,4)-Tw2(1,4); Tw3(2,4)-Tw2(2,4); Tw3(3,4)-Tw2(3,4)]); Tw2(1,3); Tw2(2,3); Tw2(3,3)];
    Jacobcol3=[cross([Tw3(1,3); Tw3(2,3); Tw3(3,3)], [Tw3(1,4)-Tw3(1,4); Tw3(2,4)-Tw3(2,4); Tw3(3,4)-Tw3(3,4)]); Tw3(1,3); Tw3(2,3); Tw3(3,3)];

    J = [Jacobcol1 Jacobcol2, Jacobcol3];


end