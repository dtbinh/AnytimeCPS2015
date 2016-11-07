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
    %x
    [mx(fts_ix),CIx(fts_ix,:),Intx(fts_ix,:)] = getMeanAndCI(pfd.err_x);
    [my(fts_ix),CIy(fts_ix,:),Inty(fts_ix,:)] = getMeanAndCI(pfd.err_y);
    [mz(fts_ix),CIz(fts_ix,:),Intz(fts_ix,:)] = getMeanAndCI(pfd.err_z);
    
end

% variance