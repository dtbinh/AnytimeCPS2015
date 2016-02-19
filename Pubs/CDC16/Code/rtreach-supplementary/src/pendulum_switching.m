%Inverted Pendulum
%
%Fall 2008
%
%Taylor Johnson
%johnso99@nospam-illinois.edu
%University of Illinois at Urbana-Champaign
%Coordinated Science Laboratory
%Department of Electrical and Computer Engineering
%

%switching
%
%inputs current_controller - present controller index (1=safety, 2=base,
%                            3=exp) (1x1)
%       P - P matrix from LMI problem definining stability region, where
%           the matrix is indexed in the 3rd dimension by the current
%           controller (4x4x3)
%       x - current, future, and next future state values (



%************ Changed the argument ************
function [controller] = pendulum_switching(current_controller, P, x)
    safety = 1;
    base = 2;
    experimental = 3;
    
    % compute norms for all controller regions
    c_norm = [];
    for i = safety : experimental
        c(i).norm = x' * P(:,:,i) * x;
        c_norm(i) = c(i).norm;
    end
    
    % find controller with smallest norm
    [c_y, c_i] = min(c_norm);
    
    % the index of the smallest norm is the best controller usable
    controller = c_i;
    
    % double check for safety
    while c(controller).norm > 1 && controller ~= safety
        controller = controller - 1;
    end
    
    % TODO: change, always assuming safety for now for experiments
    controller = safety;
    
%     
% 
%     %region based on x'*P*x<1: have to check current controller to determine proper P to use
%     if (x'*P(:,:,current_controller)*x > 1)
%        %current controller leaving stabilizable region, if possible, switch
%        %to controller with larger stabilizable region
%         if (current_controller == experimental)
%             if(x'*P(:,:,base)*x > 1)
%                 controller = safety;
%             else
%                 controller = base;
%             end;
%         else
%             controller = safety;
%         end;
%     else
%         if (current_controller == 2)
%             if(x'*P(1:4,1:4,3)*x < 1)
%                 controller = 3;
%             else
%                 controller = current_controller;
%             end;
%         elseif (current_controller == 1)
%             if(x'*P(1:4,1:4,2)*x < 1)
%                 if(x'*P(1:4,1:4,3)*x < 1)
%                     controller = 3;
%                 else
%                     controller = 2;
%                 end;
%             else
%                 controller = current_controller;
%             end;
%         else
%             controller = current_controller;
%         end;
%     end;
end