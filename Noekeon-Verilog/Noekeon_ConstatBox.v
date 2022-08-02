// Moduł realizujący S-Boxa zwracający wartość stałej rundowej
// Ten moduł jest układem kombinacyjnym

module NoekeonConstatBox(
	input wire	[4:0]		inRoundNum,
	output wire	[7:0]		outRoundConst

);

assign outRoundConst =
	(inRoundNum == 5'd00) ? 8'h80:
	(inRoundNum == 5'd01) ? 8'h1B:
	(inRoundNum == 5'd02) ? 8'h36:
	(inRoundNum == 5'd03) ? 8'h6C:
	(inRoundNum == 5'd04) ? 8'hD8:
	(inRoundNum == 5'd05) ? 8'hAB:
	(inRoundNum == 5'd06) ? 8'h4D:
	(inRoundNum == 5'd07) ? 8'h9A:
	(inRoundNum == 5'd08) ? 8'h2F:
	(inRoundNum == 5'd09) ? 8'h5E:
	(inRoundNum == 5'd10) ? 8'hBC:
	(inRoundNum == 5'd11) ? 8'h63:
	(inRoundNum == 5'd12) ? 8'hC6:
	(inRoundNum == 5'd13) ? 8'h97:
	(inRoundNum == 5'd14) ? 8'h35:
	(inRoundNum == 5'd15) ? 8'h6A:
	8'hD4;

endmodule
