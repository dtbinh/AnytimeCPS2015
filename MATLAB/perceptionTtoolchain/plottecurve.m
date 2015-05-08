npts = size(tecurve,1);
a = zeros(npts,2);
M = 0;
for i=1:npts
    M = max(M,tecurve{i,2}(2));
end
misspenalty = M;
for i=1:npts
    a(i,:) = tecurve{i,2};
    a(i,2) = a(i,2) + tecurve{i,3}*misspenalty;
    sprintf('%d ,%d, %d\n',a(i,1),a(i,2),tecurve{i,3})
end
[st,six] = sort(a(:,1));
se = a(six,2);
figure
plot(st,se,'ro');
hold on
plot(st,se)

