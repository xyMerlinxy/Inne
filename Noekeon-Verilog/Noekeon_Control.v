// Moduł sprawuje rolę zarządzającą pracą pozostałych modułów wchodzących w skład modulu Noekeon
// Jest oparty o maszynę stanów

// W trakcie wprowadzania klucza należy ustawić inMode
// W trakcie wprowadzania danych należy ustawić inDecipher

module NoekeonControl(
	input wire				inClk,
	input wire				inReset,
	input wire				inMode,			// 0 - directed key, 1 - in-directed key
	input wire				inDecipher,		//w stanie wysoki moduł będzie realizował deszyfrowanie, w stanie nisk będzie realizował szyfrowanie 
	input wire				inDataWr,
	input wire				inKeyWr,
	output wire				outBusy,

	// zarządzanie rejestrem klucza
	output wire				outKeyWrCipher,	// zapis klucza z DataOutReg
	output wire				outKeyWrExt,		// zapis klucza z zewnętrznego źródła
	
	// zarzadzanie rejestrem danych
	output wire				outDataWrKey,		// zapis danych z klucza
	output wire				outDataWrExt,		// zapis danych z zewnętrzengo źródła
	output wire 			outDatawrInt,		// zapis danych z modułu realizującego funkcję rundy
	
	output wire	[4:0]		outRoundNumber,	// licznik rundy
	
	output wire				outRegOutDataWr,	// zapis danych z ostaniej rundy na rejestr wyjściowy

	output wire				outIntDecipher,
	output wire				outResetKey			// służy do resetowania rejestru klucza

);

// Stany:
// 0 - oczekiwanie
// 1 - szyfrowanie
// 2 - ostania runda szyfrowania klucza
// 3 - ostatnia runda szyfrowania wiadomości
// 4 - deszyfrowanie
// 5 - ostania runda deszyfrowania

reg	[4:0]		regRoundNum; 
reg	[2:0]		regState = 3'd0;
reg				regMode = 1'd0;
reg				regDecipher = 1'd0;

always @(posedge(inClk) or posedge(inReset)) begin
	if(inReset == 1'b1) begin
		regRoundNum = 5'b0; 
		regState = 3'd0;
		regMode = 1'd0;
		regDecipher = 1'd0;
	end else begin
		case(regState)
			3'd0 :	begin
							// indirected key
							if((inKeyWr == 1'b1) & (inMode == 1'b1)) begin
								regState = 3'd1;
								regRoundNum = 5'b0;
								regDecipher = 1'b0;
								regMode = 1'b1;
							end else begin
								if(inDataWr == 1'b1) begin
									regMode = 1'b0;
									// szyfrowanie
									if(inDecipher == 1'b0) begin
										regState = 3'd1;
										regDecipher = 1'b0;
										regRoundNum = 5'b0;
									// deszyfrowanie
									end else begin
										regState = 3'd4;
										regDecipher = 1'b1;
										regRoundNum = 5'd16;
									end
								end
							end
						end
						
			3'd1 :	begin
							if(regRoundNum < 5'd15) begin
								regRoundNum = regRoundNum + 5'd1;
							end else begin
								if(regMode == 1'b1) begin
									regState = 3'd2;
									regRoundNum = regRoundNum + 5'd1;
								end else begin
									regState = 3'd3;
									regRoundNum = regRoundNum + 5'd1;
								end
								
							end
						end
			3'd2 :	begin
							regState = 3'd0;
						end
			3'd3 :	begin
							regState = 3'd0;
						end
			3'd4 :	begin
							if(regRoundNum > 5'd1) begin
								regRoundNum = regRoundNum - 5'd1;
							end else begin
								regState = 3'd5;
								regRoundNum = regRoundNum - 5'd1;
							end
						end
			3'd5 :	begin
							regState = 3'd0;
						end
		endcase
	end
end

assign outRoundNumber = regRoundNum;

// wpisanie klucza do rejestru klucza
assign outKeyWrExt = ((regState == 3'd0) & (inKeyWr==1'b1) & (inMode==1'b0)) ? 1'b1 : 1'b0;

// wpisanie klucza do rejestru danych
assign outDataWrKey = ((regState == 3'd0) & (inKeyWr==1'b1) & (inMode==1'b1)) ? 1'b1 : 1'b0;

// zapisanie klucza z DataOutReg
assign outKeyWrCipher = (regState == 3'd2) ? 1'b1 : 1'b0;


// zapis danych na wyjście
assign outRegOutDataWr = ((regState == 3'd3) | (regState == 3'd5)) ? 1'b1 : 1'b0;

// zapis danych do reg Data w trakcie szyfrowania
assign outDatawrInt = ((regState == 3'd1) | (regState == 3'd4)) ? 1'b1 : 1'b0;

assign outIntDecipher = regDecipher;

assign outDataWrExt = ((regState == 3'd0) & (inDataWr==1'b1)) ? 1'b1 : 1'b0;

assign outBusy = (regState == 3'd0) ? 1'b0 : 1'b1;

assign outResetKey = ((inReset == 1'b1) | ((regState == 3'd0) & (inKeyWr == 1'b1) & (inMode == 1'b1))) ? 1'b1 : 1'b0;

endmodule
