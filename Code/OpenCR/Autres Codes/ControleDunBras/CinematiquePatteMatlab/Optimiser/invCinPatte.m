% invCinPatte - ArachnUS - Cin�matique de Patte
% Fonction qui retourne la position angulaire de la repr�sentation de la
% patte � partir d'une position cart�sienne
% Cr�ation : 13 Mars 2019 - 11h
% Derni�re Modification : 13 Mars 2019 - 11h

function IK = invCinPatte(Pgoal, q, Tw0)
    Pcurr = fk_4_ik(q,Tw0);
    
    Rgoal=EulerXYZtoRot(Pgoal(4:6));        %Goal rotation matrix
    ii = 1;
    Err = abs(Pgoal-Pcurr);                 %Error between Pgoal and Pcurr
    
    while max(Err)>0.001                    %Beginning of the iterative method
%     for ii=1:1000                         %Uncomment line if you prefer a number of iterations rather than an error to respect
        Pcurr_old = Pcurr;
        Rcurr=EulerXYZtoRot(Pcurr(4:6));    %Current rotational matrix from Euler angles
        delta_R=Rgoal-Rcurr;                %Difference between matrices
        Omega=delta_R/Rcurr;                %matrix differential rule: delta_R=Omega*Rcurr. So Omega = delta_R*inv(Rcurr)

        dX(4,:)=(Omega(3,2)-Omega(2,3))/2;  %Finding wx from W
        dX(5,:)=(Omega(1,3)-Omega(3,1))/2;  %Finding wy from W
        dX(6,:)=(Omega(2,1)-Omega(1,2))/2;  %Finding wz from W

        
        dX(1:3,:) = Pgoal(1:3)-Pcurr(1:3);  %positional displacement as seen in the class notes
        
        TwF = transMat_w2f(q, Tw0);
        Tw1 = TwF(1:4,1:4);
        Tw2 = TwF(1:4, 5:8);
        Tw3 = TwF(1:4, 9:12);
        J = Jacobien(Tw0, Tw1, Tw2, Tw3);   %Determination of the Jacobian at angle q
        A = inv(J'*J);
        dTheta = A*J'*dX;                      %Inverse Kinematics formula
        q = q + dTheta;                     %Finding new angles
        Pcurr = fk_4_ik(q, Tw0); %Determining new Pcurr from new q
        Err = abs(Pcurr_old-Pcurr);         %Determining Err from new Pcurr
        ii = ii+1; 
    end
    IK = q;
end