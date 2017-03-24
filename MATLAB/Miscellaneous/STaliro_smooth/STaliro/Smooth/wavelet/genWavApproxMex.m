function Sd_test = genWavApproxMex(SmoothOpt,x_test)

%% general codegen for signed dist for all kinds of predicates
 %dim = numel(x_test); 
 %C_00k = SmoothOpt.preds.WavParams(1).C_00k;
 %D_ejk = SmoothOpt.preds.WavParams(1).D_ejk;
 %k_min = SmoothOpt.preds.WavParams(1).k_min;
 %k_max = SmoothOpt.preds.WavParams(1).k_max;
 %j_min = SmoothOpt.preds.WavParams(1).j_min;
 %j_max = SmoothOpt.preds.WavParams(1).j_max;
 %E_dash = SmoothOpt.preds.WavParams(1).E_dash;
 C_00k = zeros(1,1,3);
 D_ejk = zeros(1,1,3);
 k_min = 0;
 k_max = 2;
 j_min = 0;
 j_max = 0;
 E_dash = ones(4,2);
 x_test = [0;0];
 cfg=coder.config('mex');
        
    %for get coeffs (grid_x,dist_array_xy,dx,j_min,j_max,k_min,k_max,E_dash,0);
    arg_ins = {coder.typeof(x_test,[Inf,1]), coder.typeof(C_00k,[1,1,Inf]),...
        coder.typeof(D_ejk,[Inf,Inf,Inf]), coder.typeof(k_min), coder.typeof(k_max),...
        coder.typeof(j_min), coder.typeof(j_max), coder.typeof(E_dash,[Inf,Inf])};
    codegen -config cfg alt_getWavApprox_vector_genable -report -args arg_ins
    
    %test it
    Sd_test = 1;
    if(0)
    Sd_test = alt_getWavApprox_vector_genable_mex([0;0],C_00k,D_ejk,k_min,k_max,j_min,j_max,E_dash);
    end
