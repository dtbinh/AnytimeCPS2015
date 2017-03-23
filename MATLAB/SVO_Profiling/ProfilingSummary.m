% Make profile data mate

%deterministic with 95% CI
fts = 50:50:250;

mx = zeros(numel(fts),1);
my = zeros(numel(fts),1);
mz = zeros(numel(fts),1);
CIx = zeros(numel(fts),2);
CIy = zeros(numel(fts),2);
CIz = zeros(numel(fts),2);
Intx = zeros(numel(fts),2);
Inty = zeros(numel(fts),2);
Intz = zeros(numel(fts),2);

for fts_ix = 1:numel(fts)
    fname = strcat('Errs_',num2str(fts(fts_ix)));
    load(fname);
    pfd = recreate_profilingData(Data_rec);
    Data(fts_ix) = pfd;
    %x
    [mx(fts_ix),CIx(fts_ix,:),Intx(fts_ix,:)] = getMeanAndCI(pfd.err_x);
    [my(fts_ix),CIy(fts_ix,:),Inty(fts_ix,:)] = getMeanAndCI(pfd.err_y);
    [mz(fts_ix),CIz(fts_ix,:),Intz(fts_ix,:)] = getMeanAndCI(pfd.err_z);
    
    var_x(fts_ix) = var(pfd.err_x);
    var_y(fts_ix) = var(pfd.err_y);
    var_z(fts_ix) = var(pfd.err_z);
    % plot
    figure(1);
    subplot(311)
    hold on;
    plot(fts(fts_ix),mean(pfd.err_x),'*');
    grid on;
    subplot(312)
    plot(fts(fts_ix),mean(pfd.err_y),'*');
    hold on;
    grid on;
    subplot(313)
    hold on;
    plot(fts(fts_ix),mean(pfd.err_z),'*');
    grid on;
    
    figure(2);
    subplot(311)
    hold on;
    plot(fts(fts_ix),std(pfd.err_x),'*');
    grid on;
    subplot(312)
    plot(fts(fts_ix),std(pfd.err_y),'*');
    hold on;
    grid on;
    subplot(313)
    hold on;
    plot(fts(fts_ix),std(pfd.err_z),'*');
    grid on;
end

% variance
%order x 



%plots
