.name "World Trade Center"
.comment "Be my plane"

		sti r1, %:lv, %1
		sti r1, %:b_live, %1
lv:		live %1
		ld %-32, r4
		fork %:right

left:	fork %:l_2

l_1:	ld %0, r3
		ldi %:build, r3, r2
		and r1, %0, r1
		zjmp %:build		

l_2:	ld %4, r3
		ldi %:build, r3, r2
		and r1, %0, r1
		zjmp %:build		

right:	fork %:r_2

r_1:	ld %8, r3
		ldi %:build, r3, r2
		and r1, %0, r1
		zjmp %:build		

r_2:	ld %12, r3
		ldi %:build, r3, r2
		and r1, %0, r1
		zjmp %:build		

build:	sti r2, r3, r4
b_live:	live %0
		zjmp %-42
