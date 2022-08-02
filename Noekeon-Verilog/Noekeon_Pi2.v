// Moduł realizuje operację Pi2 algorytmu Noekeon

module NoekeonPi2(
	input wire	[127:0]	inData,
	output wire	[127:0]	outData
);

assign outData[31:0]		= inData[31:0];
assign outData[63:32]	= {inData[32],inData[63:33]};
assign outData[95:64]	= {inData[68:64],inData[95:69]};
assign outData[127:96]	= {inData[97:96],inData[127:98]};

endmodule
