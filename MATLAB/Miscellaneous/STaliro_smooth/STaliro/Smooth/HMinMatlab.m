function HyDistOut = HMinMatlab(inp1,inp2)

HyDistOut.dl = double(0.0);
HyDistOut.ds = double(0.0);
if ((inp1.dl<inp2.dl) || ((inp1.dl==inp2.dl) && (inp1.ds<=inp2.ds)))
		HyDistOut = inp1;
else
        HyDistOut = inp2;
end