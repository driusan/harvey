ulong	strtoul(char*, char**, int);

#include "../port/portfns.h"

void	aamloop(int);
void	cgaputc(int);
void	cgaputs(char*, int);
int	cistrcmp(char*, char*);
int	cistrncmp(char*, char*, int);
void	(*coherence)(void);
void	etherinit(void);
void	etherstart(void);
int	floppyinit(void);
void	floppyproc(void);
long	floppyread(int, void*, long);
vlong	floppyseek(int, vlong);
long	floppywrite(int, void*, long);
void	fpinit(void);
char*	getconf(char*);
ulong	getcr0(void);
ulong	getcr2(void);
ulong	getcr4(void);
int	getfields(char*, char**, int, char);
ulong	getstatus(void);
int	atainit(void);
long	ataread(int, void*, long);
vlong	ataseek(int, vlong);
long	atawrite(int, void*, long);
void	i8042a20(void);
void	i8042reset(void);
void	idecheck(Device*);
int	inb(int);
void	insb(int, void*, int);
ushort	ins(int);
void	inss(int, void*, int);
ulong	inl(int);
void	insl(int, void*, int);
void	kbdinit(void);
int	kbdintr0(void);
int	kbdgetc(void);
long*	mapaddr(ulong);
void	microdelay(int);
void	mmuinit(void);
uchar	nvramread(int);
void	outb(int, int);
void	outsb(int, void*, int);
void	outs(int, ushort);
void	outss(int, void*, int);
void	outl(int, ulong);
void	outsl(int, void*, int);
void	printcpufreq(void);
void	putgdt(Segdesc*, int);
void	putidt(Segdesc*, int);
void	putcr3(ulong);
void	putcr4(ulong);
void	puttr(ulong);
void	rdmsr(int, vlong*);
void	rdtsc(uvlong*);
void	scsiinit(void);
long	scsiread(int, void*, long);
long	scsiseek(int, long);
long	scsiwrite(int, void*, long);
int	setatapart(int, char*);
int	setscsipart(int, char*);
void	setvec(int, void (*)(Ureg*, void*), void*);
int	tas(Lock*);
void	trapinit(void);
void	uartspecial(int, void (*)(int), int (*)(void), int);
int	uartgetc(void);
void	uartputc(int);
void	wbflush(void);
void	cpuid(char*, int*, int*);
#define PADDR(a)	((ulong)(a)&~KZERO)

void	ideinit(Device *d);
int	ideread(Device *d, long,  void*);
int idewrite(Device *d, long, void*);
long	atasize(Device *d);
void	atainitstub(Device *d);
