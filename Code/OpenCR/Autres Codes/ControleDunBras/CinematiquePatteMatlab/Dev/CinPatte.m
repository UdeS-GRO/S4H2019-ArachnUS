% Cin�matique de patte
% ArachnUS - Projet S4 - GRO
% Cr�ation : 7 Mars 2019 - 21h30
% Derni�re Modification : 8 Mars 2019 - 9h30

clear all;
% ======== Constantes ========
lv = 72.5;      % mm
lbx = 116.1;    % mm
qv = 0;
qbx = 0;

DOF = 3;
graphlim = lv+lbx;

% ======== Param�tres DH ========
%       alpha    ri_1   di      theta       
dh = [  0       0       0       qv;
        0       lv      0       qbx;
        0       lbx     0       0];
L = size(dh);

for index=1:L(1)
   alpha(index) = dh(index,1);
   d(index) = dh(index,3);
   r(index) = dh(index,2);
   q(index) = dh(index,4);
end

% ======== Matrice de transformation ========
% Transformation entre le world frame et le bras
TW0 = [ cosd(20)       sind(20)       0       0;
        -sind(20)      cosd(20)       0       0;
        0       0       1       0;
        0       0       0       1];
    
% Matrice de transformation entres frames
for index=1:L(1)
    Ti_im1(:,:,index)=[     cos(q(index)) -sin(q(index)) 0 r(index);...
                            sin(q(index))*cos(alpha(index)) cos(alpha(index))*cos(q(index)) -sin(alpha(index))  -d(index)*sin(alpha(index)); ...
                            sin(q(index))*sin(alpha(index)) cos(q(index))*sin(alpha(index)) cos(alpha(index))   d(index)*cos(alpha(index));...
                            0 0 0 1];
end

% Matrices de transformations entre joint et world frame
T0(:,:,1) = TW0*Ti_im1(:,:,1);
for index = 2: L(1)
    T0(:,:,index) = T0(:,:,index-1)*Ti_im1(:,:,index);
end

% ======== Position du end effector ========
for index = 1:L(1)
    v(:,:,index) = T0(1:3, 4, index);
end

coord = [v(:,:,1) v(:,:,2) v(:,:,3)];

% ======== Jacobien ========
%Making the first column of the Jacobian
Jacobcol1=[cross([TW0(1,3); TW0(2,3); TW0(3,3)], [T0(1,4,DOF); T0(2,4,DOF); T0(3,4,DOF)]); TW0(1,3); TW0(2,3); TW0(3,3)];
J(:,1) = Jacobcol1;
for index = 1:DOF
% Algorithm for the columns of the Jacobian
    Jacobcol(:,:,index)=[cross([T0(1,3,index); T0(2,3,index); T0(3,3,index)], [T0(1,4,DOF)-T0(1,4,index); T0(2,4,DOF)-T0(2,4,index); T0(3,4,DOF)-T0(3,4,index)]); T0(1,3,index); T0(2,3,index); T0(3,3,index)];
end

% Making the loop to place the column in the right order
for index = 2:DOF
    J(:,index)=Jacobcol(:,1,index);
end 

Jacobien = Jacobian_complete('Modified', DOF, dh, TW0, q, 'Radians')

% ======= Cin�matique inverse ========
Pgoal = [coord(:,3);MatRotationToEuler(T0(1:3, 1:3, 3))];
IK = InverseKinematics_complete('Modified', DOF, dh, TW0, Pgoal, transpose(q), 'Radians')


% ======= Graphique de la patte ========
figure(1)
plot(coord(1,:), coord(2,:))
xlim([-graphlim graphlim])
ylim([-graphlim graphlim])
hold on
grid on

plot(0, 0, '-r*')

