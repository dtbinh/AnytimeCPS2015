function InpSignal = ComputeInputSignals(stepTime,UPoint,interType,tmp_CP,inpBound,simTime,isVarTime)
% ComputeInputSignals - Compute input signals given the parameters of the
% search space and the simulation options set.
%
% USAGE
% InpSignal = ComputeInputSignals(stepTime,UPoint,interType,tmp_CP,inpBound,simTime,isVarTime)
%
% INPUTS:
%   stepTime: If stepTime is a scalar, then the output is a column vector with the
%       values of the input signals at the time indicated by stepTime.
%       If stepTime is vector, then the output is an array where each column 
%       contains the values of each input signal at each point in time in stepTime.
%   
%   UPoint: The Upoint vector can be one of the following: 
%       1) vector of control point values if opt.varying_cp_times == 0 or 
%       2) vector of control point values and their corresponding 
%          timestamps if varying_cp_times = 1.
%       E.g. If inputSignal1 has 2 control points with values [cp1_1, cp1_2], 
%            inputSignal2 has 3 control points with values [cp2_1, cp2_2, cp2_3], 
%            and varying_cp_times = 0, then UPoint will be a row vector of the 
%            form [cp1_1 cp1_2 cp2_1 cp2_2 cp2_3].
%
%   interType: This is a cell array that contains the interpolation type
%       for each input signal. For an explanation of the different options see the  
%       staliro_options documentation: <a href="matlab: doc staliro_options.interpolationtype">staliro_options.interpolationtype</a>         
%
%   tmp_CP: A vector indicating the cumulative number of control points for
%       each input signal. Ex: tmp_CP(1) indicates the number of control points
%       for input signal 1; tmp_CP(2) = control points for inputs signal 1 and
%       signal 2.
%
%   inpBound: A n-by-2 array with the ranges for the inputs, where n is the 
%       number of input signals. 
%
%   simTime: Indicates the total simulation time.
%
%   isVarTime: Whether the option <a href="matlab: doc staliro_options.varying_cp_times">staliro_options.varying_cp_times</a> is enabled.
%
% OUTPUTS:
%   InpSignal: An array that contains the input signals that are generated.
%
% Notes: 
% * if one of the signals is interpolated using splines and the resulting
%   input signal does not satisfy the corresponding constraints, then
%   InpSignal will be an empty array.

% (C) 2010, Georgios Fainekos, Arizona State University

% History: 
% 2013.10.25 BH Support for varying_cp_times
% 2012.05.12 GF Stand alone function
%               Added support for random processes.
% 2011.08.22 GF Last major update

ns = length(stepTime);  % number of simulation steps
nu = length(tmp_CP);    % number of input signals
ni = length(interType); % number of different interpolation types


InpSignal = zeros(ns,nu);
idx_offset = tmp_CP(end)+1;

for ii = 1:nu
    
    % Get for each input signal the corresponding control points
    if ii==1
        U_tmp = UPoint(1:tmp_CP(1));
    else
        U_tmp = UPoint(tmp_CP(ii-1)+1:tmp_CP(ii));
    end
    
    % Is the interpolation function the same for all input signals?
    if ni==1
        idx_it = 1;
    else
        idx_it = ii;
    end

    % When variable time stamps: for all cases the timeVector is the same. 
    % When fixed time stamps: it dependes on the case => handled in the
    % corresponding interpolation function
    if isVarTime==1
        timeVector = UPoint(tmp_CP(end)+1:end)';
    elseif isVarTime==2
        if iscolumn(UPoint)
            UPoint = UPoint';
        end         
        if ii==1
            timeVector = [0 UPoint(idx_offset:(idx_offset+tmp_CP(1)-3)) simTime]';
            idx_offset = idx_offset+tmp_CP(1)-2;
        else
            timeVector = [0 UPoint(idx_offset:(idx_offset+tmp_CP(ii)-tmp_CP(ii-1)+-3)) simTime]';
            idx_offset = idx_offset+tmp_CP(ii)-tmp_CP(ii-1)-2;
        end
    end
    
	% Use the appropriate interpolation function
    if isa(interType{idx_it},'function_handle')
        
        InterpFcnPt = interType{idx_it};
        
        if isVarTime>0
            InpSignal(:,ii) = InterpFcnPt(timeVector,U_tmp,stepTime);
        else
            InpSignal(:,ii) = InterpFcnPt(U_tmp,stepTime);
        end        
        
    else
        
        switch interType{idx_it}

            case 'bool'
                
                % isBool = 1;
                nbnodes = length(U_tmp);
                assert(min(U_tmp >= 0 & U_tmp <= 1), 'When interpolation type is bool, the range of the input signal must be given as [0,1].') 
                if isVarTime>0
                    nbnodes = nbnodes-1;
                else
                    timeVector = 0:(simTime/length(U_tmp)):simTime;
                end

                vals = U_tmp >= 0.5; % randi(2,nbnodes,1)-1;
                bsignal = zeros(ns,1);
                for v = 1:nbnodes
                    bsignal(stepTime >= timeVector(v) & stepTime <= timeVector(v+1)) = vals(v);  
                end
                
                if isVarTime>0
                    bsignal(end) = vals(end);
                end
                
                InpSignal(:,ii) = bsignal;  

            case 'UR'
                assert(length(U_tmp)==1,['S-Taliro: Input signal ',num2str(ii),' is constant, but more than 1 control points are provided.']);
                InpSignal(:,ii) = inpBound(ii,1)+(inpBound(ii,2)-inpBound(ii,1))*rand(ns,1);  

            case 'const'
                assert(length(U_tmp)==1,['S-Taliro: Input signal ',num2str(ii),' is constant, but more than 1 control points are provided.']);
                InpSignal(:,ii) = U_tmp*ones(ns,1);

            case 'pconst'

                % For varying time distribution of control points
                if isVarTime==0
                    timeVector = 0:simTime/(length(U_tmp)):simTime;
                end

                InpSignal(:,ii) = piecewise_const(timeVector,U_tmp,stepTime);

            otherwise

                % For varying time distribution of control points
                if isVarTime==0
                    timeVector = 0:simTime/(length(U_tmp)-1):simTime;
                end

                InpSignal(:,ii) = interp1(timeVector,U_tmp,stepTime,interType{idx_it});
                if strcmp(interType{idx_it},'spline')
                    lwBd = repmat(inpBound(ii,1),ns,1);
                    upBd = repmat(inpBound(ii,2),ns,1);
                    if ~(min(lwBd<=InpSignal(:,ii) & InpSignal(:,ii)<=upBd))
                        InpSignal = [];
                        return
                    end
                end
        end
    end
end

if ns==1
    InpSignal = InpSignal';
end

end
