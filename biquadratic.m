h = 1/2;
q = 1/4;
o = 1/8;
s = 1/16;
a = [[1 0 0 0 0 0 0 0 0];
     [1 0 0 h 0 0 q 0 0];
     [1 0 0 1 0 0 1 0 0];
     [1 h q 1 h q 1 h q]
     [1 1 1 1 1 1 1 1 1];
     [1 1 1 h h h q q q];
     [1 1 1 0 0 0 0 0 0];
     [1 h q 0 0 0 0 0 0];
     [1 h q h q o q o s]];
inv(a)
