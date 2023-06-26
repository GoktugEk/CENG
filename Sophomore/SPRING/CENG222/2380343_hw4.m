N = ceil(21141);

lower_n =250;
lower_p =0.62;
n = 50; %parameter given in question
p = 0.62; %parameter given in question


Weights = zeros(N,1);

for k=1:N;

    U = rand(lower_n,1);
    F = sum(U < lower_p);

    weight = 0;

    xmin = 0; xmax =8; ymax = 0.22;

    for f=1:F;
        CX = 0; CY = ymax; F = 0;
        while (CY > F);
            U = rand; V = rand;
            CX = xmin + (xmax - xmin) * U; CY = ymax*V;

            if CX <= 2
                F = 0.07* CX;
            elseif CX <= 5
                F = -0.02*(CX-4)^2+0.22;
            elseif CX <= 7
                F = 0.08 * (5 - CX) + 0.2;
            elseif CX <= 8
                F = -0.04 *	CX + 0.32;
            else 
                F=0;
            end
        end;
        weight = weight + CX;
    end;
    Weights(k) = weight;
end;

est = mean(Weights>640);
expected = mean(Weights);
stdw = std(Weights);
fprintf('Estimated probability = %f\n',est);
fprintf('Expected weight = %f\n',expected);
fprintf('Standard deviation = %f\n',stdw);



