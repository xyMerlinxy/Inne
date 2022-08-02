// Moduł pamięciowy przechowujący klucz
// Pozwala na wpisanie klucza z interfejsu zewnętrznego oraz wyjścia szyfrowanych danych

module NoekeonKeyReg(
	input wire				inClk,
	input wire				inReset,
	
	input wire				inKeyWrExt,		// zapis klucza z interfejsu zewnętrznego
	input wire	[127:0]	inKeyDataExt,
	
	input wire	 			inKeywrInt,		// zapis danych z modułu realizującego funkcję ostatniej rundy
	input wire	[127:0]	inKeyDataInt,
	
	output wire	[127:0]	outKey
);


reg [127:0]		KeyReg = 128'd0;

always @(posedge(inClk) or posedge(inReset))
begin
	if(inReset == 1'b1) begin
		KeyReg = 128'b0;
	end else begin
		if(inKeyWrExt == 1'b1) begin
			KeyReg = inKeyDataExt;
		end else begin
			if (inKeywrInt == 1'b1) begin
				KeyReg = inKeyDataInt;
			end
		end
	end
end

assign outKey = KeyReg;

endmodule
