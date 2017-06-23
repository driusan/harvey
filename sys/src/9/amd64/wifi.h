typedef struct Wkey Wkey;
typedef struct Wnode Wnode;
typedef struct Wifi Wifi;
typedef struct Wifipkt Wifipkt;

enum {
	Essidlen = 32,
};

/* cipher */
enum {
	TKIP	= 1,
	CCMP	= 2,
};

struct Wkey
{
	int		cipher;
	int		len;
	uint64_t		tsc;
	unsigned char		key[];
};

struct Wnode
{
	unsigned char	bssid[Eaddrlen];
	char	ssid[Essidlen+2];

	char	*status;

	int	rsnelen;
	unsigned char	rsne[258];
	Wkey	*txkey[1];
	Wkey	*rxkey[5];

	int	aid;		/* association id */
	uint32_t	lastsend;
	uint32_t	lastseen;

	unsigned char	*minrate;	/* pointers into wifi->rates */
	unsigned char	*maxrate;
	unsigned char	*actrate;

	uint32_t	txcount;	/* statistics for rate adaption */
	uint32_t	txerror;

	/* stuff from beacon */
	int	ival;
	int	cap;
	int	channel;
	int	brsnelen;
	unsigned char	brsne[258];
};

struct Wifi
{
	Ether	*ether;

	int	debug;

	RWlock	crypt;
	Queue	*iq;
	uint32_t	watchdog;
	uint32_t	lastauth;
	Ref	txseq;
	void	(*transmit)(Wifi*, Wnode*, Block*);

	/* for searching */
	unsigned char	bssid[Eaddrlen];
	char	essid[Essidlen+2];

	/* supported data rates by hardware */
	unsigned char	*rates;

	/* effective base station */
	Wnode	*bss;

	Wnode	node[32];
};

struct Wifipkt
{
	unsigned char	fc[2];
	unsigned char	dur[2];
	unsigned char	a1[Eaddrlen];
	unsigned char	a2[Eaddrlen];
	unsigned char	a3[Eaddrlen];
	unsigned char	seq[2];
	unsigned char	a4[Eaddrlen];
};

Wifi *wifiattach(Ether *ether, void (*transmit)(Wifi*, Wnode*, Block*));
void wifiiq(Wifi*, Block*);
int wifihdrlen(Wifipkt*);
void wifitxfail(Wifi*, Block*);

long wifistat(Wifi*, void*, long, uint32_t);
long wifictl(Wifi*, void*, long);
void wificfg(Wifi*, char*);
