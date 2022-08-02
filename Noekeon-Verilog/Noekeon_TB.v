module NoekeonTb;

reg	[7:0]	TEST = 8'b0;
integer i;
/////////////////////////////////////////

parameter   inClkp = 10;
reg         inClk  = 1'b0;

always
begin
    #(inClkp/2) inClk = !inClk;
end

/////////////////////////////////////////
reg		regReset = 1'b0;
reg		regMode = 1'b0;
reg		regDecipher = 1'b0;

reg		inDataWr	= 1'b0;
reg	[127:0]	inDataData	= 128'b0;
reg		inKeyWr		= 1'b0;
reg	[127:0]	inKeyData	= 128'b0;

wire 	[127:0]	outDataData;
wire		outBusy;

Noekeon neokeon(
	.inClk(inClk),
	.inReset(regReset),
	.inMode(regMode),
	.inDecipher(regDecipher),
	.inDataWr(inDataWr),
	.inDataData(inDataData),
	.inKeyWr(inKeyWr),
	.inKeyData(inKeyData),
	.outBusy(outBusy),
	.outData(outDataData)
);

always
begin

// directed mode
    TEST = TEST + 1;
    regMode = 1'b0; regDecipher = 1'b0;
    inKeyWr = 1'b0; inKeyData = 128'b0;
    inDataWr = 1'b0; inDataData = 128'b0; #(inClkp);
    inKeyWr = 1'b1; inKeyData = 128'b0; #(inClkp);
    inKeyWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
    inDataWr = 1'b1; inDataData = 128'b0; #(inClkp);
    inDataWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
	
    if (outDataData != 128'h503D2DFC24B70148699E29FAB1656851) begin
        $display("TEST: %3d BLAD\n", TEST);
        $stop;
    end else begin
        $display("TEST: %3d SZYFRACJA OK", TEST);
        $display("Wynik: %h", outDataData);
    end 

    TEST = TEST + 1;
    regMode = 1'b0; regDecipher = 1'b1;
    inKeyWr = 1'b0; inKeyData = 128'b0;
    inDataWr = 1'b0; inDataData = 128'b0; #(inClkp);
    inKeyWr = 1'b1; inKeyData = 128'b0; #(inClkp);
    inKeyWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
    inDataWr = 1'b1; inDataData = outDataData; #(inClkp);
    inDataWr = 1'b0;
    
    wait(outBusy == 1'b0 && inClk == 1'b0);
	
    if (outDataData != 128'h0) begin
        $display("TEST: %3d BLAD\n", TEST);
        $stop;
    end else begin
        $display("TEST: %3d DESZYFRACJA OK", TEST);
        $display("Wynik: %h", outDataData);
    end 
    

// indirected mode
    TEST = TEST + 1;
    regMode = 1'b1; regDecipher = 1'b0;
    inKeyWr = 1'b0; inKeyData = 128'b0;
    inDataWr = 1'b0; inDataData = 128'b0; #(inClkp);
    inKeyWr = 1'b1; inKeyData = 128'b0; #(inClkp);
    inKeyWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
    inDataWr = 1'b1; inDataData = 128'b0; #(inClkp);
    inDataWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
	
    if (outDataData != 128'hF678178B99A99F089299C716BA693381) begin
        $display("TEST: %3d BLAD\n", TEST);
        $stop;
    end else begin
        $display("TEST: %3d SZYFRACJA INDIRECTED OK", TEST);
        $display("Wynik: %h", outDataData);
    end 

    TEST = TEST + 1;
    regMode = 1'b1; regDecipher = 1'b1;
    inKeyWr = 1'b0; inKeyData = 128'b0;
    inDataWr = 1'b0; inDataData = 128'b0; #(inClkp);
    inKeyWr = 1'b1; inKeyData = 128'b0; #(inClkp);
    inKeyWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
    inDataWr = 1'b1; inDataData = outDataData; #(inClkp);
    inDataWr = 1'b0;
    
    wait(outBusy == 1'b0 && inClk == 1'b0);
	
    if (outDataData != 128'h0) begin
        $display("TEST: %3d BLAD\n", TEST);
        $stop;
    end else begin
        $display("TEST: %3d DESZYFRACJA INDIRECTED OK", TEST);
        $display("Wynik: %h", outDataData);
    end 

// resetTest - szyfrowanie po resecie powinno wykonać się poprawnie
	TEST = TEST + 1;
    regMode = 1'b1; regDecipher = 1'b0;
    inKeyWr = 1'b0; inKeyData = 128'b0;
    inDataWr = 1'b0; inDataData = 128'b0; #(inClkp);
    inKeyWr = 1'b1; inKeyData = 128'b0; #(inClkp);
    inKeyWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
    inDataWr = 1'b1; inDataData = 128'b0; #(inClkp);
    inDataWr = 1'b0;
	#(inClkp);#(inClkp);#(inClkp);#(inClkp);
	regReset = 1'b1;#(inClkp)
	regReset = 1'b0;#(inClkp)
	
	regMode = 1'b1; regDecipher = 1'b0;
    inKeyWr = 1'b0; inKeyData = 128'b0;
    inDataWr = 1'b0; inDataData = 128'b0; #(inClkp);
    inKeyWr = 1'b1; inKeyData = 128'b0; #(inClkp);
    inKeyWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
    inDataWr = 1'b1; inDataData = 128'b0; #(inClkp);
    inDataWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
	
    if (outDataData != 128'hF678178B99A99F089299C716BA693381) begin
        $display("TEST: %3d BLAD\n", TEST);
        $stop;
    end else begin
        $display("TEST: %3d Reset test OK", TEST);
        $display("Wynik: %h", outDataData);
    end 
	 
// indirected bez wpisywania klucza ponownie
    TEST = TEST + 1;
    regMode = 1'b1; regDecipher = 1'b0;
    inKeyWr = 1'b0; inKeyData = 128'b0;
    inDataWr = 1'b0; inDataData = 128'b0; #(inClkp);
    inKeyWr = 1'b1; inKeyData = 128'hF678178B99A99F089299C716BA693381; #(inClkp);
    inKeyWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
    inDataWr = 1'b1; inDataData = 128'h5011C7D8DF7B6FAA283C1F7B52F88A7B; #(inClkp);
    inDataWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
	
    if (outDataData != 128'hC277FA70D9495515C82AE6E25096F2BF) begin
        $display("TEST: %3d BLAD\n", TEST);
        $stop;
    end else begin
        $display("TEST: %3d SZYFRACJA INDIRECTED v2 OK", TEST);
        $display("Wynik: %h", outDataData);
    end 

    TEST = TEST + 1;
    regMode = 1'b1; regDecipher = 1'b1;
    inKeyWr = 1'b0; inKeyData = 128'b0;
    inDataWr = 1'b0; inDataData = 128'b0; #(inClkp);

    inDataWr = 1'b1; inDataData = outDataData; #(inClkp);
    inDataWr = 1'b0;
    
    wait(outBusy == 1'b0 && inClk == 1'b0);
	
    if (outDataData != 128'h5011C7D8DF7B6FAA283C1F7B52F88A7B) begin
        $display("TEST: %3d BLAD\n", TEST);
        $stop;
    end else begin
        $display("TEST: %3d DESZYFRACJA INDIRECTED TEN SAM KLUCZ OK", TEST);
        $display("Wynik: %h", outDataData);
    end
	 
	 
// 10 krotny test

    TEST = TEST + 1;
    regMode = 1'b1; regDecipher = 1'b0;
    inKeyWr = 1'b0; inKeyData = 128'b0;
    inDataWr = 1'b0; inDataData = 128'b0; #(inClkp);
    inKeyWr = 1'b1; inKeyData = 128'hF678178B99A99F089299C716BA693381; #(inClkp);
    inKeyWr = 1'b0;
    wait(outBusy == 1'b0 && inClk == 1'b0);
    inDataWr = 1'b1; inDataData = outDataData; #(inClkp);
    inDataWr = 1'b0;
    
    wait(outBusy == 1'b0 && inClk == 1'b0);	 
	 
    $stop;
end

endmodule
