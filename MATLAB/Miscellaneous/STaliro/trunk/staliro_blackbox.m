classdef staliro_blackbox < handle
% Class definition for the S-Taliro options
%
% opt = staliro_blackbox
%
% The above function call sets the following default values for the class
% properties (along with a description of other possible choices). Each 
% property is initialized to the default value.
%
% opt.model_fcnptr = @Blackboxmodel;
% Set the field with function pointer to the blackmodel file.
% opt.CLG = CLG
%     CLG -  the graph that corresponds to the finite state machine of the 
%			 system. This should be a cell vector with the adjacency list 
%			 of the graph. 
%		     If there are multiple FSM, then G should be cell vector where 
%			 each entry is a cell vector with the adjacency list for each 
% 			 FSM. In this case, the length of G should match the number of 
%			 columns of L.
%			 Example: We will set a graph with 2 FSM with 2 states each:
%			 	FSM = {[2],[1]}; % State 1 transitions to 2 and vice versa.
%				CLG{1} = FSM;
%				CLG{2} = FSM;
%			 This is required when hybrid distance metrics are used.
%
% opt.Grd = GRD
%      GRD - the guards that enable the switch from one location to the 
%			 next. In case of a single FSM, this is a structure array with  
%			 the following entries:
%				GRD(i,j).A; GRD(i,j).b
%			 A transition from state i to state j is enabled if the current 
%			 state is x and GRD(i,j).A*x<=GRD(i,j).b.
%			 The guards can be defined over the space 'X' or the space 'Y'.
%			 If there are multiple FSM, then GRD should be a cell vector
%			 where each entry should be structure array as defined above.
%
% num_of_HAs = opt.find_numofHAs(clg)
%       num_of_HAs - it is the number of hybrid automatas in the system. it
%       provides backward compatability to single HA representation. Use
%       this method to obtain the number of HAs based on the CLG provided.
% (C) 2016, Rahul Thekkalore, Arizona State University
    properties
        model_fcnptr = '';
        CLG = {};
        Grd = [];
    end 
    
    methods
        
        function obj = staliro_blackbox(varargin)
            if nargin>0
                error(' staliro_blackbox: Please access directly the properties of the object.')
            end
        end
            
    end
    
    methods 
        function set.model_fcnptr(obj,model_ptr)
           obj.model_fcnptr = model_ptr;
        end
        
        function set.CLG(obj,Clg)
           obj.CLG=Clg;
        end
        function set.Grd(obj,grd)
           obj.Grd=grd;
        end
    end
    
% to be added in next release. To be used by dp_taliro to check whether the
% system is single or multiple hybrid automatas.
%     methods
%         function num_of_HAs = find_numofHAs(clg)
%             if isnumeric(clg{1})
%                 if isempty(clg{1})
%                     num_of_HAs = 0;
%                 else
%                     num_of_HAs = 1;
%                 end
%             elseif iscell(clg{1})
%                 num_of_HAs = length(clg);
%             else
%                 error('Unknown representation of CLG \n ')
%             end
%         end
%     end
end

%check if guard exits for every clg..if not assert an error
% function check_clg_grd(obj)
%             % check if CLG is a non empty vector
%             if (~isempty(obj.CLG))&&~(isvector(obj.CLG))
%                 error('S-Taliro: Control graph must be a non empty vector.');
%             end
%             Clg_dim= length(obj.CLG);
%             % if grd not empty then check if grd is specified for every CLG 
%             % Grd empty implies no contraint on state transitions.
%             % So Grd must either be empty or exist for every CLG pair.
%             if ~isempty(obj.Grd) 
%                 for clg_col = 1 : Clg_dim
%             % CLG cell content must be vector with transition pair.
%                     if ~isvector(obj.CLG{clg_col})
%                         error('S-Taliro: Control graph cell must be a vector specifying transition from initial to finale state');
%                     end
%                     if (length(obj.CLG{clg_col})>2)
%                         error('S-Taliro: Control graph cell must be a vector specifying transition from initial to finale state')
%                     end
%             %for transition mentioned in CLG check if Grd is defined
%                     if (length(obj.CLG{clg_col}) == 2) 
%                         initial_loc = obj.CLG{clg_col}(1);                    
%                         final_loc = obj.CLG{clg_col}(2);
%                         if(isempty(obj.Grd(initial_loc,final_loc).A)||isempty(obj.Grd(initial_loc,final_loc).b))
%                             error('S-Taliro:Transition is specified between the two locations in control graph but guards for the transition not specified');
%                         end
%                     end
%                 end
%             end
%         end
