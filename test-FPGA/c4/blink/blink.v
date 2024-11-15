module blink(clk, led0);
input wire clk;
output wire led0;

reg led;
initial led <= 1'b0;


reg [24:0] counter;
initial counter <= 25'd0;


always @(posedge clk) begin
	if(counter==25'd2500000 /*25000000*/) begin 
		counter <= 25'd0;
		led <= ~led;
	end else begin
		counter <= counter + 1'b1;
	end
end



assign led0 = led;


endmodule
