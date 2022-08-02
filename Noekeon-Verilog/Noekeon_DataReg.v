// Moduł pamięciowy przechowujący dane
// Pozwala na wpisanie danych z interfejsu zewnętrznego, z wyjścia funkcji rundy oraz zapis klucza jako danych

module NoekeonDataReg(
	input wire				inClk,
	input wire				inReset,
	
	input wire				inDataWrKey,		// zapis klucza jako danych
	input wire	[127:0]	inDataDataKey,
	
	input wire				inDataWrExt,		// zapis danych z zewnętrzengo interfejsu
	input wire	[127:0]	inDataDataExt,
	
	input wire	 			inDatawrInt,		// zapis danych z modułu realizującego funkcję rundy
	input wire	[127:0]	inDataDataInt,
	
	output wire	[127:0]	outData
);

reg [127:0]		DataReg = 128'b0;

always @(posedge(inClk) or posedge(inReset))
begin
	if(inReset == 1'b1) begin
		DataReg = 128'b0;
	end else begin
		if(inDataWrKey == 1'b1) begin
			DataReg = inDataDataKey;
		end else begin
			if (inDataWrExt == 1'b1) begin
				DataReg = inDataDataExt;
			end else begin
				if (inDatawrInt == 1'b1) begin
					DataReg = inDataDataInt;
				end
			end
		end
	end
end

assign outData = DataReg;

endmodule
