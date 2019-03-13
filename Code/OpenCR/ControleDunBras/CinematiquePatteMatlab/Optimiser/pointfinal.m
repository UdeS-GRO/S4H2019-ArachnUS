% pointfinal - ArachnUS - Cin�matique de Patte
% Fonction qui trouve la position du bout de la patte � partir de ce qui a
% �t� calcul� par la cin�matique directe ou inverse
% Cr�ation : 13 Mars 2019 - 10h
% Derni�re Modification : 13 Mars 2019 - 10h

function P = pointfinal(A, op);
    
    Add = [0;12;0];

    if op == 1
        P = A - Add;
    elseif op == -1
        P = A + Add;
    else
        message = 'Entre une valeur de op soit de 1 ou de -1 pour ajouter ou enlever la distance du bout de la patte'
        P = A;
    end
end