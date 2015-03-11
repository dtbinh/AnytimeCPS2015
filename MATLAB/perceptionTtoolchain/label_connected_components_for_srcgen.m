function L = label_connected_components_for_srcgen(BW, n, minimumSize)
% n = 4 or 8
% BW = black and white image
% minimumSize: ignore all components of less than a minimumSize pixels

L = zeros(size(BW));
q = zeros(0,2);
curlabel = 1;
a = size(BW);
for i=1:a(1)
    for j=1:a(2)
        if BW(i,j)==1 && ~L(i,j)
            L(i,j)=curlabel;
            q = [q; i,j];
            % pop
            while ~isempty(q)
                p = q(1,:);
                q = q(2:end,:);
                % get neighbors
                nhbrs = get_neighbours(n,p(1),p(2),a(1),a(2));
                for k=1:size(nhbrs,1)
                    if BW(nhbrs(k,1),nhbrs(k,2))==1 && ~L(nhbrs(k,1),nhbrs(k,2))
                        L(nhbrs(k,1), nhbrs(k,2))=curlabel;
                        q = [q;nhbrs(k,:)];
                    end
                end
            end
            ff = find(L==curlabel);
            nbPix = length(ff);
            if nbPix <= minimumSize
                L(ff)=0;
            else
                curlabel = curlabel+1;
            end
        else
            % do nothing
        end
    end
end