
#1: 10
#2: 100
#3: 1000
#4: 100000 1
#5: 100000
#6: 1000000

#1: parameters
#2: all + trap
#3: all
#4: all + random
#5: edges + random high

./wesnoth_gen 10 60 3 1 5 6 7 > test/0.sample.a.in;
./wesnoth_gen 1 30 11 2 > test/1.a.in;
./wesnoth_gen 2 80 11 2 > test/1.b.in;
./wesnoth_gen 3 40 11 2 > test/1.c.in;
./wesnoth_gen 4 50 11 2 > test/1.d.in;
./wesnoth_gen 5 20 11 2 > test/1.e.in;
./wesnoth_gen 6 70 11 2 > test/1.f.in;
./wesnoth_gen 7 40 11 2 > test/1.g.in;
./wesnoth_gen 8 51 11 2 > test/1.h.in;
./wesnoth_gen 9 34 11 2 > test/1.i.in;
./wesnoth_gen 10 1 100000 4 > test/1.j.in;
./wesnoth_gen 100 51 100 3 > test/2.a.in;
./wesnoth_gen 90 40 90 3 > test/2.b.in;
./wesnoth_gen 95 90 95 3 > test/2.c.in;
./wesnoth_gen 85 3 85 3 > test/2.d.in;
./wesnoth_gen 84 35 84 3 > test/2.e.in;
./wesnoth_gen 1000 51 1000 3 > test/3.a.in;
./wesnoth_gen 999 40 999 3 > test/3.b.in;
./wesnoth_gen 998 36 998 3 > test/3.c.in;
./wesnoth_gen 997 33 997 3 > test/3.d.in;
./wesnoth_gen 996 17 996 3 > test/3.e.in;
./wesnoth_gen 995 40 995 3 > test/3.f.in;
./wesnoth_gen 100000 40 1 1 39935 > test/4.a.in;
./wesnoth_gen 100000 40 1 1 39936 > test/4.b.in;
./wesnoth_gen 100000 40 1 1 40000 > test/4.c.in;
./wesnoth_gen 100000 40 1 1 40001 > test/4.d.in;
./wesnoth_gen 100000 40 1 1 50000 > test/4.e.in;
./wesnoth_gen 100000 40 1 1 50001 > test/4.f.in;
./wesnoth_gen 90000 51 1 1 45879 > test/4.g.in;
./wesnoth_gen 90000 51 1 1 45880 > test/4.h.in;
./wesnoth_gen 90000 51 1 1 45900 > test/4.i.in;
./wesnoth_gen 90000 51 1 1 45901 > test/4.j.in;
./wesnoth_gen 98765 35 1 1 34536 > test/4.k.in;
./wesnoth_gen 98765 35 1 1 34537 > test/4.l.in;
./wesnoth_gen 98765 35 1 1 34566 > test/4.m.in;
./wesnoth_gen 98765 35 1 1 34567 > test/4.n.in;
./wesnoth_gen 98765 35 1 1 34854 > test/4.o.in;
./wesnoth_gen 98765 35 1 1 34855 > test/4.p.in;
./wesnoth_gen 98765 35 1 1 90000 > test/4.q.in;
./wesnoth_gen 88888 1 1 1 878 > test/4.r.in;
./wesnoth_gen 88888 1 1 1 879 > test/4.s.in;
./wesnoth_gen 88888 1 1 1 880 > test/4.t.in;
./wesnoth_gen 99999 99 1 1 99998 > test/4.u.in;
./wesnoth_gen 99999 99 1 1 9 > test/4.v.in;
./wesnoth_gen 100000 51 100000 5 > test/5.a.in;
./wesnoth_gen 100000 36 100000 5 > test/5.b.in;
./wesnoth_gen 100000 75 100000 5 > test/5.c.in;
./wesnoth_gen 100000 34 100000 5 > test/5.d.in;
./wesnoth_gen 98888 37 100000 5 > test/5.e.in;
./wesnoth_gen 1000 1 1000 3 > test/5.f.in;
./wesnoth_gen 1000000 51 100000 5 > test/6.a.in;
./wesnoth_gen 1000000 36 100000 5 > test/6.b.in;
./wesnoth_gen 1000000 60 100000 5 > test/6.c.in;
./wesnoth_gen 1000000 40 100000 5 > test/6.d.in;
./wesnoth_gen 999999 37 100000 5 > test/6.e.in;
./wesnoth_gen 1000 1 1000 3 > test/6.f.in;

./wesnoth_okmaker < test/0.sample.a.in > test/0.sample.a.out;
./wesnoth_okmaker < test/1.a.in > test/1.a.out;
./wesnoth_okmaker < test/1.b.in > test/1.b.out;
./wesnoth_okmaker < test/1.c.in > test/1.c.out;
./wesnoth_okmaker < test/1.d.in > test/1.d.out;
./wesnoth_okmaker < test/1.e.in > test/1.e.out;
./wesnoth_okmaker < test/1.f.in > test/1.f.out;
./wesnoth_okmaker < test/1.g.in > test/1.g.out;
./wesnoth_okmaker < test/1.h.in > test/1.h.out;
./wesnoth_okmaker < test/1.i.in > test/1.i.out;
./wesnoth_okmaker < test/1.j.in > test/1.j.out;
./wesnoth_okmaker < test/2.a.in > test/2.a.out;
./wesnoth_okmaker < test/2.b.in > test/2.b.out;
./wesnoth_okmaker < test/2.c.in > test/2.c.out;
./wesnoth_okmaker < test/2.d.in > test/2.d.out;
./wesnoth_okmaker < test/2.e.in > test/2.e.out;
./wesnoth_okmaker < test/3.a.in > test/3.a.out;
./wesnoth_okmaker < test/3.b.in > test/3.b.out;
./wesnoth_okmaker < test/3.c.in > test/3.c.out;
./wesnoth_okmaker < test/3.d.in > test/3.d.out;
./wesnoth_okmaker < test/3.e.in > test/3.e.out;
./wesnoth_okmaker < test/3.f.in > test/3.f.out;
./wesnoth_okmaker < test/4.a.in > test/4.a.out;
./wesnoth_okmaker < test/4.b.in > test/4.b.out;
./wesnoth_okmaker < test/4.c.in > test/4.c.out;
./wesnoth_okmaker < test/4.d.in > test/4.d.out;
./wesnoth_okmaker < test/4.e.in > test/4.e.out;
./wesnoth_okmaker < test/4.f.in > test/4.f.out;
./wesnoth_okmaker < test/4.g.in > test/4.g.out;
./wesnoth_okmaker < test/4.h.in > test/4.h.out;
./wesnoth_okmaker < test/4.i.in > test/4.i.out;
./wesnoth_okmaker < test/4.j.in > test/4.j.out;
./wesnoth_okmaker < test/4.k.in > test/4.k.out;
./wesnoth_okmaker < test/4.l.in > test/4.l.out;
./wesnoth_okmaker < test/4.m.in > test/4.m.out;
./wesnoth_okmaker < test/4.n.in > test/4.n.out;
./wesnoth_okmaker < test/4.o.in > test/4.o.out;
./wesnoth_okmaker < test/4.p.in > test/4.p.out;
./wesnoth_okmaker < test/4.q.in > test/4.q.out;
./wesnoth_okmaker < test/4.r.in > test/4.r.out;
./wesnoth_okmaker < test/4.s.in > test/4.s.out;
./wesnoth_okmaker < test/4.t.in > test/4.t.out;
./wesnoth_okmaker < test/4.u.in > test/4.u.out;
./wesnoth_okmaker < test/4.v.in > test/4.v.out;
./wesnoth_okmaker < test/5.a.in > test/5.a.out;
./wesnoth_okmaker < test/5.b.in > test/5.b.out;
./wesnoth_okmaker < test/5.c.in > test/5.c.out;
./wesnoth_okmaker < test/5.d.in > test/5.d.out;
./wesnoth_okmaker < test/5.e.in > test/5.e.out;
./wesnoth_okmaker < test/5.f.in > test/5.f.out;
./wesnoth_okmaker < test/6.a.in > test/6.a.out;
./wesnoth_okmaker < test/6.b.in > test/6.b.out;
./wesnoth_okmaker < test/6.c.in > test/6.c.out;
./wesnoth_okmaker < test/6.d.in > test/6.d.out;
./wesnoth_okmaker < test/6.e.in > test/6.e.out;
./wesnoth_okmaker < test/6.f.in > test/6.f.out;

