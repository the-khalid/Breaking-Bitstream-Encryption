
module blinker (
    input wire clk,       // 100 MHz clock
    output reg led        // Output to LED
);

    reg [25:0] counter = 0;

    always @(posedge clk) begin
        counter <= counter + 1;
        if (counter == 26_000_000) begin
            counter <= 0;
            led <= ~led;
        end
    end

endmodule
