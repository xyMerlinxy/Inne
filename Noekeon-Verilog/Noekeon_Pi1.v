// Moduł realizuje operację Pi1 algorytmu Noekeon

module NoekeonPi1(
	input wire	[127:0]	inData,
	output wire	[127:0]	outData
);

assign outData[31:0]		= inData[31:0];
assign outData[63:32]	= {inData[62:32],inData[63]};
assign outData[95:64]	= {inData[90:64],inData[95:91]};
assign outData[127:96]	= {inData[125:96],inData[127:126]};

endmodule
