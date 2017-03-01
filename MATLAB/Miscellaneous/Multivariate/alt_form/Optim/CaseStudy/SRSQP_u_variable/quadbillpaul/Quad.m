classdef Quad
    % A quadrotor unit
    
    properties
        parent % quad obj to follow
        isFollowing % boolean (am I following someone)
        x % meters
        y % meters
        z % meters
        roll  % degrees
        pitch % degrees
        yaw   % degrees
        roll_des  % degrees
        pitch_des % degrees
        yaw_des   % degrees
        velX % m/s
        velY % m/s
        velZ % m/s
        accX % m/s^2
        accY % m/s^2
        accZ % m/s^2
        % - simulated RF data -
        rf_velX
        rf_velY
        rf_velZ
        rf_alt
        rf_yaw
        rf_pitch
        rf_roll
        % - simulated cam data -
        cam_offset
        cam_x
        cam_y
        cam_z
        cam_canSee
        cam_vel_x
        cam_vel_y
        cam_vel_z
        cam_x_actual
        cam_y_actual
        cam_z_actual
        % - for flight extrapolation
        cam_x_old
        cam_y_old
        cam_z_old
        rf_yaw_old
        cam_downTime
        % - distance to follower in world frame -
        dist_x_des
        dist_y_des
        dist_z_des
        % - simulated thrust and integration variables -
        thrust
        p
        q
        r
        pdot
        qdot
        rdot
        
        armLength % meters
        mass % kg
        FOV % camera field of view, degrees
        
        % PID integral terms
        thrust_i
        pitch_i
        roll_i
    end
    
    methods
        % constructor
        function obj = Quad(x,y,z,yaw,pitch,roll)
            obj.isFollowing = 0;
            obj.x = x;
            obj.y = y;
            obj.z = z;
            obj.roll = roll;
            obj.pitch = pitch;
            obj.yaw = yaw;
            obj.roll_des = roll;
            obj.pitch_des = pitch;
            obj.yaw_des = yaw;
            obj.armLength = 0.3;
            obj.mass = 0.900;
            obj.velX = 0;
            obj.velY = 0;
            obj.velZ = 0;
            obj.accX = 0;
            obj.accY = 0;
            obj.accZ = 0;
            obj.rf_velX = 0;
            obj.rf_velY = 0;
            obj.rf_velZ = 0;
            obj.rf_alt = 0;
            obj.rf_yaw = 0;
            obj.rf_pitch = 0;
            obj.rf_roll = 0;
            obj.cam_offset = obj.armLength;
            obj.cam_x = 0;
            obj.cam_y = 0;
            obj.cam_z = 0;
            obj.cam_x_actual = 0;
            obj.cam_y_actual = 0;
            obj.cam_z_actual = 0;
            obj.cam_canSee = 0;
            obj.dist_x_des = 0;
            obj.dist_y_des = 0;
            obj.dist_z_des = 0;
            obj.FOV = 360;
            obj.thrust = 0;
            obj.p = 0;
            obj.q = 0;
            obj.r = 0;
            obj.pdot = 0;
            obj.qdot = 0;
            obj.rdot = 0;
            obj.thrust_i = 0;
            obj.pitch_i = 0;
            obj.roll_i = 0;
            % - for flight extrapolation -
            obj.cam_x_old = 0;
            obj.cam_y_old = 0;
            obj.cam_z_old = 0;
            obj.rf_yaw_old = 0;
            obj.cam_downTime = 0;
            
        end
        
        % return x,y,z coordinates in world frame of a specified motor
        function coord = motorLoc(obj,mot)
            switch(mot)
                case 1
                    coord = [obj.x;obj.y;obj.z] + obj.WRB*[obj.armLength;0;0];
                case 2
                    coord = [obj.x;obj.y;obj.z] + obj.WRB*[0;obj.armLength;0];
                case 3
                    coord = [obj.x;obj.y;obj.z] + obj.WRB*[-obj.armLength;0;0];
                case 4
                    coord = [obj.x;obj.y;obj.z] + obj.WRB*[0;-obj.armLength;0];
                otherwise
                    error('must specify an integer between 1 and 4');
            end
        end
        % world coordinates to body coordinates
        function BRW = BRW(obj)
            % negative below to account for matlab's coord. frame
            phi = -pi*obj.roll/180;
            theta = pi*obj.pitch/180;
            % negative below to account for matlab's coord. frame
            psi = -pi*obj.yaw/180;
            
            BRW = [ cos(psi)*cos(theta) - sin(phi)*sin(psi)*sin(theta), cos(theta)*sin(psi) + cos(psi)*sin(phi)*sin(theta), -cos(phi)*sin(theta);...
                -cos(phi)*sin(psi),  cos(phi)*cos(psi),  sin(phi);...
                cos(psi)*sin(theta) + cos(theta)*sin(phi)*sin(psi), sin(psi)*sin(theta) - cos(psi)*cos(theta)*sin(phi),  cos(phi)*cos(theta)];
        end
        % world coordinates to body, yaw only
        function BRW = BRW_yaw(obj)
            % negative below to account for matlab's coord. frame
            phi = 0;
            theta = 0;
            psi = -pi*obj.yaw/180;
            
            BRW = [cos(psi) -sin(psi) 0; sin(psi) cos(psi) 0; 0 0 1];
        end
        % body coordinates to world coordinates
        function WRB = WRB(obj)
            WRB = obj.BRW';
        end
        % body coordinates to world coordinates, yaw only
        function WRB = WRB_yaw(obj)
            WRB = obj.BRW_yaw()';
        end
        % constrain number between two values
        function val = constrain(obj,num,max,min)
            if num > max
                val = max;
            elseif num < min
                val = min;
            else
                val = num;
            end
        end
        % return x,y,z of forward-facing camera vector
        function coord = cameraVector(obj)
            coord = [obj.x;obj.y;obj.z] + obj.WRB*[obj.cam_offset;0;0];
        end
        % return up-facing camera vector from origin
        function vect = cameraUpVector(obj)
            vect = obj.WRB*[0;0;obj.armLength];
        end
        % draw sphere representing body
        function drawBody(obj)
            diameter = 0.05; % 5 cm
            [X,Y,Z] = sphere();
            X = X*diameter + obj.x;
            Y = Y*diameter + obj.y;
            Z = Z*diameter + obj.z;
            surf(X,Y,Z,'EdgeColor','none','FaceColor',[0 0 1]);
            % shadow
            plot(obj.x,obj.y,'.','LineWidth',2,...
                'MarkerEdgeColor','k',...
                'MarkerFaceColor','k',...
                'MarkerSize',10);
        end
        % draw arms
        function drawArms(obj)
            r = 0.02; % 2 cm radius
            n = 10; % granularity
            [X,Y,Z] = cylinder2P(r,n,obj.motorLoc(1)',obj.motorLoc(3)');
            h1 = surf(X,Y,Z);
            [X,Y,Z] = cylinder2P(r,n,obj.motorLoc(2)',obj.motorLoc(4)');
            h2 = surf(X,Y,Z);
            if obj.isFollowing == 1
                set(h1,'FaceColor',[1 0 0],'EdgeColor','none');
                set(h2,'FaceColor',[1 0 0],'EdgeColor','none');
            else
                set(h1,'FaceColor',[0 0 0],'EdgeColor','none');
                set(h2,'FaceColor',[0 0 0],'EdgeColor','none');
            end
        end
        % draw fiducial
        function drawFiducial(obj)
            coord = obj.motorLoc(3);
            radiusF = 0.05;
            X = coord(1);
            Y = coord(2);
            Z = coord(3);
            [xF,yF,zF] = sphere(20);
            hF = surf(radiusF*xF+X,radiusF*yF+Y,radiusF*zF+Z);
            set(hF,'FaceColor',[1 0 0],'EdgeColor','none');
        end
        % draw camera target
        function drawCamera(obj)
            coord = cameraVector(obj);
            X = coord(1); Y = coord(2); Z = coord(3);
            text(X,Y,Z,'*','HorizontalAlignment','center');
        end
        % draw camera coordinates from body frame
        function drawCameraCoords(obj)
            x = obj.BRW_yaw*([obj.cam_x; 0; 0]) + [obj.x; obj.y; obj.z];
            y = obj.BRW_yaw*([0; obj.cam_y; 0]) + [obj.x; obj.y; obj.z];
            z = [obj.x; obj.y; obj.z] + [0; 0; obj.cam_z];
            plot3([obj.x x(1)],[obj.y x(2)],[obj.z x(3)],'r','LineWidth',2);
            plot3([obj.x y(1)],[obj.y y(2)],[obj.z y(3)],'g','LineWidth',2);
            plot3([obj.x z(1)],[obj.y z(2)],[obj.z z(3)],'y','LineWidth',2);
        end
        % set parent quadrotor
        function obj = setParent(obj,parent,x,y,z)
            obj.parent = parent;
            obj.isFollowing = 1;
            obj.dist_x_des = x;
            obj.dist_y_des = y;
            obj.dist_z_des = z;
        end
        % set overall thrust
        function obj = setThrust(obj,thrust)
            obj.thrust = thrust;
        end
        % set desired yaw
        function obj = setYaw(obj,ang)
            obj.yaw_des = ang;
        end
        % set desired pitch
        function obj = setPitch(obj,ang)
            obj.pitch_des = ang;
        end
        % set desired roll
        function obj = setRoll(obj,ang)
            obj.roll_des = ang;
        end
        % receive simulated RF data
        function obj = simulateRF(obj,error)
            errorToAdd = -error + (2*error)*rand();
            % right now we're only sending yaw
            obj.rf_yaw = obj.parent.yaw + errorToAdd;
            
        end
        % determine fiducial location in camera
        function obj = parseCamera(obj,dT,error)
            % generate random numbers
            randX = -error + (2*error)*rand();
            randY = -error + (2*error)*rand();
            randZ = -error + (2*error)*rand();
            
            x = 0;
            y = 0;
            z = 0;
            canSee = 1;
            if obj.isFollowing == 0
                % not following anything
                return;
            end
            
            % define camera transform
            FOV = obj.FOV*180/pi;
            camRotX = obj.roll*pi/180;
            camRotY = -obj.pitch*pi/180;
            camRotZ = obj.yaw*pi/180;
            Cx = [1 0 0; 0 cos(camRotX) -sin(camRotX); 0 sin(camRotX) cos(camRotX)];
            Cy = [cos(camRotY) 0 sin(camRotY); 0 1 0; -sin(camRotY) 0 cos(camRotY)];
            Cz = [cos(camRotZ) -sin(camRotZ) 0; sin(camRotZ) cos(camRotZ) 0; 0 0 1];
            C = Cx*Cy*Cz;
            AxCx = [obj.parent.x; obj.parent.y; obj.parent.z] - [obj.x;obj.y;obj.z];
            D = C*AxCx;
            x = D(1);
            y = D(2);
            z = D(3);
            
            % define camera transform for only yaw
            camRotZ = obj.yaw*pi/180;
            Cz = [cos(camRotZ) -sin(camRotZ) 0; sin(camRotZ) cos(camRotZ) 0; 0 0 1];
            C_yaw = Cz;
            AxCx = [obj.parent.x; obj.parent.y; obj.parent.z] - [obj.x;obj.y;obj.z];
            D_yaw = C_yaw*AxCx;
            x_yaw = D_yaw(1) + randX;
            y_yaw = D_yaw(2) + randY;
            
            
            % raise flag if target is out of FOV
            if abs(atan(z/x)*180/pi) > obj.FOV/2 || abs(atan(y/x)*180/pi) > obj.FOV/2 || x < 0
                canSee = 0;
            end
            
            
            % convert camera x,y,z to world x,y,z using inverse camera
            % transform
            W = inv(C)*([x; y; z] + [0; 0; 0]);
            world_z = W(3) + randZ;
            
            
            obj.cam_x_actual = x_yaw;
            obj.cam_y_actual = y_yaw;
            obj.cam_z_actual = world_z;
            
            
            obj.cam_canSee = canSee;
            
            % handle if the target is out of view
            if canSee == 0

                obj.cam_x = obj.dist_x_des;
                obj.cam_y = obj.dist_y_des;
                obj.cam_z = obj.dist_z_des;
                
                obj.cam_vel_x = 0;
                obj.cam_vel_y = 0;
                obj.cam_vel_z = 0;
                                                                                
            else
                % update velocity guesses
                obj.cam_vel_x = (x_yaw - obj.cam_x);
                obj.cam_vel_y = (y_yaw - obj.cam_y);
                obj.cam_vel_z = (world_z - obj.cam_z);
                
                obj.cam_x = x_yaw;
                obj.cam_y = y_yaw;
                obj.cam_z = world_z;
                
                obj.cam_downTime = 0;
                obj.cam_x_old = obj.cam_x;
                obj.cam_y_old = obj.cam_y;
                obj.cam_z_old = obj.cam_z;
            end
            
        end
        % respond to stimuli (for followers)
        function obj = respond(obj,dT)
            % max desired angles
            MAX_ANGLE = 20;
            
            % gain terms
            Kp = 23;
            Ki = 0.0;
            Kd = 18;
            Kp_thrust = 100;
            Ki_thrust = 4;
            Kd_thrust = 6;
            
            % accumulate thrust integral term
            obj.thrust_i = obj.thrust_i + (obj.cam_z-obj.dist_z_des);
            obj.pitch_i = obj.pitch_i + (obj.cam_x-obj.dist_x_des);
            obj.roll_i = obj.roll_i + (obj.cam_y-obj.dist_y_des);
            
            % update desired angles
            obj.yaw_des = obj.rf_yaw;
            obj.pitch_des = Kp*(obj.cam_x-obj.dist_x_des) + Ki*(obj.pitch_i) + Kd*obj.cam_vel_x/dT;
            obj.roll_des = Kp*(obj.cam_y-obj.dist_y_des) + Ki*(obj.roll_i) + Kd*obj.cam_vel_y/dT;
            obj.thrust = Kp_thrust*(obj.cam_z-obj.dist_z_des) + Ki_thrust*(obj.thrust_i)...
                + Kd_thrust*obj.cam_vel_z/dT;
            
            % don't try to pitch/roll if close to the ground
            if(obj.z < 1)
                obj.pitch_des = 0;
                obj.roll_des = 0;
            end
            
            % constrain values for a max acceleration
            obj.pitch_des = obj.constrain(obj.pitch_des,MAX_ANGLE,-MAX_ANGLE);
            obj.roll_des = obj.constrain(obj.roll_des,MAX_ANGLE,-MAX_ANGLE);
            
        end
        % update parameters
        function obj = update(obj,dT,Kp,Ki,Kd)
            % PID controls
            error_pitch = obj.pitch_des - obj.pitch;
            rate_pitch = obj.p/dT;
            obj.pdot = Kp*error_pitch - Kd*rate_pitch;
            
            error_roll = obj.roll_des - obj.roll;
            rate_roll = obj.q/dT;
            obj.qdot = Kp*error_roll - Kd*rate_roll;
            
            error_yaw = obj.yaw_des - obj.yaw;
            rate_yaw = obj.r/dT;
            obj.rdot = Kp*error_yaw - Kd*rate_yaw;
            
            % update angular velocities
            obj.p = obj.p+(dT*obj.pdot);
            obj.q = obj.q+(dT*obj.qdot);
            obj.r = obj.r+(dT*obj.rdot);
            
            % update angles
            obj.pitch = obj.pitch+(dT*obj.p);
            obj.roll = obj.roll+(dT*obj.q);
            obj.yaw = obj.yaw+(dT*obj.r);
            
            % update accelerations
            thrust_xy = obj.BRW_yaw*[obj.thrust*sin(obj.pitch*pi/180)/obj.mass;...
                obj.thrust*sin(obj.roll*pi/180)/obj.mass; 0];
            obj.accX = thrust_xy(1);
            obj.accY = thrust_xy(2);
            obj.accZ = obj.thrust*cos((obj.pitch + obj.roll)*pi/180)/obj.mass - 9.81;
            
            % update velocities
            obj.velX = obj.velX + obj.accX*dT;
            obj.velY = obj.velY + obj.accY*dT;
            obj.velZ = obj.velZ + obj.accZ*dT;
            
            % update coordinates
            obj.x = obj.x+(dT*obj.velX);
            obj.y = obj.y+(dT*obj.velY);
            obj.z = obj.z+(dT*obj.velZ);
            
            % check for ground collision
            if(obj.z < 0)
                obj.z = 0;
                obj.pitch = 0;
                obj.roll = 0;
                obj.velX = 0;
                obj.velY = 0;
                obj.velZ = 0;
                obj.accX = 0;
                obj.accY = 0;
                obj.accZ = 0;
            end
            
        end
        % calculate error
        function err = absError(obj)
            err = sqrt((obj.dist_x_des-obj.cam_x_actual)^2 +...
            (obj.dist_y_des-obj.cam_y_actual)^2 +...
            (obj.dist_z_des-obj.cam_z_actual)^2);
        end
    end
end

