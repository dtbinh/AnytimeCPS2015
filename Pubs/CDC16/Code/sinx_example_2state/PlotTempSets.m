load('TempSets_par');
figure;
for i = 1:counter
    M = TempSet{i};
    MA = M(:,1:2);
    MB = M(:,3);
    Cd = Polyhedron('A',MA,'B',MB);
    Cd.minHRep;
    hold all;
    Cd.plot;
end
