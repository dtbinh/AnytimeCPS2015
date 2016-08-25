function [r1, r2, r3] = quat2angle( q, varargin )
%  QUAT2ANGLE Convert quaternion to rotation angles.
%   [R1 R2 R3] = QUAT2ANGLE( Q ) calculates the calculates the set of
%   rotation angles, R1, R2, R3, for a given quaternion, Q.  Input Q is an
%   M-by-4 matrix containing M quaternions.  R1 returns an M array of
%   first rotation angles.  R2 returns an M array of second rotation
%   angles.  R3 returns an M array of third rotation angles. Each element
%   of Q must be a real number.  Additionally, Q has its scalar number as 
%   the first column. Rotation angles are output in radians.   
%
%   [R1 R2 R3] = QUAT2ANGLE( Q, S ) calculates the set of rotation
%   angles, R1, R2, R3, for a given quaternion, Q, and a
%   specified rotation sequence, S. 
%
%   The default rotation sequence is 'ZYX' where the order of rotation
%   angles for the default rotation are R1 = Z Axis Rotation, R2 = Y Axis
%   Rotation, and R3 = X Axis Rotation. 
%
%   All rotation sequences, S, are supported: 'ZYX', 'ZYZ', 'ZXY', 'ZXZ',
%   'YXZ', 'YXY', 'YZX', 'YZY', 'XYZ', 'XYX', 'XZY', and 'XZX'.
%
%   Examples:
%
%   Determine the rotation angles from q = [1 0 1 0]:
%      [yaw, pitch, roll] = quat2angle([1 0 1 0])
%
%   Determine the rotation angles from multiple quaternions:
%      q = [1 0 1 0; 1 0.5 0.3 0.1];
%      [pitch, roll, yaw] = quat2angle(q, 'YXZ')
%
%   See also ANGLE2DCM, DCM2ANGLE, DCM2QUAT, ANGLE2QUAT, QUAT2DCM. 

%   Copyright 2000-2007 The MathWorks, Inc.
%   $Revision: 1.1.6.1 $  $Date: 2007/05/10 13:42:36 $

%   Limitations: 
%   The limitations for the 'ZYX', 'ZXY', 'YXZ', 'YZX', 'XYZ', and 'XZY'
%   implementations generate an R2 angle that lies between +/- 90 
%   degrees, and R1 and R3 angles that lie between +/- 180 degrees. 
%
%   The limitations for the 'ZYZ', 'ZXZ', 'YXY', 'YZY', 'XYX', and 'XZX'
%   implementations generate an R2 angle that lies between 0 and 
%   180 degrees, and R1 and R3 angles that lie between +/- 180 degrees. 

% error(nargchk(1, 2, nargin,'struct'));

if nargin == 1
    type = 'zyx';
else
    if ischar( varargin{1} )
        type = varargin{1};
    else
        error('aero:quat2angle:notchar','Rotation sequence is not a string.');
    end
end

qin = quatnormalize( q );

switch lower( type )
    case 'zyx'
        [r1, r2, r3] = threeaxisrot( 2.*(qin(:,2).*qin(:,3) + qin(:,1).*qin(:,4)), ...
                                   qin(:,1).^2 + qin(:,2).^2 - qin(:,3).^2 - qin(:,4).^2, ...
                                  -2.*(qin(:,2).*qin(:,4) - qin(:,1).*qin(:,3)), ...
                                   2.*(qin(:,3).*qin(:,4) + qin(:,1).*qin(:,2)), ...
                                   qin(:,1).^2 - qin(:,2).^2 - qin(:,3).^2 + qin(:,4).^2);
    case 'zyz'
        [r1, r2, r3] = twoaxisrot( 2.*(qin(:,3).*qin(:,4) - qin(:,1).*qin(:,2)), ...
                                 2.*(qin(:,2).*qin(:,4) + qin(:,1).*qin(:,3)), ...
                                 qin(:,1).^2 - qin(:,2).^2 - qin(:,3).^2 + qin(:,4).^2, ...
                                 2.*(qin(:,3).*qin(:,4) + qin(:,1).*qin(:,2)), ...
                                -2.*(qin(:,2).*qin(:,4) - qin(:,1).*qin(:,3)));
                
    case 'zxy'
        [r1, r2, r3] = threeaxisrot( -2.*(qin(:,2).*qin(:,3) - qin(:,1).*qin(:,4)), ...
                                    qin(:,1).^2 - qin(:,2).^2 + qin(:,3).^2 - qin(:,4).^2, ...
                                    2.*(qin(:,3).*qin(:,4) + qin(:,1).*qin(:,2)), ...
                                   -2.*(qin(:,2).*qin(:,4) - qin(:,1).*qin(:,3)), ...
                                    qin(:,1).^2 - qin(:,2).^2 - qin(:,3).^2 + qin(:,4).^2);

    case 'zxz'
        [r1, r2, r3] = twoaxisrot( 2.*(qin(:,2).*qin(:,4) + qin(:,1).*qin(:,3)), ...
                                -2.*(qin(:,3).*qin(:,4) - qin(:,1).*qin(:,2)), ...
                                 qin(:,1).^2 - qin(:,2).^2 - qin(:,3).^2 + qin(:,4).^2, ...
                                 2.*(qin(:,2).*qin(:,4) - qin(:,1).*qin(:,3)), ...
                                 2.*(qin(:,3).*qin(:,4) + qin(:,1).*qin(:,2)));

    case 'yxz'
        [r1, r2, r3] = threeaxisrot( 2.*(qin(:,2).*qin(:,4) + qin(:,1).*qin(:,3)), ...
                                   qin(:,1).^2 - qin(:,2).^2 - qin(:,3).^2 + qin(:,4).^2, ...
                                  -2.*(qin(:,3).*qin(:,4) - qin(:,1).*qin(:,2)), ...
                                   2.*(qin(:,2).*qin(:,3) + qin(:,1).*qin(:,4)), ...
                                   qin(:,1).^2 - qin(:,2).^2 + qin(:,3).^2 - qin(:,4).^2);
       
    case 'yxy'
        [r1, r2, r3] = twoaxisrot( 2.*(qin(:,2).*qin(:,3) - qin(:,1).*qin(:,4)), ...
                                 2.*(qin(:,3).*qin(:,4) + qin(:,1).*qin(:,2)), ...
                                 qin(:,1).^2 - qin(:,2).^2 + qin(:,3).^2 - qin(:,4).^2, ...
                                 2.*(qin(:,2).*qin(:,3) + qin(:,1).*qin(:,4)), ...
                                -2.*(qin(:,3).*qin(:,4) - qin(:,1).*qin(:,2)));
      
    case 'yzx'       
        [r1, r2, r3] = threeaxisrot( -2.*(qin(:,2).*qin(:,4) - qin(:,1).*qin(:,3)), ...
                                    qin(:,1).^2 + qin(:,2).^2 - qin(:,3).^2 - qin(:,4).^2, ...
                                    2.*(qin(:,2).*qin(:,3) + qin(:,1).*qin(:,4)), ...
                                   -2.*(qin(:,3).*qin(:,4) - qin(:,1).*qin(:,2)), ...
                                    qin(:,1).^2 - qin(:,2).^2 + qin(:,3).^2 - qin(:,4).^2);
        
    case 'yzy'
        [r1, r2, r3] = twoaxisrot( 2.*(qin(:,3).*qin(:,4) + qin(:,1).*qin(:,2)), ...
                                -2.*(qin(:,2).*qin(:,3) - qin(:,1).*qin(:,4)), ...
                                 qin(:,1).^2 - qin(:,2).^2 + qin(:,3).^2 - qin(:,4).^2, ...
                                 2.*(qin(:,3).*qin(:,4) - qin(:,1).*qin(:,2)), ...
                                 2.*(qin(:,2).*qin(:,3) + qin(:,1).*qin(:,4)));

    case 'xyz'
        [r1, r2, r3] = threeaxisrot( -2.*(qin(:,3).*qin(:,4) - qin(:,1).*qin(:,2)), ...
                                    qin(:,1).^2 - qin(:,2).^2 - qin(:,3).^2 + qin(:,4).^2, ...
                                    2.*(qin(:,2).*qin(:,4) + qin(:,1).*qin(:,3)), ...
                                   -2.*(qin(:,2).*qin(:,3) - qin(:,1).*qin(:,4)), ...
                                    qin(:,1).^2 + qin(:,2).^2 - qin(:,3).^2 - qin(:,4).^2);
        
    case 'xyx'
        [r1, r2, r3] = twoaxisrot( 2.*(qin(:,2).*qin(:,3) + qin(:,1).*qin(:,4)), ...
                                -2.*(qin(:,2).*qin(:,4) - qin(:,1).*qin(:,3)), ...
                                 qin(:,1).^2 + qin(:,2).^2 - qin(:,3).^2 - qin(:,4).^2, ...
                                 2.*(qin(:,2).*qin(:,3) - qin(:,1).*qin(:,4)), ...
                                 2.*(qin(:,2).*qin(:,4) + qin(:,1).*qin(:,3)));
        
    case 'xzy'
        [r1, r2, r3] = threeaxisrot( 2.*(qin(:,3).*qin(:,4) + qin(:,1).*qin(:,2)), ...
                                   qin(:,1).^2 - qin(:,2).^2 + qin(:,3).^2 - qin(:,4).^2, ...
                                  -2.*(qin(:,2).*qin(:,3) - qin(:,1).*qin(:,4)), ...
                                   2.*(qin(:,2).*qin(:,4) + qin(:,1).*qin(:,3)), ...
                                   qin(:,1).^2 + qin(:,2).^2 - qin(:,3).^2 - qin(:,4).^2);
        
    case 'xzx'
        [r1, r2, r3] = twoaxisrot( 2.*(qin(:,2).*qin(:,4) - qin(:,1).*qin(:,3)), ...
                                 2.*(qin(:,2).*qin(:,3) + qin(:,1).*qin(:,4)), ...
                                 qin(:,1).^2 + qin(:,2).^2 - qin(:,3).^2 - qin(:,4).^2, ...
                                 2.*(qin(:,2).*qin(:,4) + qin(:,1).*qin(:,3)), ...
                                -2.*(qin(:,2).*qin(:,3) - qin(:,1).*qin(:,4)));
    otherwise
        error('aero:quat2angle:unknownrotation','Unknown rotation sequence, %s', type);
end

    function [r1, r2, r3] = threeaxisrot(r11, r12, r21, r31, r32)
        % find angles for rotations about X, Y, and Z axes
        r1 = atan2( r11, r12 );
        r2 = asin( r21 );
        r3 = atan2( r31, r32 );
    end

    function [r1, r2, r3] = twoaxisrot(r11, r12, r21, r31, r32)
        r1 = atan2( r11, r12 );
        r2 = acos( r21 );
        r3 = atan2( r31, r32 );
    end
end

function qout = quatnormalize( q )
%  QUATNORMALIZE Normalize a quaternion.
%   N = QUATNORMALIZE( Q ) calculates the normalized quaternion, N, for a
%   given quaternion, Q.  Input Q is an M-by-4 matrix containing M
%   quaternions.  N returns an M-by-4 matrix of normalized quaternions.
%   Each element of Q must be a real number.  Additionally, Q has its
%   scalar number as the first column.
%
%   Examples:
%
%   Normalize q = [1 0 1 0]:
%      normal = quatnormalize([1 0 1 0])
%
%   See also QUATCONJ, QUATDIVIDE, QUATINV, QUATMOD, QUATMULTIPLY, 
%   QUATNORM, QUATROTATE.

%   Copyright 2000-2005 The MathWorks, Inc.
%   $Revision: 1.1.6.1 $  $Date: 2005/11/01 23:39:35 $

qout = q./(quatmod( q )* ones(1,4));
end
function mod = quatmod( q )
%  QUATMOD Calculate the modulus of a quaternion.
%   N = QUATMOD( Q ) calculates the modulus, N, for a given quaternion, Q.  
%   Input Q is an M-by-4 matrix containing M quaternions.  N returns a 
%   column vector of M moduli.  Each element of Q must be a real number.  
%   Additionally, Q has its scalar number as the first column.
%
%   Examples:
%
%   Determine the modulus of q = [1 0 0 0]:
%      mod = quatmod([1 0 0 0])
%
%   See also QUATCONJ, QUATDIVIDE, QUATINV, QUATMULTIPLY, QUATNORM,
%   QUATNORMALIZE, QUATROTATE.

%   Copyright 2000-2005 The MathWorks, Inc.
%   $Revision: 1.1.6.1 $  $Date: 2005/11/01 23:39:32 $

mod = sqrt(quatnorm( q ));
end
function qout = quatnorm( q )
%  QUATNORM Calculate the norm of a quaternion.
%   N = QUATNORM( Q ) calculates the norm, N, for a given quaternion, Q.  Input
%   Q is an M-by-4 matrix containing M quaternions.  N returns a column vector
%   of M norms.  Each element of Q must be a real number.  Additionally, Q has
%   its scalar number as the first column.
%
%   Examples:
%
%   Determine the norm of q = [1 0 0 0]:
%      norm = quatnorm([1 0 0 0])
%
%   See also QUATCONJ, QUATDIVIDE, QUATINV, QUATMOD, QUATMULTIPLY, 
%   QUATNORMALIZE, QUATROTATE.

%   Copyright 2000-2005 The MathWorks, Inc.
%   $Revision: 1.1.6.1 $  $Date: 2005/11/01 23:39:34 $

if any(~isreal(q(:)))
    error('aero:quatnorm:isnotreal','Input elements are not real.');
end

if (size(q,2) ~= 4)
    error('aero:quatnorm:wrongdim','Input dimension is not M-by-4.');
end

qout = sum(q.^2,2);
end