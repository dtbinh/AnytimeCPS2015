%%
close all;
realistic = 0;
if(realistic)

Pouter_1 = Polyhedron([41 23;51 22;51 -22;41 -23]);
Pouter_1.plot('alpha',0.9,'color','green');hold on;
Pouter_2 = Polyhedron([-43 19;-43 -19;-53 16;-53 -16;-42 21;-42 -21;-22 17;-22 -17]);
Pouter_2.plot('alpha',0.9,'color','green');grid on;

P1 = Polyhedron([-43 19; -20 42.5; 20 42.5;41 23; 41 -23; 20 -42.5;-20 -42.5;-43 -19]);
P1.plot('alpha',0.1);

P2 = Polyhedron([-17 22;17 22;22 17; 22 -17;17 -22;-17 -22;-22 -17;-22 17]);
P2.plot('alpha',0.7,'color','blue');

P3 = Polyhedron([-8 7.5;8 7.5;10 4.5;10 -4.5;8 -7.5;-8 -7.5;-10 -4.5;-10 4.5]);
P3.plot('alpha',0.7,'color','black');
else
    %squares
   mag = 47; 
   P1 = Polyhedron('ub',mag*ones(2,1),'lb',-mag*ones(2,1));
   mag = 28;
   P2 = Polyhedron('ub',mag*ones(2,1),'lb',-mag*ones(2,1));
   mag = 11;
   P3 = Polyhedron('ub',mag*ones(2,1),'lb',-mag*ones(2,1));
   Pouter_2 = Polyhedron([-53 16;-47 16;-53 -16;-47 -16]);
   Pouter_1 = Polyhedron([47 22;53 22;47 -22; 53 -22]);
end



%%
close all
figure;
plot(P1);
hold on;
plot(Pouter_1,'color','green');
hold on;
plot(Pouter_2,'color','green');
hold on;
plot(P2,'color','blue');
hold on;
plot(P3,'color','black');

