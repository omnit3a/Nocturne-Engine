function init()
   
   -- this code is run once, before the main loop starts   
   init_renderer()
   create_window("<Your project name here>", 640, 480)
end

function main()
   while true do

      -- press escape key to exit the program      
      if is_key_held("Escape") then
	 break
      end

      -- insert main game loop here
      
      redraw_window()
   end

   -- insert any code for closing the program here,
   -- such as code for saving the game
end