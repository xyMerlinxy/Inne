// Moduł pamiętający stan wyjściowy danych z modułu ostatniej rundy

module NoekeonDataOutReg(
	input wire 				inClk,
	input wire				inReset,
	
	input wire	[127:0]	inData,
	input wire				inWr,
	
	output wire [127:0]	outData
);

reg [127:0]		DataOutReg = 128'b0;

always @(posedge(inClk) or posedge(inReset))
begin
	if(inReset == 1'b1) begin
		DataOutReg = 128'b0;
	end else begin
		if(inWr == 1'b1) begin
			DataOutReg = inData;
		end
	end
end

assign outData = DataOutReg;

endmodule
