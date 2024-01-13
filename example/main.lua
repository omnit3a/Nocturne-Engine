function init()
   init_renderer()
   create_window("Game!", 256, 256)
end

function main()
   running = true
   while running do
      if (is_key_held("Escape") and is_key_held("Left Shift")) then
	 running = false
      end
      redraw_window()
   end
end
