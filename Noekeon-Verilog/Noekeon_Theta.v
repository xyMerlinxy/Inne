// Moduł realizuje operację Theta algorytmu Noekeon
// Jest to moduł kombinacyjny

module NoekeonTheta(
	input wire	[127:0]	inData,
	input wire	[127:0]	inKey,
	output wire	[127:0]	outData
);

assign outData[007:000] = inKey[007:000] ^ inData[039:032] ^ inKey[039:032] ^ inData[103:096] ^ inKey[103:096] ^ inData[047:040] ^ inKey[047:040] ^ inData[111:104] ^ inKey[111:104] ^ inData[063:056] ^ inKey[063:056] ^ inData[127:120] ^ inData[007:000] ^ inKey[127:120];
assign outData[015:008] = inKey[015:008] ^ inData[047:040] ^ inKey[047:040] ^ inData[111:104] ^ inKey[111:104] ^ inData[055:048] ^ inKey[055:048] ^ inData[119:112] ^ inKey[119:112] ^ inData[039:032] ^ inKey[039:032] ^ inData[103:096] ^ inData[015:008] ^ inKey[103:096];
assign outData[023:016] = inKey[023:016] ^ inData[055:048] ^ inKey[055:048] ^ inData[119:112] ^ inKey[119:112] ^ inData[063:056] ^ inKey[063:056] ^ inData[127:120] ^ inKey[127:120] ^ inData[047:040] ^ inKey[047:040] ^ inData[111:104] ^ inData[023:016] ^ inKey[111:104];
assign outData[031:024] = inKey[031:024] ^ inData[063:056] ^ inKey[063:056] ^ inData[127:120] ^ inKey[127:120] ^ inData[039:032] ^ inKey[039:032] ^ inData[103:096] ^ inKey[103:096] ^ inData[055:048] ^ inKey[055:048] ^ inData[119:112] ^ inData[031:024] ^ inKey[119:112];
assign outData[039:032] = inData[039:032] ^ inData[007:000] ^ inData[071:064] ^ inData[015:008] ^ inData[079:072] ^ inData[031:024] ^ inData[095:088] ^ inKey[039:032];
assign outData[047:040] = inData[047:040] ^ inData[015:008] ^ inData[079:072] ^ inData[023:016] ^ inData[087:080] ^ inData[007:000] ^ inData[071:064] ^ inKey[047:040];
assign outData[055:048] = inData[055:048] ^ inData[023:016] ^ inData[087:080] ^ inData[031:024] ^ inData[095:088] ^ inData[015:008] ^ inData[079:072] ^ inKey[055:048];
assign outData[063:056] = inData[063:056] ^ inData[031:024] ^ inData[095:088] ^ inData[007:000] ^ inData[071:064] ^ inData[023:016] ^ inData[087:080] ^ inKey[063:056];
assign outData[071:064] = inKey[071:064] ^ inData[039:032] ^ inKey[039:032] ^ inData[103:096] ^ inKey[103:096] ^ inData[047:040] ^ inKey[047:040] ^ inData[111:104] ^ inKey[111:104] ^ inData[063:056] ^ inKey[063:056] ^ inData[127:120] ^ inData[071:064] ^ inKey[127:120];
assign outData[079:072] = inKey[079:072] ^ inData[047:040] ^ inKey[047:040] ^ inData[111:104] ^ inKey[111:104] ^ inData[055:048] ^ inKey[055:048] ^ inData[119:112] ^ inKey[119:112] ^ inData[039:032] ^ inKey[039:032] ^ inData[103:096] ^ inData[079:072] ^ inKey[103:096];
assign outData[087:080] = inKey[087:080] ^ inData[055:048] ^ inKey[055:048] ^ inData[119:112] ^ inKey[119:112] ^ inData[063:056] ^ inKey[063:056] ^ inData[127:120] ^ inKey[127:120] ^ inData[047:040] ^ inKey[047:040] ^ inData[111:104] ^ inData[087:080] ^ inKey[111:104];
assign outData[095:088] = inKey[095:088] ^ inData[063:056] ^ inKey[063:056] ^ inData[127:120] ^ inKey[127:120] ^ inData[039:032] ^ inKey[039:032] ^ inData[103:096] ^ inKey[103:096] ^ inData[055:048] ^ inKey[055:048] ^ inData[119:112] ^ inData[095:088] ^ inKey[119:112];
assign outData[103:096] = inData[103:096] ^ inData[007:000] ^ inData[071:064] ^ inData[015:008] ^ inData[079:072] ^ inData[031:024] ^ inData[095:088] ^ inKey[103:096];
assign outData[111:104] = inData[111:104] ^ inData[015:008] ^ inData[079:072] ^ inData[023:016] ^ inData[087:080] ^ inData[007:000] ^ inData[071:064] ^ inKey[111:104];
assign outData[119:112] = inData[119:112] ^ inData[023:016] ^ inData[087:080] ^ inData[031:024] ^ inData[095:088] ^ inData[015:008] ^ inData[079:072] ^ inKey[119:112];
assign outData[127:120] = inData[127:120] ^ inData[031:024] ^ inData[095:088] ^ inData[007:000] ^ inData[071:064] ^ inData[023:016] ^ inData[087:080] ^ inKey[127:120];

endmodule
