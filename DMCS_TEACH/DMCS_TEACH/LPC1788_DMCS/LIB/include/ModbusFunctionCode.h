
struct ModBus_FCode_01{
	unsigned char	Address;
	unsigned char	FunctionCode;
	unsigned short	RegBegin;
	unsigned short	RegCount;
	unsigned short	CrcVal;
};

struct ModBus_FCode_03{
	unsigned char	Address;
	unsigned char	FunctionCode;
	unsigned short	RegBegin;
	unsigned short	RegCount;
	unsigned short	CrcVal;
};

struct ModBus_FBCode_03{
	unsigned char	Address;
	unsigned char	FunctionCode;
	unsigned short	ByteCount;
	unsigned char	Value[247];
};

struct ModBus_FCode_05{
	unsigned char	Address;
	unsigned char	FunctionCode;
	unsigned short	BitBegin;
	unsigned short	BitValue;
	unsigned short	CrcVal;
};

struct ModBus_FCode_06{
	unsigned char	Address;
	unsigned char	FunctionCode;
	unsigned short	BitBegin;
	unsigned short	BitValue;
	unsigned short	CrcVal;
};

struct ModBus_FCode_10{
	unsigned char	Address;
	unsigned char	FunctionCode;
	unsigned short	RegBegin;
	unsigned short	RegCount;
	unsigned char	ByteCount;
	unsigned char	Value[247];
};
struct ModBus_FBCode_10{
	unsigned char	Address;
	unsigned char	FunctionCode;
	unsigned short	RegBegin;
	unsigned short	RegCount;
};

union ModBus_FCode{
 	 struct ModBus_FCode_01	F01;
 	 struct ModBus_FCode_03	F03;
 	 struct ModBus_FCode_05	F05;
 	 struct ModBus_FCode_05	F06;
 	 struct ModBus_FCode_10	F10;
};

union ModBus_FBCode{
	struct ModBus_FBCode_03	F03;
	struct ModBus_FBCode_10	F10;
};
