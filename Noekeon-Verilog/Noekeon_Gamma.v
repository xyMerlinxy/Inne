// Moduł realizujący opearcję Gamma

module NoekeonGamma(
	input wire	[127:0]	inData,
	output wire	[127:0]	outData
);

NoekeonGammaSbox sbox00(.inData({inData[096], inData[064], inData[032], inData[000]}), .outData({outData[096], outData[064], outData[032], outData[000]}));
NoekeonGammaSbox sbox01(.inData({inData[097], inData[065], inData[033], inData[001]}), .outData({outData[097], outData[065], outData[033], outData[001]}));
NoekeonGammaSbox sbox02(.inData({inData[098], inData[066], inData[034], inData[002]}), .outData({outData[098], outData[066], outData[034], outData[002]}));
NoekeonGammaSbox sbox03(.inData({inData[099], inData[067], inData[035], inData[003]}), .outData({outData[099], outData[067], outData[035], outData[003]}));
NoekeonGammaSbox sbox04(.inData({inData[100], inData[068], inData[036], inData[004]}), .outData({outData[100], outData[068], outData[036], outData[004]}));
NoekeonGammaSbox sbox05(.inData({inData[101], inData[069], inData[037], inData[005]}), .outData({outData[101], outData[069], outData[037], outData[005]}));
NoekeonGammaSbox sbox06(.inData({inData[102], inData[070], inData[038], inData[006]}), .outData({outData[102], outData[070], outData[038], outData[006]}));
NoekeonGammaSbox sbox07(.inData({inData[103], inData[071], inData[039], inData[007]}), .outData({outData[103], outData[071], outData[039], outData[007]}));
NoekeonGammaSbox sbox08(.inData({inData[104], inData[072], inData[040], inData[008]}), .outData({outData[104], outData[072], outData[040], outData[008]}));
NoekeonGammaSbox sbox09(.inData({inData[105], inData[073], inData[041], inData[009]}), .outData({outData[105], outData[073], outData[041], outData[009]}));
NoekeonGammaSbox sbox10(.inData({inData[106], inData[074], inData[042], inData[010]}), .outData({outData[106], outData[074], outData[042], outData[010]}));
NoekeonGammaSbox sbox11(.inData({inData[107], inData[075], inData[043], inData[011]}), .outData({outData[107], outData[075], outData[043], outData[011]}));
NoekeonGammaSbox sbox12(.inData({inData[108], inData[076], inData[044], inData[012]}), .outData({outData[108], outData[076], outData[044], outData[012]}));
NoekeonGammaSbox sbox13(.inData({inData[109], inData[077], inData[045], inData[013]}), .outData({outData[109], outData[077], outData[045], outData[013]}));
NoekeonGammaSbox sbox14(.inData({inData[110], inData[078], inData[046], inData[014]}), .outData({outData[110], outData[078], outData[046], outData[014]}));
NoekeonGammaSbox sbox15(.inData({inData[111], inData[079], inData[047], inData[015]}), .outData({outData[111], outData[079], outData[047], outData[015]}));
NoekeonGammaSbox sbox16(.inData({inData[112], inData[080], inData[048], inData[016]}), .outData({outData[112], outData[080], outData[048], outData[016]}));
NoekeonGammaSbox sbox17(.inData({inData[113], inData[081], inData[049], inData[017]}), .outData({outData[113], outData[081], outData[049], outData[017]}));
NoekeonGammaSbox sbox18(.inData({inData[114], inData[082], inData[050], inData[018]}), .outData({outData[114], outData[082], outData[050], outData[018]}));
NoekeonGammaSbox sbox19(.inData({inData[115], inData[083], inData[051], inData[019]}), .outData({outData[115], outData[083], outData[051], outData[019]}));
NoekeonGammaSbox sbox20(.inData({inData[116], inData[084], inData[052], inData[020]}), .outData({outData[116], outData[084], outData[052], outData[020]}));
NoekeonGammaSbox sbox21(.inData({inData[117], inData[085], inData[053], inData[021]}), .outData({outData[117], outData[085], outData[053], outData[021]}));
NoekeonGammaSbox sbox22(.inData({inData[118], inData[086], inData[054], inData[022]}), .outData({outData[118], outData[086], outData[054], outData[022]}));
NoekeonGammaSbox sbox23(.inData({inData[119], inData[087], inData[055], inData[023]}), .outData({outData[119], outData[087], outData[055], outData[023]}));
NoekeonGammaSbox sbox24(.inData({inData[120], inData[088], inData[056], inData[024]}), .outData({outData[120], outData[088], outData[056], outData[024]}));
NoekeonGammaSbox sbox25(.inData({inData[121], inData[089], inData[057], inData[025]}), .outData({outData[121], outData[089], outData[057], outData[025]}));
NoekeonGammaSbox sbox26(.inData({inData[122], inData[090], inData[058], inData[026]}), .outData({outData[122], outData[090], outData[058], outData[026]}));
NoekeonGammaSbox sbox27(.inData({inData[123], inData[091], inData[059], inData[027]}), .outData({outData[123], outData[091], outData[059], outData[027]}));
NoekeonGammaSbox sbox28(.inData({inData[124], inData[092], inData[060], inData[028]}), .outData({outData[124], outData[092], outData[060], outData[028]}));
NoekeonGammaSbox sbox29(.inData({inData[125], inData[093], inData[061], inData[029]}), .outData({outData[125], outData[093], outData[061], outData[029]}));
NoekeonGammaSbox sbox30(.inData({inData[126], inData[094], inData[062], inData[030]}), .outData({outData[126], outData[094], outData[062], outData[030]}));
NoekeonGammaSbox sbox31(.inData({inData[127], inData[095], inData[063], inData[031]}), .outData({outData[127], outData[095], outData[063], outData[031]}));

endmodule
