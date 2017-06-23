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
	uint8_t		key[];
};

struct Wnode
{
	uint8_t	bssid[Eaddrlen];
	char	ssid[Essidlen+2];

	char	*status;

	int	rsnelen;
	uint8_t	rsne[258];
	Wkey	*txkey[1];
	Wkey	*rxkey[5];

	int	aid;		/* association id */
	uint32_t	lastsend;
	uint32_t	lastseen;

	uint8_t	*minrate;	/* pointers into wifi->rates */
	uint8_t	*maxrate;
	uint8_t	*actrate;

	uint32_t	txcount;	/* statistics for rate adaption */
	uint32_t	txerror;

	/* stuff from beacon */
	int	ival;
	int	cap;
	int	channel;
	int	brsnelen;
	uint8_t	brsne[258];
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
	uint8_t	bssid[Eaddrlen];
	char	essid[Essidlen+2];

	/* supported data rates by hardware */
	uint8_t	*rates;

	/* effective base station */
	Wnode	*bss;

	Wnode	node[32];
};

struct Wifipkt
{
	uint8_t	fc[2];
	uint8_t	dur[2];
	uint8_t	a1[Eaddrlen];
	uint8_t	a2[Eaddrlen];
	uint8_t	a3[Eaddrlen];
	uint8_t	seq[2];
	uint8_t	a4[Eaddrlen];
};

Wifi *wifiattach(Ether *ether, void (*transmit)(Wifi*, Wnode*, Block*));
void wifiiq(Wifi*, Block*);
int wifihdrlen(Wifipkt*);
void wifitxfail(Wifi*, Block*);

long wifistat(Wifi*, void*, long, uint32_t);
long wifictl(Wifi*, void*, long);
void wificfg(Wifi*, char*);
