#define RANDOM_MAX 8191
#define CENTER 4096

#define SLEEP(cycles, label)\
	mov a, cycles $\
	label: $\
	dec a $\
	test a $\
	jnz label $\

loop:

int 0
and a, RANDOM_MAX
mov b, a
sub b, CENTER

int 0
and a, RANDOM_MAX
sub a, CENTER

int 1

SLEEP(100000, dolme)

jmp loop
