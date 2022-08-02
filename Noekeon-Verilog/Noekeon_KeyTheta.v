// Moudł realizuje operację Theta na kluczu jeśli wykonywana jest operacja deszyfrowania, w przeciwnym wypadku nic nie robi.
// Ten moduł jest modułem kombinacyjnym

module NoekeonKeyTheta(
	input wire	[127:0]	inKey,
	input wire				inDecipher, // 0 - szyfrowanie, 1 - deszyfrowanie
	output wire	[127:0]	outKey
);

wire	[127:0]	outTheta;

NoekeonTheta noekeon_Theta(
		.inData(inKey),
		.inKey(128'h0),
		.outData(outTheta)
);

assign outKey = (inDecipher == 1'b1) ? outTheta : inKey;

endmodule
