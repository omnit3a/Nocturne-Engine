function init()
   init_renderer()
   create_window("Example Project", 256, 256)
end

function main()
   while true do
      if (is_key_held("Escape")) then
	 break
      end	 
      
      id = load_bmp("default.bmp", 1)
      draw_texture(id)
      
      redraw_window()
   end
end
