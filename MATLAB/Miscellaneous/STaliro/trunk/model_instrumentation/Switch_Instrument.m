function [switch_block_info] = Switch_Instrument(modelName,switcharray,blockList,connHandleList)
% Instruments the switch blocks in the model with output ports and
% returns an output struct with switch block information.
% Inputs:
%	modelName -  simulink model name to be instrumented
%	switcharray - cell array of list of switch blocks that are to be  
%   instrumented. The cell array must contain the complete path of 
%   the block in the model. 
%   For Ex: saturate_blocks{1}=Toy_demo/subsystem1/switch1 will instrument 
%   the block switch1.
%   block_List - list of the blocks in the model obtained from Model_Reader
%   connHandleList - list handles of the blocks in the model
%
% Outputs:
%   switch_block_info -  structure with follpwing fields:
%      bool_blocks - structure array for boolean switch blocks with fields
%           * conn_handle - array of handles of source block connected to
%           the switch blocks.
%           * rel_conn_handle - struture storing information of the source
%           blocks connected to relational operator blocks. 
%      double_blocks - structure array for double switch blocks with fields
%           * threshold - array containing switchng thresholds
%           corresponding to each  double type switch blocks
%           * criteria - array containng criteria for switching. stores
%           either '>=' or '>' corresponding to each doubele switch blocks.
%           *outportindex - array of output port index added corresponding
%           to each double type switch block
%      num_of_boolsw - number of boolean type switch blocks
%      num_of_doublesw - number of double type switch blocks
%      numport_index - the index where Numerical outport ends
%      endport_index - end index of output port added in the model
%      instrumentation 

    %Initialisation output structure
    switch_block_info=struct('bool_blocks',{},'double_blocks',{},'num_of_boolsw',0,'num_of_doublesw',0,'numport_index',0,'endport_index',0);
    
    % Copy input arguments
    if isempty(switcharray)
       swcount = 0;
    else
        switch_cell_size=size(switcharray);
        swcount= switch_cell_size(1,1);% get number of rows
    end
    
    eval([modelName,'([],[],[],''compile'');']);    
    % Check the data type connected to switch block trigger input
    % and save the info in cell arrays
    Switchconnhandle=zeros(swcount,1);
    Switchconnhandlebool=zeros(swcount,1);
    doubleswitch=0;
    boolswitch=0;
    for i=1:swcount
        portTypeList = get_param(switcharray{i,1}, 'CompiledPortDataTypes');
        portConn = get_param(switcharray{i,1}, 'PortConnectivity');
        if(strcmp(portTypeList.Inport{1,2},'double'))
            %call=1;
            switcharray{i,3}=1; % storing a 1 to imply that a double data type is connected to switch
            Switchconnhandle(i,1)= portConn(2,1).SrcBlock; %storing the handle of source block having double data type
            Switchconnhandle(i,2)= portConn(2,1).SrcPort+1;
            doubleswitch=doubleswitch+1;
        elseif (strcmp(portTypeList.Inport{1,2},'boolean'))
            switcharray{i,3}=2; % there is boolean connection
            Switchconnhandlebool(i,1)= portConn(2,1).SrcBlock;%storing the handle of source block having bool data type
            Switchconnhandlebool(i,2)= portConn(2,1).SrcPort+1;
            boolswitch=boolswitch+1;
        end
    end
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
   Relsourcehandle=struct('source1',[],'source1type','','source2type','','source2',[],'out1',[],'out2',[]); 
   for  i=1: swcount
        if (Switchconnhandlebool(i,1)~=0)
            portConn = get_param(Switchconnhandlebool(i,1), 'PortConnectivity');
            Inpblock1= portConn(1,1).SrcBlock; %storing the handle of source block 1
            Inpblock2= portConn(2,1).SrcBlock;%storing the handle of source block 2
            % Use structures to store the handle of blocks
            % connected to relational operation blocks
            Relsourcehandle(i,1).source1type= get_param(Inpblock1, 'BlockType');
            Relsourcehandle(i,1).source1=Inpblock1; 
            Relsourcehandle(i,1).source2type= get_param(Inpblock2, 'BlockType');
            Relsourcehandle(i,1).source2=Inpblock2;%handle of source block2 of relational operator if it is not constant
        end
   end
   eval([modelName,'([],[],[],''term'');']);
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
   
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 newoutportnumber=0;
 mainparenthandle=get_param(blockList{1},'Handle');
 newoutport=0;
 pos = [1000 125 1025 135];
 %Section adds outports for double type switch blocks before the Numerical
 %ports for bool type switches
 switchdouble_info=struct('threshold',[],'criteria','','outportindex',[]);
 double_count=0;
 for i_count=1:swcount
    if (switcharray{i_count,3}==1)
        for j=1:length(blockList)
            if(connHandleList{j} == Switchconnhandle(i_count,1))
                newoutport=newoutport+1;
                outportstring=num2str(newoutport);
                outportstring=strcat('out-',outportstring); % to create new name for the outport that is going to be added
                pos=pos+ [0 50 0 50];% update the position coordinates of the block to be addeded to avoid overlap
                open_system(modelName);%open_system(name);
                blkname=get_param(blockList{j}, 'Name');
                data=get_param(switcharray{i_count,1},'Handle');
                childblockhandle=find_system(data,'FollowLinks', 'on', ...
                    'LookUnderMasks', 'none' );
                srcportnumber= Switchconnhandle(i_count,2);
                newoutportnumber=AddOutport(mainparenthandle,childblockhandle,blkname,srcportnumber,pos,outportstring); % call the function to add outport
                switchdouble_info(i_count,1).outportindex=newoutportnumber;
                double_count= double_count+1;
                str_threshold = str2double(get_param(switcharray{i_count,1},'Threshold'));
                % evaluate block variable from input file
                if(isnan(str_threshold))
                    try
                    strvalue=get_param(switcharray{i_count,1},'Threshold');
                    switchdouble_info(i_count,1).threshold = evalin('base', strvalue);
                    catch
                        error('could not evaluate threshold of switch block. please load the variable in base workspace\n')
                    end
                else
                    switchdouble_info(i_count,1).threshold = str_threshold;
                end
                criteria_str= get_param(switcharray{i_count,1},'Criteria');
                if strcmp(criteria_str,'u2 >= Threshold')
                    switchdouble_info(i_count,1).criteria='>=';
                elseif strcmp(criteria_str,'u2 > Threshold')
                    switchdouble_info(i_count,1).criteria='>';
                else
                    switchdouble_info(i_count,1).criteria='~=0';
                end
                break;
            end               
        end
    end
 end
 
 %Section adds Numerical outports. Numerical outports are added first and then Location outports are added.  
    for i = 1:swcount
       if (switcharray{i,3} == 2)
   %%%% How to consider first port is also constant?%%%%%  
   %%%Gong to fail if both inputs to relational is constant%%%
           if(~strcmpi(Relsourcehandle(i,1).source1type,'Constant'))
               newoutport=newoutport+1;
               outportstring=num2str(newoutport);
               outportstring=strcat('out-',outportstring); % to create new name for the outport that is going to be added
               pos=pos+ [0 50 0 50];  % update the position coordinates of the block to be addeded to avoid overlap
               open_system(modelName);%open_system(name);

               blkname=get_param(Relsourcehandle(i,1).source1, 'Name');
               childblockhandle=find_system(Switchconnhandlebool(i,1),'FollowLinks', 'on', ...
                                'LookUnderMasks', 'none' );
               srcportnumber= Switchconnhandlebool(i,2);
               newoutportnumber=AddOutport(mainparenthandle,childblockhandle,blkname,srcportnumber,pos,outportstring); % call the function to add outport
               Relsourcehandle(i,1).out1=newoutportnumber;
           end
           
           if(~strcmpi(Relsourcehandle(i,1).source2type,'Constant'))
               newoutport = newoutport+1;
               outportstring = num2str(newoutport);
               outportstring = strcat('out-',outportstring); % to create new name for the outport that is going to be added
               pos = pos+ [0 50 0 50]; 
               open_system(modelName);%open_system(name);
               
               blkname = get_param(Relsourcehandle(i,1).source2, 'Name');
               childblockhandle = find_system(Switchconnhandlebool(i,1),'FollowLinks', 'on', ...
                                'LookUnderMasks', 'none' );  
               srcportnumber = Switchconnhandlebool(i,2);
               newoutportnumber = AddOutport(mainparenthandle,childblockhandle,blkname,srcportnumber,pos,outportstring);
               Relsourcehandle(i,1).out2 = newoutportnumber;
           end
       end
    end
 guardsize = newoutportnumber;
 %Numerical outports end here. Store the index where Numerical outport ends
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%Section adds Location outports%%%
    for i = 1:swcount
        if (switcharray{i,3}==2)
            for j=1:length(blockList)
                if(connHandleList{j} == Switchconnhandlebool(i,1))
                    newoutport = newoutport+1;
                    outportstring = num2str(newoutport);
                    outportstring = strcat('out-',outportstring); % to create new name for the outport that is going to be added
                    pos = pos+ [0 50 0 50];% update the position coordinates of the block to be addeded to avoid overlap
                    open_system(modelName);%open_system(name);         
                    blkname=get_param(blockList{j}, 'Name');          
                    data=get_param(switcharray{i,1},'Handle');
                    childblockhandle=find_system(data,'FollowLinks', 'on', ...
                    'LookUnderMasks', 'none' );
                    srcportnumber= Switchconnhandlebool(i,2);
                    newoutportnumber = AddOutport(mainparenthandle,childblockhandle,blkname,srcportnumber,pos,outportstring); % call the function to add outport
                    break;
                end
            end                
         end       
     end
    endofoutports=newoutportnumber;
    %addition of Location outports end here. Store the index.   
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

   switch_block_info(1).bool_blocks.conn_handle= Switchconnhandlebool;
   switch_block_info(1).bool_blocks.rel_conn_handle= Relsourcehandle;
   switch_block_info(1).double_blocks= switchdouble_info;
   switch_block_info(1).num_of_boolsw=boolswitch;
   switch_block_info(1).num_of_doublesw=double_count;
   switch_block_info(1).numport_index=guardsize;
   switch_block_info(1).endport_index=endofoutports; 
   
end

