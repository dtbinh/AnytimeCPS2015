% General
%load('Sets_10cube.mat'); %sets s.t abs(pos(x,y,z))<=10, abs(vel(x,y,z)<=10,...
                         %abs(roll, pitch)<=rad2deg(30), abs(thrust)<=10,
                         %extra A_lift(:,:,5) for 45 ms delay mode, not
                         %used here, no set computations for that mode
                         %either
load('Sets_100cube.mat');       %large sets                  
H = 10; %fixed

% fill Params for opts
for i = 1:numel(deltas)
	params{i}.A_0 = A_lift(:,:,i);
	params{i}.A = A_lift(:,:,i);
	params{i}.B_0 = B_lift(:,:,i);
	params{i}.B = B_lift(:,:,i);
	params{i}.H_0 = Zj{i}(1).A;
	params{i}.H_1 = Zj{i}(2).A;
	params{i}.H_2 = Zj{i}(3).A;
	params{i}.H_3 = Zj{i}(4).A;
	params{i}.H_4 = Zj{i}(5).A;
	params{i}.H_5 = Zj{i}(6).A;
	params{i}.H_6 = Zj{i}(7).A;
	params{i}.H_7 = Zj{i}(8).A;
	params{i}.H_8 = Zj{i}(9).A;
	params{i}.H_9 = Zj{i}(10).A;
	params{i}.H_10 = Zj{i}(11).A;
	params{i}.Hf = Zf_box{i}.A;
	params{i}.gf = Zf_box{i}.b;
    params{i}.Q = diag([10 10 10 .1 .1 .1 1 1 1 ]);
    params{i}.Q0 = diag([10 10 10 .1 .1 .1 0 0 0]);
    params{i}.Q_final = params{i}.Q;
    params{i}.R = diag([1 1 1]);
    params{i}.g_0 = Zj{i}(1).b;
	for j = 1:H
		params{i}.g{j} = Zj{i}(j+1).b;
	end
end

%% vars for state etc
Tsim = 100;
z_state = zeros(9,Tsim+1);
u = zeros(3,Tsim);
mode = zeros(Tsim+1,1);
costs = zeros(numel(deltas),1)';
vars = cell(numel(deltas),1);
status = cell(numel(deltas),1);
inp = cell(numel(deltas),1);
Power = 0*[1;2;3;4;5];
alpha= 0.001;

z_state(:,1) = zeros(9,1);%z0
z_state(:,1) = [1*ones(3,1);0*ones(3,1);zeros(3,1)];
z_ref = zeros(9,Tsim+1);

for i = 1:Tsim+1
   z_ref(:,i) = [.5;.5;1;zeros(6,1)]; 
end
mode(1) = 1; %initial mode


for t = 1:Tsim+1
	A = A_lift(:,:,mode(t));
	B = B_lift(:,:,mode(t));
    t
    % dynamics
	z_state(:,t+1) = A*z_state(:,t) + B*(u(:,t));%+[0;0;.5*9.8]);
    
    % rmpc for all modes
    for i = 1:numel(deltas)
        params{i}.A_0 = A;
        params{i}.B_0 = B;
        params{i}.z0 = z_state(:,t+1);
        params{i}.z_ref = z_ref(:,t+1);
        [vars{i},status{i}] = cvxsolve_general(params{i},[]);
         figure(i);
         hold on;grid on;
        for j = 1:11
        %    plot(t+j-1,vars{i}.u{j}(1),'ro');hold on; %if you want to see
        %    inputs
         %   plot(t+j-1,vars{i}.u{j}(2),'go');hold on;
            plot(t+j-1,vars{i}.z{j}(1),'go');hold on; %pos in x, y are symmetric
            
%             plot(t+j-1,vars{i}.z{j}(3),'bo');hold on;
        end
        %plot(t,vars{i}.z{1}(1),'ko');hold on;
        drawnow;
        costs(i) = status{i}.optval+alpha*Power(i);
        
        inp{i} = vars{i}.u_0;
    end
    sprintf('costs %f %f %f %f %f',costs)
	[~,ix] = min(costs);
    % or fix mode here
    
	mode(t+1) = ix;
    sprintf('Mode %d', mode(t+1))
    z_state(:,t+1)'
	u(:,t+1) = inp{ix};
    % pause(3);
end

