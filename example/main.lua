function init()
   init_renderer()
   create_window("Example Project", 16, 16)
end

x = 0
y = 8

function main()
   running = true
   while running do
      if (is_key_held("Escape") and is_key_held("Left Shift")) then
	 running = false
      end

      if is_key_held("Left") then
	 x = x - 1
      end

      if is_key_held("Right") then
	 x = x + 1
      end

      draw_pixel(x, y, 255, 255, 255)
      
      redraw_window()
   end
   destroy_window()
end
