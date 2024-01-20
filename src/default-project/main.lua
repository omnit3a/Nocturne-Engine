function init()   
   -- this code is run once, before the main loop starts   
   init_renderer()
   create_window("<Your project name here>", 640, 480)
end

function close()
   destroy_window()
   os.exit()
end

function main()
   while true do
      -- press escape key to exit the program      
      if is_key_held("Escape") then
	 close_game()
      end

      -- insert main game loop here
      
      redraw_window()
   end
end