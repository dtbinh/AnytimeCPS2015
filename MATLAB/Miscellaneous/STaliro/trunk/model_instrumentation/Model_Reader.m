function [non_linear_blocklist ] = Model_Reader(modelName,exclusion_list)
% Annotate the simulink model and save the list of blocklists, saturate and
% switch blocks in the system.
% Use this function independently to obtain the list of swich/saturate
% blocks in the model and develop the exclusion list to run the model
% instrumentation functionality.
% Inputs:
%	modelName -  simulink model name to be instrumented
%	exclusion_list - cell array of list of blocks that are to be excluded 
%   for instrumentation. The cell array must contain the complete path of 
%   the block in the model. 
%   For Ex: exclusion_list{1}=Toy_demo/subsystem1/switch1 will exclude the
%   block switch1 from instrumentation.
% Outputs:
%   non_linear_blocklist -  structure with follpwing fields:
%       switch_blocks - cell array of switch blocks in the system excluding
%       the blocks mentioned in exclusion_list.
%       saturate_blocks - cell array of satutate blocks in the system 
%       excluding the blocks mentioned in exclusion_list. 
%       blockList - list of all the blocks in the model.
%       connHandleList - list handles of the blocks in the model

 % check correctness of inputs
    if (nargin == 0)
          fprintf('\n USAGE: BlackBoxToyotaEngine_added_features(''modelName'')\n');
          fprintf('Please give model name without file extension.\n');
        return;
    elseif (nargin >0) 
        if (isempty(modelName))
        error('\n ERROR: Please pass Simulink model name as a parameter without file extension.\n');
        %return;
        end
        if (nargin == 2)
            if iscell(exclusion_list)
            exclusion_list_array=exclusion_list;
            else
            error('\n the exclusion list must be a cell array of switch/saturate blocks \n')
            end
        elseif(nargin == 1)
        exclusion_list_array={};  
        end
    end
    
    %Initialise the Output
    non_linear_blocklist= struct('switch_blocks',{},'saturate_blocks',{},'blockList',{},'connHandleList',{},'num_org_outports',[]);
    
    %initialisations
    swcount=0; % Initialise the switch count
    %switcharray{1,1}='';
    switcharray = {};
    saturation_count=0; % Initialise the saturation count
    %saturation_array{1,1}='';
    saturation_array = {};
    
 % Turn off warnings that can arise from model to be opened/loaded
    warning('off');
    wasModelOpenedAlready = 1;
    try
        blockList = find_system( modelName, 'FollowLinks', 'on', ...
           'LookUnderMasks', 'all' );
    catch
        fprintf('\nModel ''%s'' is not open. Trying to load model.\n', modelName);
        wasModelOpenedAlready = 0;
        try
            load_system(modelName);
            blockList = find_system( modelName, 'FollowLinks', 'on', ...
           'LookUnderMasks', 'none' );
        catch
            fprintf('ERROR: Model ''%s'' could not be loaded.\nBe sure to give model name as a parameter without file extension.\n', modelName);
            return;
        end
    end

    name = get_param(blockList{1}, 'Name');
    fprintf('Model ''%s'' is read. Name: ''%s'' total %d blocks \n', modelName, name, length(blockList));
    
    handleList = cell(length(blockList), 1); % Keeps handles of items
    inPortList = cell(length(blockList), 1); % If an item is input port, keeps # of port
    outPortList = cell(length(blockList), 1); % If an item is output port, keeps # of port
    connHandleList = cell(length(blockList), 1); % If an item is input/output port of its parent, keeps handle of its parent

    for i = 1:length(blockList)
        handleList{i} = get_param(blockList{i}, 'Handle');
        try
            blockType = cellstr(get_param(blockList{i}, 'BlockType'));
        catch
            blockType = 'none';
        end
        if (strcmpi(blockType,'Inport'))
            inPortList{i} = get_param(blockList{i}, 'Port');
            outPortList{i} = 0;
            connHandleList{i} = get_param(get_param(blockList{i}, 'Parent'), 'Handle');
        elseif (strcmpi(blockType,'Outport'))
            inPortList{i} = 0;
            outPortList{i} = get_param(blockList{i}, 'Port');
            connHandleList{i} = get_param(get_param(blockList{i}, 'Parent'), 'Handle');

        else
            connHandleList{i} = handleList{i};
            inPortList{i} = 0;
            outPortList{i} = 0;
        end
        % switch/saturate blocks in masked subsystem not considered for now.
        % Switch/saturate blocks in masked system identified and ignored
        Parentblock=get_param(blockList{i},'Parent');
        try
            Parentmaskstatus=get_param(Parentblock,'Mask');
        catch
            Parentmaskstatus='OFF';
        end
        if (strcmpi(blockType,'Switch')&& strcmpi(Parentmaskstatus,'OFF'))    
             %fprintf('switch block no is %d \n',i);
             exclusion_status=0;
             if (~isempty(exclusion_list_array))
                 for i_excl_list = 1: length(exclusion_list_array)
                     if strcmp(blockList{i},exclusion_list_array{i_excl_list})
                         exclusion_status=1;
                         break;
                     end
                 end
                 if exclusion_status==1
                     exclusion_status=0;
                     continue;
                 end
             end
             switchname = blockList{i};
             swcount=swcount+1;
             switcharray{swcount,1}=switchname;
        elseif (strcmpi(blockType,'Saturate') && strcmpi(Parentmaskstatus,'OFF'))    
             %fprintf('saturation block no is %d \n',i);
             exclusion_status=0;
             if (~isempty(exclusion_list_array))
                 for i_excl_list = 1: length(exclusion_list_array)
                     if strcmp(blockList{i},exclusion_list_array{i_excl_list})
                         exclusion_status=1;
                         break;
                     end
                 end
                 if exclusion_status==1
                     exclusion_status=0;
                     continue;
                 end
             end
             saturation_count=saturation_count+1;
             saturation_name = blockList{i};
             saturation_array{saturation_count,1}=saturation_name;
        end
    end
    outport_array = find_system(modelName,'SearchDepth',1,'BlockType','Outport');
    non_linear_blocklist(1).num_org_outports = length(outport_array);
    % update the output structure    
    non_linear_blocklist(1).switch_blocks= switcharray;
    non_linear_blocklist(1).saturate_blocks= saturation_array;
    non_linear_blocklist(1).blockList= blockList;
    non_linear_blocklist(1).connHandleList = connHandleList;
    
    fprintf(' Model read done \n');
end
