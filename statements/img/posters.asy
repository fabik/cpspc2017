import graph;
import geometry;

unitsize(1cm);

xlimits(0, 11);
ylimits(0, 8);

xaxis(BottomTop, Ticks(extend=true, pTick=lightgrey, ptick=invisible));
yaxis(LeftRight, Ticks(extend=true, pTick=lightgrey, ptick=invisible));

xequals(Label("$x$",align=2NE),0,ymin=0, ymax=7.5, p=linewidth(1.5pt), Arrow(2mm));
yequals(Label("$y$",align=2NE),0,xmin=0, xmax=10.5, p=linewidth(1.5pt), Arrow(2mm));

dot((0,0));

pair[] body = {(1,2),(4,1),(4,4),(6,1),(6,4),(8,3),(6,5),(10,4)};

fill((1,1)--(5,1)--(5,5)--(1,5)--cycle,gray);
fill((4,5)--(4,7)--(7,7)--(7,5)--cycle,gray);
fill((6,2)--(7,2)--(7,4)--(6,4)--cycle,gray);
//for(int i=0;i<body.length;++i) dot(body[i]); 

//draw( body[0] -- body[1] );
//draw( body[0] -- body[2] );

int[] q1 = {4,7,3,6};
for (int i=0; i<2; ++i) {
    draw( (q1[+i],q1[2+i]) -- (q1[1],q1[2]), linewidth(1));
    draw( (q1[+i],q1[2+i]) -- (q1[0],q1[3]), linewidth(1));
    dot((q1[i],q1[2+i]));
    dot((q1[i],q1[3 - i]));
}

int[] q1 = {2,3,2,4};
for (int i=0; i<2; ++i) {
    draw( (q1[+i],q1[2+i]) -- (q1[1],q1[2]), linewidth(1));
    draw( (q1[+i],q1[2+i]) -- (q1[0],q1[3]), linewidth(1));
    dot((q1[i],q1[2+i]));
    dot((q1[i],q1[3 - i]));
}

int[] q1 = {1,8,1,7};
for (int i=0; i<2; ++i) {
    draw( (q1[+i],q1[2+i]) -- (q1[1],q1[2]), linewidth(1));
    draw( (q1[+i],q1[2+i]) -- (q1[0],q1[3]), linewidth(1));
    dot((q1[i],q1[2+i]));
    dot((q1[i],q1[3 - i]));
}

int[] q1 = {9,10,2,3};
for (int i=0; i<2; ++i) {
    draw( (q1[+i],q1[2+i]) -- (q1[1],q1[2]), linewidth(1));
    draw( (q1[+i],q1[2+i]) -- (q1[0],q1[3]), linewidth(1));
    dot((q1[i],q1[2+i]));
    dot((q1[i],q1[3 - i]));
}
