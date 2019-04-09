% findpoint - ArachnUS - Cin�matique de Patte
% Fonction qui trouve la position d�crite par la matrice de transformation
% Arguments : T est la matrice de transformation
% Sortie : A est la position d�crite par la matrice de transformation

% Cr�ation : 13 Mars 2019 - 10h
% Derni�re Modification : 13 Mars 2019 - 10h

function A = findpoint(T);
    A = T(1:3,4);
end