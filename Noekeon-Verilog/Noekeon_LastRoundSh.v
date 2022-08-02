// Moduł realizuje funkcje rundy algorytmu Noekeon
// Jest to złożenie operacji Theta oraz XOR ze stałą rundową

module NoekeonLastRoundSh(
	input wire	[127:0]	inData,
	input wire	[127:0]	inKey,
	input wire	[7:0]		inRoundconst,
	input wire				inDecipher,		// 0 - szyfrowanie, 1- deszyfrowanie
	output wire	[127:0]	outData
);

wire	[127:0]	temp1;
wire	[127:0]	temp2;

assign temp1 = (inDecipher == 1'b1) ? inData: {inData[127:8],inData[7:0]^inRoundconst};
NoekeonTheta noekeon_theta(.inKey(inKey), .inData(temp1), .outData(temp2));
assign outData = (inDecipher == 1'b0) ? temp2: {temp2[127:8],temp2[7:0]^inRoundconst};

endmodule
