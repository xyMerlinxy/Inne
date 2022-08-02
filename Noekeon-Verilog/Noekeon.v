// Moduł realizujący szyfr Noekeon
// Spaja on wszystkie pozostałe moduły projektu

module Noekeon(
	input wire				inClk,
	input wire				inReset,
	input wire				inMode,			// 0 - directed key, 1 - in-directed key
	input wire				inDecipher,		// 0 - szyfrowanie, 1 deszyfrowanie
	input wire				inDataWr,
	input wire	[127:0]	inDataData,
	input wire				inKeyWr,
	input wire	[127:0]	inKeyData,
	output wire				outBusy,
	output wire	[127:0]	outData
);

wire			controlOutKeyWrCipher;	// zapis klucza z DataOutReg
wire			controlOutKeyWrExt;		// zapis klucza z zewnętrznego źródła
wire			controlOutDataWrKey;		// zapis danych z klucza
wire			controlOutDataWrExt;		// zapis danych z zewnętrzengo źródła
wire			controlOutDatawrInt;		// zapis danych z modułu realizującego funkcję rundy

wire			controlOutRegOutDataWr;	// zapis danych z ostaniej rundy na rejestr wyjściowy

wire			controlOutResetKey;		// służy do resetowania rejestru klucza

// klucz
wire				controlOutIntDecipher;
wire	[127:0]	keyBeforeTheta;
wire	[127:0]	keyAfterTheta;

wire	[4:0]		controlOutRoundNumber;  // licznik rundy
wire	[7:0]		roundConstant;

// Dane
wire	[127:0]	regDataData;
wire	[127:0]	LastRoundData;
wire	[127:0]	RoundData;

// Control
NoekeonControl noekeon_Control(
	.inClk(inClk),
	.inReset(inReset),
	.inMode(inMode),
	.inDecipher(inDecipher),
	.inDataWr(inDataWr),
	.inKeyWr(inKeyWr),
	.outBusy(outBusy),
	.outKeyWrCipher(controlOutKeyWrCipher),	
	.outKeyWrExt(controlOutKeyWrExt),		
	.outDataWrKey(controlOutDataWrKey),
	.outDataWrExt(controlOutDataWrExt),
	.outDatawrInt(controlOutDatawrInt),
	.outRoundNumber(controlOutRoundNumber),
	.outRegOutDataWr(controlOutRegOutDataWr),
	.outIntDecipher(controlOutIntDecipher),
	.outResetKey(controlOutResetKey)
);

// KeyReg
NoekeonKeyReg noekeon_KeyReg(
 	.inClk(inClk),
 	.inReset(controlOutResetKey),
 	.inKeyWrExt(controlOutKeyWrExt),
 	.inKeyDataExt(inKeyData),
  	.inKeywrInt(controlOutKeyWrCipher),
 	.inKeyDataInt(LastRoundData),
 	.outKey(keyBeforeTheta)
);

// DataReg
NoekeonDataReg noekeon_DataReg(
 	.inClk(inClk),
 	.inReset(inReset),
 	.inDataWrKey(controlOutDataWrKey),
 	.inDataDataKey(inKeyData),
 	.inDataWrExt(controlOutDataWrExt),
 	.inDataDataExt(inDataData),
  	.inDatawrInt(controlOutDatawrInt),
 	.inDataDataInt(RoundData),
 	.outData(regDataData)
);

// RoundSH
NoekeonRoundSh noekeon_RoundSh(
 	.inData(regDataData),
 	.inKey(keyAfterTheta),
 	.inRoundconst(roundConstant),
 	.inDecipher(controlOutIntDecipher),
 	.outData(RoundData)
);

// LastRoundSh
NoekeonLastRoundSh noekeon_LastRoundSh(
 	.inData(regDataData),
 	.inKey(keyAfterTheta),
 	.inRoundconst(roundConstant),
 	.inDecipher(controlOutIntDecipher),
 	.outData(LastRoundData)
);

// DataOutReg
NoekeonDataOutReg noekeon_DataOutReg(
	.inClk(inClk),
 	.inReset(inReset),
 	.inData(LastRoundData),
 	.inWr(controlOutRegOutDataWr),
	.outData(outData)
);

// ConstatnBox
NoekeonConstatBox noekeon_ConstatBox(
 	.inRoundNum(controlOutRoundNumber),
	.outRoundConst(roundConstant)
);

// KeyTheta
NoekeonKeyTheta noekeon_KeyTheta(
 	.inKey(keyBeforeTheta),
 	.inDecipher(controlOutIntDecipher),
 	.outKey(keyAfterTheta)
);

endmodule
