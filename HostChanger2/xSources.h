vector<byte> xSources_key = {0x66,0xBC,0xE6,0xC6,0x0E,0x69,0x20,0xA0,0x61,0x9A,0xAF,0xF6,0x31,0xB7,0xA8,0x61,0xFE,0xD0,0x09,0x18,0xD3,0xC3,0x44,0xF2,0xEB,0xDD,0x43,0x7B,0x74,0xB4,0x12,0xAF};
vector<byte> xSources_iv = {0xBA,0xF3,0x6B,0xF7,0x46,0x00,0xE9,0x4F,0x25,0x34,0xB4,0x4A,0x44,0xC7,0xDC,0x5F};
vector<vector<byte>> xSources = {
	{0xDE,0x99,0x5D,0xFB,0xD2,0x9C,0x88,0x4B,0xCB,0x37,0x97,0x36,0xF5,0x3B,0x9B,0xA4},
	{0xC0,0x5C,0x9E,0xC7,0x28,0x3A,0xB9,0x3E,0xB6,0xB2,0xAD,0x37,0x96,0xBA,0x53,0x56},
	{0x2C,0x98,0x9E,0x6D,0x7C,0x79,0x37,0x8E,0x43,0x97,0xF8,0x2D,0x94,0x91,0x5F,0x38},
	{0xCA,0x78,0x88,0x10,0xD7,0xFF,0xB5,0x43,0x4C,0xA9,0xDF,0x54,0x11,0xF4,0x82,0x2D},
	{0xD7,0x31,0x6E,0xA6,0x8F,0x66,0xA7,0x62,0xF6,0x54,0x46,0xD0,0xA2,0xE9,0xC3,0x4A},
	{0x65,0x73,0x9A,0xCF,0xE1,0xBF,0xE4,0x56,0x0E,0x9B,0x73,0x51,0xD0,0x62,0xF2,0x58,0x80,0x90,0x93,0x89,0x39,0xE4,0xD0,0x12,0x74,0x23,0x40,0xF0,0xB0,0x88,0x20,0xBF},
	{0x15,0x2F,0xC8,0x8B,0x73,0x13,0x9B,0x2D,0xA6,0xAF,0xE9,0xDB,0xA0,0x82,0x77,0x21},
	{0x81,0x60,0xB7,0xAF,0x8C,0x13,0xD5,0x6D,0x1B,0x75,0x2C,0xC8,0xB3,0xD0,0xE4,0xEB},
	{0x09,0x02,0xBB,0x00,0x55,0xCA,0x9E,0x24,0x67,0x19,0x6B,0x69,0x72,0xED,0x81,0xB7,0x2C,0x60,0x92,0x49,0x4F,0x96,0x1B,0xB6,0x52,0xEA,0xEF,0x31,0x17,0xFF,0x07,0x94},
	{0x2E,0x3F,0xE0,0x85,0x6F,0x20,0x18,0x74,0x9C,0x5B,0x09,0x8E,0x0F,0x7E,0x98,0x98},
	{0x1C,0x18,0xF5,0x06,0x22,0xA5,0x2F,0x44,0xB6,0xC4,0xBB,0x3F,0x18,0x7B,0x39,0xF0,0xEA,0x4A,0x48,0x39,0x8D,0xF4,0x40,0x0C,0x27,0x8E,0xDC,0x22,0xFC,0xFB,0x93,0x43,0x77,0xC5,0xAB,0x03,0xAE,0x93,0xCD,0x62,0xB8,0xA1,0xEE,0x44,0xE1,0xDB,0x44,0x9F},
	{0x1C,0x18,0xF5,0x06,0x22,0xA5,0x2F,0x44,0xB6,0xC4,0xBB,0x3F,0x18,0x7B,0x39,0xF0,0x48,0x77,0xA5,0x7E,0x7D,0xEF,0x7E,0xDB,0x2D,0x81,0xA0,0x05,0xE7,0x46,0x51,0xFA,0x55,0xEA,0xDA,0x73,0x60,0x1F,0x37,0x4F,0x60,0xBC,0x28,0x24,0x7C,0xB5,0x04,0x4C},
	{0xA7,0xB9,0x47,0xA7,0x2C,0x2C,0x69,0x28,0xA5,0x55,0x96,0x76,0xD2,0x40,0x42,0xC6,0xD4,0x68,0xEB,0x10,0x26,0x0E,0x68,0x52,0x37,0xF7,0xB3,0x9C,0xEE,0xB5,0x94,0x89,0xFC,0x63,0x3E,0x82,0x87,0xC7,0xEE,0x60,0xE3,0xDD,0xE1,0xF1,0x92,0xBE,0x65,0x8F},
	{0xC5,0x7E,0x40,0xF6,0xF2,0x61,0xC6,0x3C,0x12,0xF2,0xB8,0xA2,0xA3,0xFB,0xB5,0x22},
	{0x8F,0x5B,0xBB,0x6C,0x24,0x3E,0x88,0x38,0xE5,0x20,0xDE,0x7F,0x76,0x64,0x11,0x2C},
	{0x79,0x44,0x11,0x97,0xDF,0x9E,0xFC,0xF6,0x14,0x7B,0xF2,0x27,0x42,0xFE,0x3B,0xFA},
	{0xAF,0x9E,0x85,0xA8,0x32,0xEA,0x08,0x29,0x2F,0xA9,0x94,0x6F,0xFF,0x88,0xE4,0x7B},
	{0x65,0x73,0x9A,0xCF,0xE1,0xBF,0xE4,0x56,0x0E,0x9B,0x73,0x51,0xD0,0x62,0xF2,0x58,0x1A,0x71,0x0C,0x5C,0x88,0x25,0x20,0x16,0xE5,0x14,0xC7,0x9F,0x12,0xFF,0x81,0x9F},
};
